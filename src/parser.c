#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <gmp.h>
#include "status.h"

int main(int argc, char* argv[]) {

	int preset_flag;
	int form_flag;
	static struct option longopts[] = {
		{ NULL, 	required_argument, 	NULL, 		'a' },
		{ NULL, 	required_argument, 	NULL, 		'b' },
		{ "size", 	required_argument, 	NULL, 		's' },
		{ "preset", 	required_argument, 	&preset_flag, 	'p' },
		{ "form", 	required_argument, 	&form_flag, 	'f' },
		{ "graph", 	no_argument, 		&graph_flag, 	'g' },
		{ "help", 	no_argument, 		NULL, 		'h' }

	}
	int c;
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
"  Generates elliptic curves for educational and cryptographical purposes. Performs elliptic curve arithemtic.\n"
"\n"
"  options:\n"
"   -a			select the 'a' constant in an EC curve.\n"
"   -b			select the 'b' constant in an EC curve.\n"
"   -s, --size		bit size for the key (recommended: 256)\n"
"   -p, --preset=PRESET choose a preconfigured curve\n"
"			   (options: \"brainpool256\", \"curve25519\", \"nist256\", \"secp256k1\")\n"
"   -f, --form=FORM	specify a different equation form (default: shortw)\n"
"			   (options: \"shortw\", \"longw\", \"edward\", \"montgomery\", \"hessian\")\n"
"   -g, --graph		graph a plot of the curve\n"
"   -h, --help		display this message\n"

		);
	}

	gmp_printf("%Zd\n%Zd\n", argument.a, argument.b);
	printf("%d\n%d\n", argument.s, argument.r);
	return 0;
}
