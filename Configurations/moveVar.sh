#!/bin/bash

MNT=/media/pi/rootfs/
TARGET=$MNT/var

mkdir $TARGET

sudo rsync -av /var/ $TARGET

sudo ln -s  $TARGET/log log

sudo ln -s  $TARGET/lib lib

#edit /etc/fstab
#get uuid of disk
sudo ls -l /dev/disk/by-uuid/

UUID=3384282c-d684-404d-8eb1-69a1a94dc7e8       $MNT       ext4    nofail,defaults   0   0

