#encoding:utf-8
import os
import sys
import subprocess
import json
import string
from collections import defaultdict
code=[]
def test():	
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
	
test()
print code
