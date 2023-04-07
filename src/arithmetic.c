#include <gmp.h>
#include "point.h"
#include "curves.h"
#include "arithmetic.h"

#define INFTY NULL

void weierstrass_slope(mpz_t rop, point_t P, point_t Q, mpz_t order) {
	mpz_t slope, y_final, x_final;
	mpz_inits(slope, y_final, x_final, NULL);

	mpz_sub(y_final, P.y, Q.y);
	mpz_sub(x_final, P.x, Q.x);

	mpz_invert(slope, y_final, x_final); // Fix this
	mpz_mod(rop, slope, order);

	mpz_clears(slope, y_final, x_final, NULL);
}

point_t weierstrass_addition(curve_t curve, point_t P, point_t Q) {
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
	
	mpz_clears(slope, delta_x, R_x, R_y);
	return R;
}

point_t weierstrass_doubling(curve_t curve, point_t P) {
	// assert P = Q
	// lambda = (3x_p^2 + a) / 2y_p
	// x_r = lambda^2 - 2x_p
	// y_r = lambda(delta_x) - y_p
	
	mpz_t lambda, delta, x_r, y_r, buf, scnd_buf;
	mpz_inits(lambda, delta, x_r, y_r, buf, scnd_buf, NULL);
	
	//lambda
	mpz_pow_ui(buf, P.x, 2);
	mpz_mul_ui(buf, buf, 3);
	mpz_add(buf, buf, curve.a);

	   // Calculate xgcd(buf, 2y)
	mpz_mul_ui(scnd_buf, P.y, 2);
	mpz_invert(scnd_buf, scnd_buf, curve.p);
	mpz_mul(lambda, buf, scnd_buf);
	mpz_mod(lambda, lambda, curve.p);

	// x_r
	mpz_exp_ui(buf, lambda, 2);
	mpz_mul_ui(scnd_buf, P.x, 2);
	mpz_sub(x_r, buf, scnd_buf);
	mpz_mod(x_r, x_r, curve.p);

	// y_r
	mpz_sub(delta, P.x, x_r);
	mpz_mul(buf, lambda, delta);
	mpz_sub(buf, buf, P.y);
	mpz_mod(y_r, buf, curve.p);

	mpz_clears(lambda, delta, buf, scnd_buf);
	point_t doubled_point;
	mpz_set(doubled_point.x, x_r);
	mpz_set(doubled_point.y, y_r);

	return doubled_point;
}
