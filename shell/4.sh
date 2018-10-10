#!/bin/bash
#cd /home/zhouli/
#tar -zcf dbll`date +%Y-%m-%d`.tar.gz DBLL   #在zhouli这个文件夹下
#mv /home/zhouli/dbll`date +%Y-%m-%d`.tar.gz /home/zhouli/debug
#cd /
tar -zcf /home/zhouli/debug/`date +%Y-%m-%d-%H:%M`.tar.gz /etc
#find /home/zhouli/debug -mtime +7 -name '*.gz' -ok rm -f {} \;
find /home/zhouli/debug -mmin +7 -name '*.gz' -exec rm -f {} \;
