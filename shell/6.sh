#!/bin/bash
#file=1.sh
#extention=${file##*.}
#echo $extention
#echo ${file##*.}

i=0
ls .
for file in $(ls .)
do
#	echo $file
	extention=${file##*.}
	if [[ $extention = txt && ! (-s $file) ]]
	then
		rm $file
		let "i++"
	fi
done
echo $i
ls .




