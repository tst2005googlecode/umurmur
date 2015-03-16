uMurmur is a minimalistic [Mumble](http://mumble.sourceforge.net/) server primarily targeted to run on routers with an open OS like OpenWRT. The server part of Mumble is called Murmur, hence the name uMurmur.

# uMurmur 0.2.15 released #
This release contains a IPv6 dual stack implementation contributed by Felix Morgner. It's updated to use Protobuf-C version 1.0.0.
See the [Changelog](https://github.com/fatbob313/umurmur/blob/master/ChangeLog) for full list of changes.

Since Googlecode no longer supports downloads of tarballs the releases from now on will be hosted by Github via the release tag. Link to this release: https://github.com/fatbob313/umurmur/archive/0.2.15.tar.gz

A consequence of this is that the tarball will not contain the autotools generated files, a script `autogen.sh` in the release base directory needs to be run to generate these.

## Overview ##
Version 0.2.x of uMurmur supports version 1.2.x Mumble clients. It is not compatible with version 1.1.x of Mumble.

Highlights of the 0.2.x releases:
  * Uses Mumble protocol 1.2.x, meaning that clients 1.2.x are supported.
  * Support for PolarSSL as an alternative to OpenSSL.
  * Whisper target to channels, channel trees and linked channels.
  * Temporary channels can be created by users.
  * Channel links can be configured in the configuration file.
  * Channels can be configured non-enterable in configuration file.
  * Positional audio is stripped if users are not in the same plugin context (playing the same game).

## Documentation for 0.2.x ##
This is not complete yet (and probably never will...). Changelog and README in the source tree at GitHub. Apart from that, the following sources of information are available:
  * [Configuring](http://code.google.com/p/umurmur/wiki/Configuring02x)
  * [Admin](http://code.google.com/p/umurmur/wiki/Admin) - How to enable admin user functionality
  * [umurmur-general](http://groups.google.com/group/umurmur-general) discussion group

## Precompiled packages ##
I just make the source code available here. Precompiled packages are prepared by others. Here is a (incomplete) list of distributions/platforms, some found using Google.
  * OpenWRT. I've heard people are using these on DD-WRT as well.
  * Freetz
  * QNAP
  * XTreamer
  * Arch Linux
  * NetBSD

## Do you like uMurmur? ##
You can show your appreciation of uMurmur by pressing the Flattr button below if you have an account there or donate via PayPal. I'm not expecting to get rich, but could definitely use some beer-money :)
<wiki:gadget border="0" url="https://gist.githubusercontent.com/stefansundin/8195226/raw/flattr-gadget.xml" width="110" height="20" up\_uid="b419617" up\_title="uMurmur" up\_desc="uMurmur" up\_url="https://code.google.com/p/umurmur/" />

You can also donate money via Paypal, just press the button below:
<wiki:gadget border="0" url="https://gist.github.com/fatbob313/ebe306697af14efd1ebb/raw/86af29e3384ef44af67a8c522c09bc4ff3350456/paypal-gadget.xml" up\_business="N9J488LQ5E4UC" />

## Random info ##
uMurmur is written in C and uses [OpenSSL](http://www.openssl.org) or [PolarSSL](http://www.polarssl.org), [libconfig](http://www.hyperrealm.com/libconfig/libconfig.html) libraries and libprotobuf\_c from the [Protobuf-c](http://code.google.com/p/protobuf-c/) project for communication using Google's protocol buffers.

It targets to fill the needs of a pretty small group of users communicating, which in part originates from the other goal of working well on a small system with a limited CPU and limited amount of disk space. It also aims to minimize writing to the disk since these kinds of systems usually only has a flash memory for disk.

## PolarSSL vs OpenSSL ##
PolarSSL uses a _lot_ less RAM memory than OpenSSL:
  * uMurmur linked to PolarSSL lib with 7 connected users uses ~900 Kb (code + data). Each new connection increases mem usage by ~60-70 kB.
  * uMurmur linked to OpenSSL lib with 7 connected users uses ~4 Mb (code + data). Each new connection increases mem usage by ~400 kB.

The above figures are measured with `top` on a MIPS device (Netgear WGT634U) so the accuracy is not really good, but rather a rough indication.

On-disk memory usage is a lot less for PolarSSL:
```
root@router2:~# ls -l /usr/lib/libpolarssl.so
-rwxr-xr-x    1 root     root       183073 Feb 13 17:53 /usr/lib/libpolarssl.so
root@router2:~# ls -l /usr/lib/libssl.so.0.9.8
-rw-r--r--    1 root     root       204371 Sep 22 20:12 /usr/lib/libssl.so.0.9.8
root@router2:~# ls -l /usr/lib/libcrypto.so.0.9.8
-rw-r--r--    1 root     root       912927 Sep 22 20:12 /usr/lib/libcrypto.so.0.9.8
```
Note: PolarSSL library contains both SSL and crypto code.

I haven't noticed any great difference in CPU usage between the two.

## Comparison to Murmur ##
uMurmur supports a subset of the features of Murmur. To list some of the differences compared to Murmur:
  * Channels are statically configured in configuration file - no channel add/rename/move. Temporary channels can be added however.
  * No user database.
  * No ACL support, but instead a simpler approach using a password enabled admin user functionality.
  * No ICE or DBus interface.
  * No user avatar support.

Some of the above might change in the future, but additions will always be within the original design goals of keeping it as lean, mean and simple as possible.
