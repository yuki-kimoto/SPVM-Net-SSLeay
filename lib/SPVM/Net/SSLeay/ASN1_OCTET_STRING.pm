package SPVM::Net::SSLeay::ASN1_OCTET_STRING;



1;

=head1 Name

SPVM::Net::SSLeay::ASN1_OCTET_STRING - ASN1_OCTET_STRING Data Structure in OpenSSL

=head1 Description

Net::SSLeay::ASN1_OCTET_STRING class in L<SPVM> represents L<ASN1_OCTET_STRING|https://pub.sortix.org/sortix/release/nightly/man/man3/ASN1_OCTET_STRING_free.3.html> data structure in OpenSSL

=head1 Usage

  use Net::SSLeay::ASN1_OCTET_STRING;

=head1 Instance Methods

=head2 DESTROY

C<method DESTROY : void ();>

Calls native L<ASN1_OCTET_STRING_free|https://pub.sortix.org/sortix/release/nightly/man/man3/ASN1_OCTET_STRING_free.3.html> function given the pointer value of the instance if C<no_free> flag of the instance is not a true value.

=head1 See Also

=over 2

=item * L<Net::SSLeay|SPVM::Net::SSLeay>

=back

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License

