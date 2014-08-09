
mkdir -p /tmp/build/var/www/tmp
mkdir -p /tmp/build/root/avrdude-6.0rc1
mkdir -p /tmp/build/root/openocd-code/src

cp  update/updatescript.sh /tmp/build/var/www

cp  processor/processor.php /tmp/build/var/www
cp  processor/avrdude.rc /tmp/build/var/www
cp  processor/openocd.rc /tmp/build/var/www

cp  web/server.php /tmp/build/var/www
cp  web/client.php /tmp/build/var/www
cp  web/render.php /tmp/build/var/www
cp  web/index.php /tmp/build/var/www
cp  web/embeddedprog.php /tmp/build/var/www
cp  web/download.php /tmp/build/var/www

cp  server/server.py /tmp/build/root/server.py

cp openocd-code/src/openocd /tmp/build/root/openocd-code/src

cp avrdude-6.0rc1/avrdude /tmp/build/root/avrdude-6.0rc1

cp client/embeddedprog.py /tmp/build/var/www/tmp

cd /tmp/build
tar cvfz update.tar.gz var/ root/
cd -
mv /tmp/build/update.tar.gz update/

rm -r /tmp/build




