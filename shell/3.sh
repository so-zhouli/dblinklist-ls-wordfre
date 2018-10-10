#!/bin/bash
i=1
j=1
touch content$j
while read line
do
	if [ $i -gt 5 ]
	then
		i=1
		let "j++"
		touch content$j
	fi
	echo $line >>content$j
	let "i++"
done < content

