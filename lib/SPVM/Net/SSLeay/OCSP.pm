package SPVM::Net::SSLeay::OCSP;



1;

=head1 Name

SPVM::Net::SSLeay::OCSP - OCSP Name Space in OpenSSL

=head1 Description

Net::SSLeay::OCSP class in L<SPVM> represents L<OCSP|https://docs.openssl.org/master/man3/OCSP_response_status/> Name Space in OpenSSL

=head1 Usage

  use Net::SSLeay::OCSP;

=head1 Class Methods

=head2 response_status_str

C<static method response_status_str : string ($code : long);>

Calls native L<OCSP_response_status_str|https://man.openbsd.org/OCSP_basic_sign.3> function, and returns its return value.

=head2 response_status

C<static method response_status : int ($resp : L<Net::SSLeay::OCSP_RESPONSE|SPVM::Net::SSLeay::OCSP_RESPONSE>);>

Calls native L<OCSP_response_status|https://docs.openssl.org/1.1.1/man3/OCSP_response_status> function, and returns its return value.

Exceptions:

The OCSP response $resp must be defined. Otherwise an exception is thrown.

=head1 See Also

=over 2

=item * L<Net::SSLeay::OCSP_RESPONSE|SPVM::Net::SSLeay::OCSP_RESPONSE>

=item * L<Net::SSLeay::OCSP_REQUEST|SPVM::Net::SSLeay::OCSP_REQUEST>

=item * L<Net::SSLeay|SPVM::Net::SSLeay>

=back

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License

