package SPVM::Net::SSLeay::X509_STORE_CTX;



1;

=head1 Name

SPVM::Net::SSLeay::X509_STORE_CTX - X509_STORE_CTX Data Structure in OpenSSL

=head1 Description

Net::SSLeay::X509_STORE_CTX class in L<SPVM> represents L<X509_STORE_CTX|https://docs.openssl.org/3.1/man3/X509_STORE_CTX_new/> data structure in OpenSSL.

=head1 Usage

  use Net::SSLeay::X509_STORE_CTX;

=head1 Instance Methods

=head2 set_error

C<method set_error : void ($s : int);>

Calls native L<X509_STORE_CTX_set_error|https://docs.openssl.org/master/man3/X509_STORE_CTX_get_error> function given $s.

=head2 get_error

C<method get_error : int ();>

Calls native L<X509_STORE_CTX_get_error|https://docs.openssl.org/master/man3/X509_STORE_CTX_get_error> function, and returns its return value.

=head2 get_error_depth

C<method get_error_depth : int ();>

Calls native L<X509_STORE_CTX_get_error_depth|https://docs.openssl.org/master/man3/X509_STORE_CTX_get_error_depth> function, and returns its return value.

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License

