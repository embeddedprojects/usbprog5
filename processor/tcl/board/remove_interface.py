with open("../../openocd.rc","r") as r:
	lines=r.

for line in lines:
	with open(line,'r') as r:
		tmp_lines=r.readlines()
	with open(line,'w') as w:
		for tmp_line in tmp_lines:
			if "interface" in line or "Interface" in line :
				pass
			else:
				w.write(tmp_line)
