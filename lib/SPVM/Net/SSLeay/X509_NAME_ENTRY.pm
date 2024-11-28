package SPVM::Net::SSLeay::X509_NAME_ENTRY;



1;

=head1 Name

SPVM::Net::SSLeay::X509_NAME_ENTRY - X509_NAME_ENTRY Data Structure in OpenSSL

=head1 Description

Net::SSLeay::X509_NAME_ENTRY class in L<SPVM> represents L<X509_NAME_ENTRY|https://docs.openssl.org/3.2/man3/X509_new/> data structure in OpenSSL

=head1 Usage

  use Net::SSLeay::X509_NAME_ENTRY;

=head1 Fields

=head2 ref_x509_name

C<has ref_x509_name : Net::SSLeay::X509_NAME;>

=head1 Instance Methods

=head2 DESTROY

C<method DESTROY : void ();>

Calls native L<X509_free|https://docs.openssl.org/3.2/man3/X509_new> function given the pointer value of the instance if C<no_free> flag of the instance is not a true value.

=head1 See Also

=over 2

=item * L<Net::SSLeay::PEM|SPVM::Net::SSLeay::X509>

=item * L<Net::SSLeay|SPVM::Net::SSLeay>

=back

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License

