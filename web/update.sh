#!/bin/bash
sudo killall python
sudo killall openocd
tar xvzf /var/www/tmp/update.tar.gz -C /  
sync
touch /tmp/update_done
chmod 777 /tmp/update_done
chmod +x /var/www/updatescript.sh
sudo /var/www/updatescript.sh

chmod +x /root/server.py
sudo /root/server.py &
exit 0
