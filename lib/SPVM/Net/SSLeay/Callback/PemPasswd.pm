package SPVM::Net::SSLeay::Callback::PemPassword;



1;

=head1 Name

SPVM::Net::SSLeay::Callback::PemPassword - Callback for SSL_CTX_set_default_passwd_cb function in OpenSSL.

=head1 Description

Net::SSLeay::Callback::PemPassword interface in L<SPVM> is the callback for L<SSL_CTX_set_default_passwd_cb|https://docs.openssl.org/1.0.2/man3/SSL_CTX_set_default_passwd_cb> function in OpenSSL.

=head1 Usage

  use Net::SSLeay::Callback::PemPassword;

=head1 Interface Methods

C<required method : int ($ssl : L<Net::SSLeay|SPVM::Net::SSLeay>, $rwflag : int, $arg : object);>

This method is callback for native L<SSL_CTX_set_default_passwd_cb|https://docs.openssl.org/1.0.2/man3/SSL_CTX_set_default_passwd_cb> function.

=head1 See Also

=over 2

=item * L<Net::SSLeay::SSL_CTX|SPVM::Net::SSLeay::SSL_CTX>

=item * L<Net::SSLeay|SPVM::Net::SSLeay>

=back

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License

