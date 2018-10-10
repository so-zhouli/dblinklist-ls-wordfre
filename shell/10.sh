#!/bin/bash
if [ $1 ] 
then
	cd $1
else    # path not input 
	cd .
fi
for file in $(ls .)
do
	if [[ -f $file && -x $file ]]
	then
		cat $file |while read line
		do
			str1=$(echo ${line:1:3})
	#		echo $str1
			str=$(echo $(ls -l $file))
			if [ $str1 !=  ELF ]
			then
				echo $file ${str:0:10} 
			fi
			break
		done
	fi
done
