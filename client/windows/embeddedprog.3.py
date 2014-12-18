import socket
import sys
import json
import os
import base64
import argparse
import ast
import subprocess
import webbrowser

#opening and returning socket
def connect(sa,port,code):
	try:
		sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		if code['v']>= 2:
			print 'sock = ',sock
		#server_adress = ('ein','test')
		server_address = (sa, port)
		if code['v']>= 1:
			print  'connecting to %s port %s' % server_address
		sock.connect(server_address)
		
	except: 
		print "couldnt connect "+ 'to %s port %s' % server_address

		return "/done"

	return sock

#prototype for 2way communication
def golive(code,sock):
	t1_stop=threading.Event()
        t1=threading.Thread(target=live,args=(decoded['laufzeit'],t1_stop,number,p))
        t1.daemon=True

        t1.start()

        t1_stop.set()   
        t1_stop.clear() 

	return " "

#show the message returned from server
def show (code,sock):
	try:
		print code['msg']
	except:
		pass
	print "done"
	return " "

# show the supported cpu types
def showall(code,sock):
	i=0
	print " "

		
	print "the avr processors:"
	print " "
	for s in code['avr']:
		i+=1
		if i<2:
			if len(s)<8:
				a="\t\t\t"
			elif len(s)<16:
				a="\t\t"
			else:
				a="\t"
			sys.stdout.write(s+a)
		else:
			i=0
			print s
	print " "
	print " "
	print "the openocd processors"
	print " "
	i=0
	for s in code['ocd']:
		i+=1
		if i<3:
		
                        if len(s)<8:
                                a="\t\t\t"
                        elif len(s)<16:
                                a="\t\t"
                        else:
                               	a="\t"
			sys.stdout.write(s+a)
		else:
			i=0
			print s
	return " "



#gets the input and save it in an dictionary
def inpt():



        #try:                                
                parser = argparse.ArgumentParser()


		parser.add_argument("--browser", help="Open The Web Browser of USBprog 5 OpenOCD;", action="store_true")
                parser.add_argument("--processor", help="select target processor;")
		parser.add_argument("--voltage", help="select target voltage (1 for 1V8;3 for 3V3;5 for 5V5)",type=int,default=3)
                parser.add_argument("--eeprog-ip",  help="select target ip (default via usb 10.0.0.1) ;saved in eeprog.cfg")
                parser.add_argument("--eeprog-port",type=int,  help="select target port (default 8888); saved in eeprog.cfg ",default=8888)
                parser.add_argument("--signature",  help="not needed at the time... for signature just input processor only",action="store_true")
                parser.add_argument("--speed",type=int,default=2, help="changes speed; 2 is default setting, 1=(B=1), 2=(B=10), 3=(b=100)")
                parser.add_argument("--atmel-studio", help="(atmel-studio)write flash, needs complete path to file ")		
                parser.add_argument("--flash-read", help="read flash, needs complete path to file ")
                parser.add_argument("--eeprom-read",  help="read eeprom , needs complete path to file")
                parser.add_argument("--fuse-read-low", help="read fuse_low ",action="store_true")
                parser.add_argument("--fuse-read-high", help="read fuse_high ",action="store_true")
                parser.add_argument("--fuse-read-extended", help="read fuse_extended ",action="store_true")
		#parser.add_argument("--fuse-read-all", help="read fuses in following order: low, high, extended ",action="store_true")
                parser.add_argument("--flash-write", help="write flash , needs complete path to file")
                parser.add_argument("--eeprom-write",  help="write eeprom , needs complete path to file")
                parser.add_argument("--fuse-write-low",  help="write fuse_low ")
                parser.add_argument("--fuse-write-high",  help="write fuse_high ")
                parser.add_argument("--fuse-write-extended",  help="write fuse_extended ")
                parser.add_argument("--show-all", help="shows all processors",action="store_true")
                parser.add_argument("--raw",  help='not implemented')
		parser.add_argument("--mode",help="to change mode (openocd,avrdude), it will set itself via the chosen processor")
		parser.add_argument("--safe", help='saves the input for later use')		
		parser.add_argument("--load", help="load saved input, needs an int value", type=int)
		parser.add_argument("--delete", help="delete flash",action="store_true")
		parser.add_argument("--erase", help="delete flash",action="store_true")
		parser.add_argument("--del-conf",help="delete an save from conf, needs int value",type=int)
		parser.add_argument("--desc",help="needed for browser temp conf")
		parser.add_argument("--verbose",'-v',action='count',help="verbose output -v,-vv,-vvv ")
		parser.add_argument("--gdb",help="'start's or 'stop's gdb (openocd)")
		parser.add_argument("--dump",help="Please insert the command in following form: \n mdw [phys] addr [count] \n\n   mdw = 32-bit word\n   mdh = 16-bit halfword\n   mdb = 8-bit byte\n\nWhen the current target has an MMU which is present and active, addr is interpreted as a virtual address. Otherwise, or if the optional phys flag is specified, addr is interpreted as a physical address. If count is specified, displays that many units")
		




		#creating dictionary with default value =none
                args=parser.parse_args()
                lis={   
			"v":None,
			"processor":None,
                        "eeprog_ip":None,
                        "eeprog_port":None,
                        "signature":None,
                        "speed":None,
                        "flash-read":None,
                        "eeprom-read":None,
                        "fuse-read-low":None,
                        "fuse-read-high":None,
                        "fuse-read-extended":None,
			#"fuse-read-all":None,
                        "flash-write":None,
                        "eeprom-write":None,
                        "fuse-write-low":None,
                        "fuse-write-high":None,
                        "fuse-write-extended":None,
                        "show-all":None,
                        "raw":None,
			"mode":None,
			"safe":None,
			"load":None,
			"delete":False,
			"del-conf":None,
			"desc":None,
			"gdb":None,
			"rename": None,
			"dump":None,
			"web":None,
			"voltage":None,
			"browser":False,
			"atmel-studio":None
                }
		#submiting input values into dictionary
		lis["v"]=args.verbose
                lis["processor"]=args.processor
                lis["eeprog-ip"]=args.eeprog_ip
                lis["eeprog-port"]=args.eeprog_port
                lis["signature"]=args.signature
                lis["speed"]=args.speed
                lis["flash-read"]=args.flash_read
                lis["eeprom-read"]=args.eeprom_read
                lis["fuse-read-low"]=args.fuse_read_low
                lis["fuse-read-high"]=args.fuse_read_high
                lis["fuse-read-extended"]=args.fuse_read_extended
		#lis["fuse-read-all"]=args.fuse_read_all
                lis["flash-write"]=args.flash_write
                lis["eeprom-write"]=args.eeprom_write
                lis["fuse-write-low"]=args.fuse_write_low
                lis["fuse-write-high"]=args.fuse_write_high
                lis["fuse-write-extended"]=args.fuse_write_extended
                lis["show-all"]=args.show_all
                lis["raw"]=args.raw
		lis["mode"]=args.mode
		lis["safe"]=args.safe
		lis["load"]=args.load
		lis["delete"]=args.delete
		lis["del-conf"]=args.del_conf
		lis["desc"]=args.desc
		lis["gdb"]=args.gdb
		lis["dump"]=args.dump
		lis["voltage"]=args.voltage
		lis["browser"]=args.browser
		lis["atmel-studio"]=args.atmel_studio


		if args.erase==True:
			lis["delete"]=args.erase

#loading server ip and port from conf file if not inputed
		if lis['eeprog-ip']==None:

			try:
				if lis['v']>= 2:
					print "open file to read ip-config"
				try:
					with open("/var/www/eeprog.rc",'r') as r:
						if lis['v']>= 3:	
							print "getline"
						a=r.readline()
				except:
					pass
				if lis['v']>= 3:
					print "literal"
					print a
				a=ast.literal_eval(a)
				if lis['v']>= 3:
					print a, "dict"
				lis['eeprog-ip']=a['eeprog-ip']
				lis['eeprog-port']=int(a['eeprog-port'])
			except:
				if lis['v']>= 2:
					print "no conf file aviable, you can use --eeprog-ip and --eeprog-port to set the ip and port;default port = 8888;default ip 10.0.0.1"
				lis['eeprog-ip']="10.0.0.1"
				lis['eeprog-port']=8888
		else:
#saving new input values for server ip port in conf file
			if lis['v']>= 2:
				print "saving ip in file"
			try:			
				with open("/var/www/eeprog.rc",'r') as r:
					lines=r.readlines()
			except:
				pass
			with open("/var/www/eeprog.rc",'w') as w:
				w.write("{'eeprog-ip': '"+lis['eeprog-ip']+"' , 'eeprog-port':"+str(lis['eeprog-port'])+"}\n")
				i=0
				try:
					for line in lines:
						if i!= 0:
							w.write(line)
						i=i+1
				except:
					pass
		if 'nt' in os.name:
			if lis['atmel-studio']!=None:
				lis['atmel-studio']=lis['atmel-studio'].replace('\\','/')
			if lis['flash-write']!=None:
				lis['flash-write']=lis['flash-write'].replace('\\','/')	
			if lis['flash-read']!=None:
				lis['flash-read']=lis['flash-read'].replace('\\','/')
			if lis['eeprom-write']!=None:
				lis['eeprom-write']=lis['eeprom-write'].replace('\\','/')
			if lis['eeprom-read']!=None:
				lis['eeprom-read']=lis['eeprom-read'].replace('\\','/')
		return lis

#sends an file in b64 code to server
def send_file(code , sock):
	if code['v']>= 1:
		print "send file"
        sock.sendall('send')
	if code['v']>= 2:
		print "send send to server"
        buf = sock.recv(16)
	if code['v']>= 2:
		print "recieved response from server" 
		print "reply= ",buf
	
	
        if buf == ('rdy'):
		if code['v']>= 2:
			print "open file"
                with open(str(code['path']),'rb+') as f:
			if code['v']>= 3:
				print "read"
                        buf=f.read()
			if code['v']>= 3:
				print "from file = ",buf
				print "sendall in b64"
			b=base64.b64encode(buf)
                        sock.sendall(b)
			if code['v']>= 3:
				print "after sendall"
			#sock.flush()
	if code['v']>= 2:
		print "close file"
	#sock.flush()
	sock.sendall('/done')
	#sock.flush()
	if code['v']>= 2:
		print "waiting for server reply"
        buf= sock.recv(4)
        if buf == 'done':
		if code['v']>= 2:
                	print "reply = done"
                return 0
        return -1


#recieves a file in b64 code from server and saves it in an file
def recieve_file(code,connection):
	if code['v']>= 1:
		print "recieve file"
        statusr=connection.recv(16)
	if code['v']>= 2:
		print "reply from server= ",statusr
        if statusr== 'send':
		if code['v']>= 3:
			print "reply from server == 'send' "
			print "send rdy to server"
                connection.sendall('rdy')
		line=" "
		if code['v']>= 2:
			print "open file"
			
			print str(code['path'])
		if 'nt' in os.name:
				code['path']=code['path'].replace('/','\\')
                with open(str(code['path']),'wb') as f:
			line=connection.recv(8192)
                        while '/done' not in line:
				if code['v']>= 3:
					print "write to file file"
                                f.write(line.decode('base64'))
                                f.flush()
				if code['v']>= 3:
					print ""
                                line=connection.recv(8192) 
                        line, ignored ,statusr =line.partition('/')
			f.write(line.decode('base64'))              
                        connection.sendall('done')
                        return statusr


#recieve realtime output from server(openocd/avrdude output)		
def recieve_realtime(sock,code):
	if code['v']>= 1:
		print "recieve output in 'realtime'" 
	out = ' '
	failsave= ''
	part='nothing'
	while ('/done' not in out) and ('/done' not in failsave):
		failsave=failsave+out
		if '/done' in failsave :
			out, ignored, part =out.partition('/done')
		sys.stdout.write(out)
		sys.stdout.flush()
		if part == 'nothing':
			out=sock.recv(128)
		else:
	 		out, ignored, part =part.partition('/done')
			while '}' not in part:
				part=part+sock.recv(1)
			#sys.stdout.write(out)
			#sys.stdout.flush()
			code=ast.literal_eval(part)
			
			failsave=lisst.get(code['mode'])(code,sock)
			if failsave == '/done':
				sys.exit()
			return 
		
	out, ignored ,status =out.partition('/')
	sys.stdout.write(out)
	sys.stdout.flush()
	
	return status


#prototype for cmd menu 


#def cls():
	#os.system('cls' if os.name=='nt' else 'clear')

#def startup():
#	#cls()
#	path=""
#	lis={
#		"1":"go",
#		"2":"set_file",
#		"3":"set_file_execute",
#		"4":"set_file_execute_w_only",
#		"5":"get_file",
#		"6":"restore_backup",
#		"x":"exit"}
#
#	inp=""
#	while inp not in('1','2','3','4','5','6','x'):
#		cls()
#		print inp
#		print "1 == go //program wird ausgefuehrt\n2 == set_file //eine datei wird zum server uebermittelt\n3 == set_file_execute //eine datei wird uebermittelt,danach das program ausgefuehrt\n4 == set_file_execute_w_only //wie 3 aber die ausgabe des programms wird nicht uebermittelt\n5 == get_file //eine datei wird zurueckgegeben falls vorhanden\n6 == restore_backup //eine datei wird auf dem server wieder hergestellt\n-----------------------------------------------------------------------\nx == exit"
#		#inp=sys.stdin.read(1)
#		inp=raw_input()
#		#sys.stdin.flush()
#	code['mode']=lis[inp]
#	#print code['mode']
#	#clear=sys.stdin.read()
#	if inp == 'x':
#		return 'ende'
#	#lol =sys.stdin.readline()
#	if inp not in ('6','5','2'):
#		cls()
 #    		print "geben sie den auszufuehrenden shell code ein"
  #    		#execu=sys.stdin.readline()
#		execu=raw_input()
 #    		#sys.stdin.flush()
  #  		code['execute']=execu
#	#sys.stdin.readline()
#	if inp != '1':
#		cls()
#		print "geben sie den namen der datei an"
#		#name=sys.stdin.readline()
#		#sys.stdin.flush()
#		name=raw_input()
#		
#		if '/'  in name:
#			if './'  in name:
#				hel , ignored, name=name.partition('./')
#				print name
#			else:
#				while '/'  in name:
#					part,hel,name=name.partition('/')
#					path=path+part+hel
#					
#		code['name']=name
#		code['path']=path
#	print code
#


#
def go(code,sock):
	if code['v']>= 1:
		print "go"
	recieve_realtime(sock,code)
        return " "
def set_file(code,sock):
	if code['v']>= 1:
		print "set_file"
	send_file(code,sock)
        return " "
def set_file_execute(code,sock):
	if code['v']>= 1:
        	print "set_file_execute"
        send_file(code,sock)
	if code['v']>= 2:
        	print "vor go"
        go(code,sock)
        return " "
def set_file_execute_w_only(code,sock):
	if code['v']>= 1:
        	print "set_file_execute_w_only"
        send_file(code,sock)
	return " "
def get_file(code,sock):
	if code['v']>= 1:
        	print "get_file"
        recieve_file(code,sock)
	return " "
def restore_backup(code):
	if code['v']>= 1:
        	print"restore backup"
        restore(code)
	return " "
def exit(code,sock):
	return "/done"
def browser(code,sock):
	try:
		
		print code['msg']
	except:
		pass
	webbrowser.open('http://'+code['eeprog-ip']+'/index.php?software=atmel',new=0,autoraise=True)
	return "/done"

inn=" "

#get input/saved code
code=inpt()
#open Browser
if code['browser'] == True :
	webbrowser.open('http://'+code['eeprog-ip'],new=0,autoraise=True)
#connect port
if code['v']>= 1:
	print "connect port"
sock=connect(code['eeprog-ip'],code['eeprog-port'],code)
#making dictionary for funktion calls per server
lisst={
		"go":go,
                "set_file":set_file,
                "set_file_execute":set_file_execute,
                "set_file_execute_w_only":set_file_execute_w_only,
                "get_file":get_file,
                "restore_backup":restore_backup,
		"exit":exit,
		"show-all":showall,
		"show":show,
		"browser":browser
                }






try:


		code=inpt()
		if code['v']>= 1:
			print "send code to server"
		if code['v']>= 3:
			print "code =="
			print code
			print "in json"
			print json.dumps(code)
			
		sock.sendall(json.dumps(code))
		while "/done" not in inn:
			
			code=" "
			code=sock.recv(8192)
			temp='a'
			if(('show-all' in code)or("'ocd': ['" in code)or("'avr': ['" in code) ):
			 while '}' not in temp :
				temp=sock.recv(8192)
				code=code+temp
			code=ast.literal_eval(code)
			if code['v']>= 2:
				print "order== ",code['mode']
			inn=lisst.get(code['mode'])(code,sock)
		
except Exception as ex: 
	print  'unexpected error'
	print ex
finally:
		sock.close()
