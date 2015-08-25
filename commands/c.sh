#!/bin/bash

#cd /root/commands/

/bin/bash $1/command.sh
RESULT=$?
echo "$RESULT"


exit $RESULT
