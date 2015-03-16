uMurmur should be able to be built on any remotely POSIX-compliant platform.

Make sure you have the required libraries installed: libconfig, libprotobuf-c and OpenSSL or PolarSSL.

To build with OpenSSL:
```
./configure --with-ssl=openssl
make
make install
```
To build with PolarSSL:
```
./configure --with-ssl=polarssl
make
make install
```

Note that Protobuf-C can be built using `./configure --disable-protoc`. This will only build the runtime library and you are relieved of the dependency on Protobuf.

### List of packages (from debian repo) required to compile umurmur on debian ###

```
aptitude install libconfig8 libconfig++8
aptitude install libconfig8-dev libconfig++8-dev
aptitude install protobuf-c-compiler  protobuf-compiler  libprotobuf-c0 libprotobuf-c0-dev
aptitude install libssl-dev
```


## Build instructions for for version uMurmur 0.2.6 and earlier ##
To build with OpenSSL:
Make sure you have OpenSSL and development packages installed. Enter the 'src' subdirectory and issue a 'make'. If any package is installed in a nonstandard place you need to edit the Makefile.

To build with PolarSSL:
Edit the Makefile to reflect the location of PolarSSL and uncomment the PolarSSL-relevant lines. Comment the OpenSSL-relevant lines. libconfig development package need to be installed. Issue 'make'.

## Build for OpenWRT ##
Note that umurmur is available as a package in OpenWRT. Check the package repository.

To build for OpenWRT you need a Linux/Unix-like host. Cygwin under Windows is not supported. Use a linux dist image with VMWare or some other virtual machine if you don't have a spare Linux build server (but everyone has one, don't they ;)

Something along the line of:
  1. Follow instructions on openwrt.org to clone/checkout the OpenWRT sources and build it for your particular platform.
  1. Update the package lists: `scripts/feeds update base && scripts/feeds update packages`
  1. Install umurmur `scripts/feeds install -d m umurmur-polarssl`
  1. To use another version edit feeds/packages/net/umurmur/Makefile. Be sure to update the MD5 checksum.
  1. Build it `make package/umurmur/compile`
  1. Package shall end up under the `bin/<platform>/packages/` directory.

## Build for SheevaPlug ##

Make sure you have the build-essential package.

`sudo apt-get install build-essential `

You can start in whatever fold you like, but I started at home, for simplicity.

`mkdir ~/murmur cd murmur`

Next we get the source for umurmur, and untar it. (make sure to grab the most recent version. 0.2.6 is the most recent as of writing this.

`wget http://umurmur.googlecode.com/files/umurmur-0.2.6.tar.gz && tar xfz umurmur-0.2.6.tar.gz`

Next we need to get the most recent libconfig from hyperrealm.com. I'm not sure if this is the most efficient way, but it works.
```
wget http://www.hyperrealm.com/libconfig/libconfig-1.4.6.tar.gz && tar xfz libconfig-1.4.6.tar.gz 
cd libconfig-1.4.6 
```
I had to use sudo because of a permission denied error in /tmp.

`sudo ./configure`

Then we make it to get our libconfig.h

`sudo make`

Then we install, so the lconfig library gets where it needs to be. (sorta)

`sudo make install`

Then copy the lib/libconfig.h to the umurmur/src directory.

`cp lib/libconfig.h ../umurmur-0.2.6/src/ `

On my little plug, it decided to put lconfig in /usr/local/lib, so I needed to move it so the umurmur make could find it.

`sudo cp /usr/local/lib/libcon* /usr/lib/ `

Now, we make sure we are in the umurmur source directory.

`cd ~/murmur/umurmur-0.2.6/src`

then, just make. (or sudo make, if you have any problems.) make After it finishes, list your directory, and you should see umurmurd. yay!