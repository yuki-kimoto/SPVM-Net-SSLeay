package SPVM::Net::SSLeay::SSL_SESSION;



1;

=head1 Name

SPVM::Net::SSLeay::SSL_SESSION - SSL_SESSION data strucutre in OpenSSL

=head1 Description

Net::SSLeay::SSL_SESSION class in L<SPVM> represents  L<SSL_SESSION|https://docs.openssl.org/1.1.1/man3/SSL_SESSION_free/> data strucutre in OpenSSL.

=head1 Usage

  use Net::SSLeay::SSL_SESSION;

=head1 Instance Methods

=head2 DESTROY

C<method DESTROY : void ();>

Frees native L<SSL_SESSION|https://docs.openssl.org/1.1.1/man3/SSL_SESSION_free/> object by calling native L<SSL_SESSION_free|https://docs.openssl.org/1.1.1/man3/SSL_SESSION_free/> function if C<no_free> flag of the instance is not a true value.

=head1 See Also

=over 2

=item * L<Net::SSLeay|SPVM::Net::SSLeay>

=back

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License

