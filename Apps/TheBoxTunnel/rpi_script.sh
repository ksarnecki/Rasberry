#!/bin/bash

DEFAULT_ROUTE=$(ip route show default | awk '/default/ {print $3}')

while true; do
  PORT="`wget -qO- http://m.lekseek.com/thebox/list`"
  sleep 3s
  ./rpi_main.exe m.lekseek.com $PORT $DEFAULT_ROUTE 80
done