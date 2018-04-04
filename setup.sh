#!/bin/bash

# docker network create --driver=bridge --subnet=172.28.5.0/16 net

setup_sender() {
    echo "docker rm --force c_sender; docker run -e MODE=sender -it --name c_sender --network net --ip 172.27.5.10 datagram-sockets-sample"
}

setup_receiver() {
    echo "docker rm --force c_receiver; docker run -e MODE=receiver -it --name c_receiver --network net --ip 172.27.5.11 datagram-sockets-sample"
}

split() {
    command_sender=$(setup_sender);
    command_receiver=$(setup_receiver);
    osascript -e 'tell application "System Events" to tell process "Terminal" to keystroke "d" using {command down, shift down}'
    osascript -e "tell application \"System Events\" to tell process \"Terminal\" to keystroke \"${command_sender}\""
    osascript -e 'tell application "System Events" to tell process "Terminal" to key code 52'
    osascript -e 'tell application "System Events" to keystroke key code 126 using {command down, option down}'

    osascript -e 'tell application "System Events" to tell process "Terminal" to keystroke "d" using command down'
    osascript -e "tell application \"System Events\" to tell process \"Terminal\" to keystroke \"${command_receiver}\""
    osascript -e 'tell application "System Events" to tell process "Terminal" to key code 52'
    osascript -e 'tell application "System Events" to keystroke key code 125 using {command down, option down}'
}

docker build -t datagram-sockets-sample .
split
