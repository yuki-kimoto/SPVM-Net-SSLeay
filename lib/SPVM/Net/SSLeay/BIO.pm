package SPVM::Net::SSLeay::BIO;



1;

=head1 Name

SPVM::Net::SSLeay::BIO - BIO data structure in OpenSSL

=head1 Description

Net::SSLeay::BIO class of L<SPVM> represents L<BIO|https://docs.openssl.org/1.0.2/man3/BIO_new> data structure in OpenSSL.

=head1 Usage

  use Net::SSLeay::BIO;

=head1 Class Methods

=head2 new

C<static method new : L<Net::SSLeay::BIO|SPVM::Net::SSLeay::BIO> ();>

Creates a new L<Net::SSLeay::BIO|SPVM::Net::SSLeay::BIO> object and returns its.

Implementation:

This method calls L<BIO_new|https://docs.openssl.org/1.0.2/man3/BIO_new/> function given the return value of C<BIO_s_mem()> as the first argument.

The pointer value of the new L<Net::SSLeay::BIO|SPVM::Net::SSLeay::BIO> object is set to the return value of C<BIO_new> function.

=head1 Instance Methods

=head2 DESTROY

C<method DESTROY : void ();>

Frees L<BIO|https://docs.openssl.org/1.0.2/man3/BIO_new> object using L<BIO_free|https://docs.openssl.org/1.0.2/man3/BIO_free> function if C<no_free> flag of the instance is not a true value.

=head2 read

C<method read : int ($data : mutable string, $dlen : int = -1);>

Attempts to read $dlen bytes from C<BIO> and places the data in $data using L<BIO_read|https://docs.openssl.org/1.0.2/man3/BIO_read/> function and returns its return value.

If $dlen is lower than 0, it is set to the length of $data.

Exceptions:

The $data must be defined. Otherwise an exception is thrown.

The $dlen must be lower than or equal to the length of the $data. Otherwise an exception is thrown.

If BIO_read failed, an exception is thrown.

=head2 write

C<method write : int ($data : string, $dlen : int = -1);>

Attempts to write $dlen bytes from $data to C<BIO> using L<BIO_write|https://docs.openssl.org/1.0.2/man3/BIO_write/> function and returns its return value.

If $dlen is lower than 0, it is set to the length of $data.

Exceptions:

The $data must be defined. Otherwise an exception is thrown.

The $dlen must be lower than or equal to the length of the $data. Otherwise an exception is thrown.

If BIO_write failed, an exception is thrown.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

