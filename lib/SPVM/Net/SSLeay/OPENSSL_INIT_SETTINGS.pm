package SPVM::Net::SSLeay::OPENSSL_INIT_SETTINGS;



1;

=head1 Name

SPVM::Net::SSLeay::OPENSSL_INIT_SETTINGS - OPENSSL_INIT_SETTINGS Data Structure in OpenSSL

=head1 Description

Net::SSLeay::OPENSSL_INIT_SETTINGS class in L<SPVM> represents L<OPENSSL_INIT_SETTINGS|https://docs.openssl.org/1.1.1/man3/OPENSSL_init_crypto> data structure in OpenSSL.

=head1 Usage

  use Net::SSLeay::OPENSSL_INIT_SETTINGS;

=head1 Instance Methods

=head2 DESTROY

C<method DESTROY : void ();>

Calls native L<OPENSSL_INIT_free|https://docs.openssl.org/1.1.1/man3/OPENSSL_init_crypto> function given the pointer value of the instance if C<no_free> flag of the instance is not a true value.

=head1 See Also

=over 2

=item * L<Net::SSLeay::OPENSSL|SPVM::Net::SSLeay::OPENSSL>

=item * L<Net::SSLeay::OPENSSL_INIT|SPVM::Net::SSLeay::OPENSSL_INIT>

=item * L<Net::SSLeay|SPVM::Net::SSLeay>

=back

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License

