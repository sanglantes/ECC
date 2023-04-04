#ifndef CURVES_H
#define CURVES_H

typedef enum {
	SWEIER = 0,
	MNTGOM = 1,
	EDWARD = 2
} form_t;

typedef struct Curve {
	mpz_t   p;
	mpz_t   a;
	mpz_t   b;
	point_t generator;
	mpz_t	n;
	form_t  form;
} curve_t;

curve_t create_curve25519();
curve_t create_p256();

#endif
