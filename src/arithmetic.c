#include <gmp.h>
#include "point.h"
#include "curves.h"
#include "arithmetic.h"

#define INFTY NULL

void discrete_slope(mpz_t rop, point_t P, point_t Q, mpz_t order) {
	mpz_t slope, y_final, x_final;
	mpz_inits(slope, y_final, x_final, NULL);

	mpz_sub(y_final, P.y, Q.y);
	mpz_sub(x_final, P.x, Q.x);

	mpz_cdiv_q(slope, y_final, x_final);
	mpz_mod(rop, slope, order);

	mpz_clears(slope, y_final, x_final, NULL);
}

point_t point_addition(curve_t curve, point_t P, point_t Q) {
	// P + Q = R
	point_t R;	
	mpz_t slope, delta_x, R_x, R_y;
	
	point_init(R);
	mpz_inits(slope, delta_x, R_x, R_y, NULL);

	// R_x = (s^2 - x_P - x_Q) mod p
	discrete_slope(slope, P, Q, curve.p); // s_i
	mpz_pow_ui(slope, slope, 2);	      // s_i1 ^ 2
	mpz_sub(delta_x, P.x, Q.x);	      // P_x - Q_x
	mpz_sub(R_x, slope, delta_x);	      // s_i1 - P_x - Q_x
	mpz_mod(R_x, R_x, curve.n);	      // s_i2 mod p

	// R_y = (P_y) + s * (P_x - Q_x) mod p
	discrete_slope(slope, P, Q, curve.p); // s_i
	mpz_mul(slope, slope, delta_x);       // s_i * (P_x - Q_x)
	mpz_sub(slope, slope, P.y);	      // s_i1 - P_y
	mpz_mod(R_y, slope, curve.p);	      // s_i2 mod p
	
	// R
	mpz_set(R.x, R_x);
	mpz_set(R.y, R_y);

	return R;
}
