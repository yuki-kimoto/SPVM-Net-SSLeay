use 5.008_007;
use ExtUtils::MakeMaker;
use strict;
use warnings;
use Config;
use Getopt::Long 'GetOptions';

GetOptions(
  'meta' => \my $meta,
  'no-build-spvm-modules' => \my $no_build_spvm_modules,
);

if ($meta) {
  $no_build_spvm_modules = 1;
}

unless ($meta) {
  # Do something such as environment check.
}

my %configure_and_runtime_requires = ('SPVM' => '0.990143');
WriteMakefile(
  NAME => 'SPVM::Net::SSLeay',
  VERSION_FROM => 'lib/SPVM/Net/SSLeay.pm',
  LICENSE => 'mit',
  ($] >= 5.005 ?
    (ABSTRACT_FROM => 'lib/SPVM/Net/SSLeay.pm',
     AUTHOR => 'Yuki Kimoto<kimoto.yuki@gmail.com>') : ()),
  test => {TESTS => 't/*.t t/*/*.t t/*/*/*.t'},
  clean => {FILES => ['.spvm_build', 't/.spvm_build']},
  META_MERGE => {
    'meta-spec' => { version => 2 },
    resources => {
      repository => {
        type => 'git',
        url  => 'https://github.com/yuki-kimoto/SPVM-Net-SSLeay.git',
        web  => 'https://github.com/yuki-kimoto/SPVM-Net-SSLeay',
      },
    },
    no_index => {
      directory => [],
    }
  },
  NORECURS => 1,
  CONFIGURE_REQUIRES => {
    %configure_and_runtime_requires,
  },
  PREREQ_PM         => {
    %configure_and_runtime_requires,
    'SPVM::Sys' => '0.528',
  },
  TEST_REQUIRES => {
    'SPVM::Mozilla::CA' => '0.001',
    'SPVM::IO' => '0.204003',
    'SPVM::FindBin' => '0.031',
    'SPVM::Go' => '0.022',
  },
);

sub MY::postamble {

  my $make_rule = '';
  
  unless ($no_build_spvm_modules) {
    require SPVM::Builder::Util::API;
    
    local @INC = ('lib', @INC);
    
    # Define classes for Net::SSLeay
    my @ssleay_native_classes = (
      'Net::SSLeay',
      'Net::SSLeay::ASN1_ENUMERATED',
      'Net::SSLeay::ASN1_GENERALIZEDTIME',
      'Net::SSLeay::ASN1_INTEGER',
      'Net::SSLeay::ASN1_OBJECT',
      'Net::SSLeay::ASN1_TIME',
      'Net::SSLeay::ASN1_OCTET_STRING',
      'Net::SSLeay::BIO',
      'Net::SSLeay::Constant',
      'Net::SSLeay::DER',
      'Net::SSLeay::ERR',
      'Net::SSLeay::EVP',
      'Net::SSLeay::EVP_CIPHER_CTX',
      'Net::SSLeay::EVP_MD',
      'Net::SSLeay::EVP_PKEY',
      'Net::SSLeay::GENERAL_NAME',
      'Net::SSLeay::OBJ',
      'Net::SSLeay::OPENSSL',
      'Net::SSLeay::OPENSSL_INIT',
      'Net::SSLeay::OPENSSL_INIT_SETTINGS',
      'Net::SSLeay::PEM',
      'Net::SSLeay::PKCS12',
      'Net::SSLeay::RAND',
      'Net::SSLeay::SSL_CTX',
      'Net::SSLeay::SSL_METHOD',
      'Net::SSLeay::X509',
      'Net::SSLeay::X509_CRL',
      'Net::SSLeay::X509_NAME',
      'Net::SSLeay::X509_NAME_ENTRY',
      'Net::SSLeay::X509_REVOKED',
      'Net::SSLeay::X509_STORE',
      'Net::SSLeay::X509_STORE_CTX',
      'Net::SSLeay::X509_VERIFY_PARAM',
      'Net::SSLeay::Util',
    );

    # Generate a single parallel make rule for Net::SSLeay native classes
    $make_rule .= SPVM::Builder::Util::API::create_make_rule_parallel({
      native_classes => \@ssleay_native_classes,
    });
    
  }
  
  return $make_rule;
}

1;
