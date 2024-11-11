package SPVM::Net::SSLeay::RAND;



1;

=head1 Name

SPVM::Net::SSLeay::RAND - RAND Name Space in OpenSSL

=head1 Description

Net::SSLeay::RAND class in L<SPVM> represents RAND name space in OpenSSL.

=head1 Usage

  use Net::SSLeay::RAND;

=head1 Class Methods

=head2 seed

C<static method seed : void ($buf : string, $num : int);>

Calls native L<RAND_seed|https://docs.openssl.org/3.0/man3/RAND_add/> function.

Exceptions:

The buffer $buf must be defined. Otherwise an exception is thrown.

=head1 See Also

=over 2

=item * L<Net::SSLeay|SPVM::Net::SSLeay>

=back

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License

