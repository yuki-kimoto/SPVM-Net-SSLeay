package SPVM::Net::SSLeay::X509_EXTENSION;



1;

=head1 Name

SPVM::Net::SSLeay::X509_EXTENSION - X509_EXTENSION Data Structure in OpenSSL

=head1 Description

Net::SSLeay::X509_EXTENSION class in L<SPVM> represents L<X509_EXTENSION|https://docs.openssl.org/3.1/man3/X509_dup/> data structure in OpenSSL

=head1 Usage

  use Net::SSLeay::X509_EXTENSION;

=head1 Instance Methods

=head2 DESTROY

C<method DESTROY : void ();>

Calls native L<X509_EXTENSION_free|https://docs.openssl.org/3.1/man3/X509_dup/> function given the pointer value of the instance if C<no_free> flag of the instance is not a true value.

=head1 See Also

=over 2

=item * L<Net::SSLeay|SPVM::Net::SSLeay>

=back

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License

