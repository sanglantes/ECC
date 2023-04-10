#include <gmp.h>
#include "point.h"

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
