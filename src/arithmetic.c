#include <gmp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "point.h"
#include "curves.h"
#include "arithmetic.h"

#define INFTY 0

void weierstrass_slope(mpz_t rop, point_t P, point_t Q, mpz_t order) {
	mpz_t slope, y_final, x_final;
	mpz_inits(slope, y_final, x_final, NULL);

	mpz_sub(y_final, Q.y, P.y);
	mpz_sub(x_final, Q.x, P.x);

	mpz_invert(x_final, x_final, order);
	mpz_mul(slope, y_final, x_final);
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
	weierstrass_slope(slope, P, Q, curve.p); // s_i
	mpz_pow_ui(slope, slope, 2);
	mpz_sub(slope, slope, P.x);	      // P_x - Q_x
	mpz_sub(R_x, slope, Q.x);	      // s_i1 - P_x - Q_x
	mpz_mod(R_x, R_x, curve.p);	      // s_i2 mod p

	// R_y = (P_y) + s * (P_x - Q_x) mod p
	weierstrass_slope(slope, P, Q, curve.p); // s_i
	mpz_sub(delta_x, P.x, R_x);
	mpz_mul(slope, slope, delta_x);       // s_i * (P_x - Q_x)
	mpz_sub(slope, slope, P.y);	      // s_i1 - P_y
	mpz_mod(R_y, slope, curve.p);	      // s_i2 mod p
	
	// R
	mpz_set(R.x, R_x);
	mpz_set(R.y, R_y);

	
	mpz_clears(slope, delta_x, R_x, R_y, NULL);
	return R;
}

//point_t weierstrass_double(curve_t curve, point_t P) {
//	// assert P = Q
//	// lambda = (3x_p^2 + a) / 2y_p
//	// x_r = lambda^2 - 2x_p
//	// y_r = lambda(delta_x) - y_p
//	
//	mpz_t lambda, delta, x_r, y_r, buf, scnd_buf;
//	mpz_inits(lambda, delta, x_r, y_r, buf, scnd_buf, NULL);
//	
//	//lambda
//	mpz_pow_ui(buf, P.x, 2);
//	mpz_mul_ui(buf, buf, 3);
//	mpz_add(buf, buf, curve.a);
//
//	   // Calculate xgcd(buf, 2y)
//	mpz_mul_ui(scnd_buf, P.y, 2);
//	mpz_invert(scnd_buf, scnd_buf, curve.p);
//	mpz_mul(lambda, buf, scnd_buf);
//	mpz_mod(lambda, lambda, curve.p);
//
//	// x_r
//	mpz_pow_ui(buf, lambda, 2);
//	mpz_mul_ui(scnd_buf, P.x, 2);
//	mpz_sub(x_r, buf, scnd_buf);
//	mpz_mod(x_r, x_r, curve.p);
//
//	// y_r
//	mpz_sub(delta, P.x, x_r);
//	mpz_mul(buf, lambda, delta);
//	mpz_sub(buf, buf, P.y);
//	mpz_mod(y_r, buf, curve.p);
//
//	mpz_clears(lambda, delta, buf, scnd_buf, NULL);
//	point_t doubled_point;
//	mpz_set(doubled_point.x, x_r);
//	mpz_set(doubled_point.y, y_r);
//
//	return doubled_point;
//}
//
//point_t double_and_add(curve_t curve, point_t P, mpz_t scalar) {
//	point_t buffer, temp;
//	point_init(buffer);
//	point_init(temp);
//	temp = P;
//	size_t bit_length = mpz_sizeinbase(scalar, 2);
//
//	for (size_t i = 0; i < bit_length; i++) {
//		if (mpz_tstbit(scalar, bit_length - i) == 1) {
//			buffer = weierstrass_addition(curve, P, buffer);
//		}
//		temp = weierstrass_double(curve, temp);
//	}
//
//	return buffer;
//}

int main() {
	curve_t debug_curve;
	mpz_t rop;
	mpz_inits(rop, debug_curve.p, debug_curve.a, debug_curve.b, NULL);
	point_t P, Q; point_init(P); point_init(Q);
	P = set_point("7", "6");
	Q = set_point("5", "10");
	mpz_set_ui(debug_curve.p, 17);
	mpz_set_ui(debug_curve.a, 2);
	mpz_set_ui(debug_curve.b, 2);
	
	point_t W; point_init(W);
	W = weierstrass_addition(debug_curve, P, Q);
	gmp_printf("(%Zd, %Zd)\n", W.x, W.y);

	return 0;
}
