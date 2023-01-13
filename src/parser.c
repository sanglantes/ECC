#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <gmp.h>
#include "status.h"
#include "parser.h"

void print_usage(FILE* stream) { 
	fprintf(stream,
"usage: ./ecc [-a integer_constant] [-b integer_constant] <-s key_size> [-p presets] [-f file] [-g] [-h]\n"
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
int main(int argc, char* argv[]) {

	int preset_flag;
	int form_flag;
	int graph_flag;
	int option_index = 0;
	static struct option longopts[] = {
		{ "a", 		optional_argument, 	0, 	0	 },
		{ "b",  	optional_argument, 	0, 	0	 },
		{ "size", 	required_argument, 	0, 	0	 },
		{ "preset", 	required_argument, 	0, 	0	 },
		{ "form", 	required_argument, 	0, 	0	 },
		{ "graph", 	no_argument, 		0, 	0	 },
		{ "help", 	no_argument, 		0, 	'h'	 },
		{ NULL,         0,       		NULL,  	0 	 }
	};

	int c;
	while ((c = getopt_long(argc, argv, "h", longopts, NULL)) != -1)
		switch(c) {
			case 'h':
				print_usage(stdout);
				return -1;
				break;
			case '?':
				break;
			default:
				printf("unknown argument\n");
				print_usage(stderr);
				return -1;
		}
	return 0;
}
