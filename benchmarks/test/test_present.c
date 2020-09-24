
#include <stdio.h>

#include "present.h"

void puthex64(uint64_t in) {
    for(int i = 0; i < 16; i += 1) {
        unsigned char x = (in >> (60-4*i)) & 0xF;
        printf("%x", x);
    }
}

uint64_t test_vectors[1][4] = {
// Plaintext         , Key0               , Key1               , Ciphertext
{0x0000000000000000UL,0x0000000000000000UL,0x0000000000000000UL,0x5579c1387b228445UL}
};

int main (int argc, char ** argv) {

    for(int i = 0; i < 1; i ++) {

        uint64_t pt = test_vectors[i][0];
        uint64_t k0 = test_vectors[i][1];
        uint64_t k1 = test_vectors[i][2];
        uint64_t ct = test_vectors[i][3];

        uint64_t rk[32];
        present80_keyschedule(rk, k1, k0);

        for(int i = 0; i < 32; i ++) {
        }

        uint64_t ct_out;
        present_enc_ecb(&ct_out, &pt, rk);

        puthex64(pt     ); printf(", ");
        puthex64(ct     ); printf(", ");
        puthex64(ct_out ); printf("\n");

        if(ct_out != ct) {
            printf("FAIL\n");
            return 1;
        }

    }

    return 0;

}
