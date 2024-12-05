package SPVM::Net::SSLeay::X509_REVOKED;



1;

=head1 Name

SPVM::Net::SSLeay::X509_REVOKED - X509_REVOKED Data Strucuture in OpenSSL

=head1 Description

Net::SSLeay::X509_REVOKED class in L<SPVM> represents L<X509_REVOKED|https://docs.openssl.org/master/man3/X509_CRL_get0_by_serial> data strucuture in OpenSSL.

=head1 Usage

  use Net::SSLeay::X509_REVOKED;

=head1 Class Methods

=head2 new

C<static method new : L<Net::SSLeay::X509_REVOKED|SPVM::Net::SSLeay::X509_REVOKED> ();>

Calls native L<X509_REVOKED_new|https://docs.openssl.org/1.1.1/man3/X509_dup/> function, creates a new  L<Net::SSLeay::X509_REVOKED|SPVM::Net::SSLeay::X509_REVOKED> object, sets the pointer value of the object to the return value of the native function, and returns the new object.

Exceptions:

If X509_REVOKED_new failed, an exception is thrown with C<eval_error_id> set to the basic type ID of L<Net::SSLeay::Error|SPVM::Net::SSLeay::Error> class.

=head1 Instance Methods

C<method DESTROY : void ();>

Calls native L<X509_REVOKED_free|https://docs.openssl.org/master/man3/X509_dup/> function given the pointer value of the instance if C<no_free> flag of the instance is not a true value.

=head1 See Also

=over 2

=item * L<Net::SSLeay::X509_REVOKED|SPVM::Net::SSLeay::X509_REVOKED>

=item * L<Net::SSLeay::X509|SPVM::Net::SSLeay::X509>

=item * L<Net::SSLeay|SPVM::Net::SSLeay>

=back

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License

