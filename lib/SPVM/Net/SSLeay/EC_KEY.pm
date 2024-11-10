package SPVM::Net::SSLeay::EC_KEY;



1;

=head1 Name

SPVM::Net::SSLeay::EC_KEY - EC_KEY data structure in OpenSSL

=head1 Description

Net::SSLeay::EC_KEY class in L<SPVM> represents L<EC_KEY|https://docs.openssl.org/master/man3/EC_KEY_new/> data structure in OpenSSL

=head1 Usage

  use Net::SSLeay::EC_KEY;

=head1 Class Methods



=head1 Instance Methods

=head2 DESTROY

C<method DESTROY : void ();>

Frees L<EC_KEY|https://docs.openssl.org/master/man3/EC_KEY_new/> object by calling L<EC_KEY_free|https://docs.openssl.org/master/man3/EC_KEY_new/> function if C<no_free> flag of the instance is not a true value.

=head1 See Also



=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License

