package SPVM::Net::SSLeay;

our $VERSION = "0.031";

1;

=head1 Name

SPVM::Net::SSLeay - OpenSSL Binding and SSL data strcuture.

=head1 Description

Net::SSLeay class in L<SPVM> is a binding for OpenSSL. This class itself represents L<SSL|https://docs.openssl.org/master/man3/SSL_new/> data structure.

B<Warnings:>

B<The tests haven't been written yet. The features may be changed without notice.> 

=head1 Details

=head2 Requirement

OpenSSL 1.1.1

=head1 Modules

=over 2

=item * L<Net::SSLeay|SPVM::Net::SSLeay>

=item * L<Net::SSLeay::ASN1_ENUMERATED|SPVM::Net::SSLeay::ASN1_ENUMERATED>

=item * L<Net::SSLeay::ASN1_GENERALIZEDTIME|SPVM::Net::SSLeay::ASN1_GENERALIZEDTIME>

=item * L<Net::SSLeay::ASN1_INTEGER|SPVM::Net::SSLeay::ASN1_INTEGER>

=item * L<Net::SSLeay::ASN1_OBJECT|SPVM::Net::SSLeay::ASN1_OBJECT>

=item * L<Net::SSLeay::ASN1_OCTET_STRING|SPVM::Net::SSLeay::ASN1_OCTET_STRING>

=item * L<Net::SSLeay::ASN1_STRING|SPVM::Net::SSLeay::ASN1_STRING>

=item * L<Net::SSLeay::ASN1_TIME|SPVM::Net::SSLeay::ASN1_TIME>

=item * L<Net::SSLeay::BIO|SPVM::Net::SSLeay::BIO>

=item * L<Net::SSLeay::Callback::AlpnSelect|SPVM::Net::SSLeay::Callback::AlpnSelect>

=item * L<Net::SSLeay::Callback::Msg|SPVM::Net::SSLeay::Callback::Msg>

=item * L<Net::SSLeay::Callback::PemPassword|SPVM::Net::SSLeay::Callback::PemPassword>

=item * L<Net::SSLeay::Callback::TlsextServername|SPVM::Net::SSLeay::Callback::TlsextServername>

=item * L<Net::SSLeay::Callback::Verify|SPVM::Net::SSLeay::Callback::Verify>

=item * L<Net::SSLeay::Constant|SPVM::Net::SSLeay::Constant>

=item * L<Net::SSLeay::DER|SPVM::Net::SSLeay::DER>

=item * L<Net::SSLeay::ERR|SPVM::Net::SSLeay::ERR>

=item * L<Net::SSLeay::Error|SPVM::Net::SSLeay::Error>

=item * L<Net::SSLeay::Error::PEM_R_NO_START_LINE|SPVM::Net::SSLeay::Error::PEM_R_NO_START_LINE>

=item * L<Net::SSLeay::Error::SSL_ERROR_WANT_READ|SPVM::Net::SSLeay::Error::SSL_ERROR_WANT_READ>

=item * L<Net::SSLeay::Error::SSL_ERROR_WANT_WRITE|SPVM::Net::SSLeay::Error::SSL_ERROR_WANT_WRITE>

=item * L<Net::SSLeay::EVP|SPVM::Net::SSLeay::EVP>

=item * L<Net::SSLeay::EVP_CIPHER_CTX|SPVM::Net::SSLeay::EVP_CIPHER_CTX>

=item * L<Net::SSLeay::EVP_MD|SPVM::Net::SSLeay::EVP_MD>

=item * L<Net::SSLeay::EVP_PKEY|SPVM::Net::SSLeay::EVP_PKEY>

=item * L<Net::SSLeay::GENERAL_NAME|SPVM::Net::SSLeay::GENERAL_NAME>

=item * L<Net::SSLeay::OBJ|SPVM::Net::SSLeay::OBJ>

=item * L<Net::SSLeay::OPENSSL|SPVM::Net::SSLeay::OPENSSL>

=item * L<Net::SSLeay::OPENSSL_INIT|SPVM::Net::SSLeay::OPENSSL_INIT>

=item * L<Net::SSLeay::OPENSSL_INIT_SETTINGS|SPVM::Net::SSLeay::OPENSSL_INIT_SETTINGS>

=item * L<Net::SSLeay::PEM|SPVM::Net::SSLeay::PEM>

=item * L<Net::SSLeay::PKCS12|SPVM::Net::SSLeay::PKCS12>

=item * L<Net::SSLeay::RAND|SPVM::Net::SSLeay::RAND>

=item * L<Net::SSLeay::SSL_CTX|SPVM::Net::SSLeay::SSL_CTX>

=item * L<Net::SSLeay::SSL_METHOD|SPVM::Net::SSLeay::SSL_METHOD>

=item * L<Net::SSLeay::Util|SPVM::Net::SSLeay::Util>

=item * L<Net::SSLeay::X509|SPVM::Net::SSLeay::X509>

=item * L<Net::SSLeay::X509_CRL|SPVM::Net::SSLeay::X509_CRL>

=item * L<Net::SSLeay::X509_EXTENSION|SPVM::Net::SSLeay::X509_EXTENSION>

=item * L<Net::SSLeay::X509_NAME|SPVM::Net::SSLeay::X509_NAME>

=item * L<Net::SSLeay::X509_NAME_ENTRY|SPVM::Net::SSLeay::X509_NAME_ENTRY>

=item * L<Net::SSLeay::X509_REVOKED|SPVM::Net::SSLeay::X509_REVOKED>

=item * L<Net::SSLeay::X509_STORE|SPVM::Net::SSLeay::X509_STORE>

=item * L<Net::SSLeay::X509_STORE_CTX|SPVM::Net::SSLeay::X509_STORE_CTX>

=item * L<Net::SSLeay::X509_VERIFY_PARAM|SPVM::Net::SSLeay::X509_VERIFY_PARAM>

=back

=head1 Usage

  use Net::SSLeay;
  use Net::SSLeay::Net::SSLeay::SSL_METHOD;
  use Net::SSLeay::Net::SSLeay::SSL_CTX;
  
  my $ssl_method = Net::SSLeay::SSL_METHOD->TLS_method;
  
  my $ssl_ctx = Net::SSLeay::SSL_CTX->new($ssl_method);
  
  my $ssl = Net::SSLeay->new($ssl_ctx);

=head1 Examples

See source codes of L<IO::Socket::SSL|https://metacpan.org/pod/SPVM::IO::Socket::SSL> about examples of L<Net::SSLeay|SPVM::Net::SSLeay>.

=head1 Fields

=head2 operation_error

C<has operation_error : ro int;>

The place where the return value of L<SSL_get_error|https://docs.openssl.org/1.1.1/man3/SSL_get_error/> function is stored.

=head1 Class Methods

=head2 new

C<static method new : Net::SSLeay ($ssl_ctx : L<Net::SSLeay::SSL_CTX|SPVM::Net::SSLeay::SSL_CTX>);>

Creates a new L<Net::SSLeay|SPVM::Net::SSLeay> object, creates a L<SSL|https://docs.openssl.org/master/man3/SSL_new/> object by calling native L<SSL_new|https://docs.openssl.org/master/man3/SSL_new/> function given the L<Net::SSLeay::SSL_CTX|SPVM::Net::SSLeay::SSL_CTX> object $ssl_ctx, sets the pointer value of the new L<Net::SSLeay::SSL_CTX|SPVM::Net::SSLeay::SSL_CTX> object to the return value of L<SSL_new|https://docs.openssl.org/master/man3/SSL_new/> function, and returns the new L<Net::SSLeay::SSL_CTX|SPVM::Net::SSLeay::SSL_CTX> object.

L</"ssl_ctx"> field is set to $ssl_ctx.

Exceptions:

If SSL_new failed, an exception is thrown with C<eval_error_id> set to the basic type ID of L<Net::SSLeay::Error|SPVM::Net::SSLeay::Error> class.

=head2 alert_desc_string_long

C<static method alert_desc_string_long : string ($value : int);>

Calls native L<SSL_alert_desc_string_long|https://docs.openssl.org/1.1.1/man3/SSL_alert_type_string/> function given the pointer value of the instance, $type, and returns its return value.

=head2 load_client_CA_file

C<static method load_client_CA_file : L<Net::SSLeay::X509_NAME|SPVM::Net::SSLeay::X509_NAME>[] ($file : string);>

Calls native L<SSL_load_client_CA_file|https://docs.openssl.org/3.0/man3/SSL_load_client_CA_file/> function,.

If its return value is NULL, returns undef.

Ohterwise, converts its return value to the array of L<Net::SSLeay::X509_NAME|SPVM::Net::SSLeay::X509_NAME>, and returns the array.

Exceptions:

The file $file must be defined. Otherwise an exception is thrown.

If load_client_CA_file failed, an exception is thrown with C<eval_error_id> set to the basic type ID of L<Net::SSLeay::Error|SPVM::Net::SSLeay::Error> class.

=head2 select_next_proto

C<static method select_next_proto : int ($out_ref : string[], $outlen_ref : byte*, $server : string, $server_len : int, $client : string, $client_len : int);>

Calls native L<SSL_select_next_proto|https://docs.openssl.org/3.0/man3/SSL_CTX_set_alpn_select_cb> function given the pointer value of the instance, the pointer of a native temporary variable C<out_ref>, $outlen_ref, $server, $server_len, $client, $client_len, and returns its return value.

If a string is returned in C<out_ref>, creates a new string from it and C<*outlen_ref>, sets C<$out_ref->[0]> to the string.

=head1 Instance Methods

=head2 version

C<native method version : int ();>

Calls native L<version|https://docs.openssl.org/master/man3/SSL_get_version> function, and returns its return value.

=head2 get_mode

C<method get_mode : long ();>

Calls native L<get_mode|https://docs.openssl.org/1.1.1/man3/SSL_CTX_set_mode/> function, and returns its return value.

=head2 set_mode

C<method set_mode : long ($mode : long);>

Calls native L<SSL_set_mode|https://docs.openssl.org/1.1.1/man3/SSL_CTX_set_mode/> function given the pointer value of the instance, $mode, and returns its return value.

=head2 clear_mode

C<method clear_mode : long ($mode : long);>

Calls native L<SSL_clear_mode|https://docs.openssl.org/1.1.1/man3/SSL_CTX_set_mode/> function given the pointer value of the instance, $mode, and returns its return value.

=head2 set_tlsext_host_name

C<method set_tlsext_host_name : int ($name : string);>

Calls native L<SSL_set_tlsext_host_name|https://docs.openssl.org/1.1.1/man3/SSL_CTX_set_tlsext_servername_callback> function given the host name $name, and returns its return value.

Exceptions:

The host name $name must be defined. Otherwise an exception is thrown.

If SSL_set_tlsext_host_name failed, an exception is thrown with C<eval_error_id> set to the basic type ID of L<Net::SSLeay::Error|SPVM::Net::SSLeay::Error> class.

=head2 get_servername

C<method get_servername : string ($type : int);>

Calls native L<SSL_get_servername|https://docs.openssl.org/master/man3/SSL_CTX_set_tlsext_servername_callback> function given the pointer value of the instance, $type, and returns its return value.

=head2 get_SSL_CTX

C<method get_SSL_CTX : L<Net::SSLeay::SSL_CTX|SPVM::Net::SSLeay::SSL_CTX> ();>

Calls native L<SSL_get_SSL_CTX|https://docs.openssl.org/3.4/man3/SSL_get_SSL_CTX/> function given the pointer value of the instance, creates a new L<Net::SSLeay::SSL_CTX|SPVM::Net::SSLeay::SSL_CTX> object, sets the pointer value of the new object to the return value of the native function, sets C<no_free> flag of the new object to 1, creates a reference from the new object to the instance, and returns the new object.

=head2 set_SSL_CTX

C<method set_SSL_CTX : Net::SSLeay::SSL_CTX ($ctx : Net::SSLeay::SSL_CTX);>

Calls native L<SSL_set_SSL_CTX|https://docs.openssl.org/3.4/man3/SSL_get_SSL_CTX/> function given the pointer value of the instance, creates a new L<Net::SSLeay::SSL_CTX|SPVM::Net::SSLeay::SSL_CTX> object, sets the pointer value of the new object to the return value of the native function, sets C<no_free> flag of the new object to 1, creates a reference from the new object to the instance, and returns the new object.

=head2 set_fd

C<method set_fd : int ($fd : int);>

Calls native L<SSL_set_fd|https://docs.openssl.org/master/man3/SSL_set_fd/> function given the pointer value of the instance, $fd, and returns its return value.

Exceptions:

If SSL_set_fd failed, an exception is thrown with C<eval_error_id> set to the basic type ID of L<Net::SSLeay::Error|SPVM::Net::SSLeay::Error> class.

=head2 connect

C<method connect : int ();>

Calls native L<SSL_connect|https://docs.openssl.org/1.0.2/man3/SSL_connect/> function, and returns its return value.

Exceptions:

If SSL_connect failed, an exception is thrown with C<eval_error_id> set to the basic type ID of L<Net::SSLeay::Error|SPVM::Net::SSLeay::Error> class and with L</"operation_error"> field set to the return vlaue of L<SSL_get_error|https://docs.openssl.org/1.1.1/man3/SSL_get_error/> function given the return value of L<SSL_connect|https://docs.openssl.org/1.0.2/man3/SSL_connect/> function.

=head2 accept

C<method accept : int ();>

Calls native L<SSL_accept|https://docs.openssl.org/master/man3/SSL_accept/> function, and returns its return value.

Exceptions:

If SSL_accept failed, an exception is thrown with C<eval_error_id> set to the basic type ID of L<Net::SSLeay::Error|SPVM::Net::SSLeay::Error> class and with L</"operation_error"> field set to the return vlaue of L<SSL_get_error|https://docs.openssl.org/1.1.1/man3/SSL_get_error/> function given the return value of L<SSL_accept|https://docs.openssl.org/1.0.2/man3/SSL_accept/> function.

=head2 read

C<method read : int ($buf : mutable string, $num : int = -1, $offset : int = 0);>

Calls native L<SSL_read|https://docs.openssl.org/1.1.1/man3/SSL_read/> function given the pointer value of the instance, $buf at the offest $offset, $num, and returns its return value.

Exceptions:

The buffer $buf must be defined. Otherwise an exception is thrown.

The offset $offset must be greater than or equal to 0. Otherwise an exception is thrown.

The offset $offset + $num must be lower than or equal to the length of the buffer $buf. Otherwise an exception is thrown.

If SSL_read failed, an exception is thrown with C<eval_error_id> set to the basic type ID of L<Net::SSLeay::Error|SPVM::Net::SSLeay::Error> class and with L</"operation_error"> field set to the return vlaue of L<SSL_get_error|https://docs.openssl.org/1.1.1/man3/SSL_get_error/> function given the return value of L<SSL_read|https://docs.openssl.org/1.0.2/man3/SSL_read/> function.

=head2 write

C<method write : int ($buf : string, $num : int = -1, $offset : int = 0);>

Calls native L<SSL_write|https://docs.openssl.org/1.1.1/man3/SSL_write/> function, given the pointer value of the instance, $buf at the offset $offset, $num, and returns its return value.

Exceptions:

The buffer $buf must be defined. Otherwise an exception is thrown.

The offset $offset must be greater than or equal to 0. Otherwise an exception is thrown.

The offset $offset + $num must be lower than or equal to the length of the buffer $buf. Otherwise an exception is thrown.

If SSL_write failed, an exception is thrown with C<eval_error_id> set to the basic type ID of L<Net::SSLeay::Error|SPVM::Net::SSLeay::Error> class and with L</"operation_error"> field set to the return vlaue of L<SSL_get_error|https://docs.openssl.org/1.1.1/man3/SSL_get_error/> function given the return value of L<SSL_write|https://docs.openssl.org/1.0.2/man3/SSL_write/> function.

=head2 shutdown

C<method shutdown : int ();>

Calls native L<SSL_shutdown|https://docs.openssl.org/master/man3/SSL_shutdown/> function, and returns its return value.

Exceptions:

If SSL_shutdown failed, an exception is thrown with C<eval_error_id> set to the basic type ID of L<Net::SSLeay::Error|SPVM::Net::SSLeay::Error> class and with L</"operation_error"> field set to the return vlaue of L<SSL_get_error|https://docs.openssl.org/1.1.1/man3/SSL_get_error/> function given the return value of L<SSL_shutdown|https://docs.openssl.org/1.0.2/man3/SSL_shutdown/> function.

=head2 get_shutdown

C<method get_shutdown : int ();>

Calls native L<SSL_get_shutdown|https://docs.openssl.org/master/man3/SSL_set_shutdown/> function, and returns its return value.

=head2 get_cipher

C<method get_cipher : string ();>

Calls native L<SSL_get_cipher|https://docs.openssl.org/1.0.2/man3/SSL_get_current_cipher/> function, and returns its return value.

=head2 get_certificate

C<method get_certificate : L<Net::SSLeay::X509|SPVM::Net::SSLeay::X509> ();>

Calls native L<SSL_get_certificate|https://docs.openssl.org/master/man3/SSL_get_certificate> function.

If the return value of the native function is NULL, returns undef.

Otherwise, creates a new L<Net::SSLeay::X509|SPVM::Net::SSLeay::X509> object, sets the pointer value of the new object to the return value of the native function, and returns the new object.

C<no_free> flag of the new object is set to 1.

=head2 get_peer_certificate

C<method get_peer_certificate : L<Net::SSLeay::X509|SPVM::Net::SSLeay::X509> ();>

Calls native L<SSL_get_peer_certificate|https://docs.openssl.org/master/man3/SSL_get_peer_certificate> function.

If the return value of the native function is NULL, returns undef.

Otherwise, creates a new L<Net::SSLeay::X509|SPVM::Net::SSLeay::X509> object, sets the pointer value of the new object to the return value of the native function, and returns the new object.

=head2 get0_alpn_selected

C<method get0_alpn_selected : void ($data_ref : string[], $len_ref : int*);>

Calls native L<SSL_get0_alpn_selected|https://docs.openssl.org/1.1.1/man3/SSL_CTX_set_alpn_select_cb> function given the pointer value of the instance, $data_ref, $len_ref.

=head2 get0_alpn_selected_return_string

C<method get0_alpn_selected_return_string : string ()>

Calls L</"get0_alpn_selected"> method given appropriate arguments, and returns the output string.

=head2 get_peer_cert_chain

C<method get_peer_cert_chain : L<Net::SSLeay::X509|SPVM::Net::SSLeay::X509>[] ();>

Calls native L<SSL_get_peer_cert_chain|https://docs.openssl.org/1.1.1/man3/SSL_get_peer_cert_chain> function.

If its return value is NULL, returns undef.

Ohterwise, converts its return value to the array of L<Net::SSLeay::X509|SPVM::Net::SSLeay::X509>, and returns the array.

method get_SSL_CTX : Net::SSLeay::SSL_CTX ();

=head2 set_msg_callback

C<method set_msg_callback : void ($cb : L<Net::SSLeay::Callback::Msg|SPVM::Net::SSLeay::Callback::Msg>);>

Calls native L<SSL_set_msg_callback|https://docs.openssl.org/1.1.1/man3/SSL_CTX_set_msg_callback> function given the pointer value of the instance, $cb, $arg, and returns its return value.

=head2 dump_peer_certificate

C<static method dump_peer_certificate : string ();>

Returns the same output of Perl's L<Net::SSLeay#dump_peer_certificate|https://metacpan.org/dist/Net-SSLeay/view/lib/Net/SSLeay.pod#Convenience-routines> function.

=head2 DESTROY

C<method DESTROY : void ();>

Frees native L<SSL|https://docs.openssl.org/1.0.2/man3/SSL_free> object by calling native L<SSL_free|https://docs.openssl.org/1.0.2/man3/SSL_free> function if C<no_free> flag of the instance is not a true value.

=head1 Config Builder

L<SPVM::Net::SSLeay::ConfigBuilder>

=head1 FAQ

=head2 Is LibreSSL supported?

Yes.

=head1 Porting

This class is a Perl's L<Net::SSLeay> porting to L<SPVM>.

=head1 Repository

L<SPVM::Net::SSLeay - Github|https://github.com/yuki-kimoto/SPVM-Net-SSLeay>

=head1 Author

Yuki Kimoto<kimoto.yuki@gmail.com>

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

