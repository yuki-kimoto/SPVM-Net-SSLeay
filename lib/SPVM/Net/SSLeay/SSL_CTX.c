
// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include <assert.h>

// For set_default_verify_paths_windows method
#ifdef _WIN32

#include <windows.h>
#include <wincrypt.h>
#include <cryptuiapi.h>

#pragma comment (lib, "crypt32.lib")
#pragma comment (lib, "cryptui.lib")

#endif

#include <openssl/ssl.h>
#include <openssl/err.h>

enum {
  SPVM__Net__SSLeay__SSL_CTX__my__NATIVE_ARGS_MAX_LENGTH = 16,
};

static const char* FILE_NAME = "Net/SSLeay/SSL_CTX.c";

__thread SPVM_ENV* thread_env;

int32_t SPVM__Net__SSLeay__SSL_CTX__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_ssl_method = stack[0].oval;
  
  SSL_METHOD* ssl_method = env->get_pointer(env, stack, obj_ssl_method);
  
  SSL_CTX* self = SSL_CTX_new(ssl_method);
  
  if (!self) {
    int64_t ssl_error = ERR_peek_last_error();
    
    char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
    ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
    
    env->die(env, stack, "[OpenSSL Error]SSL_CTX_new failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
    
    int32_t tmp_error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    error_id = tmp_error_id;
    
    return error_id;
  }
  
  // OpenSSL 1.1+ default
  SSL_CTX_set_mode(self, SSL_MODE_AUTO_RETRY);
  
  void* obj_self = env->new_pointer_object_by_name(env, stack, "Net::SSLeay::SSL_CTX", self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_self;
  env->call_instance_method_by_name(env, stack, "init", 0, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  thread_env = env;
  
  stack[0].oval = obj_self;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__get_mode(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  int64_t mode = SSL_CTX_get_mode(self);
  
  stack[0].lval = mode;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__set_mode(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  int64_t mode = stack[1].lval;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  int64_t new_mode = SSL_CTX_set_mode(self, mode);
  
  stack[0].lval = new_mode;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__get0_param(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  X509_VERIFY_PARAM* x509_verify_param = SSL_CTX_get0_param(self);
  
  void* obj_address_x509_verify_param = env->new_pointer_object_by_name(env, stack, "Address", x509_verify_param, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  stack[0].oval = obj_address_x509_verify_param;
  env->call_class_method_by_name(env, stack, "Net::SSLeay::X509_VERIFY_PARAM", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  void* obj_x509_verify_param = stack[0].oval;
  
  // X509_VERIFY_PARAM_up_ref, X509_VERIFY_PARAM_dup does not exists.
  env->set_no_free(env, stack, obj_x509_verify_param, 1);
  env->set_field_object_by_name(env, stack, obj_x509_verify_param, "ref_ssl_ctx", obj_self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_x509_verify_param;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__set_default_verify_paths(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  int32_t status = SSL_CTX_set_default_verify_paths(self);
  
  if (!(status == 1)) {
    int64_t ssl_error = ERR_peek_last_error();
    
    char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
    ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
    
    env->die(env, stack, "[OpenSSL Error]SSL_CTX_set_default_verify_paths failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
    
    int32_t tmp_error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    error_id = tmp_error_id;
    
    return error_id;
  }
  
  stack[0].ival = status;
  
  return 0;
}

// Originally copied from https://stackoverflow.com/questions/9507184/can-openssl-on-windows-use-the-system-certificate-store
int32_t SPVM__Net__SSLeay__SSL_CTX__set_default_verify_paths_windows(SPVM_ENV* env, SPVM_VALUE* stack) {
#if !_WIN32
  env->die(env, stack, "Net::SSLeay::SSL_CTX#set_default_verify_paths_windows method is not supported on this system(!_WIN32)", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  X509_STORE *store = SSL_CTX_get_cert_store(self);
  
  HCERTSTORE hStore = CertOpenSystemStore(0, "ROOT");
  
  if (!hStore) {
    error_id = env->die(env, stack, "[Windows Error]CertOpenSystemStore failed.", __func__, FILE_NAME, __LINE__);
    goto END_OF_FUNC;
  }
  
  PCCERT_CONTEXT pContext = NULL;
  
  while (pContext = CertEnumCertificatesInStore(hStore, pContext)) {
    char *encoded_cert = pContext->pbCertEncoded;
    
    X509 *x509 = d2i_X509(NULL, (const unsigned char **)&encoded_cert, pContext->cbCertEncoded);
    
    if (!x509) {
      int64_t ssl_error = ERR_peek_last_error();
      
      char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
      ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
      
      env->die(env, stack, "[OpenSSL Error]d2i_X509 failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
      
      int32_t tmp_error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
      if (error_id) { return error_id; }
      error_id = tmp_error_id;
      
      goto END_OF_FUNC;
    }
    
    int32_t status = X509_STORE_add_cert(store, x509);
    
    X509_free(x509);
    
    if (!(status == 1)) {
      int64_t ssl_error = ERR_peek_last_error();
      
      char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
      ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
      
      env->die(env, stack, "[OpenSSL Error]X509_STORE_add_cert failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
      
      int32_t tmp_error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
      if (error_id) { return error_id; }
      error_id = tmp_error_id;
      
      goto END_OF_FUNC;
    }
  }
  
  END_OF_FUNC:
  
  if (hStore) {
    CertCloseStore(hStore, 0);
  }
  
  return error_id;
#endif
}

int32_t SPVM__Net__SSLeay__SSL_CTX__use_certificate_file(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_file = stack[1].oval;
  
  if (!obj_file) {
    return env->die(env, stack, "The file $file must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* file = env->get_chars(env, stack, obj_file);
  int32_t file_length = env->length(env, stack, obj_file);
  
  int32_t type = stack[2].ival;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  int32_t status = SSL_CTX_use_certificate_file(self, file, type);
  
  if (!(status == 1)) {
    int64_t ssl_error = ERR_peek_last_error();
    
    char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
    ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
    
    env->die(env, stack, "[OpenSSL Error]SSL_CTX_use_certificate_file failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
    
    int32_t tmp_error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    error_id = tmp_error_id;
    
    return error_id;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__use_certificate_chain_file(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_file = stack[1].oval;
  
  if (!obj_file) {
    return env->die(env, stack, "The file $file must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  char* file = (char*)env->get_chars(env, stack, obj_file);
  int32_t file_length = env->length(env, stack, obj_file);
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  int32_t status = SSL_CTX_use_certificate_chain_file(self, file);
  
  if (!(status == 1)) {
    int64_t ssl_error = ERR_peek_last_error();
    
    char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
    ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
    
    env->die(env, stack, "[OpenSSL Error]SSL_CTX_use_certificate_chain_file failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
    
    int32_t tmp_error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    error_id = tmp_error_id;
    
    return error_id;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__use_PrivateKey_file(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_file = stack[1].oval;
  
  if (!obj_file) {
    return env->die(env, stack, "The file $file must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  char* file = (char*)env->get_chars(env, stack, obj_file);
  int32_t file_length = env->length(env, stack, obj_file);
  
  int32_t type = stack[2].ival;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  int32_t status = SSL_CTX_use_PrivateKey_file(self, file, type);
  
  if (!(status == 1)) {
    int64_t ssl_error = ERR_peek_last_error();
    
    char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
    ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
    
    env->die(env, stack, "[OpenSSL Error]SSL_CTX_use_PrivateKey_file failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
    
    int32_t tmp_error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    error_id = tmp_error_id;
    
    return error_id;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__use_PrivateKey(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_pkey = stack[1].oval;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  if (!obj_pkey) {
    return env->die(env, stack, "The EVP_PKEY object $pkey must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  EVP_PKEY* pkey = env->get_pointer(env, stack, obj_pkey);
  
  // The reference counter of pkey is incremented on success
  int32_t status = SSL_CTX_use_PrivateKey(self, pkey);
  
  if (!(status == 1)) {
    int64_t ssl_error = ERR_peek_last_error();
    
    char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
    ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
    
    env->die(env, stack, "[OpenSSL Error]SSL_CTX_use_PrivateKey failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
    
    int32_t tmp_error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    error_id = tmp_error_id;
    
    return error_id;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__set_cipher_list(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_str = stack[1].oval;
  
  if (!obj_str) {
    return env->die(env, stack, "The cipher list $str must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  char* str = (char*)env->get_chars(env, stack, obj_str);
  int32_t str_length = env->length(env, stack, obj_str);
  
  int32_t type = stack[2].ival;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  int32_t status = SSL_CTX_set_cipher_list(self, str);
  
  if (!(status == 1)) {
    int64_t ssl_error = ERR_peek_last_error();
    
    char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
    ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
    
    env->die(env, stack, "[OpenSSL Error]SSL_CTX_set_cipher_list failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
    
    int32_t tmp_error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    error_id = tmp_error_id;
    
    return error_id;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__set_ciphersuites(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_str = stack[1].oval;
  
  if (!obj_str) {
    return env->die(env, stack, "The ciphersuites $str must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  char* str = (char*)env->get_chars(env, stack, obj_str);
  int32_t str_length = env->length(env, stack, obj_str);
  
  int32_t type = stack[2].ival;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  int32_t status = SSL_CTX_set_ciphersuites(self, str);
  
  if (!(status == 1)) {
    int64_t ssl_error = ERR_peek_last_error();
    
    char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
    ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
    
    env->die(env, stack, "[OpenSSL Error]SSL_CTX_set_ciphersuites failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
    
    int32_t tmp_error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    error_id = tmp_error_id;
    
    return error_id;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__load_verify_locations(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_file = stack[1].oval;
  
  void* obj_path = stack[2].oval;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  const char* file = NULL;
  if (obj_file) {
    file = env->get_chars(env, stack, obj_file);
  }
  
  const char* path = NULL;
  if (obj_path) {
    path = env->get_chars(env, stack, obj_path);
  }
  
  int32_t status = SSL_CTX_load_verify_locations(self, file, path);
  
  if (!(status == 1)) {
    int64_t ssl_error = ERR_peek_last_error();
    
    char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
    ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
    
    env->die(env, stack, "[OpenSSL Error]SSL_CTX_load_verify_locations failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
    
    int32_t tmp_error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    error_id = tmp_error_id;
    
    return error_id;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__get_cert_store(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  X509_STORE* x509_store = SSL_CTX_get_cert_store(self);
  
  assert(x509_store);
  
  void* obj_address_x509_store = env->new_pointer_object_by_name(env, stack, "Address", x509_store, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  stack[0].oval = obj_address_x509_store;
  env->call_class_method_by_name(env, stack, "Net::SSLeay::X509_STORE", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  void* obj_x509_store = stack[0].oval;
  
  X509_STORE_up_ref(x509_store);
  
  stack[0].oval = obj_x509_store;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__set_options(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  int64_t options = stack[1].lval;
  
  int64_t ret = SSL_CTX_set_options(self, options);
  
  stack[0].lval = ret;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__get_options(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  int64_t ret = SSL_CTX_get_options(self);
  
  stack[0].lval = ret;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__clear_options(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  int64_t options = stack[1].lval;
  
  int64_t ret = SSL_CTX_clear_options(self, options);
  
  stack[0].lval = ret;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__set_alpn_protos(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_protos = stack[1].oval;
  
  if (!obj_protos) {
    return env->die(env, stack, "The protocols $protos must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* protos = (const char*)env->get_elems_byte(env, stack, obj_protos);
  
  int32_t protos_len = stack[2].ival;
  
  if (protos_len < 0) {
    protos_len = env->length(env, stack, obj_protos);
  }
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  int32_t status = SSL_CTX_set_alpn_protos(self, protos, protos_len);
  
  if (!(status == 0)) {
    int64_t ssl_error = ERR_peek_last_error();
    
    char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
    ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
    
    env->die(env, stack, "[OpenSSL Error]SSL_CTX_set_alpn_protos failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
    
    int32_t tmp_error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    error_id = tmp_error_id;
    
    return error_id;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__set1_groups_list(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_list = stack[1].oval;
  
  if (!obj_list) {
    return env->die(env, stack, "The group list $list must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* list = env->get_chars(env, stack, obj_list);
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  int64_t status = SSL_CTX_set1_groups_list(self, list);
  
  if (!(status == 1)) {
    int64_t ssl_error = ERR_peek_last_error();
    
    char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
    ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
    
    env->die(env, stack, "[OpenSSL Error]SSL_CTX_set1_groups_list failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
    
    int32_t tmp_error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    error_id = tmp_error_id;
    
    return error_id;
  }
  
  stack[0].lval = status;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__get_session_cache_mode(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  int64_t mode = SSL_CTX_get_session_cache_mode(self);
  
  stack[0].lval = mode;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__set_session_cache_mode(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  int64_t mode = stack[1].lval;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  int64_t ret_mode = SSL_CTX_set_session_cache_mode(self, mode);
  
  stack[0].lval = ret_mode;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__set_post_handshake_auth(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  int32_t val = stack[1].ival;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  SSL_CTX_set_post_handshake_auth(self, val);
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__set_session_id_context(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_sid_ctx = stack[1].oval;
  
  if (!obj_sid_ctx) {
    return env->die(env, stack, "The context $sid_ctx must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* sid_ctx = env->get_chars(env, stack, obj_sid_ctx);
  
  int32_t sid_ctx_len = stack[2].ival;
  
  if (sid_ctx_len < 0) {
    sid_ctx_len = env->length(env, stack, obj_sid_ctx);
  }
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  int32_t status = SSL_CTX_set_session_id_context(self, sid_ctx, sid_ctx_len);
  
  if (!(status == 1)) {
    int64_t ssl_error = ERR_peek_last_error();
    
    char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
    ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
    
    env->die(env, stack, "[OpenSSL Error]SSL_CTX_set_session_id_context failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
    
    int32_t tmp_error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    error_id = tmp_error_id;
    
    return error_id;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__set_min_proto_version(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  int32_t version = stack[1].ival;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  int32_t status = SSL_CTX_set_min_proto_version(self, version);
  
  if (!(status == 1)) {
    int64_t ssl_error = ERR_peek_last_error();
    
    char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
    ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
    
    env->die(env, stack, "[OpenSSL Error]SSL_CTX_set_min_proto_version failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
    
    int32_t tmp_error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    error_id = tmp_error_id;
    
    return error_id;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__set_client_CA_list(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_list = stack[1].oval;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  if (!obj_list) {
    return env->die(env, stack, "The list $list must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  STACK_OF(X509_NAME)* x509_names_stack = sk_X509_NAME_new_null();
  
  int32_t list_length = env->length(env, stack, obj_list);
  
  for (int32_t i = 0; i < list_length; i++) {
    void* obj_x509_name = env->get_elem_object(env, stack, obj_list, i);
    X509_NAME* x509_name = env->get_pointer(env, stack, obj_x509_name);
    sk_X509_NAME_push(x509_names_stack, X509_NAME_dup(x509_name));
  }
  
  // STACK_OF(X509_NAME) object is set. The old stack and values are freed and replaced the old stack to the new stack.
  SSL_CTX_set_client_CA_list(self, x509_names_stack);
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__add_client_CA(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_x509 = stack[1].oval;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  if (!obj_x509) {
    return env->die(env, stack, "The X509 object $cacert must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  X509* x509 = env->get_pointer(env, stack, obj_x509);
  
  // x509 is copied by X509_NAME_dup.
  int32_t status = SSL_CTX_add_client_CA(self, x509);
  
  if (!(status == 1)) {
    int64_t ssl_error = ERR_peek_last_error();
    
    char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
    ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
    
    env->die(env, stack, "[OpenSSL Error]SSL_CTX_add_client_CA failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
    
    int32_t tmp_error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    error_id = tmp_error_id;
    
    return error_id;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__add_extra_chain_cert(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_x509 = stack[1].oval;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  if (!obj_x509) {
    return env->die(env, stack, "The X509 object $x509 must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  X509* x509 = env->get_pointer(env, stack, obj_x509);
  
  // SSL_CTX destructor calls X509_free on x509.
  int32_t status = SSL_CTX_add_extra_chain_cert(self, x509);
  
  if (!(status == 1)) {
    int64_t ssl_error = ERR_peek_last_error();
    
    char* ssl_error_string = env->get_stack_tmp_buffer(env, stack);
    ERR_error_string_n(ssl_error, ssl_error_string, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE);
    
    env->die(env, stack, "[OpenSSL Error]SSL_CTX_add_extra_chain_cert failed:%s.", ssl_error_string, __func__, FILE_NAME, __LINE__);
    
    int32_t tmp_error_id = env->get_basic_type_id_by_name(env, stack, "Net::SSLeay::Error", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    error_id = tmp_error_id;
    
    return error_id;
  }
  
  X509_up_ref(x509);
  
  stack[0].ival = status;
  
  return 0;
}

static int SPVM__Net__SSLeay__SSL_CTX__my__verify_cb(int preverify_ok, X509_STORE_CTX* x509_store_ctx) {
  
  int32_t error_id = 0;
  
  int32_t ret_status = 0;
  
  SPVM_ENV* env = thread_env;
  
  SPVM_VALUE* stack = env->new_stack(env);
  
  SSL* ssl = (SSL*)X509_STORE_CTX_get_ex_data(x509_store_ctx, SSL_get_ex_data_X509_STORE_CTX_idx());
  
  if (!ssl) {
    env->die(env, stack, "X509_STORE_CTX_get_ex_data(x509_store_ctx, SSL_get_ex_data_X509_STORE_CTX_idx()) failed.", __func__, FILE_NAME, __LINE__);
    
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  
  SSL_CTX* self = SSL_get_SSL_CTX(ssl);
  
  if (!self) {
    env->die(env, stack, "SSL_get_SSL_CTX(ssl) failed.", __func__, FILE_NAME, __LINE__);
    
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  
  char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
  snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%p", self);
  stack[0].oval = env->new_string(env, stack, tmp_buffer, strlen(tmp_buffer));
  env->call_instance_method_by_name(env, stack, "GET_VERIFY_CB", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  void* obj_cb = stack[0].oval;
  
  if (!obj_cb) {
    env->die(env, stack, "GET_VERIFY_CB method returns undef.", __func__, FILE_NAME, __LINE__);
    
    env->print_exception_to_stderr(env, stack);
    goto END_OF_FUNC;
  }
  
  void* obj_address_x509_store_ctx = env->new_pointer_object_by_name(env, stack, "Address", x509_store_ctx, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    goto END_OF_FUNC;
  }
  stack[0].oval = obj_address_x509_store_ctx;
  env->call_class_method_by_name(env, stack, "Net::SSLeay::X509_STORE_CTX", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    goto END_OF_FUNC;
  }
  void* obj_x509_store_ctx = stack[0].oval;
  env->set_no_free(env, stack, obj_x509_store_ctx, 1);
  
  stack[0].oval = obj_cb;
  stack[1].ival = preverify_ok;
  stack[2].oval = obj_x509_store_ctx;
  
  env->call_instance_method_by_name(env, stack, "", 3, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  ret_status = stack[0].ival;
  
  END_OF_FUNC:
  
  env->free_stack(env, stack);
  
  return ret_status;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__set_verify(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  int32_t mode = stack[1].ival;
  
  void* obj_cb = stack[2].oval;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  SSL_verify_cb native_cb = NULL;
  if (obj_cb) {
    native_cb = &SPVM__Net__SSLeay__SSL_CTX__my__verify_cb;
    
    stack[0].oval = obj_self;
    char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
    snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%p", self);
    stack[1].oval = env->new_string(env, stack, tmp_buffer, strlen(tmp_buffer));
    stack[2].oval = obj_cb;
    env->call_instance_method_by_name(env, stack, "SET_VERIFY_CB", 3, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
  }
  
  SSL_CTX_set_verify(self, mode, native_cb);
  
  return 0;
}

static int SPVM__Net__SSLeay__SSL_CTX__my__alpn_select_cb(SSL* ssl, const unsigned char** out_ref, unsigned char* outlen_ref, const unsigned char* in, unsigned int inlen, void* native_arg) {
  
  int32_t error_id = 0;
  
  int32_t ret_status = SSL_TLSEXT_ERR_NOACK;
  
  void** native_args = (void**)native_arg;
  
  SPVM_ENV* env = (SPVM_ENV*)native_args[0];
  
  SPVM_VALUE* stack = (SPVM_VALUE*)native_args[1];
  
  void* obj_self = native_args[2];
  
  void* obj_cb = native_args[3];
  
  void* obj_arg = native_args[4];
  
  void* obj_address_ssl = env->new_pointer_object_by_name(env, stack, "Address", ssl, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    goto END_OF_FUNC;
  }
  stack[0].oval = obj_address_ssl;
  env->call_class_method_by_name(env, stack, "Net::SSLeay", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    goto END_OF_FUNC;
  }
  void* obj_ssl = stack[0].oval;
  env->set_no_free(env, stack, obj_ssl, 1);
  
  void* obj_out_ref = env->new_string_array(env, stack, 1);
  
  void* obj_in = env->new_string(env, stack, in, inlen);
  
  stack[0].oval = obj_cb;
  stack[1].oval = obj_ssl;
  stack[2].oval = obj_out_ref;
  stack[3].bref = outlen_ref;
  stack[4].oval = obj_in;
  stack[5].ival = inlen;
  stack[6].oval = obj_arg;
  env->call_instance_method_by_name(env, stack, "", 7, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    goto END_OF_FUNC;
  }
  ret_status = stack[0].ival;
  
  void* obj_out = env->get_elem_object(env, stack, obj_out_ref, 0);
  
  if (!obj_out) {
    env->die(env, stack, "An output string for set_alpn_select_cb is not set.", __func__, FILE_NAME, __LINE__);
    
    env->print_exception_to_stderr(env, stack);
    goto END_OF_FUNC;
  }
  
  const char* out = env->get_chars(env, stack, obj_out);
  *out_ref = out;
  
  env->set_field_string_by_name(env, stack, obj_self, "ref_output_for_set_alpn_select_cb", obj_out, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    goto END_OF_FUNC;
  }
  
  END_OF_FUNC:
  
  return ret_status;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__set_alpn_select_cb(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_cb = stack[1].oval;
  
  void* obj_arg = stack[2].oval;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  int (*native_cb) (SSL *ssl, const unsigned char **out, unsigned char *outlen, const unsigned char *in, unsigned int inlen, void *arg) = NULL;
  
  void* native_args[SPVM__Net__SSLeay__SSL_CTX__my__NATIVE_ARGS_MAX_LENGTH] = {0};
  if (obj_cb) {
    native_cb = &SPVM__Net__SSLeay__SSL_CTX__my__alpn_select_cb;
    
    native_args[0] = env;
    native_args[1] = stack;
    native_args[2] = obj_self;
    native_args[3] = obj_cb;
    native_args[4] = obj_arg;
  }
  
  SSL_CTX_set_alpn_select_cb(self, native_cb, native_args);
  
  return 0;
}

static int SPVM__Net__SSLeay__SSL_CTX__my__alpn_select_cb_for_protocols (SSL* ssl, const unsigned char** out_ref, unsigned char* outlen_ref, const unsigned char* in, unsigned int inlen, void* native_arg) {
  
  int32_t error_id = 0;
  
  int32_t ret_status = SSL_TLSEXT_ERR_NOACK;
  
  void** native_args = (void**)native_arg;
  
  SPVM_ENV* env = (SPVM_ENV*)native_args[0];
  
  SPVM_VALUE* stack = (SPVM_VALUE*)native_args[1];
  
  void* obj_self = native_args[2];
  
  void* obj_protocols = native_args[3];
  
  assert(obj_protocols);
  
  void* obj_out_ref = env->new_string_array(env, stack, 1);
  
  void* obj_in = env->new_string(env, stack, in, inlen);
  
  stack[0].oval = obj_protocols;
  env->call_class_method_by_name(env, stack, "Net::SSLeay::Util", "convert_to_wire_format", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  void* obj_protocols_wire_format = stack[0].oval;
  
  int32_t protocols_wire_format_length = env->length(env, stack, obj_protocols_wire_format);
  const char* protocols_wire_format = env->get_chars(env, stack, obj_protocols_wire_format);
  
  int32_t status_select_next_proto = SSL_select_next_proto((unsigned char **)out_ref, outlen_ref, in, inlen, protocols_wire_format, protocols_wire_format_length);
  
  if (status_select_next_proto == OPENSSL_NPN_NEGOTIATED) {
    ret_status = SSL_TLSEXT_ERR_OK;
  }
  
  END_OF_FUNC:
  
  return ret_status;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__set_alpn_select_cb_with_protocols(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_protocols = stack[1].oval;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  int (*native_cb) (SSL *ssl, const unsigned char **out, unsigned char *outlen, const unsigned char *in, unsigned int inlen, void *arg) = NULL;
  
  if (obj_protocols) {
    native_cb = &SPVM__Net__SSLeay__SSL_CTX__my__alpn_select_cb_for_protocols;
  }
  
  void* native_args[SPVM__Net__SSLeay__SSL_CTX__my__NATIVE_ARGS_MAX_LENGTH] = {0};
  native_args[0] = env;
  native_args[1] = stack;
  native_args[2] = obj_self;
  native_args[3] = obj_protocols;
  
  SSL_CTX_set_alpn_select_cb(self, native_cb, native_args);
  
  return 0;
}

static int SPVM__Net__SSLeay__SSL_CTX__my__default_passwd_cb(char* buf, int size, int rwflag, void* native_arg) {
  
  int32_t error_id = 0;
  
  int32_t ret_buf_length = 0;
  
  void** native_args = (void**)native_arg;
  
  SPVM_ENV* env = (SPVM_ENV*)native_args[0];
  
  SPVM_VALUE* stack = (SPVM_VALUE*)native_args[1];
  
  void* obj_self = native_args[2];
  
  void* obj_cb = native_args[3];
  
  void* obj_arg = native_args[4];
  
  void* obj_buf = env->new_string(env, stack, buf, size);
  
  stack[0].oval = obj_cb;
  stack[1].oval = obj_buf;
  stack[2].ival = size;
  stack[3].ival = rwflag;
  stack[4].oval = obj_arg;
  
  env->call_instance_method_by_name(env, stack, "", 4, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  ret_buf_length = stack[0].ival;
  
  memcpy(buf, env->get_chars(env, stack, obj_buf), size);
  
  END_OF_FUNC:
  
  return ret_buf_length;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__set_default_passwd_cb(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_cb = stack[1].oval;
  
  void* obj_arg = stack[2].oval;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  pem_password_cb* native_cb = NULL;
  
  if (obj_cb) {
    native_cb = &SPVM__Net__SSLeay__SSL_CTX__my__default_passwd_cb;
    
    void* native_args[SPVM__Net__SSLeay__SSL_CTX__my__NATIVE_ARGS_MAX_LENGTH] = {0};
    native_args[0] = env;
    native_args[1] = stack;
    native_args[2] = obj_self;
    native_args[3] = obj_cb;
    native_args[4] = obj_arg;
    SSL_CTX_set_default_passwd_cb_userdata(self, native_args);
  }
  
  SSL_CTX_set_default_passwd_cb(self, native_cb);
  
  return 0;
}

static int SPVM__Net__SSLeay__SSL_CTX__my__tlsext_servername_callback(SSL* ssl, int* al, void* native_arg) {
  
  int32_t error_id = 0;
  
  int32_t ret_status = SSL_TLSEXT_ERR_NOACK;
  
  void** native_args = (void**)native_arg;
  
  SPVM_ENV* env = (SPVM_ENV*)native_args[0];
  
  SPVM_VALUE* stack = (SPVM_VALUE*)native_args[1];
  
  void* obj_self = native_args[2];
  
  void* obj_cb = native_args[3];
  
  void* obj_arg = native_args[4];
  
  void* obj_address_ssl = env->new_pointer_object_by_name(env, stack, "Address", ssl, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  stack[0].oval = obj_address_ssl;
  env->call_class_method_by_name(env, stack, "Net::SSLeay", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  void* obj_ssl = stack[0].oval;
  
  env->set_no_free(env, stack, obj_ssl, 1);
  
  stack[0].oval = obj_cb;
  stack[1].oval = obj_ssl;
  int32_t al_tmp = 0;
  stack[2].iref = &al_tmp;
  stack[3].oval = obj_arg;
  
  env->call_instance_method_by_name(env, stack, "", 4, &error_id, __func__, FILE_NAME, __LINE__);
  ret_status = stack[0].ival;
  
  *al = al_tmp;
  
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  
  END_OF_FUNC:
  
  return ret_status;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__set_tlsext_servername_callback(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_cb = stack[1].oval;
  
  void* obj_arg = stack[2].oval;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  int (*native_cb)(SSL *s, int *al, void *arg) = NULL;
  
  if (obj_cb) {
    native_cb = &SPVM__Net__SSLeay__SSL_CTX__my__tlsext_servername_callback;
    
    void* native_args[SPVM__Net__SSLeay__SSL_CTX__my__NATIVE_ARGS_MAX_LENGTH] = {0};
    native_args[0] = env;
    native_args[1] = stack;
    native_args[2] = obj_self;
    native_args[3] = obj_cb;
    native_args[4] = obj_arg;
    SSL_CTX_set_tlsext_servername_arg(self, native_args);
  }
  
  int64_t status = SSL_CTX_set_tlsext_servername_callback(self, native_cb);
  
  assert(status == 1);
  
  stack[0].lval = status;
  
  return 0;
}

static unsigned int SPVM__Net__SSLeay__SSL_CTX__my__psk_client_cb(SSL* ssl, const char* hint, char* identity, unsigned int max_identity_len, unsigned char* psk, unsigned int max_psk_len) {
  
  int32_t error_id = 0;
  
  int32_t ret_status = 0;
  
  SPVM_ENV* env = thread_env;
  
  SPVM_VALUE* stack = env->new_stack(env);
  
  SSL_CTX* self = SSL_get_SSL_CTX(ssl);
  
  if (!self) {
    env->die(env, stack, "SSL_get_SSL_CTX(ssl) failed.", __func__, FILE_NAME, __LINE__);
    
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  
  char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
  snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%p", self);
  stack[0].oval = env->new_string(env, stack, tmp_buffer, strlen(tmp_buffer));
  env->call_instance_method_by_name(env, stack, "GET_PSK_CLIENT_CB", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  void* obj_cb = stack[0].oval;
  
  if (!obj_cb) {
    env->die(env, stack, "GET_PSK_CLIENT_CB method returns undef.", __func__, FILE_NAME, __LINE__);
    
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  
  void* obj_address_ssl = env->new_pointer_object_by_name(env, stack, "Address", ssl, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  
  stack[0].oval = obj_address_ssl;
  env->call_class_method_by_name(env, stack, "Net::SSLeay", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  void* obj_ssl = stack[0].oval;
  
  void* obj_identity = env->new_string(env, stack, identity, max_identity_len);
  
  void* obj_psk = env->new_string(env, stack, psk, max_psk_len);
  
  stack[0].oval = obj_cb;
  stack[1].oval = obj_ssl;
  stack[2].oval = obj_identity;
  stack[3].ival = max_identity_len;
  stack[4].oval = obj_psk;
  stack[5].ival = max_psk_len;
  
  env->call_instance_method_by_name(env, stack, "", 6, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  ret_status = stack[0].ival;
  
  memcpy(identity, env->get_chars(env, stack, obj_identity), max_identity_len);
  
  memcpy(psk, env->get_chars(env, stack, obj_psk), max_psk_len);
  
  END_OF_FUNC:
  
  env->free_stack(env, stack);
  
  return ret_status;
}

static int SPVM__Net__SSLeay__SSL_CTX__my__session_new_cb(SSL* ssl, SSL_SESSION* session) {
  
  int32_t error_id = 0;
  
  int32_t ret_status = 0;
  
  SPVM_ENV* env = thread_env;
  
  SPVM_VALUE* stack = env->new_stack(env);
  
  SSL_CTX* self = SSL_get_SSL_CTX(ssl);
  
  if (!self) {
    env->die(env, stack, "SSL_get_SSL_CTX(ssl) failed.", __func__, FILE_NAME, __LINE__);
    
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  
  char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
  snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%p", self);
  stack[0].oval = env->new_string(env, stack, tmp_buffer, strlen(tmp_buffer));
  env->call_instance_method_by_name(env, stack, "GET_NEW_SESSION_CB", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  void* obj_cb = stack[0].oval;
  
  if (!obj_cb) {
    env->die(env, stack, "GET_NEW_SESSION_CB method returns undef.", __func__, FILE_NAME, __LINE__);
    
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  
  void* obj_address_ssl = env->new_pointer_object_by_name(env, stack, "Address", ssl, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  stack[0].oval = obj_address_ssl;
  env->call_class_method_by_name(env, stack, "Net::SSLeay", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  void* obj_ssl = stack[0].oval;
  env->set_no_free(env, stack, obj_ssl, 1);
  
  void* obj_address_session = env->new_pointer_object_by_name(env, stack, "Address", session, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  stack[0].oval = obj_address_session;
  env->call_class_method_by_name(env, stack, "Net::SSLeay::SSL_SESSION", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  void* obj_session = stack[0].oval;
  env->set_no_free(env, stack, obj_session, 1);
  
  stack[0].oval = obj_cb;
  stack[1].oval = obj_ssl;
  stack[2].oval = obj_session;
  
  env->call_instance_method_by_name(env, stack, "", 3, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  ret_status = stack[0].ival;
  
  END_OF_FUNC:
  
  env->free_stack(env, stack);
  
  return ret_status;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__sess_set_new_cb(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_cb = stack[1].oval;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  int (*native_cb)(SSL*, SSL_SESSION*) = NULL;
                 
  if (obj_cb) {
    native_cb = &SPVM__Net__SSLeay__SSL_CTX__my__session_new_cb;
  }
  
  stack[0].oval = obj_self;
  char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
  snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%p", self);
  stack[1].oval = env->new_string(env, stack, tmp_buffer, strlen(tmp_buffer));
  stack[2].oval = obj_cb;
  env->call_instance_method_by_name(env, stack, "SET_NEW_SESSION_CB", 3, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  SSL_CTX_sess_set_new_cb(self, native_cb);
  
  return 0;
}

static void SPVM__Net__SSLeay__SSL_CTX__my__session_remove_cb(SSL_CTX *self, SSL_SESSION* session) {
  
  int32_t error_id = 0;
  
  SPVM_ENV* env = thread_env;
  
  SPVM_VALUE* stack = env->new_stack(env);
  
  int32_t ret = 0;
  if (!self) {
    env->die(env, stack, "SSL_get_SSL_CTX(ssl) failed.", __func__, FILE_NAME, __LINE__);
    
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  
  char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
  snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%p", self);
  stack[0].oval = env->new_string(env, stack, tmp_buffer, strlen(tmp_buffer));
  env->call_instance_method_by_name(env, stack, "GET_REMOVE_SESSION_CB", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  void* obj_cb = stack[0].oval;
  
  if (!obj_cb) {
    env->die(env, stack, "GET_REMOVE_SESSION_CB method returns undef.", __func__, FILE_NAME, __LINE__);
    
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  
  void* obj_address_self = env->new_pointer_object_by_name(env, stack, "Address", self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  stack[0].oval = obj_address_self;
  env->call_class_method_by_name(env, stack, "Net::SSLeay::SSL_CTX", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  void* obj_self = stack[0].oval;
  env->set_no_free(env, stack, obj_self, 1);
  
  void* obj_address_session = env->new_pointer_object_by_name(env, stack, "Address", session, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  stack[0].oval = obj_address_session;
  env->call_class_method_by_name(env, stack, "Net::SSLeay::SSL_SESSION", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  void* obj_session = stack[0].oval;
  env->set_no_free(env, stack, obj_session, 1);
  
  stack[0].oval = obj_cb;
  stack[1].oval = obj_self;
  stack[2].oval = obj_session;
  
  env->call_instance_method_by_name(env, stack, "", 3, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    env->print_exception_to_stderr(env, stack);
    
    goto END_OF_FUNC;
  }
  
  END_OF_FUNC:
  
  env->free_stack(env, stack);
  
  return;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__sess_set_remove_cb(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_cb = stack[1].oval;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  void (*native_cb)(SSL_CTX *self, SSL_SESSION* session) = NULL;
  
  if (obj_cb) {
    native_cb = &SPVM__Net__SSLeay__SSL_CTX__my__session_remove_cb;
  }
  
  stack[0].oval = obj_self;
  char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
  snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%p", self);
  stack[1].oval = env->new_string(env, stack, tmp_buffer, strlen(tmp_buffer));
  stack[2].oval = obj_cb;
  env->call_instance_method_by_name(env, stack, "SET_REMOVE_SESSION_CB", 3, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  SSL_CTX_sess_set_remove_cb(self, native_cb);
  
  return 0;
}

int32_t SPVM__Net__SSLeay__SSL_CTX__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
  
  void* obj_self = stack[0].oval;
  
  SSL_CTX* self = env->get_pointer(env, stack, obj_self);
  
  stack[0].oval = obj_self;
  snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%p", self);
  stack[1].oval = env->new_string(env, stack, tmp_buffer, strlen(tmp_buffer));
  env->call_instance_method_by_name(env, stack, "DELETE_NEW_SESSION_CB", 2, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_self;
  snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%p", self);
  stack[1].oval = env->new_string(env, stack, tmp_buffer, strlen(tmp_buffer));
  env->call_instance_method_by_name(env, stack, "DELETE_REMOVE_SESSION_CB", 2, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_self;
  snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%p", self);
  stack[1].oval = env->new_string(env, stack, tmp_buffer, strlen(tmp_buffer));
  env->call_instance_method_by_name(env, stack, "DELETE_VERIFY_CB", 2, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  if (!env->no_free(env, stack, obj_self)) {
    SSL_CTX_free(self);
  }
  
  return 0;
}
