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

void point_init(point_t point) {
	mpz_inits(point.x, point.y, NULL);
}

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
		.n = {},
		.form = MNTGOM,
	};

    	mpz_set_str(curve25519.p, "7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffed", 16);
    	mpz_set_ui(curve25519.a, 0x76d06);
    	mpz_set_ui(curve25519.b, 0x1);
	mpz_set_str(curve25519.n, "1000000000000000000000000000000014def9dea2f79cd65812631a5cf5d3ed", 16);

	curve25519.generator = set_point("9", "20ae19a1b8a086b4e01edd2c7748d14c923d4d7e6d7c61b229e9c5a27eced3d9");

	return curve25519;
}

// ****************************************************************************************
// *											  *
// * Name:   P-256									  *
// * Author: NIST									  *
// * Form:   Short Weierstrass								  *
// * Parameters:									  *
// *	p = 0xffffffff00000001000000000000000000000000ffffffffffffffffffffffff		  *
// *	A = 0xffffffff00000001000000000000000000000000fffffffffffffffffffffffc		  *
// * 	B = 0x5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604b		  *
// *	Base point = ("6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296", *
// *                  "4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5") *
// * Additional notes: Not safe when used with DUAL_EC_DRBG			  *
// *											  *
// ****************************************************************************************
curve_t create_p256() {
	curve_t p256 = {
			.p = {},
			.a = {},
			.b = {},
			.generator = {},
			.n = {},
			.form = SWEIER,
		};
	
	mpz_set_str(p256.p, "ffffffff00000001000000000000000000000000ffffffffffffffffffffffff", 16);
	mpz_set_str(p256.a, "ffffffff00000001000000000000000000000000fffffffffffffffffffffffc", 16);
	mpz_set_str(p256.b, "5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604b", 16);
	mpz_set_str(p256.n, "ffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551", 16);
	
	p256.generator = set_point("6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296",
				   "4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5");

	return p256;
}

void debug_curve(curve_t curve) {

	gmp_printf("p: %Zd\na: %Zd\nb: %Zd\ngenerator: (%Zd, %Zd)\n", curve.p, curve.a, curve.b, curve.generator.x, curve.generator.y);
}

int main() {
    curve_t curve25519 = create_p256();
    debug_curve(curve25519);

    mpz_clears(curve25519.p, curve25519.a, curve25519.b, curve25519.generator, NULL);
    return 0;
}
