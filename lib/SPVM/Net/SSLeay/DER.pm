package SPVM::Net::SSLeay::DER;



1;

=head1 Name

SPVM::Net::SSLeay::DER - Name Space for d2i_ and i2d_ prefixed functions in OpenSSL

=head1 Description

Net::SSLeay::DER class in L<SPVM> represents a name space for L<d2i_ and i2d_ prefixed functions|https://docs.openssl.org/master/man3/d2i_X509> in OpenSSL.

=head1 Usage

  use Net::SSLeay::DER;

=head1 Template Methods

The following methods are virtual template methods that does not exist. C<TYPE> represents a real type of OpenSSL.

=head2 d2i_TYPE

C<static method d2i_TYPE : C<Net::SSLeay::TYPE> ($a_ref : C<Net::SSLeay::TYPE>[], $ppin_ref : string[], $length : long);>

Calls native L<d2i_TYPE|https://docs.openssl.org/master/man3/d2i_X509> function given $a_ref, $ppin_ref, $length, and creates a new C<Net::SSLeay::TYPE> object, sets the pointer value of the new object to the return value of the native function, and returns the new object.

Exceptions:

$a_ref must be undef(Currently reuse feature is not available). Otherwise an exception is thrown.

$ppin_ref must be defined. Otherwise an exception is thrown. Otherwise an exception is thrown.

The length of $ppin_ref must be 1. Otherwise an exception is thrown. Otherwise an exception is thrown.

$ppin_ref at index 0 must be defined. Otherwise an exception is thrown. Otherwise an exception is thrown.

If d2i_TYPE failed, an exception is thrown with C<eval_error_id> set to the basic type ID of L<Net::SSLeay::Error|SPVM::Net::SSLeay::Error> class.

=head2 i2d_TYPE

C<static method i2d_TYPE : int ($a : C<Net::SSLeay::TYPE>, $ppout_ref : string[]);>

Calls native L<i2d_TYPE|https://docs.openssl.org/master/man3/d2i_X509> function given $a_ref, $ppin_ref, $length, and returns its return value.

Exceptions:

$a must be undef. Otherwise an exception is thrown.

$ppout_ref must be defined. Otherwise an exception is thrown. Otherwise an exception is thrown.

The length of $ppout_ref must be 1. Otherwise an exception is thrown. Otherwise an exception is thrown.

If i2d_TYPE failed, an exception is thrown with C<eval_error_id> set to the basic type ID of L<Net::SSLeay::Error|SPVM::Net::SSLeay::Error> class.

=head1 Class Methods

=head2 d2i_OCSP_REQUEST

C<static method d2i_OCSP_REQUEST : Net::SSLeay::OCSP_REQUEST ($a_ref : Net::SSLeay::OCSP_REQUEST[], $ppin_ref : string[], $length : long);>

See L</"d2i_TYPE"> template method.

=head2 i2d_OCSP_REQUEST

C<static method i2d_OCSP_REQUEST : int ($a : Net::SSLeay::OCSP_REQUEST, $ppout_ref : string[]);>

See L</"i2d_TYPE"> template method.

=head2 d2i_OCSP_RESPONSE

C<static method d2i_OCSP_RESPONSE : Net::SSLeay::OCSP_RESPONSE ($a_ref : Net::SSLeay::OCSP_RESPONSE[], $ppin_ref : string[], $length : long);>

See L</"d2i_TYPE"> template method.

=head2 i2d_OCSP_RESPONSE

C<static method i2d_OCSP_RESPONSE : int ($a : Net::SSLeay::OCSP_RESPONSE, $ppout_ref : string[]);>

See L</"i2d_TYPE"> template method.

=head1 See Also

=over 2

=item * L<Net::SSLeay|SPVM::Net::SSLeay>

=back

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License

