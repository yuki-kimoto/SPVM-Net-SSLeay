// Copyright (c) 2024 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include <openssl/ssl.h>
#include <openssl/err.h>

static const char* FILE_NAME = "Net/SSLeay/SSL_SESSION.c";

// Instance Methods
int32_t SPVM__Net__SSLeay__SSL_SESSION__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  SSL_SESSION* ssl_session = env->get_pointer(env, stack, obj_self);
  
  if (!env->no_free(env, stack, obj_self)) {
    SSL_SESSION_free(ssl_session);
  }
  
  return 0;
}
int32_t SPVM__Net__SSLeay__SSL_SESSION__up_ref(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  SSL_SESSION* ssl_session = env->get_pointer(env, stack, obj_self);
  
  int32_t status = SSL_SESSION_up_ref(ssl_session);
  
  if (!(status == 1)) {
    int64_t ssl_error = ERR_peek_last_error();
    
    char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
    ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
    
    env->die(env, stack, "[OpenSSL Error]SSL_SESSION_up_ref failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
    
    int32_t error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
    
    return error_id;
  }
  
  return 0;
}
