# Setup the PI for debugging

1. On the Pi, follow these
   [steps](https://www.losant.com/blog/getting-started-with-the-raspberry-pi-zero-w-without-a-monitor)
   to set it  up.
    1. make sure to update it which takes ~45 mins
1. Update again
    `sudo apt-get update`
1. Install node js
    `sudo apt-get install nodejs`
1. Install rabbit mq server
    1. Install dependencies: `sudo apt-get install socat erlang logrotate`
    1. Look for releases here:
       https://github.com/rabbitmq/rabbitmq-server
       >!! Releases must be compatible with Erlang
    1. Get the release:
        `wget https://github.com/rabbitmq/rabbitmq-server/releases/download/rabbitmq_v3_6_10/rabbitmq-server_3.6.10-1_all.deb`
    1. Use dpack to install
        `sudo dpkg -i rabbitmq-server_3.6.10-1_all.deb`
1. install pika under current user and sudoer
    * `pip3 install pika`
    * `sudo pip3 install pika`
1. create `beetree` directories on pi
    * `mkdir -p ~/beetree/tools`
    * `mkdir -p ~/beetree/foundations/trace`
    * `mkdir -p ~/beetree/exchange/registry`
1. From your beetree workspace...
    1. copy beeview directory into `~/beetree/tools`
        * `scp -r tools/beeview pi@raspberrypi.local:~/beetree/tools`
    1. copy `manifest.json` into `~/beetree/exchange/registry`
        * `scp exchange/registry/manifest.json pi@raspberrypi.local:~/beetree/exchange/registry`
    1. copy `trace-tokens-map.json` into `~/beetree/foundations/trace`
        * `scp foundations/trace/trace-tokens-map.json pi@raspberrypi.local:~/beetree/foundations/trace`
        
    1. you may have to use pi@<ip>: and remove local. This will require a password.
    
1. connect usb port to nucleo board
1. run it
    * `sudo ./beetree/tools/beeview/run-beeview /home/pi/beetree /dev/ttyACM0 --disable_rabbit -p=80`
    * *This assumes the nucleo serial port is at `/dev/ttyACM0`*
    * `--disable_rabbit` option does not try to start rabbitmq server from the command line since an instance is already running on the command line.
    
    




### Links
- [Getting Started With Raspberry Pi - No Monitor](https://www.losant.com/blog/getting-started-with-the-raspberry-pi-zero-w-without-a-monitor)
- [Adafruit](https://learn.adafruit.com/raspberry-pi-zero-creation?view=all)