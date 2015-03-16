# Installing umurmur on DD-WRT #

I'm writing this guide for people who have DD-WRT running on their router and want to use umurmur, but don't really know how to go about it. I'm not 100% sure that what I did is correct, but it worked for me on my router (TP-Link WR1043ND with DD-WRT v24sp2 build 14896). You'll need to enter quite a few commands in the console, so I made them bold. I hope the markup shows up :) I might have forgotten a command somewhere!

Enable JFFS2 as per instructions (read carefully!):

http://www.dd-wrt.com/wiki/index.php/Journalling_Flash_File_System

On my router, installing umurmur required between 200kb and 300kb, so make sure you have 300kb free space on the JFFS. You can check the free space on your status page. If you have less, you'll have to look for alternatives (USB stick or network share?).

Assuming that you have enough space available on JFFS: Log onto your router using a telnet or SSH client (Putty works well). Username is 'root' and password is the same as for the web GUI.
In the console, change your current directory to '/tmp/root', files stored there are kept in the routers RAM and as such will disappear after a reboot.

`cd /tmp/root`

Use the command 'wget' to download the required packages to '/tmp/root'.
The URLs listed below worked on my Atheros-based TP-Link WR1043ND. To find which files you need, look in the DD-WRT router database (or here:
http://www.dd-wrt.com/wiki/index.php/Supported_Devices) and find out what platform your router is based on, then find the appropriate directory in http://downloads.openwrt.org/snapshots/trunk/ for your platform and change the URLs accordingly.
```
wget http://downloads.openwrt.org/snapshots/trunk/atheros/packages/umurmur-polarssl_0.2.10-1_atheros.ipk 
wget http://downloads.openwrt.org/snapshots/trunk/atheros/packages/libpolarssl_1.1.3-1_atheros.ipk  
wget http://downloads.openwrt.org/snapshots/trunk/atheros/packages/libprotobuf-c_0.15-1_atheros.ipk 
wget http://downloads.openwrt.org/snapshots/trunk/atheros/packages/libconfig_1.4.8-2_atheros.ipk
```

Use the 'ipkg' program (http://www.dd-wrt.com/wiki/index.php/Ipkg) to
install the packages on the JFFS. 'ipkg' supports downloading and
installing the packages in 1 step, but it threw errors on my router.
Downloading them with 'wget'and then installing them like this still showed
warnings (ERROR: File not found, etc) but worked fine. You can do a 'dry
run' by using 'ipkg -d ram /tmp/root/packagename' to install the packages
in the RAM, so you can test umurmur without making permanent changes.
```
cd /jffs
ipkg -d jffs /tmp/root/umurmur-polarssl_0.2.10-1_atheros.ipk 
ipkg -d jffs /tmp/root/libpolarssl_1.1.3-1_atheros.ipk
ipkg -d jffs /tmp/root/libprotobuf-c_0.15-1_atheros.ipk 
ipkg -d jffs /tmp/root/libconfig_1.4.8-2_atheros.ipk
```

At this point, you can test whether umurmur will work by running it in
interactive mode. This means you can see the output and errors of umurmur,
and try connecting using mumble. Be sure to use the '-d' switch, otherwise
umurmur runs as a daemon:

`/jffs/usr/bin/umurmurd -d -c /jffs/etc/umurmur.conf`

If you installed to RAM using 'ipkg -d ram', replace /jffs with /tmp like
this to test umurmur in interactive mode:

`/tmp/usr/bin/umurmurd -d -c /tmp/etc/umurmur.conf -r`

You'll see warnings that you haven't configured a certificate yet and that
this is insecure. Now, try connecting with mumble! The umurmur server will
not be reachable from the internet yet, so you'll have to connect from the
LAN and use the LAN ip of the router (ef. 192.168.1.1). To exit the
interactive mode umurmur, simply use CTRL-C to end the program.
Now it's time to generate a self signed certificate. I used a linux
computer for this, a standard distribution will have 'openssl' available:
```
openssl genrsa 1024 > my_key.key 
openssl req -new -x509 -nodes -sha1 -days 365 -key my_key.key > my_selfsigned_cert.crt
```

I do not know the significance of the options given, just that they
generated the necessary key and certificate that worked with umurmur. On
Windows, you can download the Windows version of OpenSSL
(http://slproweb.com/products/Win32OpenSSL.html) and use the same commands
as shown above. The easiest way to get the files on the router is putting
them on a webspace for a moment and using 'wget' again (be sure to delete
the files from the webspace ASAP!). The harder but more secure way is to
use SSH, which you need to enable on the router
(http://www.dd-wrt.com/wiki/index.php/Telnet/SSH_and_the_Command_Line#SSH).
Then, to connect from Windows, use WinSCP
(http://www.dd-wrt.com/wiki/index.php/WinSCP). Put the files in the
`/jffs/etc/umurmur/` directory.
Now you'll have to edit the configuration file to point umurmur to the
certificate, set a server- and admin password and edit the channels. The
configuration file is located at '`/jffs/etc/umurmur.conf`'. If you just
uploaded the certificate with WinSCP, you can use the internal editor of
WinSCP to edit the file. Do not use Notepad to edit it as it will mess up
the line endings. If you need to edit the file using the console, use 'vi'
to edit the file (if you've never used 'vi' before, look here:
http://www.howtogeek.com/102468/a-beginners-guide-to-editing-text-files-with-vi/).
The comments in the file should point you in the right direction.
After saving the configuration file, check if you didn't accidentally mess
it up:
`/jffs/usr/bin/umurmurd -t -c /jffs/etc/umurmur.conf`

If you run that command and you get nothing back, your configuration file
is ok! After you fix the errors, you're ready to make umurmur start up when
the router boots. To do that, go to the Administration => Commands page in
the web GUI, paste the following lines in the text field and click 'Save
Startup':
```
kill $(cat "/var/run/umurmurd.pid")
/jffs/usr/bin/umurmurd -c /jffs/etc/umurmur.conf  -r -p /var/run/umurmurd.pid
```

That will tell the router to kill umurmur if it's still running somehow,
and start it up again using your configuration file. Now, you need to tell
the DD-WRT firewall that umurmur may accept connections from the WAN side.
Enter the following in the text area and click 'Save Firewall':
```
iptables -I INPUT -p udp --dport 64738 -j ACCEPT
iptables -I INPUT -p tcp --dport 64738 -j ACCEPT 
```

If you changed the port number in the configuration file, you have to
change it here as well!
That's it! Umurmur should now be running as desired and your friends should
be able to connect. If you set an admin password in the configuration, you
have to add this to the 'Access Tokens' list in the server menu in Mumble,
then reconnect. After reconnecting, you should be able to kick and move
your friends. Also, by default everyone can create temporary channels,
which disappear when the last player leaves it.