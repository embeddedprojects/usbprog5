#! /usr/bin/env python

import subprocess

exe="python return_test.py"

p = subprocess.Popen(exe,shell=True ,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
#echo "##############################################################################\n################################################################################"


out=p.stdout.read(1024)
print out
print "##############################################################################\n################################################################################"

p.communicate()


exitcode = p.returncode

print exitcode 

