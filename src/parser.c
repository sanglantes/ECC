#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <gmp.h>
#include "status.h"

struct Arguments {
	mpz_t			a;
	mpz_t			b;
	unsigned int	s;
	unsigned int	r;
};

int main(int argc, char* argv[]) {
	struct Arguments argument = { .r = 0 };
	int c;
	// a	CONSTANT A
	// b	CONSTANT B
	// s	KEY SIZE
	while((c = getopt(argc, argv, "a:b:s:r")) != -1) {
		switch(c)
		{
			case 'a':
					if (optarg != NULL) {
						mpz_init(argument.a);
						mpz_set_str(argument.a, optarg, 10);
					}
					else {
						fprintf(stderr, "Option '-a' requires an argument.\n");
						return FAILURE;
					}
					break;
			case 'b':
					if (optarg != NULL) {
						mpz_init(argument.b);
						mpz_set_str(argument.b, optarg, 10);
					}
					else {
						fprintf(stderr, "Option '-b' requires an argument.\n");
						return FAILURE;
					}
					break;
			case 's':
					if (optarg != NULL) {
							argument.s = strtoul(optarg, NULL, 10);
					}
					else {
							fprintf(stderr, "Option '-s' requires an argument.\n");
							return FAILURE;
					}
					break;
			case 'r':
					argument.r = 1;
					break;
		}
	}

	if(optind == 1) {
		fprintf(stderr, 
"usage: ./ecc <-a integer_constant> <-b integer_constant> <-s key_size> [-p presets] [-f file] [-g] [-h]\n"
"\n"
"		Generates elliptic curves for educational and cryptographical purposes. Performs elliptic curve arithemtic.\n"
"\n"
"		options:\n"
			"-h, --help			display this message\n"
			"-a					select the 'a' constant in an EC curve.\n"
			"-b					select the 'b' constant in an EC curve.\n"
			"-s, --size			bit size for the key (recommended: 256)\n"
			"-p, --preset=FORM	specify a different equation form (default: shortw)\n"
			"						(options: \"shortw\", \"longw\", \"edward\", \"montgomery\", \"hessian\")\n"
			"-f, --file=FILE	read configuration from a file\n"
			"-g, --graph		graph a plot of the curve\n"

		);
	}

	gmp_printf("%Zd\n%Zd\n", argument.a, argument.b);
	printf("%d\n%d\n", argument.s, argument.r);
	return 0;
}
