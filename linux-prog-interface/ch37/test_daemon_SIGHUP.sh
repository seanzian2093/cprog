echo START > /tmp/ds.conf
./daemon_SIGHUP
cat /tmp/ds.log
echo CHANGED > /tmp/ds.conf

date +'%F %X'; mv /tmp/ds.log /tmp/old_ds.log
date +'%F %X'; killall -HUP daemon_SIGHUP

ls /tmp/*ds.log
cat /tmp/old_ds.log
cat /tmp/ds.log

killall daemon_SIGHUP