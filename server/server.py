#! /usr/bin/env python
import socket
import sys
import os
import subprocess
import json
import base64
import struct, fcntl
from collections import defaultdict
import threading
import signal
import pwd, os




#start socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('', 8888)
print >>sys.stderr, 'starting up on %s port %s' % server_address
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind(server_address)
print sock.getsockname()
sock.listen(1)
inn = 'start'

#create an backup for file
def backup_file (code):
	try:
		if code['v']>=1:
			print "rw"
		with open(str(code),'r+') as r:
			with open("-"+str(code)+"-backup",'w') as w:

				buf=r.read()
				w.write(buf)
				return 1
	except:
		return 0


#restore an file from backup not used atm
def restore (code):
	if code['v']>=1:
		print "rw"
	with open("-"+str(code['name'])+"-backup",'r+') as r:
		with open(str(code['name']),'w') as w:

			buf=r.read()
			w.write(buf)


#read and send output in realtime
def realtime(connection,p,code):
	statuss='start'
	if code['v']>=2:
                print "read and transmit output"
	while statuss!='done':
		if code['v']>=3:
                	print "read"
		out=p.stdout.read(16)
		if code['v']>=3:
                        print "send"
		connection.sendall(out)
		if code['v']>=3:
                        print ""
		if out == '' and p.poll() != None:
		        if code['v']>=2:
                		print "realtime finished"
			statuss='done'
			if code['web']!=True:
				connection.sendall('\xa4')
			return statuss


#recieves file file (not used in browser)
def recieve_file(code,connection ):
	if code['v']>=1:
		print "recieve file"
	statusr=connection.recv(16)
	if statusr== 'send':
		connection.sendall('rdy')
		if code['v']>=2:
			print "open"
		line=" "
		with open('/tmp/'+str(code['name']),'wb') as f:
			if code['v']>=2:
				print "start while"
			line=connection.recv(8192)
			
    			while '\xa7' not in line:
				if code['v']>= 3:
					print "write to file"
                                f.write(line.decode('base64'))
                                f.flush()
				if code['v']>= 3:
					print ""
                                line=connection.recv(8192)
				

			if code['v']>=2:
				print "while finished"
			
			f.write(line.decode('base64'))
			if code['v']>=2:
				print "send"
			connection.sendall('done')
			if code['v']>=2:
                                print "done"
			return statusr




#sends file to client (not used in browser)
def send_file(code , sock):
        sock.sendall('send')
	if code['v']>=1:
		print "send file"
        buf = sock.recv(16)
	#print buf,"lalala"
        if buf == ('rdy'):
		if code['v']>=2:
			print "open"
                with open('/tmp/'+str(code['name']),'rb') as f:
			#print buf
                        buf=f.read()
			b=base64.b64encode(buf)
                        sock.sendall(b)
	if code['v']>=2:
		print "done"
	sock.sendall('\xa7')
	buf= sock.recv(16)
	if buf == 'done':
		return 0
	return -1


#starts subprocess and realtime()
def go(code,connection):
	if code['v']>=1:
		print "go"
	exe=str(code['execute'])
        p = subprocess.Popen(exe,shell=True ,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
	if code['v']>=2:
                print "subprocess started"
	realtime(connection,p,code)
	
	

#named set file becouse the client sets an file
def set_file(code,connection):
    if code['web']!=True:
	recieve_file(code,connection)
	if code['v']>=1:
		print "set_file"


#named set file becouse the client sets an file
def set_file_execute(code,connection):
    if code['web']!=True:
	if code['v']>=1:
		print "set_file_execute"
        recieve_file(code,connection)
	if code['v']>=1:
		print "vor go"
    go(code,connection)
	

#named set file becouse the client sets an file
def set_file_execute_w_only(code,connection):
    if code['web']!=True:	
	if code['v']>=1:
		print "set_file_execute_w_only"
        recieve_file(code,connection)		
        exe=str(code['execute'])
        p = subprocess.Popen(exe,shell=True )

#named get file becouse the client gets an file	
def get_file(code,connection):
    if code['web']!=True:
	if code['v']>=1:
		print "get_file"
	send_file(code,connection)


#decodes json code
def decodejson(content):
        print "decode"
        decoded=json.loads(str(content))
	if decoded['v']>2:
		print decoded
        return decoded





#choses a mode (avrdude,openocd)
def processor(code,connection):
	if code['v']>=1:
		print "look for atmel-studio"
	if code['processor']== None:
	
		if code['atmel-studio'] == None: 
			if code['v']>=1:
				print "no atmel-studio"            	
			
		else:
			if code['v']>=1:
				print "atmel-studio == ",code['atmel-studio']
			with open('/var/www/tmp/processor') as f:
				lines=f.read().splitlines()
				try:
					if (lines[3] == '') or (lines[3] == 'None') or ('Search' in lines[3]):
						connection.sendall("{'v':"+str(code['v'])+",'mode':'browser','msg':'to use this program an processor needs to be set','eeprog-ip':'"+code['eeprog-ip']+"'}")
						
						return code
				
					else:
						code['processor']=lines[3]
					code['voltage']=lines[1]
					code['speed']=lines[2]
					code['flash-write']=code['atmel-studio']
				except:
					connection.sendall("{'v':"+str(code['v'])+",'mode':'browser','msg':'to use this program an processor needs to be set','eeprog-ip':'"+code['eeprog-ip']+"'}")
					return code
	if code['v']>=1:
		print "choose mode via processor"
	with open('/var/www/openocd.rc','r') as f:
		print "render avr"
		processoropenocd=f.read().splitlines()
	with open('/var/www/avrdude.rc','r') as f:
		print "render ocd"
		processoravr=f.read().splitlines()
	if code['show-all'] or code['processor']== None:
		if code['processor']== None:
			if code['web']!=True:
				connection.sendall("{'v':"+str(code['v'])+",'mode':'show','msg':'to use this program an processor needs to be set'}")
                d = dict()
		d['mode']='show-all'
		d['v']=0
                a = ['1', '2']
                for i in processoravr:
                        d.setdefault("avr", []).append(i)
		for i in processoropenocd:
			d.setdefault("ocd",[]).append(i)
		d['mode']='show-all'	
		connection.sendall(str(d))



	else:
	  if code['mode'] != None:
		if code['v']>=1:
			print "mode = " ,code['mode']
	  else:
		if code['processor'] in processoravr:
			code['mode']='avrdude'
			if code['v']>=1:
				print "avrdude"
		else:
			if code['processor'] in processoropenocd:
				code['mode']='openocd'
				if code['v']>=1:
					print "openocd"	


	                else:	 
				if code['web']!=True:
                        		connection.sendall("{'v':"+str(code['v'])+",'mode':'show','msg':'to use this program an processor needs to be set'}")
               			print "AVR :"
                		d = dict()
                		d['mode']='show-all'
              			d['v']=0
                		
                		for i in processoravr:
                        		d.setdefault("avr", []).append(i)
                
                		for i in processoropenocd:
                        		d.setdefault("ocd",[]).append(i)
                

                		connection.sendall(str(d))



	return code


#prototype for live 2 way communication
def live_input(p,connection):
	inn=' '
	
        while '/done' not in inn:
		
                p.stdinn.write(inn+'\n')
		connection.recv(1024)

		
	inn, ignored ,status =out.partition('/')
	p.stdin.write(inn+'\n')




#prototype for live 2 way communication
def golive(code,connection):
        exe=str(code['execute'])
        p = subprocess.Popen(exe,shell=True )
	

	if code['telnet']:
		exe="telnet 127.0.0.1 "+str(code['telnet-port'])
	x = subprocess.Popen(exe,shell=True ,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,stdin=subprocess.PIPE)

	t1=threading.Thread(target=live_input,args=(x,connection))
        #realtime(connection,x)
	t1.daemon=True

        t1.start()
	realtime(connection,x)

	#t1_stop.set()
	#t1_stop.clear()




#logic
def logica(code,connection):
	path=''
	if code['mode']=='conf':
		return 'done'
	if code['v']>=2:
		print "logic"
        if code['mode'] == None:
                	print " kein processor"

			return " "


#
#AVRdude(AVR)
#
	if 'avrdude' in code['mode']:
		#kills openocd and unexports used ports 
		os.system('killall openocd')

#oneliners (fuses + delete)

		if code['v']>=2:
			print "avr dude"
		lisr=[]
		if code	['gdb']!= None:
			connection.sendall("{'v':"+str(code['v'])+",'msg':'gdb not aviable for avrdude'}")
			return
		if code['speed']>3:
			print "speed setting error, set to default (1)"
			code['speed']=1
		if code['speed']<1:
			print "speed setting error, set to default (1)"
			code['speed']=1
		if code['speed']==1:
			code['speed']='1'
		if code['speed']==2:
			code['speed']='5'
		if code['speed']==3:
			code['speed']='10'
		if code['v']>=1:
			print "after speed settings"






		code['execute']="/root/avrdude-6.1/avrdude -p "+code['processor']+" -c usbprog5 -i "+code['speed']


		if code['v']>=2:
			print code['execute']
		if code['delete']:
			code['execute']=code['execute']+" -e"
		if code['fuse-read-low']:
			if code['v']>=1:
				print "read fuse-low"
			code['execute']=code['execute']+" -U lfuse:r:-:h"		
			if code['v']>=2:
				print code['execute']		
		if code['fuse-read-high']:
			if code['v']>=1:
				print "read fuse-high"
			code['execute']=code['execute']+" -U hfuse:r:-:h"
			if code['v']>=2:
				print code['execute']
		if code['fuse-read-extended']:
			if code['v']>=1:
				print "read fuse-extended"
			code['execute']=code['execute']+" -U efuse:r:-:h"
			if code['v']>=2:
				print code['execute']
			if code['v']>=2:
				print code['execute']



		if code['fuse-write-low']!= None:
			if code['v']>=1:
				print "write fuse-low"
			code['execute']=code['execute']+" -U lfuse:w:"+code['fuse-write-low']+":m"
			if code['v']>=2:
				print code['execute']
		if code['fuse-write-high']!= None:
			if code['v']>=1:
				print "write fuse-high"
			code['execute']=code['execute']+" -U hfuse:w:"+code['fuse-write-high']+":m"
			if code['v']>=2:
				print code['execute']	
		if code['fuse-write-extended']!= None:
			if code['v']>=1:
				print "write fuse-extended"
			code['execute']=code['execute']+" -U efuse:w:"+code['fuse-write-extended']+":m"
                	if code['v']>=2:
				print code['execute']

 
		if code['v']>=2:
			print "nach fuse"

#eeprom read        
		if code['eeprom-read']!= None:
			if code['v']>=1:
				print "read eeprom"

			nameer=code['eeprom-read']
                       	if './'  in nameer:
                               	hel , ignored, nameer=nameer.partition('./')

               		else:
                               	while '/'  in nameer:
                                       	part,hel,nameer=nameer.partition('/')
					if code['v']>=3:
						print nameer
                                       	path=path+part+hel
					if code['v']>=3:
						print "current path =",path
					
			if '.bin'in nameer:
				ende=":b"
			elif '.hex'in nameer:
				ende=":i"
			else:
				ende =":a"


			lisr.append("er")
			code['execute']=code['execute']+" -U eeprom:r:/tmp/"+nameer+ende+" -E vcc,reset"
			if code['v']>=2:
				print code['execute']	
		


#eeprom write
                if code['eeprom-write']!= None:
			if code['v']>=1:
				print "write eeprom"
              
                   

                        nameew=code['eeprom-write']
                        if './'  in nameew:
                                hel , ignored, nameew=nameew.partition('./')
                             
                        else:
                                while '/'  in nameew:
                                        part,hel,nameew=nameew.partition('/')
                                        path=path+part+hel


                        if '.bin'in nameew: 
                                ende=":b"
                        elif '.hex'in nameew: 
                                ende=":i"
                        else:   
                                ende =":a"
			if code['web']!=True:
				connection.sendall("{'v':"+str(code['v'])+",'mode':'set_file','path':'"+code['eeprom-write']+"'}")

			code['name']=nameew
			set_file(code,connection)
			if code['load']!=0:
				if code['web']!=True:
					code['execute']=code['execute']+" -U eeprom:w:"+'"/tmp/'+nameew+'"'+ende		
				else:			
					code['execute']=code['execute']+" -U eeprom:w:"+'"/var/www/save/'+nameew+'"'+ende
			else:
				code['execute']=code['execute']+" -U eeprom:w:"+'"/var/www/tmp/'+nameew+'"'+ende


			
			
			if code['v']>=2:
				print code['execute']
                        
			
		if code['v']>=3:
			print "after eeprom write"

#flash read
                if code['flash-read']!= None:
			if code['v']>=1:
				print "read flash"
            

                       	namefr=code['flash-read']
                        if './'  in namefr:
                                hel , ignored, namefr=namefr.partition('./')

                        else:
				if code['v']>=3:
					print "vor partition"
					print "namefr == name of file, flash read"
					print "name fr=",namefr 
                                while '/'  in namefr:
                                        part,hel,namefr=namefr.partition('/')
					if code['v']>=3:
						print namefr
                                        path=path+part+hel
					if code['v']>=3:
						print "current path =",path

			if code['v']>=2:
				print "nach path"
				print "path =",path
				print "namefr =",namefr 
                        if '.bin'in namefr: 
                                ende=":b"
                        elif '.hex'in namefr: 
                                ende=":i"
                        else:   
                                ende =":a"

	


			code['execute']=code['execute']+" -U flash:r:/tmp/"+'"'+namefr+'"'+ende
			if code['v']>=2:
				print code['execute']
			lisr.append("fr")
          
			print "nach fr"
	

#flash write		
                if code['flash-write']!= None:
			if code['v']>=1:
				print "write flash"



                        namefw=code['flash-write']
	
                        if './'  in namefw:
                                hel , ignored, namefw=namefw.partition('./')
        
                        else:
                                while '/'  in namefw:
                                        part,hel,namefw=namefw.partition('/')
                                        path=path+part+hel

	
                        if '.bin'in namefw: 
                                ende=":b"
                        elif '.hex'in namefw: 
                                ende=":i"
			elif '.elf' in namefw:
				ende=":i"
                        else:   
                                ende =":a"
			if code['web']!=True:
				connection.sendall("{'v':"+str(code['v'])+",'mode':'set_file','path':'"+code['flash-write']+"'}")
				
			code['name']=namefw
                        set_file(code,connection)
			if '.elf' in namefw:
            			subprocess.call(['avr-objcopy','-O', 'ihex', '/tmp/'+namefw, '/tmp/output.hex'])
				namefw='output.hex'
			if code['load']!=0:
				if code['web']!=True:
					code['execute']=code['execute']+" -U flash:w:"+'"/tmp/'+namefw+'"'+ende		
				else:			
					code['execute']=code['execute']+" -U flash:w:"+'"/var/www/save/'+namefw+'"'+ende
			else:
				code['execute']=code['execute']+" -U flash:w:"+'"/var/www/tmp/'+namefw+'"'+ende
			print code['name']	
			if code['v']>=2:
				print code['execute']
	

	
#prototype for raw input
		if code['raw']!= None:
			print "try raw"
			code['execute']="avrdude "+code['raw']


		#print code['v']
		if code['web']!=True:
			connection.sendall("{'mode':'go','v':" + str(code['v']) + "}")
		
		go(code,connection)



#flash read addition for browser (move file, set file as www data)
		if code['flash-read']!= None:
			print "filename =",namefr
			if code['web'] == True:
				subprocess.call(['/bin/mv', '/tmp/'+namefr, '/var/www/tmp/'+namefr])
				subprocess.call(["chmod", "777",  "/var/www/tmp/"+namefr])
				subprocess.call(["chown", "-cR", "www-data:www-data", "/var/www/tmp/"+namefr])	

#eeprom read addition for browser (move file, set file as www data)
		if code['eeprom-read']!= None:
			print "filename =",nameer
			if code['web'] == True:
				subprocess.call(['/bin/mv', '/tmp/'+nameer, '/var/www/tmp/'+nameer])
				subprocess.call(["chmod", "777",  "/var/www/tmp/"+nameer])
				subprocess.call(["chown", "-cR", "www-data:www-data", "/var/www/tmp/"+nameer])


		if "fr" in lisr:
			if code['v']>=1:
				print "flash-read"
				print "speicherort== "+code['flash-read']
			if code['web']!=True:
				connection.sendall("{'v':"+str(code['v'])+",'mode':'get_file','path':'"+code['flash-read']+"'}")
			if code['v']>=2:
				print "nach send all"
			code['name']=namefr
			if code['web']!=True:
				get_file(code,connection)
		if "er" in lisr:
			if code['v']>=1:
				print "eeprom-read"
				print "speicherort= ",code['eeprom-read']
			if code['web']!=True:
				connection.sendall("{'v':"+str(code['v'])+",'mode':'get_file','path':'"+code['eeprom-read']+"'}")
			code['name']=nameer
			if code['web']!=True:
				get_file(code,connection)
			#subprocess.call('/bin/rm', '/root/'+nameer)




#
#Openocd(ARM)
#	
	if "openocd" in  code['mode']:



		if code['flash-read']!=None:
			connection.sendall("{'v':"+str(code['v'])+",'msg':'flash-read not implemented for openocd'}")
			return
		if code['delete']:
			connection.sendall("{'v':"+str(code['v'])+",'msg':'delete flash not  implemented for openocd'}")
			return
		if code['v']>=1:
			print "openocd"

		code['execute']='/root/openocd-code/src/openocd -f /root/openocd-code/tcl/interface/embeddedprog.cfg -f /root/openocd-code/tcl/target/'+code['processor']+'.cfg'
		if code['dump']!= None:
			code['execute']=code['execute']+' -c "init;halt;'+code['dump']+';exit"'

#starts gdb for eclipse debugging
		if code['eclipse']==True:
				with open('/var/www/tmp/port','r') as r:
					gdb=r.readline()
					gdb.replace('\n','')
					gdb.replace('\r','')
					tel=r.readline()
				subprocess.Popen(['/root/openocd-code/src/openocd','-f','/root/openocd-code/tcl/interface/embeddedprog.cfg','-f','/root/openocd-code/tcl/target/'+code['processor']+'.cfg','-c','telnet_port '+tel+';gdb_port '+gdb])

#start/stop gdb/telnet
		if code['gdb']!= None:
		
			if code['v']>=2:
				print "gdb ==",code['gdb'] 
			
			if (code['gdb']=='stop') :
			
					subprocess.call(['killall', 'openocd'])
					if code['web']!=True:
						connection.sendall("{'v':"+str(code['v'])+",'mode':'exit'}")
					return
			if (code['gdb']=='start'):
				with open('/var/www/tmp/port','r') as r:
					gdb=r.readline()
					gdb.replace('\n','')
					gdb.replace('\r','')
					tel=r.readline()
				subprocess.Popen(['/root/openocd-code/src/openocd','-f','/root/openocd-code/tcl/interface/embeddedprog.cfg','-f','/root/openocd-code/tcl/target/'+code['processor']+'.cfg','-c','telnet_port '+tel+';gdb_port '+gdb])
		
				if code['web']!=True:
					connection.sendall("{'v':"+str(code['v'])+",'mode':'exit'}")
				return
		if code['flash-write'] != None:
			if code['v']>=1:
				print "write flash"
            

                        namefw=code['flash-write']
                
                        if './'  in namefw:
                                hel , ignored, namefw=namefw.partition('./')
                                print "./" ,namefw
                        else:
                                while '/'  in namefw:
					if code['v']>=2:
						print namefw
                                        part,hel,namefw=namefw.partition('/')
					if code['v']>=2:
						print part,hel,path
                                        path=path+part+hel

             

                        if '.elf'in namefw:
                                ende="reset"
			elif '.hex' in namefw:
				ende="reset"

                        else:
                                ende ="reset"

			code['name']=namefw
			if code['web']!=True:
                        	connection.sendall("{'v':"+str(code['v'])+",'mode':'set_file','path':'"+code['flash-write']+"'}")
                        if code['v']>=2:
                                print "vor setfile"
	
                        set_file(code,connection)
		




			if code['load']!=0:
				if code['web']!= True:
					code['execute']=code['execute']+' -c "init;reset halt;program  /tmp/'+code['name']+" "+ende+';init;resume"'
				else:
					code['execute']=code['execute']+' -c "init;reset halt;program  /var/www/save/'+code['name']+" "+ende+';init;resume"'
     			
			else:
				code['execute']=code['execute']+' -c "init;reset halt;program  /var/www/tmp/'+code['name']+" "+ende+';init;resume"'
		else:
			#if code['eclipse']==True:
			#	code['execute']=code['execute']+' -c "init";resume'
			#else:
			code['execute']=code['execute']+' -c "init;exit;quit"'
#prototype raw input
                if code['raw']!= None:
			print "try raw mode"
                        code['execute']="/home/eproo/openocd-0.8.0-rc1/src/openocd -f /home/eproo/openocd-0.8.0-rc1/tcl/interface/ftdi/olimex-arm-usb-ocd.cfg "+code['raw']
		if code['web']!=True:
                	connection.sendall("{'v':"+str(code['v'])+",'mode':'go'}")
                go(code,connection)

		if code['web']!=True:
			connection.sendall("{'v':"+str(code['v'])+",'mode':'exit'}")	


def conf (code):
	if code['v']>=1:
		print "conf"
	if(code['rename']!=None):
		try:
			with open("/var/www/save/eeprog.rc",'r') as r:
                                        i=0
					lines=r.readlines()

					for line in lines:
					
                                        	if i==int(code['load']):
                                                	new=line
                                                i=i+1
                                               
		except:
                            pass
		codeneu=json.loads(new)
		codeneu['desc']=code['rename']
		i=0
		with open("/var/www/save/eeprog.rc",'w') as w:

			for line in lines:
				
				if i==int(code['load']):
					w.write(json.dumps(codeneu)+"\n")
				else:
					w.write(line)
				i=i+1
		code['mode']='conf'
		return code





#asking if the input+conf should be saved for later use
	if(code['safe']!=None):

#saving tmp data from browser
		print code
		if code['v']>=2:
			print "code safe = ",code['safe']
		if code['web'] == '':
			code['web']=True
		if code['web'] == None:
			code['web']=True

		if(('/tmp.' in code['safe'])and(code['flash-write']!=None)):
			if code['v']>=2:
                		print "safe conf = ",code['flash-write']
			if code['eeprom']==1:
				code['eeprom-write'] = code['flash-write']
				code['flash-write'] = None
				

                	f=open("/var/www/save/eeprog.rc","r")
                	lines=f.readlines()

                	f.close()
                	f=open("/var/www/save/eeprog.rc","w")
                	i=0
                	for line in lines:
                        	
                        	if i!=0:
                                	f.write(line)
				else:
					f.write(json.dumps(code)+"\n")
				i=i+1
                	f.close()
			code['mode']='conf'
			return code

#saving tmp  data + input as profile
		else:
			code['desc']=code['safe']
                        with open("/var/www/save/eeprog.rc",'r') as r:
                                i=0                                
                                line=r.readline()
                        safe=json.loads(line)
			if safe['eeprom']==1:
				code['eeprom']=1
				safe['backflash']=safe['eeprom-write']
				while os.path.isfile("/var/www/save/"+safe['eeprom-write']):
					safe['eeprom-write']=safe['backflash']
					i=i+1
					safe['eeprom-write']=safe['eeprom-write']+'('+str(i)+')'
				code['eeprom-write']="/var/www/save/"+safe['eeprom-write']
				safe['flash-write'] = safe['eeprom-write']
				ende=code['eeprom-write']
					
			else:
				code['eeprom']=0
				safe['backflash']=safe['flash-write']

				while os.path.isfile("/var/www/save/"+safe['flash-write']):
					safe['flash-write']=safe['backflash']
					i=i+1
					safe['flash-write']=safe['flash-write']+'('+str(i)+')'
				code['flash-write']="/var/www/save/"+safe['flash-write']
				ende=code['flash-write']
			
			while '.' in ende:
				path, ignored,ende=ende.partition('.')
			if code['v']>=2:
				print safe['safe']
				print safe['flash-write']
			subprocess.call(['cp', safe['safe'] ,'/var/www/save/'+safe['flash-write']])
			with open("/var/www/save/eeprog.rc",'a') as a:
				a.write(json.dumps(code)+"\n")

			code['mode']='conf'
			os.system("chmod 777 /var/www/save/*")
			return code

#asking if an config should be deleted(if yes it will be deleted)
	elif(code['del-conf']!=None):
		if code['v']>=1:
			print "del conf = ",code['del-conf']

		f=open("/var/www/save/eeprog.rc","r")
		lines=f.readlines()
	
		f.close()
		f=open("/var/www/save/eeprog.rc","w")
		i=0
		for line in lines:
			if ((code["del-conf"] == 0)and(i<1)):
				f.write('{"load": null, "fuse-write-low": null, "fuse-read-extended": false, "fuse-write-extended": null, "signature": false, "raw": null, "gdb": null, "eeprog_port": null, "flash-write": null, "speed": 2, "processor": null, "del-conf": null, "flash-read": null, "safe": null, "show-all": false, "fuse-read-high": false, "eeprog-port": 8888, "desc": null, "fuse-write-high": null, "eeprom-write": null, "fuse-read-low": false, "eeprog_ip": null, "eeprog-ip": "127.0.0.1", "mode": null, "v": 0, "eeprom-read": null, "delete": false, "web": true,"rename": null,"dump": null,"voltage": 3}\n')
			else:	
				if (i)!=(code["del-conf"]):
					f.write(line)
				else :
					rm=json.loads(line)
					print line
					print rm['eeprom']
					if rm['eeprom'] == 0:
						subprocess.call(['rm', rm['flash-write'] ])				
					else:
						subprocess.call(['rm', rm['eeprom-write'] ])
			i=i+1
		f.close()
		code['mode']='conf'
		code['v']=0

        else:
#asking if an saved config should be loaded, if yes it is loaded
		if(code['load']!=None):
			line=""
			if code['v']>=2:
				print code['processor']
				print code['load']
			try:
                		with open("/var/www/save/eeprog.rc",'r') as r:
                        		i=0
			
					
					
                        		while i<(int(code['load'])+1):
                                		line=r.readline()
                                		i=i+1
						print i,line
			except:
				pass
			codeneu=json.loads(line)
			
			if code['load']==0:
				if code['v']>=2:
					print "code load ==",code['load']
					print "old save -> write"
					
				if codeneu['eeprom']==0:	
                        		codeneu['flash-write']=codeneu['safe']
					
				else:
					codeneu['eeprom-write']=codeneu['safe']
			codeneu['load']=code['load']	
			code=codeneu
			
		return code



#prototype change ip
def change_ip():
	if code['ip']!= None:
		call(['ifconif','usb0',code['ip']])
		code['mode']='conf'



def change_voltage (code):
	if code['voltage'] == 3:
		subprocess.call(["/bin/sh", "/root/3V3.sh"])
	if code['voltage'] == 1:
		subprocess.call(["/bin/sh", "/root/1V8.sh"])
	if code['voltage'] == 5:
		subprocess.call(["/bin/sh", "/root/5V0.sh"])
	return



try:

	subprocess.call(["/bin/rm", "/var/www/tmp/processor"])
	subprocess.call(["touch", "/var/www/tmp/processor"])
	subprocess.call(["chmod", "777", "/var/www/tmp/processor"])
	with open("/var/www/tmp/processor",'w') as w:
		w.write("0\n3\n1\nSearch Processor ...\n")
	subprocess.call(["/bin/rm", "/tmp/gdb_runs"])
	subprocess.call(["touch", "/tmp/update_done"])
	subprocess.call(["chmod", "777", "/tmp/update_done"])
	subprocess.call(["chown", "-cR", "www-data:www-data", "/tmp/update_done"])	

except:
	pass
try:
#if 1==1:
	while inn!='kill':
		
		print >>sys.stderr, 'waiting for a connection'
		connection, client_address = sock.accept()
		try:
		#if 1==1:	

		
			inn = connection.recv(2048)
			
			print >>sys.stderr, 'connection from', client_address

			code=decodejson(inn)
			code=conf(code)
			
			code=processor(code,connection)
			change_voltage (code)

		  	logica(code,connection)	
	
			if code['web']!=True:
				connection.sendall("{'v':"+str(code['v'])+",'mode':'exit'}")
			print "connection closed"
			connection.close()



#try:
		#try:
			pass
		except Exception as e: 
			print "error"
			print >>sys.stderr , 'connection closed', client_address
			print e
			import traceback, os.path
    			exc_type, exc_obj, exc_tb = sys.exc_info()
    			fname = os.path.split(exc_tb.tb_frame.f_code.co_filename)[1]
    			print(exc_type, fname, exc_tb.tb_lineno)
       		

		
		
		finally:
			subprocess.call(["sync"])
			connection.close()


except:
	sock.close()


finally:
	subprocess.call(["/bin/rm", "/tmp/update_done"])
	print "programm beendet"
