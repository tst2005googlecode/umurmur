Configuring uMurmur really is pretty simple and self explanatory if you aren't allergic to text configuration files. The only tricky things I can think of is:
  1. The `max_bandwidth` parameter unit is bytes/second per user.
  1. The Root channel bust be defined first.
  1. The channels _must_ have their parent channel defined before in the list.

Example configuration file:

```
max_bandwidth = 5000;
welcometext = "Welcome to fatbob's uMurmur server!";
certificate = "/etc/umurmur/cert.crt";
private_key = "/etc/umurmur/key.key";
password = "";
max_users = 10;

channels = ( {
         name = "Root";
         parent = "";
         description = "The Root of all channels";
         },
         {
         name = "COH";
         parent = "Root";
         description = "Company of heroes";
         },
         {
         name = "Axis";
         parent = "COH";
         description = "The Axis channel";
         },
         {
         name = "Allies";
         parent = "COH";
         description = "The Allies channel";
         }
);
default_channel = "COH";
```