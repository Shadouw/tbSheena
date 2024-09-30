# tbSheena

Sheena Is A Punk Rocker Bot. 

She can be added to a Telegram group and answers with predefined phrases whenever she reads a word she knows.


## Talk to the BotFather to create a new bot

- Give it a name and a username, remember the token. The token *must never* be shared.
- Disable "Group Privacy" to allow it to read group messages

## Build container

You can compile Sheena inside docker. Please clone with sub modules, e.g. `git clone --recurse-submodules git@github.com:Shadouw/tbSheena.git`. 
The following command builds a container named ```sheena``` and compiles her:
```docker build -t sheena .```

Afterwards Sheena can run inside this container, e.g. on a Raspberry Pi.

## Run Sheena

I run Sheena with docker-compose:

```yaml
version: "2"
services:
  sheena:
      image: sheena
      # In this example the container data is located in /docker/tbsheena
      volumes:
          - /docker/tbsheena:/etc/tbsheena
      # Please use your own token
      command: tbsheena -t 123456:ABC-DEF1234ghIkl-zyx57W2v1u123ew11
      restart: unless-stopped
```

Copy the ```configexample/phrases.txt``` into your local config folder, modify it and run your container.

## Dependencies
 - https://github.com/slowriot/libtelegram
