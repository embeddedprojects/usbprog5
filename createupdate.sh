
mkdir -p /tmp/build/var/www/tmp
mkdir -p /tmp/build/root/avrdude-6.1
mkdir -p /tmp/build/root/openocd-code/src
mkdir -p /tmp/build/root/openocd-code/tcl/target
mkdir -p /tmp/build/root/openocd-code/tcl/board
mkdir -p /tmp/build/root/openocd-code/tcl/interface
mkdir -p /tmp/build/root/makeprocessor/tcl/target
mkdir -p /tmp/build/root/makeprocessor/tcl/board


cp  update/updatescript.sh /tmp/build/var/www

cp  processor/processor.php /tmp/build/var/www
cp  processor/avrdude.rc /tmp/build/var/www
cp  processor/openocd.rc /tmp/build/var/www
cp  processor/makeprocessor.py /tmp/build/root/makeprocessor
cp  processor/add-processor.txt /tmp/build/root



cp  web/server.php /tmp/build/var/www
cp  web/client.php /tmp/build/var/www
cp  web/render.php /tmp/build/var/www
cp  web/index.php /tmp/build/var/www
cp  web/embeddedprog.php /tmp/build/var/www
cp  web/download.php /tmp/build/var/www
cp  web/jquery.min.js /tmp/build/var/www
cp  web/jquery.flexselect.js /tmp/build/var/www
cp  web/liquidmetal.js /tmp/build/var/www
cp  web/flexselect.css /tmp/build/var/www
cp  web/download_icon.png /tmp/build/var/www
cp  web/icon_help.png /tmp/build/var/www
cp  web/update.php /tmp/build/var/www
cp  web/embedded_zeichen.jpg /tmp/build/var/www
cp  web/atmel_einstellungen.png /tmp/build/var/www

cp version /tmp/build/root/version



cp  server/server.py /tmp/build/root/server.py

cp -r openocd-0.9.0/src/openocd /tmp/build/root/openocd-code/src/

cp -r openocd-0.9.0/tcl/interface /tmp/build/root/openocd-code/tcl/

cp -r  processor/tcl /tmp/build/root/openocd-code/

cp avrdude-6.1/avrdude /tmp/build/root/avrdude-6.1
cp processor/avrdude.conf /tmp/build/root/avrdude-6.1

cp client/embeddedprog.py /tmp/build/var/www/tmp
cp client/windows/installer/setup.exe /tmp/build/var/www/tmp

cd /tmp/build
chmod -R 777 /tmp/build/ 
tar cvfz update.tar.gz var/ root/ 
cd -
mv /tmp/build/update.tar.gz update/

rm -r /tmp/build




