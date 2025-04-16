#ifndef SHA256_H
#define SHA256_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void sha256(const void *data, size_t len, uint8_t *hash);

#ifdef __cplusplus
}
#endif

#endif  // SHA256_H
