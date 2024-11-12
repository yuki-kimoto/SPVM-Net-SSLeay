package SPVM::Net::SSLeay::X509;



1;

=head1 Name

SPVM::Net::SSLeay::X509 - X509 data structure in OpenSSL

=head1 Description

Net::SSLeay::X509 class in L<SPVM> represents L<X509|https://docs.openssl.org/3.1/man3/X509_new/> data structure in OpenSSL

=head1 Usage

  use Net::SSLeay::X509;

=head1 Instance Methods

=head2 get_issuer_name

C<method get_issuer_name : L<Net::SSLeay::X509_NAME|SPVM::Net::SSLeay::X509_NAME> ();>

Calls native L<X509_get_issuer_name|https://docs.openssl.org/3.3/man3/X509_get_subject_name> function, creates a new L<Net::SSLeay::X509_NAME|SPVM::Net::SSLeay::X509_NAME> object, sets the pointer value of the new object to the return vlaue of the native function, and returns the new object.

The C<no_free> flag of the new object is set to 1.

=head2 get_subject_name

C<method get_subject_name : L<Net::SSLeay::X509_NAME|SPVM::Net::SSLeay::X509_NAME> ();>

Calls native L<X509_get_subject_name|https://docs.openssl.org/3.3/man3/X509_get_subject_name> function, creates a new L<Net::SSLeay::X509_NAME|SPVM::Net::SSLeay::X509_NAME> object, sets the pointer value of the new object to the return vlaue of the native function, and returns the new object.

The C<no_free> flag of the new object is set to 1.

=head2 digest

C<method digest : int ($type : L<Net::SSLeay::EVP_MD|SPVM::Net::SSLeay::EVP_MD>, $md : mutable string, $len_ref : int*);>

Calls native L<X509_digest|https://docs.openssl.org/master/man3/X509_digest> function given $type, the pointer value of $md, $len_ref, and returns its return value.

Exceptions:

The digest type $type must be defined. Otherwise an exception is thrown.

The output buffer $md must be defined. Otherwise an exception is thrown.

The length of output buffer $md must be greater than or equal to EVP_MAX_MD_SIZE. Otherwise an exception is thrown.

If X509_digest failed, an exception is thrown with C<eval_error_id> set to the basic type ID of L<Net::SSLeay::Error|SPVM::Net::SSLeay::Error> class.

=head2 DESTROY

C<method DESTROY : void ();>

Frees native L<X509|https://docs.openssl.org/3.1/man3/X509_new/> object by calling native L<X509_free|https://docs.openssl.org/3.1/man3/X509_free/> function if C<no_free> flag of the instance is not a true value.

=head1 FAQ

=head2 How to create a new Net::SSLeay::X509 object?

A way is reading PEM file by calling native L<Net::SSLeay::PEM#read_bio_X509|SPVM::Net::SSLeay::PEM/"read_bio_X509"> method.

=head1 See Also

=over 2

=item * L<Net::SSLeay::X509_STORE|SPVM::Net::SSLeay::X509_STORE>

=item * L<Net::SSLeay::PEM|SPVM::Net::SSLeay::PEM>

=item * L<Net::SSLeay|SPVM::Net::SSLeay>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

