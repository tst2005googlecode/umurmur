Installing uMurmur on a OpenWRT router should just be a matter of copying the .ipk file to your router's /tmp directory, for example by issuing this command from a nearby host (you can of course use WinSCP or whatever):
```
# scp umurmur_N.N.N-N.ipk root@<router address>:/tmp
```
If you haven't got OpenSSL and libconfig installed, opkg will complain when installing, so you'd better go ahead and download/build and then install them first.

Then install it with opkg:
```
# opkg install umurmur_N.N.N-N.ipk
```
Then take a minute to create a configuration, see the [Configuring](Configuring.md) page.

Then if you don't want to restart the router, you need to start up uMurmur with
```
# /etc/init.d/umurmur start
```
I intend to fix a post-install script that starts it up automatically after installing some time. It will however start automatically during boot.

You can check the log to see if it started up OK:
```
# logread
Oct 14 21:54:10 OpenWrt daemon.info uMurmud[5727]: INFO: PID-file: /var/run/umurmurd.pid
Oct 14 21:54:10 OpenWrt daemon.info uMurmud[5727]: INFO: List of ciphers:
Oct 14 21:54:10 OpenWrt daemon.info uMurmud[5727]: INFO: DHE-RSA-AES256-SHA
Oct 14 21:54:10 OpenWrt daemon.info uMurmud[5727]: INFO: DHE-DSS-AES256-SHA
Oct 14 21:54:10 OpenWrt daemon.info uMurmud[5727]: INFO: AES256-SHA
Oct 14 21:54:10 OpenWrt daemon.info uMurmud[5727]: INFO: EDH-RSA-DES-CBC3-SHA
Oct 14 21:54:10 OpenWrt daemon.info uMurmud[5727]: INFO: EDH-DSS-DES-CBC3-SHA
Oct 14 21:54:10 OpenWrt daemon.info uMurmud[5727]: INFO: DES-CBC3-SHA
Oct 14 21:54:10 OpenWrt daemon.info uMurmud[5727]: INFO: DES-CBC3-MD5
Oct 14 21:54:10 OpenWrt daemon.info uMurmud[5727]: INFO: DHE-RSA-AES128-SHA
Oct 14 21:54:10 OpenWrt daemon.info uMurmud[5727]: INFO: DHE-DSS-AES128-SHA
Oct 14 21:54:10 OpenWrt daemon.info uMurmud[5727]: INFO: AES128-SHA
Oct 14 21:54:10 OpenWrt daemon.info uMurmud[5727]: INFO: RC2-CBC-MD5
Oct 14 21:54:10 OpenWrt daemon.info uMurmud[5727]: INFO: RC4-SHA
Oct 14 21:54:10 OpenWrt daemon.info uMurmud[5727]: INFO: RC4-MD5
Oct 14 21:54:10 OpenWrt daemon.info uMurmud[5727]: INFO: RC4-MD5
Oct 14 21:54:10 OpenWrt daemon.info uMurmud[5727]: INFO: Setting default channel COH
Oct 14 21:54:10 OpenWrt daemon.info uMurmud[5727]: INFO: Adding channel COH parent Root
Oct 14 21:54:10 OpenWrt daemon.info uMurmud[5727]: INFO: Adding channel Allies parent COH
Oct 14 21:54:10 OpenWrt daemon.info uMurmud[5727]: INFO: Adding channel Axis parent COH
Oct 14 21:54:10 OpenWrt daemon.info uMurmud[5727]: INFO: Setting SCHED_RR prio 1
```