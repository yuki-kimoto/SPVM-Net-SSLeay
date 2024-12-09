package SPVM::Net::SSLeay::X509_STORE;



1;

=head1 Name

SPVM::Net::SSLeay::X509_STORE - X509_STORE data structure in OpenSSL

=head1 Description

Net::SSLeay::X509_STORE in L<SPVM> represetns L<X509_STORE|https://docs.openssl.org/1.1.1/man3/X509_STORE_new/> data structure in OpenSSL.

=head1 Usage

  use Net::SSLeay::X509_STORE;

=head1 Instance Methods

=head2 set_flags

C<method set_flags : void ($flags : long);>

Calls native L<X509_STORE_set_flags|https://docs.openssl.org/master/man3/X509_STORE_set_flags/> function given $flags.

Exceptions:

If X509_STORE_set_flags failed, an exception is thrown with C<eval_error_id> set to the basic type ID of L<Net::SSLeay::Error|SPVM::Net::SSLeay::Error> class.

=head2 add_cert

C<method add_cert : int ($x : L<Net::SSLeay::X509|SPVM::Net::SSLeay::X509>);>

Calls native L<X509_STORE_add_cert|https://docs.openssl.org/1.1.1/man3/X509_STORE_add_cert/> function given the pointer value of $x.

Exceptions:

If X509_STORE_add_cert failed, an exception is thrown with C<eval_error_id> set to the basic type ID of L<Net::SSLeay::Error|SPVM::Net::SSLeay::Error> class.

=head2 add_crl

C<method add_crl : void ($x : L<Net::SSLeay::X509_CRL|SPVM::Net::SSLeay::X509_CRL>);>

Calls native L<X509_STORE_add_crl|https://docs.openssl.org/3.0/man3/X509_STORE_add_crl/> function given the pointer value of $x.

Exceptions:

If X509_STORE_add_crl failed, an exception is thrown with C<eval_error_id> set to the basic type ID of L<Net::SSLeay::Error|SPVM::Net::SSLeay::Error> class.

=head2 DESTROY

C<method DESTROY : void ();>

Calls native L<X509_STORE_free|https://docs.openssl.org/3.1/man3/X509_STORE_free/> function given the pointer value of the instance if C<no_free> flag of the instance is not a true value.

=head1 FAQ

=head2 How to get a new Net::SSLeay::X509_STORE object?

A way is using L<Net::SSLeay::SSL_CTX#get_cert_store|SPVM::Net::SSLeay::SSL_CTX/"get_cert_store"> method.

=head1 See Also

=over 2

=item * L<Net::SSLeay::X509|SPVM::Net::SSLeay::X509>

=item * L<Net::SSLeay::X509_CRL|SPVM::Net::SSLeay::X509_CRL>

=item * L<Net::SSLeay::SSL_CTX|SPVM::Net::SSLeay::SSL_CTX>

=item * L<Net::SSLeay|SPVM::Net::SSLeay>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

