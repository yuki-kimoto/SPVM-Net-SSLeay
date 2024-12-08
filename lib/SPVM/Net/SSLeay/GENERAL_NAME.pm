package SPVM::Net::SSLeay::GENERAL_NAME;



1;

=head1 Name

SPVM::Net::SSLeay::GENERAL_NAME - GENERAL_NAME Data Structure in OpenSSL

=head1 Description

Net::SSLeay::GENERAL_NAME class in L<SPVM> represents L<GENERAL_NAME|https://docs.openssl.org/master/man3/GENERAL_NAME_new/> data structure in OpenSSL

=head1 Usage

  use Net::SSLeay::GENERAL_NAME;

=head1 Class Methods

=head2 new

C<static method new : L<Net::SSLeay::GENERAL_NAME|SPVM::Net::SSLeay::GENERAL_NAME> ();>

Calls native L<GENERAL_NAME_new|https://docs.openssl.org/1.0.2/man3/GENERAL_NAME_new/> function, creates a new  L<Net::SSLeay::GENERAL_NAME|SPVM::Net::SSLeay::GENERAL_NAME> object, sets the pointer value of the object to the return value of the native function, and returns the new object.

Exceptions:

If GENERAL_NAME_new failed, an exception is thrown with C<eval_error_id> set to the basic type ID of L<Net::SSLeay::Error|SPVM::Net::SSLeay::Error> class.

=head1 Instance Methods

=head2 type

C<method get_type : int ();>

Returns the value of C<type> member variable in C<GENERAL_NAME> data strcuture.

=head2 get_data_as_string

C<method get_data_as_string : string ();>

Creates a string from the data in C<GENERAL_NAME>, and returns it.

Exceptions:

If the length of d.rid is invalid, an exception is thrown.

The value of type member variable is invalid, an exception is thrown.

=head2 DESTROY

C<method DESTROY : void ();>

Calls native L<GENERAL_NAME_free|https://docs.openssl.org/master/man3/GENERAL_NAME_new/> function given the pointer value of the instance if C<no_free> flag of the instance is not a true value.

=head1 See Also

=over 2

=item * L<Net::SSLeay|SPVM::Net::SSLeay>

=back

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License
