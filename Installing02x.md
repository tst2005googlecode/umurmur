# OpenWRT #
## Installing uMurmur with OpenSSL support ##
Installing uMurmur on a OpenWRT router running any Backfire release is easy since it's available in the package repository. Either install it using the web interface or the command line with:
```
# opkg update
# opkg install umurmur-openssl
```
If you run a Kamikaze you need to build the package as explained in the [Building](Building.md) page an then copy the .ipk file to your router's /tmp directory, for example by issuing this command from a nearby host (you can of course use WinSCP or whatever):
```
# scp umurmur-openssl_0.2.x-y.ipk root@<router address>:/tmp
```
If you haven't got OpenSSL and libconfig installed, opkg will complain when installing, so you'd better go ahead and download/build and then install them first.

Then install it with opkg:
```
# opkg install umurmur-openssl_0.2.x-y.ipk
```
Then take a minute to create a configuration, see the [Configuring02x](Configuring02x.md) page.

Make sure it is started at bootup:
```
# /etc/init.d/umurmur enable
```

Then if you don't want to restart the router, you need to start up uMurmur with
```
# /etc/init.d/umurmur start
```

You can check the log to see if it started up OK. Use the command `logread`.

## Installing uMurmur with PolarSSL support ##
Pretty much the same procedure as above but the package is called `umurmur-polarssl_0.2.x-y.ipk`.

One important difference to note though: the PolarSSL version of uMurmur doesn't generate a self-signed certificate and key automatically if it can't find it at the configured paths. It will use a predefined test-certificate and key instead, **but this is very insecure!**. The secret part of the RSA key isn't secret at all when you use the test certificate. A big fat warning will be printed to the log if the test certificate and key is used. You should generate a self-signed certificate and RSA key and move them to the target machine. This is actually pretty simple to do. You need to have OpenSSL for this (not on the target machine):
```
# openssl genrsa 1024 > my_key.key
# openssl req -new -x509 -nodes -sha1 -days 365 -key my_key.key > my_selfsigned_cert.crt
# scp my_key.key root@<router address>:/etc/umurmur/
# scp my_selfsigned_cert.crt root@<router address>:/etc/umurmur/
```
Update the configuration file to reflect the location and names of the certificate and key and you're done.

# Other platforms #
  * [Install on DD-WRT](http://code.google.com/p/umurmur/wiki/DDWRT)