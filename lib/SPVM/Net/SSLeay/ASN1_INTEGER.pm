package SPVM::Net::SSLeay::ASN1_INTEGER;



1;

=head1 Name

SPVM::Net::SSLeay::ASN1_INTEGER - ASN1_INTEGER Data Structure in OpenSSL

=head1 Description

Net::SSLeay::ASN1_INTEGER class in L<SPVM> represents L<ASN1_INTEGER|https://docs.openssl.org/3.1/man3/ASN1_INTEGER_get_int64/> data structure in OpenSSL

=head1 Usage

  use Net::SSLeay::ASN1_INTEGER;

=head1 Instance Methods

=head2 DESTROY

C<method DESTROY : void ();>

Calls native L<ASN1_INTEGER_free|https://github.com/google/boringssl/blob/master/include/openssl/asn1.h> function given the pointer value of the instance if C<no_free> flag of the instance is not a true value.

=head1 See Also

=over 2

=item * L<Net::SSLeay|SPVM::Net::SSLeay>

=back

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License

