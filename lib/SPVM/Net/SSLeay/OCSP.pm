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

Exceptions:

If SSL_CTX_new failed, an exception is thrown with C<eval_error_id> set to the basic type ID of L<Net::SSLeay::Error|SPVM::Net::SSLeay::Error> class.

=head2 basic_verify

C<static method basic_verify : int ($bs : L<Net::SSLeay::OCSP_BASICRESP|SPVM::Net::SSLeay::OCSP_BASICRESP>, $certs : L<Net::SSLeay::X509|SPVM::Net::SSLeay::X509>[], $st : L<Net::SSLeay::X509_STORE|SPVM::Net::SSLeay::X509_STORE>, $flags : long);>

Calls native L<OCSP_basic_verify|https://docs.openssl.org/1.1.1/man3/OCSP_resp_find_status> function, and returns its return value.

Exceptions:

If OCSP_basic_verify failed, an exception is thrown with C<eval_error_id> set to the basic type ID of L<Net::SSLeay::Error|SPVM::Net::SSLeay::Error> class.

=head1 See Also

=over 2

=item * L<Net::SSLeay::OCSP_RESPONSE|SPVM::Net::SSLeay::OCSP_RESPONSE>

=item * L<Net::SSLeay::OCSP_REQUEST|SPVM::Net::SSLeay::OCSP_REQUEST>

=item * L<Net::SSLeay|SPVM::Net::SSLeay>

=back

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License

