#*******************************************************************************
#*******************************************************************************
#**                                                                           **
#**                    COPYRIGHT 2000-2003 TEGIC COMMUNICATIONS               **
#**                                                                           **
#**                TEGIC COMMUNICATIONS PROPRIETARY INFORMATION               **
#**                                                                           **
#**     This software is supplied under the terms of a license agreement      **
#**     or non-disclosure agreement with Tegic Communications and may not     **
#**     be copied or disclosed except in accordance with the terms of that    **
#**     agreement.                                                            **
#**                                                                           **
#*******************************************************************************
#**                                                                           **
#**     FileName:   VERSION.PL                                                **
#**                                                                           **
#**  Description:   Perl script to create T9ver.h file                        **
#**      History:   4/13/2000: Create T9ver.h to contains T9Core compiled     **
#**                 date.                                                     **
#**                                                                           **
#*******************************************************************************
#******* 10 ****** 20 ****** 30 ****** 40 ****** 50 ****** 60 ****** 70 *******/
# 

$NamePassword       = 'TNguyen:';                      # name and password
$ServerEndpoint     = '49201';                         # constant value
$StarTeamProject	= '\T9Light';

$T9VerFileName      = 't9ver.h';


    # --------------------------------------------------------------------------------------
    # Delete the t9ver.h file if it exists
    # --------------------------------------------------------------------------------------
    if ((-e $T9VerFileName)) 
	{
        if (!(unlink ($T9VerFileName))) 
		{
            die "Can't delete $T9VerFileName";        
        }
    } 

    # --------------------------------------------------------------------------------------
    # Create t9ver.h
    # --------------------------------------------------------------------------------------
	open(T9FILE, ">$T9VerFileName") or die "Can't create file $T9VerFileName $!\n";

    print T9FILE "#ifndef T9VER_H\n";
    print T9FILE "#define T9VER_H\n\n";
#    print T9FILE "const T9U8 T9FARDATA bCoreVerDate[] = \"";
	print T9FILE "const unsigned char bCoreVerDate[] = \"";

    ($sec, $min, $hour, $mday, $mon, $year, $wday, $yday, $isdst) = localtime(time);
    $thisday = (Sun, Mon, Tue, Wed, Thu, Fri, Sat)[$wday];
    $thismon = (Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec)[$mon];
    $thisyear = 1900 + $year;

    # print hour
    if ($hour < 10)
    {
        print T9FILE '0';
    }
    print T9FILE $hour . ':';

    # print min
    if ($min < 10)
    {
        print T9FILE '0';
    }
    print T9FILE $min . ':';

    # print sec
    if ($sec < 10)
    {
        print T9FILE '0';
    }
    print T9FILE $sec . ' ';

    # print day of the week
    print T9FILE $thisday . ' ';

    # print day of the month
    if ($mday < 10)
    {
        print T9FILE '0';
    }
    print T9FILE $mday . ' ';

    # print month
    print T9FILE $thismon . ' ';

    # print year
    print T9FILE $thisyear;

    print T9FILE "\";\n\n";
    print T9FILE "#endif /* T9VER_H */\n";


