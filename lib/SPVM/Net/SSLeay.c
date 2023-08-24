// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include <openssl/ssl.h>


static const char* FILE_NAME = "Net/SSLeay.c";

int32_t SPVM__Net__SSLeay__foo(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  char *version = OPENSSL_VERSION_TEXT;
  fprintf(stderr, "OpenSSL version: %s\n", version);
    
  return 0;
}

int32_t SPVM__Net__SSLeay__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_ssl_ctx = stack[0].oval;
  
  SSL_CTX* ssl_ctx = env->get_pointer(env, stack, obj_ssl_ctx);
  
  SSL* ssl = SSL_new(ssl_ctx);
  
  void* obj_ssl = env->new_pointer_object_by_name(env, stack, "Net::SSLeay", ssl, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_ssl, "ssl_ctx", obj_ssl_ctx, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_ssl;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  SSL* ssl = env->get_pointer(env, stack, obj_self);
  
  SSL_free(ssl);
  
  return 0;
}

int32_t SPVM__Net__SSLeay__connect(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  SSL* ssl = env->get_pointer(env, stack, obj_self);
  
  int32_t status = SSL_connect(ssl);
  
  if (!(status == 1)) {
    env->die(env, stack, "[System Error]SSL_connect failed.", __func__, FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  return 0;
}

int32_t SPVM__Net__SSLeay__accept(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  SSL* ssl = env->get_pointer(env, stack, obj_self);
  
  int32_t status = SSL_accept(ssl);
  
  if (!(status == 1)) {
    env->die(env, stack, "[System Error]SSL_accept failed.", __func__, FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  return 0;
}

int32_t SPVM__Net__SSLeay__shutdown(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  SSL* ssl = env->get_pointer(env, stack, obj_self);
  
  int32_t status = SSL_shutdown(ssl);
  
  if (!(status == 1)) {
    env->die(env, stack, "[System Error]SSL_shutdown failed.", __func__, FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  return 0;
}

int32_t SPVM__Net__SSLeay__set_fd(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  int32_t fd = stack[1].ival;
  
  SSL* ssl = env->get_pointer(env, stack, obj_self);
  
  int32_t status = SSL_set_fd(ssl, fd);
  
  if (!(status == 1)) {
    env->die(env, stack, "[System Error]SSL_set_fd failed.", __func__, FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  return 0;
}

int32_t SPVM__Net__SSLeay__set_tlsext_host_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_name = stack[1].oval;
  
  if (!obj_name) {
    return env->die(env, stack, "The $name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* name = env->get_chars(env, stack, obj_name);
  
  SSL* ssl = env->get_pointer(env, stack, obj_self);
  
  int32_t status = SSL_set_tlsext_host_name(ssl, name);
  
  if (!(status == 1)) {
    env->die(env, stack, "[System Error]SSL_set_tlsext_host_name failed.", __func__, FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  return 0;
}

int32_t SPVM__Net__SSLeay__get_error(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  int32_t ret = stack[1].ival;
  
  SSL* ssl = env->get_pointer(env, stack, obj_self);
  
  int32_t ssl_error = SSL_get_error(ssl, ret);
  
  stack[0].ival = ssl_error;
  
  return 0;
}

