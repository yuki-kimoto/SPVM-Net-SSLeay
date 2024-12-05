package SPVM::Net::SSLeay::X509_CRL;



1;

=head1 Name

SPVM::Net::SSLeay::X509_CRL - X509_CRL data structure in OpenSSL

=head1 Description

Net::SSLeay::X509_CRL class in L<SPVM> represents L<X509_CRL|https://docs.openssl.org/3.1/man3/X509_CRL_new/> data structure in OpenSSL

=head1 Usage

  use Net::SSLeay::X509_CRL;

=head1 Class Methods

=head2 new

C<static method new : L<Net::SSLeay::X509_CRL|SPVM::Net::SSLeay::X509_CRL> ();>

Calls native L<X509_CRL_new|https://docs.openssl.org/1.1.1/man3/X509_dup/> function, creates a new  L<Net::SSLeay::X509_CRL|SPVM::Net::SSLeay::X509_CRL> object, sets the pointer value of the object to the return value of the native function, and returns the new object.

Exceptions:

If X509_CRL_new failed, an exception is thrown with C<eval_error_id> set to the basic type ID of L<Net::SSLeay::Error|SPVM::Net::SSLeay::Error> class.

=head1 Instance Methods

C<method DESTROY : void ();>

Calls native L<X509_CRL_free|https://docs.openssl.org/3.1/man3/X509_CRL_free/> function given the pointer value of the instance if C<no_free> flag of the instance is not a true value.

=head1 FAQ

=head2 How to create a new Net::SSLeay::X509_CRL object?

A way is reading PEM file by calling native L<Net::SSLeay::PEM#read_bio_X509_CRL|SPVM::Net::SSLeay::PEM/"read_bio_X509_CRL"> method.

=head1 See Also

=over 2

=item * L<Net::SSLeay::X509_STORE|SPVM::Net::SSLeay::X509_STORE>

=item * L<Net::SSLeay::PEM|SPVM::Net::SSLeay::PEM>

=item * L<Net::SSLeay|SPVM::Net::SSLeay>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

