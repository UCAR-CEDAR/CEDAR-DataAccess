#!/opt/local/bin/perl


select STDOUT; $| = 1;
open (LOGFILE,">count_error.log") || do_exit ("could not create log file");
open (STDERR,">&LOGFILE") || do_exit ("could not redirect stderr");

print "Directory containing cbf files? ";
$dire=<STDIN>;
print "Beginning processing at ",`date`,"\n";

cedar_count_driver($dire);

close (LOGFILE);
close (STDERR);

print $myname,"Ending processing at ",`date`,"\n";

sub do_exit
{
    my $what = shift;
    print LOGFILE $what;
    print "Notice: a problem has been detected. See error log for details!\n";
    exit(1);
}

sub cedar_count_driver
{
    print STDERR "Opening log file\n";
    $total=0;
    my $dire = shift;
    chop ($dire);
    $proc="ls $dire" . "/*.cbf";
    `$proc`;
    if(($?>>8) !=0)
    {
	do_exit ("Invalid directory");
    }
    open (PROC, "$proc|") || do_exit ("PROC is dead");
    while(<PROC>)
    {
	$eps="nrecords";
	$file=$_;
	chop($file);
	$val=`$eps -f $file`;
	$ret=$?>>8;
	if ($ret!=0)
	{
	    print "$eps has failed with return value ",$ret," on file ",$file,"\n";
	}
	else
	{
	    print "$eps: $file = $val";
	}
	$total+=$val;
    }
    close (PROC);
    print "Total number of records is ",$total,"\n";
}


