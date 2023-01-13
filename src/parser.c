#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <gmp.h>
#include "status.h"

int main(int argc, char* argv[]) {

	int preset_flag;
	int form_flag;
	int graph_flag;
	static struct option longopts[] = {
		{ NULL, 	required_argument, 	NULL, 		'a' },
		{ NULL, 	required_argument, 	NULL, 		'b' },
		{ "size", 	required_argument, 	NULL, 		's' },
		{ "preset", 	required_argument, 	&preset_flag, 	'p' },
		{ "form", 	required_argument, 	&form_flag, 	'f' },
		{ "graph", 	no_argument, 		&graph_flag, 	'g' },
		{ "help", 	no_argument, 		NULL, 		'h' }

	};

	int c;
	while((c = getopt(argc, argv, "a:b:s:r", longopts, NULL)) != -1) {
		switch(c)
		{
			case 'h':
				print_usage(stdout);
				return SUCCESS;

		}
	}

void print_usage(FILE stream) { 
	fprintf(stream,
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

	return 0;
}
