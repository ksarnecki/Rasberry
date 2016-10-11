#!/bin/bash

TARGET=/media/pi/rootfs

sudo -u postgres psql

#SHOW data_directory;
#eg. /var/lib/postgresql/9.4/main

sudo systemctl stop postgresql

sudo rsync -av /var/lib/postgresql $TARGET

sudo vim /etc/postgresql/9.4/main/postgresql.conf

#edit
# << data_direcotry = '/var/lib...' 
# >> data_directory = '/media/pi/rootfs/postgresql/9.4/main'

