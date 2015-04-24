import os

with open("../../openocd.rc","r") as r:
	lines=r.readlines()

for line in lines:
	line=line.replace("\n","")
	#print line+".cfg"
	if os.path.isfile(line+".cfg") :
		print "isfile"
		with open(line+".cfg",'r') as r:
			tmp_lines=r.readlines()
		with open(line+".cfg",'w') as w:
			print line+".cfg"
			for tmp_line in tmp_lines:
				if "interface" in tmp_line or "Interface" in tmp_line :
					pass
					print tmp_line
				if "transport select hla_jtag" in tmp_line:
					pass
					print tmp_line
				else:
					w.write(tmp_line) 
