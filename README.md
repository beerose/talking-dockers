# talking-dockers

## What does it do?

* Creates two docker containers attached to the same network.

* One is sender and the second is receiver.

* Sender sends UDP packets to receiver.

* Receiver receives UPD Packets from sender.

Kinda boring.

## How to test it?

* Only on macOS.

* Only with iTerm.

* Create network:
``` 
docker network create --driver=bridge --subnet=172.28.5.0/16 net
```
* Run ``` ./setup.sh ```
