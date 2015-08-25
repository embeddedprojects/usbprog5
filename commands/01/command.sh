#!/bin/bash -e

array RESULT

ls ../
RESULT[0]=$?

python afa
RESULT[1]=$?

echo $RESULT


for x in $RESULT; do {
echo "result is $x"
if [ $x -eq 0 ]; then {
	echo "ok"
	
	
};
else {
exit $x
}

fi
}
done
exit 1
