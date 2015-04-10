import subprocess

m16="python ../client/embeddedprog.py --processor m16 -v "
logtext=""
status_gesamt="Status:\n\n"

def go(code):
	output=""
	statuss='not'
	exe=str(m16+code)
        p = subprocess.Popen(exe,shell=True ,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)

	while statuss!='done':
		out=p.stdout.read(16)
		output=output+out
		if out == '' and p.poll() != None:
			statuss='done'

			return output

def log(test,text,status=""):
	global logtext, status_gesamt
	status_gesamt=status_gesamt+status+"\n"
	logtext=logtext+test+"\n\n"+text+"\n\n\n\n"
	
def printlog():
	global logtext, status_gesamt
	with open('./log_avr.txt','w') as w:
		w.write(status_gesamt+"\n\n------------------------------------\n\n")
		w.write(logtext) 

def signature():
	returnv=1
	status="Signature: OK"
	out=go("--signature")
	print out
	if "ERROR" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "ERROR" in line:
				status=status+line+"\n"
		returnv=0
	if "Error" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "Error" in line:
				status=status+line+"\n"
		returnv=0
	if "AVR device not responding" in out:
		status = "Signature Error: AVR device not responding"
		returnv=0
	if "initialization failed, rc=-1" in out and status == "Signature: OK":
		status = "Signature Error: initialization failed, rc=-1"
		returnv=0
	if "0x1e9403" not in out and status == "Signature: OK":
		status = "Signature Error: Wrong Signatur Read"
		returnv=0
	if "error" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "error" in line:
				status=status+line+"\n"
		returnv=0
	if "Yikes!" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "Yikes!" in line:
				status=status+line+"\n"
		returnv=0
	if "not found" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "not found" in line:
				status=status+line+"\n"
		returnv=0		
	if "timeout" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "timeout" in line:
				status=status+line+"\n"
		returnv=0
	log("read signature:",out,status)
	return returnv	



def flash_read():
	returnv=1
	status="Flash-Read: OK"
	out=go("--flash-read flash.hex")
	print out
	if "ERROR" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "ERROR" in line:
				status=status+line+"\n"
		returnv=0
	if "Error" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "Error" in line:
				status=status+line+"\n"
		returnv=0
	if "error" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "error" in line:
				status=status+line+"\n"
		returnv=0
	if "Yikes!" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "Yikes!" in line:
				status=status+line+"\n"
		returnv=0
	if "not found" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "not found" in line:
				status=status+line+"\n"
		returnv=0		
	if "timeout" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "timeout" in line:
				status=status+line+"\n"
		returnv=0
	log("flash_read:",out,status)
	return returnv

def flash_write():
	returnv=1
	status="Flash-Write: OK"
	out=go("--flash-write flash.hex")
	print out
	if "ERROR" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "ERROR" in line:
				status=status+line+"\n"
		returnv=0
	if "Error" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "Error" in line:
				status=status+line+"\n"
		returnv=0
	if "error" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "error" in line:
				status=status+line+"\n"
		returnv=0
	if "Yikes!" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "Yikes!" in line:
				status=status+line+"\n"
		returnv=0
	if "not found" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "not found" in line:
				status=status+line+"\n"
		returnv=0		
	if "timeout" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "timeout" in line:
				status=status+line+"\n"
		returnv=0
	log("flash_write:",out,status)
	return returnv

def eeprom_read():
	returnv=1
	status="eeprom-Read: OK"
	out=go("--eeprom-read eeprom.hex")
	print out
	if "ERROR" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "ERROR" in line:
				status=status+line+"\n"
		returnv=0
	if "Error" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "Error" in line:
				status=status+line+"\n"
		returnv=0
	if "error" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "error" in line:
				status=status+line+"\n"
		returnv=0
	if "Yikes!" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "Yikes!" in line:
				status=status+line+"\n"
		returnv=0
	if "not found" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "not found" in line:
				status=status+line+"\n"
		returnv=0		
	if "timeout" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "timeout" in line:
				status=status+line+"\n"
		returnv=0
	log("eeprom_read:",out,status)
	return returnv

def eeprom_write():
	returnv=1
	status="eeprom-Write: OK"
	out=go("--eeprom-write eeprom.hex")
	print out
	if "ERROR" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "ERROR" in line:
				status=status+line+"\n"
		returnv=0
	if "Error" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "Error" in line:
				status=status+line+"\n"
		returnv=0
	if "error" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "error" in line:
				status=status+line+"\n"
		returnv=0
	if "Yikes!" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "Yikes!" in line:
				status=status+line+"\n"
		returnv=0
	if "not found" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "not found" in line:
				status=status+line+"\n"
		returnv=0		
	if "timeout" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "timeout" in line:
				status=status+line+"\n"
		returnv=0
	log("eeprom_write:",out,status)
	return returnv

def fuse_read(low,high):
	returnv=1
	status="Fuse-Read: OK"
	out=go("--fuse-read-low --fuse-read-high")
	print out
	if low not in out:
		status ="Fuse-Read/Write Error: previosly written fusebits werent accepted"

		returnv=0	
	if high not in out:
		status ="Fuse-Read/Write Error: previosly written fusebits werent accepted"

		returnv=0
	if "ERROR" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "ERROR" in line:
				status=status+line+"\n"
		returnv=0
	if "Error" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "Error" in line:
				status=status+line+"\n"
		returnv=0
	if "error" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "error" in line:
				status=status+line+"\n"
		returnv=0
	if "Yikes!" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "Yikes!" in line:
				status=status+line+"\n"
		returnv=0
	if "not found" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "not found" in line:
				status=status+line+"\n"
		returnv=0		
	if "timeout" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "timeout" in line:
				status=status+line+"\n"
		returnv=0
	log("fuse_read:",out,status)
	return returnv

def fuse_write(low,high):
	returnv=1
	status="Fuse-Write: OK"
	out=go("--fuse-write-low "+low+" --fuse-write-high "+high)
	print out
	if "ERROR" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "ERROR" in line:
				status=status+line+"\n"
		returnv=0
	if "Error" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "Error" in line:
				status=status+line+"\n"
		returnv=0
	if "error" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "error" in line:
				status=status+line+"\n"
		returnv=0
	if "Yikes!" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "Yikes!" in line:
				status=status+line+"\n"
		returnv=0
	if "not found" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "not found" in line:
				status=status+line+"\n"
		returnv=0		
	if "timeout" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "timeout" in line:
				status=status+line+"\n"
		returnv=0
	log("fuse_write:",out,status)
	return returnv

def delete():
	returnv=1
	status="Delete: OK"
	out=go("--delete")
	print out
	if "ERROR" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "ERROR" in line:
				status=status+line+"\n"
		returnv=0
	if "Error" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "Error" in line:
				status=status+line+"\n"
		returnv=0
	if "error" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "error" in line:
				status=status+line+"\n"
		returnv=0
	if "Yikes!" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "Yikes!" in line:
				status=status+line+"\n"
		returnv=0
	if "not found" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "not found" in line:
				status=status+line+"\n"
		returnv=0		
	if "timeout" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "timeout" in line:
				status=status+line+"\n"
		returnv=0
	log("delete:",out,status)
	return returnv

def lockbits_read(bits):
	returnv=1
	status="Lockbits-Read: OK"
	out=go("--lockbits-read")
	print out
	if bits not in out:
		status= "Lockbits Error: Expected other lockbits"

	if "ERROR" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "ERROR" in line:
				status=status+line+"\n"
		returnv=0
	if "Error" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "Error" in line:
				status=status+line+"\n"
		returnv=0
	if "error" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "error" in line:
				status=status+line+"\n"
		returnv=0
	if "Yikes!" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "Yikes!" in line:
				status=status+line+"\n"
		returnv=0
	if "not found" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "not found" in line:
				status=status+line+"\n"
		returnv=0		
	if "timeout" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "timeout" in line:
				status=status+line+"\n"
		returnv=0
	log("lockbits_read:",out,status)
	return returnv

def lockbits_write(lockbits):
	returnv=1
	status="Lockbits-Write: OK"
	out=go("--lockbits-write "+lockbits)
	print out
	if "ERROR" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "ERROR" in line:
				status=status+line+"\n"
		returnv=0
	if "Error" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "Error" in line:
				status=status+line+"\n"
		returnv=0
	if "error" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "error" in line:
				status=status+line+"\n"
		returnv=0
	if "Yikes!" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "Yikes!" in line:
				status=status+line+"\n"
		returnv=0
	if "not found" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "not found" in line:
				status=status+line+"\n"
		returnv=0		
	if "timeout" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "timeout" in line:
				status=status+line+"\n"
		returnv=0
	log("lockbits_write:",out,status)
	return returnv



running=signature()
if running==1:
	running=flash_read()

if running==1:
	running=eeprom_read()



if running==1:
	a="0xc1"
	b="0xd9"
	running=fuse_write(a,b)
if running==1:
	running=fuse_read(a,b)
if running==1:
	c="0xe4"
	running=fuse_write(c,b)
if running==1:
	running=fuse_read(c,b)


if running==1:
	running=lockbits_read("0x3f")
if running==1:
	running=lockbits_write("0x1f")
if running==1:
	running=lockbits_read("0x1f")


if running==1:
	running=flash_read()


if running==1:
	running=delete()


if running==1:
	running=lockbits_read("0x3f")

if running==1:
	running=flash_write()
if running==1:
	running=eeprom_write()
if running==0:
	print "Error occured in Testing pls look at the logfile for more details"
printlog()

