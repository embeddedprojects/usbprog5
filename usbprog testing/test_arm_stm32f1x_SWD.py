import subprocess
import re

m16="python ../client/embeddedprog.py --processor stm32f1x -v --swd on "
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
	with open('./log_arm_swd.txt','w') as w:
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
				print line
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
	log("read signature:",out,status)
	return returnv	

def flash():
	returnv=1
	status="flash-write: OK"
	out=go("--flash-write /home/eproo/test_swd/EmbSys2-master/Software/0_aufgabe_makefile/main.elf")
	print out
	if "ERROR" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "ERROR" in line:
				print line
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
	log("flash write:",out,status)
	return returnv		


def dump():
	returnv=1
	status="dump memory: OK"
	out=go("--dump 'mdw 0 10'")
	print out
	if "ERROR" in out:
		if ": OK" in status:
			status =""
		for line in out.split('\n'):
			if "ERROR" in line:
				print line
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
	log("dump memory:",out,status)
	return returnv		
	
running=signature()
running=flash()
running=dump()


#if running==1:
#	running=flash_read()


if running==0:
	print "Error occured in Testing pls look at the logfile for more details"
printlog()
