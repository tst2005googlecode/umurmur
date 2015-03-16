# Example configuration #

_Note:_
  1. The `max_bandwidth` parameter unit is **bits/second** (changed from 0.1.x) per user.
  1. The Root channel bust be defined first in the channel list.
  1. The child channels _must_ have their parent channel defined before in the list.

Example configuration file:

```
max_bandwidth = 48000;
welcometext = "Welcome to uMurmur!";
certificate = "/etc/umurmur/cert.crt";
private_key = "/etc/umurmur/key.key";
ca_path = "/path/to/ca/certificates/";  # Location of CA certificate. Relevant for OpenSSL only.

password = "";
admin_password = "test";   # Set to enable admin functionality.
ban_length = 0;            # Length in seconds for a ban. Default is 0. 0 = forever.
enable_ban = false;        # Default is false
banfile = "banfile.txt";   # File to save bans to. Default is to not save bans to file.
sync_banfile = false;      # Keep banfile synced. Default is false, which means it is saved to at shutdown only.
allow_textmessage = true;  # Default is true
opus_threshold = 100;      # Required percentage of users that support Opus codec for it to be chosen
max_users = 10;

# bindport = 64738;
# bindaddr = "192.168.1.1";

# bindport6 = 64738;
# bindaddr6 = "fde4:8dba:82e1::/48";

# username and groupname for privilege dropping.
# Will attempt to switch user if set. 
# username = "";
# If groupname not set the user's default login group will be used
# groupname = "";

# Log to file option. Default is logging to syslog.
# umurmurd will close and reopen the logfile if SIGHUP is received.
# logfile = "/var/log/umurmurd.log";

# Channel tree definition:
# Root channel must always be defined first.
# If a channel has a parent, the parent must be defined before the child channel(s).
channels = ( {
	 name = "Root";
	 parent = "";
	 description = "Root channel. No entry.";
	 noenter = true;
	 },
	 {
	 name = "Lobby";
	 parent = "Root";
	 description = "Lobby channel";
	 },
	 {
	 name = "Red team";
	 parent = "Lobby";
	 description = "The Red team channel";
     # password = "redpw";
	 },
	 {
	 name = "Blue team";
	 parent = "Lobby";
	 description = "The Blue team channel";
     # password = "bluepw";
	 },
	 {
	 name = "Silent";
	 parent = "Root";
	 description = "Silent channel";
         silent = true;
         position = -1; # Will appear before 'lobby' channel in the client's channel tree
	 }
);
# Channel links configuration.
channel_links = ( {
	 source = "Lobby";
	 destination = "Red team";
	 },
	 {
	 source = "Lobby";
	 destination = "Blue team";
	 }
);

# The channel in which users will appear in when connecting.
# Note that default channel can't have 'noenter = true' or password set
default_channel = "Lobby";
```
## General configuration parameters ##
Many parameters are optional and have default values.

Parameters with a version number within [.md](.md) means that was the version of uMurmur the parameter was added.


Optional parameters with defaults within parenthesis:
  * `max_bandwidth` (48000)
  * `welcometext` ("Welcome to uMurmur!")
  * `certificate` ("/etc/umurmur/certificate.crt")
  * `private_key` ("/etc/umurmur/private\_key.key")
  * `ca_path` (NULL) [0.2.14]
  * `password` ("" = empty)
  * `max_users` (10)
  * `default_channel` (root channel)
  * `bindaddr` (INADDR\_ANY = all addresses the host is assigned)
  * `bindport` (64738)
  * `bindaddr6` (INADDR\_ANY = all addresses the host is assigned) [0.2.15]
  * `bindport6` (64738) [0.2.15]
  * `admin_password` ("" - if not set no admin functions enabled) [0.2.9]
  * `ban_length` (0 = forever) (seconds) [0.2.9]
  * `enable_ban` (false) [0.2.9]
  * `banfile` ("" = none) [0.2.9]
  * `sync_banfile` (false) [0.2.9]
  * `allow_textmessage` (true) [0.2.9]
  * `opus_threshold` (100) [0.2.11]

## Channels configuration ##
In the channel configuration `name` and `parent` are required. The `noenter`, `password` and `description` parameters are optional where `noenter` defaults to `false`, `description` and `password` to "". Other optional parameters are `silent` which is either `true` or `false` (default) and `position` which is an integer and defaults to 0.1

The noenter parameter controls whether a channel can be entered or not. This can be useful when grouping channels together in a 'folder', e.g. a game name.

A channel with `silent` set to true will be exactly that, silent. No speech will be transmitted.

The `position` parameter will control where the channel will appear in the clint's channel tree. The default is 0 and the channels will then be sorted alphabetically.

Summary of channel parameters:
  * `name` (required)
  * `parent` (required)
  * `noenter` (optional)
  * `password` (optional) [0.2.8]
  * `description` (optional)
  * `silent` (optional) [0.2.14]
  * `position` (optional) [0.2.14]

## Channel links configuration ##
Channel links is a one-way duplication of speech from one channel to another when whispering to the channel. It is not neccesary to configure this unless you need it. An example usage, as demonstrated in the example configuration above, is to make all speech whispered to the lobby also be directed to the team channels. The speech in the team channels is **not** directed to the lobby.

In `channel_links`, both `source` and `destination` parameter are required.