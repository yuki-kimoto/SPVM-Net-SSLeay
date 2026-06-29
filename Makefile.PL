use 5.020;
use ExtUtils::MakeMaker;
use strict;
use warnings;
use Config;
use Getopt::Long 'GetOptions';
use File::Path 'mkpath', 'rmtree';

GetOptions(
  'meta' => \my $meta,
  'no-build-spvm-modules' => \my $no_build_spvm_modules,
  'cc=s' => \my $cc,
  'ccflag=s' => \my @ccflags,
  'define=s' => \my @defines,
  'ld=s' => \my $ld,
  'ldflag=s' => \my @ldflags,
  'debug' => \my $debug,
  'build-type=s' => \my $build_type,
  'asan-on-linux' => \my $asan_on_linux,
  'msvc' => \my $msvc,
  'parallel-make' => \my $parallel_make,
  'parallel-test' => \my $parallel_test,
  'jobs=i' => \my $jobs,
);

if ($meta) {
  $no_build_spvm_modules = 1;
}

my $build_dir = '.spvm_build';
mkpath $build_dir;

my $build_work_lib_dir;
if ($msvc) {
  local @INC = @INC;
  push @INC, 'lib';
  require SPVM::Net::SSLeay::ConfigBuilder;
  require SPVM::Builder::Config;
  require File::Copy;
  my $config = SPVM::Builder::Config->new_c11;
  my $config_builder = SPVM::Net::SSLeay::ConfigBuilder->new();
  $config_builder->build_config($config);
  
  $build_work_lib_dir = '.spvm_build/work/lib';
  mkpath $build_work_lib_dir;
  
  my $lib_dirs = $config->lib_dirs;
  my $lib_dir = $lib_dirs && $lib_dirs->[0] ? $lib_dirs->[0] : undef;
  my $libs = $config->libs;
  
  if ($lib_dir) {
    for my $lib_name (@$libs) {
      my $lib_filename_a = "lib$lib_name.a";
      
      my $source_path = "$lib_dir/$lib_filename_a";
      
      if (-f $source_path) {
        my $dest_filename = "$lib_name.lib";
        my $dest_path = "$build_work_lib_dir/$dest_filename";
        
        print "Copy: $source_path -> $dest_path\n";
        File::Copy::copy($source_path, $dest_path) or die "Copy failed: $!";
      }
    }
  }
}

my $config_global_file = '.spvm_build/global.config';
generate_config_global_file($config_global_file, {
  cc            => $cc,
  ccflags       => \@ccflags,
  defines       => \@defines,
  ld            => $ld,
  ldflags       => \@ldflags,
  debug         => $debug,
  build_type    => $build_type,
  asan_on_linux => $asan_on_linux,
  msvc => $msvc,
});

my $asan_logs_dir = ".tmp/asan_logs";
if ($asan_on_linux) {
  rmtree $asan_logs_dir;
  mkpath $asan_logs_dir;
}

unless ($meta) {
  require SPVM::Builder::Util::API;
}

my $gnu_make;
unless ($meta) {
  $gnu_make = SPVM::Builder::Util::API::search_gnu_make_command();
}

unless ($meta) {
  unless (defined $jobs) {
    my $cpus = SPVM::Builder::Util::API::get_cpu_count();
    $jobs = $cpus + 2;
  }

  if ($jobs > 16) {
    $jobs = 16;
  }
}
$jobs //= 1;

my %configure_requires_and_prereq_pm = (
  'SPVM' => '0.990191',
);
WriteMakefile(
  NAME => 'SPVM::Net::SSLeay',
  VERSION_FROM => 'lib/SPVM/Net/SSLeay.pm',
  LICENSE => 'mit',
  ($] >= 5.005 ?
    (ABSTRACT_FROM => 'lib/SPVM/Net/SSLeay.pm',
     AUTHOR => 'Yuki Kimoto<kimoto.yuki@gmail.com>') : ()),
  test => {TESTS => 't/*.t t/*/*.t t/*/*/*.t'},
  clean => {FILES => ['.spvm_build']},
  META_MERGE => {
    'meta-spec' => {
      version => 2,
      # release_status => 'stable', # stable, testing, or unstable
    },
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
  MAKE => $gnu_make,
  macro => {
    $parallel_make ? (MAKEFLAGS => "-j$jobs") : (),
    $parallel_test ? ('override TEST_VERBOSE' => "scalar (eval chr(36) . q(ENV{HARNESS_OPTIONS}='j$jobs'), 0)") : (),
    $asan_on_linux ? ('override FULLPERL' => qq|LD_PRELOAD=\$\$($Config{cc} -print-file-name=libasan.so) ASAN_OPTIONS="log_path=$asan_logs_dir/asan.log:exitcode=0" $^X|) : (),
  },
  NORECURS => 1,
  CONFIGURE_REQUIRES => {
    %configure_requires_and_prereq_pm,
  },
  PREREQ_PM => {
    %configure_requires_and_prereq_pm,
    'SPVM::Sys' => '0.572',
  },
  TEST_REQUIRES => {
    'SPVM::Mozilla::CA' => '0.003',
    'SPVM::IO' => '0.249',
    'SPVM::FindBin' => '0.035',
    'SPVM::Go' => '0.030',
  }
);

package MY {
  
  sub postamble {
    my $make_rule = '';
    unless ($no_build_spvm_modules) {
      my $options = {};
      $options->{config_global_file} = $config_global_file;
      $options->{order_only_dependent_files} = ['pm_to_blib'];
      
      $options->{native_classes} = [
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
      ];
      
      $options->{precompile_classes} = [
        
      ];
      
      $make_rule .= SPVM::Builder::Util::API::create_make_rule_parallel($options);
    }
    return $make_rule;
  }
}

sub generate_config_global_file {
  my ($config_global_file, $options) = @_;
  
  my $cc             = $options->{cc};
  my $ccflags        = $options->{ccflags} // [];
  my $defines        = $options->{defines} // [];
  my $ld             = $options->{ld};
  my $ldflags        = $options->{ldflags} // [];
  my $build_type     = $options->{build_type};
  my $debug          = $options->{debug};
  my $asan_on_linux = $options->{asan_on_linux};
  my $msvc = $options->{msvc};
  
  if ($debug) {
    $build_type = 'Debug';
  }
  
  if ($asan_on_linux) {
    push @$ccflags, "-fsanitize=address", "-fno-omit-frame-pointer";
    push @$ldflags, "-fsanitize=address";
  }
  
  my $config_global_content = '';
  
  $config_global_content .= <<"EOS";
my \$config_global = SPVM::Builder::Config::Global->new;
EOS
  
  if ($msvc) {
    $config_global_content .= <<"EOS";
use SPVM::Builder::Config::Global::MSVC;
\$config_global = SPVM::Builder::Config::Global::MSVC->new;
EOS
  }
  
  if (defined $build_type) {
    $config_global_content .= <<"EOS";
\$config_global->build_type('$build_type');
EOS
  }
  
  if (defined $cc) {
    $config_global_content .= <<"EOS";
\$config_global->build_rule_any({'cc' => '$cc'});
EOS
  }
  
  for my $ccflag (@$ccflags) {
    $config_global_content .= <<"EOS";
\$config_global->build_rule_any({'+ccflags' => ['$ccflag']});
EOS
  }
  
  for my $define (@$defines) {
    $config_global_content .= <<"EOS";
\$config_global->build_rule_any({'+defines' => ['$define']});
EOS
  }
  
  if (defined $ld) {
    $config_global_content .= <<"EOS";
\$config_global->build_rule_any({'ld' => '$ld'});
EOS
  }
  
  for my $ldflag (@$ldflags) {
    $config_global_content .= <<"EOS";
\$config_global->build_rule_any({'+ldflags' => ['$ldflag']});
EOS
  }
  
  if ($msvc) {
    $config_global_content .= <<"EOS";
\$config_global->build_rule_any({'+lib_dirs' => '$build_work_lib_dir'});
EOS
  }
  
  $config_global_content .= <<"EOS";
\$config_global;
EOS
  
  open my $fh, '>', $config_global_file or die "Can't open file '$config_global_file': $!";
  print $fh $config_global_content;
}

1;

=head1 Name 

SPVM::Net::SSLeay Makefile.PL

=head1 Description

Makefile.PL for L<SPVM::Net::SSLeay> build.

=head1 Command Line Options

See the following URL for the command line options:

L<https://github.com/yuki-kimoto/SPVM/blob/master/Makefile.PL>

=cut
