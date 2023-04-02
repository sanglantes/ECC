#include <gmp.h>
#include <sys/random.h>
#include <stdint.h>

uint64_t seed() {
	uint64_t rand_seed;
	getrandom(&rand_seed, 8, 0);

	return rand_seed;
}

void large_random(mpz_t rop, mp_bitcnt_t range) {
	gmp_randstate_t state;
	gmp_randinit_default(state);

	gmp_randseed_ui(state, seed());

	mpz_urandomb(rop, state, range);
}
