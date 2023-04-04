#include <gmp.h>
#include "point.h"
#include "curves.h"
#include "arithmetic.h"

#define INFTY NULL


// The original code implemented seemingly easy arithmetic for Weierstrass curves, but seeing as Montgomery
// and Edward curves have the upper advantage in both speed and side-channel security, I've decided to
// rework this section a tad bit. I'll let the previous algorithms stay for a while until I'm done with
// the math's stuff.
// --------------------------------------------------------------------------------------------------

//void discrete_slope(mpz_t rop, point_t P, point_t Q, mpz_t order) {
//	mpz_t slope, y_final, x_final;
//	mpz_inits(slope, y_final, x_final, NULL);
//
//	mpz_sub(y_final, P.y, Q.y);
//	mpz_sub(x_final, P.x, Q.x);
//
//	mpz_inv(slope, y_final, x_final);
//	mpz_mod(rop, slope, order);
//
//	mpz_clears(slope, y_final, x_final, NULL);
//}
//
//point_t weierstrass_addition(curve_t curve, point_t P, point_t Q) {
//	// P + Q = R
//	point_t R;	
//	mpz_t slope, delta_x, R_x, R_y;
//	
//	point_init(R);
//	mpz_inits(slope, delta_x, R_x, R_y, NULL);
//
//	// R_x = (s^2 - x_P - x_Q) mod p
//	discrete_slope(slope, P, Q, curve.p); // s_i
//	mpz_pow_ui(slope, slope, 2);	      // s_i1 ^ 2
//	mpz_sub(delta_x, P.x, Q.x);	      // P_x - Q_x
//	mpz_sub(R_x, slope, delta_x);	      // s_i1 - P_x - Q_x
//	mpz_mod(R_x, R_x, curve.n);	      // s_i2 mod p
//
//	// R_y = (P_y) + s * (P_x - Q_x) mod p
//	discrete_slope(slope, P, Q, curve.p); // s_i
//	mpz_mul(slope, slope, delta_x);       // s_i * (P_x - Q_x)
//	mpz_sub(slope, slope, P.y);	      // s_i1 - P_y
//	mpz_mod(R_y, slope, curve.p);	      // s_i2 mod p
//	
//	// R
//	mpz_set(R.x, R_x);
//	mpz_set(R.y, R_y);
//	
//	mpz_clears(slope, delta_x, R_x, R_y);
//	return R;
//}

// --------------------------------------------------------------------------------------------------

point_t montgomery_transformation(curve_t curve, point_t P, point_t Q) {
	// Instead of writing every possible arithmetic algorithm for a variety of curves,
	// one should transform them to Montgomery form; a more memory efficient and secure algorithm
	// for point multiplication.
	// 
	// https://eprint.iacr.org/2017/212.pdf
	// ------------------------------------
	// Transforming from and to a Weierstrass model:
	// (x, y) |-> (u, v) = (B(x + A/3), B^2 * y)
	// (u, v) |-> (x, y) = (u/B - A/3, v/B^2)
	// E : v^2 = u^3 + (B^2(1 - A^2/3))u + B^3 * A/3(2A^2/9 - 1)
	// Note that not all Weierstrass curves are capable of isomorphic birational mappings 
	// onto a Montgomery curve. To validate the transformation, it is possible to ensure that
	// the discriminant: 4A^3 + 27B^2 doesn't divide with the field order p.
	//
	// Birational mapping is not necessary for twisted Edward curves since their
	// arithmetic isn't inconveniently slow.
	
}
