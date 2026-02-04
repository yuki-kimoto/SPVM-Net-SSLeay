use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use SPVM 'Fn';
use SPVM 'TestCase::Net::SSLeay::Online';

my $api = SPVM::api();

# Check network connectivity to httpbin.org using Perl's HTTP::Tiny
use HTTP::Tiny;
my $res = HTTP::Tiny->new(timeout => 5)->get("http://httpbin.org/get");
unless ($res->{success}) {
  plan skip_all => "No internet connection or httpbin.org is down (verified by Perl's HTTP::Tiny)";
}

my $start_memory_blocks_count = $api->get_memory_blocks_count;

ok(SPVM::TestCase::Net::SSLeay::Online->https_httpbin);

# ok(SPVM::TestCase::Net::SSLeay::Online->https_httpbin_with_mozilla_ca);

SPVM::Fn->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
