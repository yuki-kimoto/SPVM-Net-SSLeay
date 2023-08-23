// Copyright (c) 2023 [--user-name]
// MIT License

#include "spvm_native.h"

#include <openssl/opensslv.h>

static const char* FILE_NAME = "Net/SSLeay.c";

int32_t SPVM__Net__SSLeay__foo(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  warn("AAA");
  
  char *version = OPENSSL_VERSION_TEXT;
  printf("OpenSSL version: %s\n", version);
    
  return 0;
}


