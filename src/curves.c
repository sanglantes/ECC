#include <stdio.h>
#include <gmp.h>
#include "curves.h"
// ************************************************************************
// *									  *
// *                            NOTES ON curves.c                         *
// *									  *
// * This module contains the blueprint for a variety of elliptic curves. *
// * As of now, no binary curves exist. 				  *
// * All integer values are represented in base 16. 			  *
// * 									  *
// ************************************************************************

// TODO: set_point() is better suited in arithmetic section.

point_t set_point(char* x_char, char* y_char) {
	
	point_t rop = {
		.x = {},
		.y = {},
	};

	mpz_t x, y;
	mpz_inits(x, y, NULL);

	mpz_set_str(x, x_char, 16);
	mpz_set_str(y, y_char, 16);

	mpz_set(rop.x, x);
	mpz_set(rop.y, y);

	return rop;
}

// *********************************************************************************************
// *											       *
// * Name:   Curve25519									       *
// * Author: Daniel Bernstein								       *
// * Form:   Montgomery									       *
// * Parameters: 									       *
// *	p = 2^255 - 19									       *
// *	A = 0x76d06									       *
// *	B = 0x1										       *
// *	Base point = (0x9, 0x20ae19a1b8a086b4e01edd2c7748d14c923d4d7e6d7c61b229e9c5a27eced3d9) *
// *											       *
// *********************************************************************************************

curve_t create_curve25519() {

	curve_t curve25519 = {
	    .p = {},
	    .a = {},
	    .b = {},
	    .generator = {},
	    .form = MNTGOM,
	};

    	mpz_set_str(curve25519.p, "7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffed", 16);
    	mpz_set_ui(curve25519.a, 0x76d06);
    	mpz_set_ui(curve25519.b, 0x1);

	curve25519.generator = set_point("9", "20ae19a1b8a086b4e01edd2c7748d14c923d4d7e6d7c61b229e9c5a27eced3d9");

	return curve25519;
}

void debug_curve(curve_t curve) {

	gmp_printf("p: %Zd\na: %Zd\nb: %Zd\ngenerator: (%Zd, %Zd)\n", curve.p, curve.a, curve.b, curve.generator.x, curve.generator.y);
}

int main() {
    curve_t curve25519 = create_curve25519();
    debug_curve(curve25519);

    mpz_clears(curve25519.p, curve25519.a, curve25519.b, curve25519.generator, NULL);
    return 0;
}
