# Introduction #

This page describes the administrator functions introduced in uMurmur 0.2.9

# How to enable admin users #

Set an admin password in the configuration file:

`admin_password = "<password>";`

Then the user(s) who are assigned as admin(s) should set that password in the 'Tokens' menu in Mumble while connected to the uMurmur server.

_Note that a disconnect-reconnect cycle is **required** after the token is added to enable admin privileges._

When a user having the admin password set as token is connecting, the following line should appear in the uMurmur log:

`User provided admin password - [1] user@xx.xx.xx.xx:nnnnn`

By default the admin user has the following privileges:
  * Move users between channels.
  * Move users to passworded channels which the user doesn't have the password token set.
  * Mute/deafen users.
  * Move to all passworded channels regardless of password.
  * Kick users

To enable ban fuctionality, set the following in the configuration file:

`enable_ban = true;`

The duration of a ban can also be set by:

`ban_length = <time in seconds>;`

By default the duration is 0 = 'forever'. The bans can be edited using the Mumble ban editor where, among other things, the ban duration can be changed.

However, the bans are not saved by default, meaning that uMurmur will forget all bans between restarts. To save bans to a file set the following in the configuration:

`banfile = </path/to/banfile.txt>`;

By default the file is saved to only when `umurmurd` is shut down in a controlled manner (TERM signal received). This means that bans added/removed since start will be lost in case of power failure. To enable continuous sync of the banfile set the following parameter in the configuration:

`sync_banfile = true;`

**Please be aware of your system's limitations before enabling banfile saving and especially banfile sync. If you run uMurmur on a system with flash disk, the number of writes to it might in the long run result in worn out and damaged flash. If you run uMurmur on a NAS, the writes may result in that uMurmur will freeze during HD spin-up, resulting in disconnects and other general mayhem.**