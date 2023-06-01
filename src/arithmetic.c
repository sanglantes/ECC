#include <gmp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "point.h"
#include "curves.h"
#include "arithmetic.h"
#include <stdint.h>

#define INFTY 0

uint32_t ts_alg(mpz_t rop, mpz_t r, mpz_t n, mpz_t p) { // Tonelli-Shanks algorithm for solving modular square roots.
	// Find Q and S such that p - 1 = Q * 2^S
	mpz_mod_ui(rop, p, 4);
	if (mpz_legendre(n, p) == -1) {
		return -1;	
	}
	mpz_t Q, buf;
	mpz_init(Q);
	mpz_sub_ui(Q, p, 1);
	uint64_t S = 0;

	while (mpz_even_p(Q)) {
		mpz_cdiv_q_ui(Q, Q, 2);
		S++;
	}

	// Find a quadratic non-residue z.
	mpz_t z;
	mpz_init(z);
	mpz_set_ui(z, 2);

	while (mpz_jacobi(z, p) != -1) {
		mpz_add_ui(z, z, 1);
	}
	gmp_printf("z: %Zd, Q: %Zd, S: ", z, Q);

	// M <- S
	mpz_t M;
	mpz_init(M);
	mpz_set_ui(M, S);

	// c <- z^Q
	mpz_t c;
	mpz_init(c);
	mpz_powm(c, z, Q, p);
	
	// t <- n^Q
	mpz_t t;
	mpz_init(t);
	mpz_powm(t, n, Q, p);

	// R <- n^(Q + 1 / 2)
	mpz_t R, q_exp;
	mpz_inits(R, q_exp, NULL);

	mpz_add_ui(q_exp, Q, 1);
	mpz_cdiv_q_ui(q_exp, q_exp, 2);
	mpz_powm(R, n, q_exp, p);

	//gmp_printf("M: %Zd\nc: %Zd\nt: %Zd\nR: %Zd\n", M, c, t, R);
	
	// Loop
	mpz_t b, temp_b_exp, temp_t, i, two, c_exp;
	mpz_inits(b, temp_b_exp, temp_t, i, two, c_exp, NULL);
	mpz_set_ui(two, 2);
	mpz_set_ui(i, 1);

	uint32_t counter = 0;

	while (1) {
		if (mpz_cmp_d(t, 0) == 0) {
			mpz_set_ui(rop, 0);
			return 0;
		}
		else if (mpz_cmp_ui(t, 1) == 0) {
			mpz_set(rop, R);
			return 0;
		} 

		// Find the least i < i < M => t^2^i = 1

		mpz_powm(temp_t, two, i, p);

		while (mpz_cmp_ui(temp_t, 1 != 0)) {
			mpz_add_ui(i, i, 1);	
			mpz_powm(temp_t, two, i, p);
		}
		//DEBUG: Find i: clear.
		//Set b
		mpz_sub(temp_b_exp, M, i);
		mpz_sub_ui(temp_b_exp, temp_b_exp, 1);
		mpz_powm(temp_b_exp, two, temp_b_exp, p);
		mpz_powm(b, c, temp_b_exp, p);
		gmp_printf("%Zd\n", b);
		
		// M <- i
		mpz_set(M, i);

		// c <- b2
		mpz_powm_ui(c, b, 2, p);

		// t <- tb^2
		mpz_mul(t, t, c);

		// R <- Rb
		mpz_mul(R, R, b);

		mpz_add_ui(i, i, 1);
	}

	return 1;
}

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

	// R_x
	weierstrass_slope(slope, P, Q, curve.p); // s_i
	mpz_pow_ui(slope, slope, 2);
	mpz_sub(slope, slope, P.x);	      // P_x - Q_x
	mpz_sub(R_x, slope, Q.x);	      // s_i1 - P_x - Q_x
	mpz_mod(R_x, R_x, curve.p);	      // s_i2 mod p

	// R_y
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

point_t weierstrass_double(curve_t curve, point_t P) {
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
	mpz_pow_ui(buf, lambda, 2);
	mpz_mul_ui(scnd_buf, P.x, 2);
	mpz_sub(x_r, buf, scnd_buf);
	mpz_mod(x_r, x_r, curve.p);

	// y_r
	mpz_sub(delta, P.x, x_r);
	mpz_mul(buf, lambda, delta);
	mpz_sub(buf, buf, P.y);
	mpz_mod(y_r, buf, curve.p);

	mpz_clears(lambda, delta, buf, scnd_buf, NULL);
	point_t doubled_point;
	point_init(doubled_point);
	mpz_set(doubled_point.x, x_r);
	mpz_set(doubled_point.y, y_r);

	return doubled_point;
}

point_t double_and_add(curve_t curve, point_t P, mpz_t scalar) {
	point_t buffer, temp;
	point_init(buffer);
	point_init(temp);
	temp = P;
	size_t bit_length = mpz_sizeinbase(scalar, 2);

	for (size_t i = 1; i <= bit_length; i++) {
		if (mpz_tstbit(scalar, bit_length - i) == 1) {
			buffer = weierstrass_addition(curve, P, buffer);
		}
		temp = weierstrass_double(curve, temp);
	}

	return buffer;
}

int main() {

	mpz_t rop, re, ne, pe; 
	mpz_inits(rop, re, ne, pe, NULL);
	mpz_set_ui(ne, 558);
	mpz_set_ui(pe, 3257);

	ts_alg(rop, re, ne, pe);

	gmp_printf("Received output: %Zd\n", rop);

	return 0;
}
