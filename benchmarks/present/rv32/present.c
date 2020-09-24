
#include "riscvcrypto/present/rvintrin.h"
#include "riscvcrypto/present/present.h"

#define SBOX_4BIT(IN, SBHI, SBLO) (                 \
    _rv32_xperm_n(SBLO, IN             )   |        \
    _rv32_xperm_n(SBHI, IN ^ 0x88888888)   )

//! Forward Present SBox layer
static inline uint64_t present_sbox_fwd(uint64_t in) {
    
    uint32_t sb_hi  = 0x21748FE3;
    uint32_t sb_lo  = 0xDA09B65C;
    
    uint32_t in_lo  = (uint32_t)(in    );
    uint32_t in_hi  = (uint32_t)(in>>32);

    uint32_t out_lo = SBOX_4BIT(in_lo, sb_hi, sb_lo);
    uint32_t out_hi = SBOX_4BIT(in_hi, sb_hi, sb_lo);

    return (((uint64_t)out_hi) << 32) | out_lo;

}

#define RV32_PLAYER_STEP(IN,OUT) {                      \
    uint32_t vl = IN        ;                           \
	uint32_t vh = IN >> 32  ;                           \
	uint32_t zl = _rv32_zip(vl);                        \
	uint32_t zh = _rv32_zip(vh);                        \
	uint32_t rl = _rv32_zip2(_rv32_pack (zl, zh));      \
	uint32_t rh = _rv32_zip2(_rv32_packu(zl, zh));      \
	OUT = ((uint64_t)(rh) << 32) | rl;                  \
}

//! Present Permutation layer
static inline uint64_t present_player(uint64_t in) {
    // Code coppied from Claire's example: 
    //  http://svn.clairexen.net/handicraft/2020/presentperm/presentperm.cc

    RV32_PLAYER_STEP(in,in) // +6 instructions
    RV32_PLAYER_STEP(in,in) // +6 instructions
    return in;

}

#define GET_RK(K1, K0) (((uint64_t)k1 << 48) | (k0 >> 16))

void present80_keyschedule (
    uint64_t   rk[32]   ,
    uint16_t   k1       , // key bits 79..64
    uint64_t   k0         // key bits 63..0
) {

    uint64_t r0;
    uint64_t r1;
    uint64_t r2;
    uint64_t r3;

    rk[0] = GET_RK(k1, k0);

    for(int i = 1; i < 32; i ++) {

        // Rotate 80-bit key left by 61 bits == right by 19 bits.
        r0 = k0 >> 19; // new low bits of k0.
        r1 = k0 >>  3; // new k1
        r2 = k0 << 61; // new top bits of k0.
        r3 = ((uint64_t)k1) << 45 ; // new mid bits of k0.

        k1 = r1 ;
        k0 = r0 | r2 | r3;

        // Apply sbox to top 4 bits of key. i.e. bits 15..12 of k1.
        r0 = present_sbox_fwd(k1);
        k1 = (k1 & 0x0FFF) | (r0 & 0xF000);

        // Xor round number.
        k0 = k0 ^ (i << 15);

        rk[i] = GET_RK(k1, k0);
    }

}


void present_enc_ecb (
    uint64_t *  ct,
    uint64_t *  pt,
    uint64_t *  rk
){

    uint64_t state  = pt[0];
    int      round  = 0    ;

    while(round < 31) {
                                            // RV64 | RV32 |
        state   ^= rk[round];               // +2   | +2   | instructions
        state    = present_sbox_fwd(state); // +4   | +4   | instruction
        state    = present_player  (state); // +2   | +12  | instructions
                                            //  8   |  18  | Total
        round   += 1;
    }

    state  ^= rk[31];

    *ct     = state;

}

#undef SBOX_4BIT
#undef GET_RK


