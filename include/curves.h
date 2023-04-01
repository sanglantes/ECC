#ifndef CURVES_H
#define CURVES_H

typedef enum {
	SWEIER = 0,
	MNTGOM = 1,
	EDWARD = 2
} form_t;

typedef struct Point {
	mpz_t x;
	mpz_t y;
} point_t;

typedef struct Curve {
	mpz_t   p;
	mpz_t   a;
	mpz_t   b;
	point_t generator;
	form_t  form;
} curve_t;

point_t set_point(char* x_char, char* y_char);

curve_t curve25519();

#endif
