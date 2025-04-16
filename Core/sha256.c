#include "sha256.h"
#include <string.h>
#include <stdint.h>

#define ROTR(x,n) ((x >> n) | (x << (32 - n)))
#define CH(x,y,z) ((x & y) ^ (~x & z))
#define MAJ(x,y,z) ((x & y) ^ (x & z) ^ (y & z))
#define EP0(x) (ROTR(x,2) ^ ROTR(x,13) ^ ROTR(x,22))
#define EP1(x) (ROTR(x,6) ^ ROTR(x,11) ^ ROTR(x,25))
#define SIG0(x) (ROTR(x,7) ^ ROTR(x,18) ^ (x >> 3))
#define SIG1(x) (ROTR(x,17) ^ ROTR(x,19) ^ (x >> 10))

static const uint32_t k[64] = {
    0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5, 0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
    0xd807aa98,0x12835b01,0x243185be,0x550c7dc3, 0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
    0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc, 0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
    0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7, 0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
    0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13, 0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
    0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3, 0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
    0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5, 0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
    0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208, 0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

static void sha256_transform(uint32_t *h, const uint8_t *chunk) {
    uint32_t w[64];
    uint32_t a, b, c, d, e, f, g, htemp;
    int j;

    for (j = 0; j < 16; j++) {
        const size_t i = j * 4;
        w[j]  = ((uint32_t)chunk[i]     << 24);
        w[j] |= ((uint32_t)chunk[i + 1] << 16);
        w[j] |= ((uint32_t)chunk[i + 2] << 8);
        w[j] |= ((uint32_t)chunk[i + 3]);
    }
    for (j = 16; j < 64; j++) {
        w[j] = SIG1(w[j - 2]) + w[j - 7] + SIG0(w[j - 15]) + w[j - 16];
    }

    a = h[0]; b = h[1]; c = h[2]; d = h[3];
    e = h[4]; f = h[5]; g = h[6]; htemp = h[7];

    for (j = 0; j < 64; j++) {
        uint32_t t1 = htemp + EP1(e) + CH(e, f, g) + k[j] + w[j];
        uint32_t t2 = EP0(a) + MAJ(a, b, c);
        htemp = g; g = f; f = e; e = d + t1;
        d = c; c = b; b = a; a = t1 + t2;
    }

    h[0] += a; h[1] += b; h[2] += c; h[3] += d;
    h[4] += e; h[5] += f; h[6] += g; h[7] += htemp;
}

void sha256(const void *data, size_t len, uint8_t *hash) {
    uint32_t h[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    size_t i, rem;
    uint8_t block[64];
    uint64_t bitlen;

    i = 0;
    bitlen = len * 8;

    while (i + 64 <= len) {
        sha256_transform(h, (const uint8_t *)data + i);
        i += 64;
    }

    rem = len - i;
    memset(block, 0, sizeof(block));
    memcpy(block, (const uint8_t *)data + i, rem);
    block[rem++] = 0x80;

    if (rem > 56) {
        sha256_transform(h, block);
        memset(block, 0, sizeof(block));
    }

    block[56] = (uint8_t)(bitlen >> 56);
    block[57] = (uint8_t)(bitlen >> 48);
    block[58] = (uint8_t)(bitlen >> 40);
    block[59] = (uint8_t)(bitlen >> 32);
    block[60] = (uint8_t)(bitlen >> 24);
    block[61] = (uint8_t)(bitlen >> 16);
    block[62] = (uint8_t)(bitlen >> 8);
    block[63] = (uint8_t)(bitlen);

    sha256_transform(h, block);

    for (i = 0; i < 8; i++) {
        hash[i * 4 + 0] = (uint8_t)(h[i] >> 24);
        hash[i * 4 + 1] = (uint8_t)(h[i] >> 16);
        hash[i * 4 + 2] = (uint8_t)(h[i] >> 8);
        hash[i * 4 + 3] = (uint8_t)(h[i]);
    }
}
