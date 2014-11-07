#encoding:utf-8
import os
import sys
import subprocess
import json
import string
from collections import defaultdict

code=[]
vendorlen=5
namelen=0
def readfile():

	global vendorlen
	global namelen
	print "readfile"
	try:
		
		i=0
		with open("./processors.txt",'r') as r:
			lines=r.readlines()
			for line in lines:	
				temp=json.loads(line)
				if len(temp['name'])>namelen:
					namelen=len(temp['name'])
				if len(temp['vendor'])>vendorlen:
					vendorlen=len(temp['vendor'])
				if temp['name']!="":
					if temp['program']=='AVR':
						temp['name']=temp['name']+'&nbsp;('+temp['processor']+')'
					code.append(temp)
					i=i+1
			print code
				
		
		return code
	except Exception as e: 
			print "error"
			print e
    			exc_type, exc_obj, exc_tb = sys.exc_info()
    			fname = os.path.split(exc_tb.tb_frame.f_code.co_filename)[1]
    			print(exc_type, fname, exc_tb.tb_lineno)		
	return 'error'

def parseavr():
	#namelen=0
	global namelen
	template={"processor":"","name":"","vendor":"Atmel","program":"AVR"}
	
	with open("./avrdude.conf",'r') as r:
		out=r.read()
	old="!"
	codeav=[]
	i=0
	#weg, ignored , out =out.partition('#------------------------')
	while old!=out :
		old=out		
		weg, ignored , out =out.partition('#------------------------')
		if 'part parent' in weg:
			if 'deprecated' in weg:
				pass
			elif 'readme.txt' in weg:
				pass
			else:
				weg=filter(lambda x: x in string.printable, weg)
				out=weg+ignored+out
		weg, ignored , out =out.partition('part')
		weg, ignored , out =out.partition('= "')
		tempid, ignored , out =out.partition('";')
		weg, ignored , out =out.partition('= "')
		tempname, ignored , out =out.partition('";')
		#print tempid,tempname
		temp=template
		temp['processor']=tempid
		temp['name']=tempname
		line=json.dumps(temp)
		temp=json.loads(line)
		i=0
	
		if unicode("u'"+temp['name']+"',") in unicode(code):
			#print "avr" ,i,
			#print unicode(temp)
			i=i+1
		else: 
			if temp['name'] != '' and '???' not in temp['name'] :
				temp['name']=tempname+"("+tempid+")"
				code.append(temp)
				#if len(temp['name'])>namelen:
				#	namelen=len(temp['name'])
		
	return code

def parseocd():
	global namelen
	status="test"
	p = subprocess.Popen("ls tcl/target",shell=True ,stdout=subprocess.PIPE)
	template={"processor":"","name":"","vendor":"","program":"ARM"}
	codeoc=[]
	i=0
	while status!='done':
	 temp=template
	 buf=p.stdout.readline()
	 if (".cfg" in buf) or (".tcl" in buf):
		buf,ignored,ignored=buf.partition(".cfg")
		buf,ignored,ignored=buf.partition(".tcl")
		
		temp['processor']=buf
		temp['name']=buf
		line=json.dumps(temp)
		temp=json.loads(line)
		if len(temp['name'])>namelen:
			namelen=len(temp['name'])

		if unicode("u'"+temp['name']+"', ") in unicode(code):
			print "ocd" ,i
			print temp
			i=i+1
		else: 
			if temp['name'] != '':
				code.append(temp)			
	 if buf == '' and p.poll()!= None:
		status='done'
	

	p = subprocess.Popen("ls tcl/board",shell=True ,stdout=subprocess.PIPE)

	codeoc=[]
	i=0
	status="test"
	while status!='done':
		temp=template
		buf=p.stdout.readline()
		buf,ignored,ignored=buf.partition(".cfg")
		buf,ignored,ignored=buf.partition(".tcl")
		temp['processor']=buf
		temp['name']=buf
		line=json.dumps(temp)
		temp=json.loads(line)	
		if len(temp['name'])>namelen:
			namelen=len(temp['name'])
		if unicode("u'"+temp['name']+"',") in unicode(code):
			#print "board" ,i
			#print unicode("u'"+temp['name']+"', ")
			#print temp
			i=i+1
		else: 
			if temp['name'] != '':
				code.append(temp)			
		if buf == '' and p.poll()!= None:
			status='done'
	

			

		
	return code

def makephp():
	i=1
	help=True
	with open('./processor.php','w') as w:
	 with open('./avrdude.rc','w') as a:
	  with open('./openocd.rc','w') as o:
		w.write("<?php\n\n")
		w.write("$processors = array(")
		code.sort(key=lambda name: name)
		test = sorted(code, key=lambda name: name['name'].lower())
		
		while help==True:
			try:
				
				tempid=test[i]['processor']
				tempname=test[i]['name']
				tempvendor=test[i]['vendor']
				tempprogram=test[i]['program']

				if test[i]['program'] == 'AVR':
					a.write(tempid+'\n')

				if test[i]['program'] == 'ARM':
					tempid=filter(lambda x: x in string.printable, tempid)
					o.write(tempid+'\n')
				if len(tempvendor)>2:
					tempvendor=tempvendor+',&nbsp;'
				
				#print "vendorlen",y," == ",len(vendorspace)/6
				tempid=filter(lambda x: x in string.printable, tempid)
				tempprogram=filter(lambda x: x in string.printable, tempprogram)
				tempname=filter(lambda x: x in string.printable, tempname)
				w.write("'"+unicode(tempname)+"&nbsp;("+unicode(tempvendor)+""+unicode(tempprogram)+")'=>'"+unicode(tempid)+"',")
				i=i+1
			except Exception as e: 
			#	print "error"
				
			#	print e,i
    				
				
				help=False
				w.write(")\n?>")
				
readfile()
parseavr()
parseocd()
#print code
makephp()
print ""
print ""
print ""
print ""

