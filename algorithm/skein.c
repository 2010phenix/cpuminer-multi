#include "cpuminer-config.h"
#include "miner.h"

#include <string.h>
#include <stdint.h>

#include <openssl/sha.h>

#include "sha3/sph_skein.h"

/* Move init out of loop, so init once externally, and then use one single memcpy with that bigger memory block */
typedef struct {
	sph_skein512_context	skein;
} skeinhash_context_holder;

/* no need to copy, because close reinit the context */
static THREADLOCAL skeinhash_context_holder ctx;

void init_skein_contexts(void *dummy)
{
	sph_skein512_init(&ctx.skein);
}

void skeinhash(void *output, const void *input)
{
	uint32_t mask = 8;
	uint32_t zero = 0;

	//these uint512 in the c++ source of the client are backed by an array of uint32
	uint32_t hash[16];

	memset(hash, 0, 16 * sizeof(uint32_t));

	sph_skein512(&ctx.skein, input, 80);
	sph_skein512_close(&ctx.skein, hash);

	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, hash, 64);
	SHA256_Final((unsigned char*)hash, &sha256);

	memcpy(output, hash, 32);
}

int scanhash_skein(int thr_id, uint32_t *pdata, const uint32_t *ptarget,
	uint32_t max_nonce, uint64_t *hashes_done)
{
	uint32_t n = pdata[19] - 1;
	const uint32_t first_nonce = pdata[19];
	const uint32_t Htarg = ptarget[7];

	uint32_t hash64[8] __attribute__((aligned(32)));
	uint32_t endiandata[32];

	uint64_t htmax[] = {
		0,
		0xF,
		0xFF,
		0xFFF,
		0xFFFF,
		0x10000000
	};
	uint32_t masks[] = {
		0xFFFFFFFF,
		0xFFFFFFF0,
		0xFFFFFF00,
		0xFFFFF000,
		0xFFFF0000,
		0
	};

	// we need bigendian data...
	for (int kk=0; kk < 32; kk++) {
		be32enc(&endiandata[kk], ((uint32_t*)pdata)[kk]);
	};
#ifdef DEBUG_ALGO
	printf("[%d] Htarg=%X\n", thr_id, Htarg);
#endif
	for (int m=0; m < sizeof(masks); m++) {
		if (Htarg <= htmax[m]) {
			uint32_t mask = masks[m];
			do {
				pdata[19] = ++n;
				be32enc(&endiandata[19], n);
				skeinhash(hash64, &endiandata);
#ifndef DEBUG_ALGO
				if ((!(hash64[7] & mask)) && fulltest(hash64, ptarget)) {
					*hashes_done = n - first_nonce + 1;
					return true;
				}
#else
				if (!(n % 0x1000) && !thr_id) printf(".");
				if (!(hash64[7] & mask)) {
					printf("[%d]",thr_id);
					if (fulltest(hash64, ptarget)) {
						*hashes_done = n - first_nonce + 1;
						return true;
					}
				}
#endif
			} while (n < max_nonce && !work_restart[thr_id].restart);
			// see blake.c if else to understand the loop on htmax => mask
			break;
		}
	}

	*hashes_done = n - first_nonce + 1;
	pdata[19] = n;
	return 0;
}
