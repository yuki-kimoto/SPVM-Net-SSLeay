package SPVM::Net::SSLeay::PKCS12;



1;

=head1 Name

SPVM::Net::SSLeay::PKCS12 - PKCS12 Data Structure in OpenSSL

=head1 Description

Net::SSLeay::PKCS12 class in L<SPVM> represents L<PKCS12|https://docs.openssl.org/master/man3/X509_dup> data structure in OpenSSL.

=head1 Usage

  use Net::SSLeay::PKCS12;

=head1 Class Methods

=head2 new

C<static method new : L<Net::SSLeay::PKCS12|SPVM::Net::SSLeay::PKCS12> ();>

Calls native L<PKCS12_new|https://docs.openssl.org/master/man3/X509_dup> function, creates a new  L<Net::SSLeay::PKCS12|SPVM::Net::SSLeay::PKCS12> object, sets the pointer value of the object to the return value of the native function, and returns the new object.

Exceptions:

If PKCS12_new failed, an exception is thrown with C<eval_error_id> set to the basic type ID of L<Net::SSLeay::Error|SPVM::Net::SSLeay::Error> class.

=head1 Instance Methods

=head2 DESTROY

C<method DESTROY : void ();>

Calls native L<PKCS12_free|https://docs.openssl.org/master/man3/X509_dup/> function given the pointer value of the instance if C<no_free> flag of the instance is not a true value.

=head1 See Also

=over 2

=item * L<Net::SSLeay|SPVM::Net::SSLeay>

=back

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License

