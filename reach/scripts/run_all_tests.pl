#!/usr/bin/perl

use strict;
use warnings;
use File::Basename;
use Time::HiRes;

if (scalar(@ARGV) != 1)
{
	die "Usage: test.pl <app>";
}

my $app = $ARGV[0];

my @tests = split(/\s+/, `find tests -type f`);

my $start_time = Time::HiRes::gettimeofday();
for my $test (sort @tests)
{
	next if $test !~ m/\.in.txt$/;

	print "Running $test...\n";

	my $test_out = $test;
    my $test_err = $test;
	$test_out =~ s/\.in.txt$/\.my.txt/;
	$test_err =~ s/\.in.txt$/\.myerr.txt/;
    my $script_path = dirname $test;
	my $sys_ret = system("$script_path/run_one_test.sh $app $test $test_out $test_err");
}
my $end_time = Time::HiRes::gettimeofday();
printf("Overall execution time: %.5f\n", $end_time - $start_time);
