#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <gmp.h>
#include "status.h"
#include "parser.h"

void print_usage(FILE* stream) { 
	fprintf(stream,
"usage: ./ecc [-ghr] [-s key_size] [-p presets] [-i file]\n"
"\n"
"  Generates elliptic curves for educational and cryptographical purposes. Performs elliptic curve arithemtic.\n"
"\n"
"  options:\n"
"   -s, --size		bit size for the key (min: 16, max: 512)\n"
"   -p, --preset choose a preconfigured curve\n"
"			   (options: \"brainpool256\", \"curve25519\", \"nist256\", \"secp256k1\")\n"
"   -i, --input		reads curve configurations from a specified file\n"
"   -g, --graph		graph a plot of the curve\n"
"   -h, --help		display this message\n"
"\n"
"examples:\n"
"   ./ecc -i mycurve.txt -g\n"
"   ./ecc -p curve25519\n"

		);
	}
int main(int argc, char* argv[]) {

	enum FLAG_VAL
	{
		UNSET    = 0,
		POSITIVE = 1
	};
	int input_flag  = UNSET;
	int preset_flag = UNSET;
	int graph_flag  = UNSET;

	static struct option longopts[] = {
		{ "input",	required_argument,	0,	'i' },
		{ "size", 	required_argument, 	0, 	's' },
		{ "preset", 	required_argument, 	0, 	'p' },
		{ "random",	no_argument,		0,	'r'
		{ "graph", 	no_argument, 		0, 	'g' },
		{ "help", 	no_argument, 		0, 	'h' },
		{ NULL,         0,       		NULL,  	 0  }
	};
		
	if (argc == 1) {
		print_usage(stderr);
		exit(EXIT_FAILURE);
	}
	int c;
	while ((c = getopt_long(argc, argv, "hgi:s:p:", longopts, NULL)) != -1) {
		switch(c) {
			case 'h':
				print_usage(stdout);
				printf("%d\n", input_flag);
				return -1;
			case 'i':
				input_flag = POSITIVE;
				break;
			case 's':
				if (input_flag) { printf("input mode set\tskipping..."); }
				break;
			default:
				print_usage(stderr);
				return -1;
		}
	}
	return 0;
}
