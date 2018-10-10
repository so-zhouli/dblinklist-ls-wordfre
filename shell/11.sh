#!/bin/bash
echo -e "input an integer:\c"
read i
j=1
if [ $i -eq 0 ]
then
	echo "0 has no factor"
elif [ $i -lt 0 ]
then
	i=`expr 0 - $i `
fi
while(( $j<=$i ))
do
	t=`expr $i % $j `
	if [ $t -eq 0 ]
	then
		echo $j `expr 0 - $j`
	fi
	let "j++"
done
