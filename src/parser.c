#include <stdio.h>
#include <argp.h>
#include <gmp.h>
#include "status.h"

struct Arguments {
	mpz_t			a;
	mpz_t			b;
	unsigned int	f;
	unsigned int	s;
	unsigned int	r;
};

int main(int argc, char* argv[]) {
	struct Arguments argument;
	int c;
	// a	CONSTANT A
	// b	CONSTANT B
	// f	FORM
	// s	KEY SIZE
	//
	// r	RANDOM CONSTANT VALUES
	while((c = getopt(argc, argv, "-a:-b:-f:-s:r::")) != -1) {
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
			case 'f':
					if (optarg != NULL) {
								
					}
			case 'r':
					if (optarg != NULL) {
							argument.r = 1;
					}
					else {
							argument.r = 0;
					}
					break;
		}
	}

	gmp_printf("%Zd\n%Zd\n", argument.a, argument.b);
	printf("%d\n%d\n%d\n", argument.f, argument.s, argument.r);
	return 0;
}
