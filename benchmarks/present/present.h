
#include <stdint.h>

#ifndef __PRESENT_H__
#define __PRESENT_H__

/*
@brief Encrypt a single 64-bit block pt, under key k, to give ciphertext ct.
*/
void present_enc_ecb (
    uint64_t  * ct, //!< Ciphertext
    uint64_t  * pt, //!< Plaintext
    uint64_t  * rk  //!< Round keys
);

void present80_keyschedule (
    uint64_t   rk[32]   ,
    uint16_t   k1       , // key bits 79..64
    uint64_t   k0         // key bits 63..0
);

#endif

