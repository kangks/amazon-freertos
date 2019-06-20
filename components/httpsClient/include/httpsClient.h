#ifndef _HTTPS_CLIENT_H_
#define _HTTPS_CLIENT_H_

// #if defined (__cplusplus)
// extern "C" {
// #endif

#include "mbedtls/net_sockets.h"
#include "mbedtls/debug.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/error.h"
#include "mbedtls/certs.h"
#include "mbedtls/platform.h"

int testSSL( void );

// #if defined (__cplusplus)
// }
// #endif

#endif
