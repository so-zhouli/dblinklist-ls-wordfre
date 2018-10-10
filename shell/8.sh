#!/bin/bash
find_risk_file()
{
	i=0
	perm=777
	for file in $(find $1 -perm $perm)
	do
		let "i++"
		echo "$file is at risk"
		chmod 754 $file
	done
	if [ $i -eq 0 ]
	then 
		echo "there is no file at risk in $1"
	fi
}

if [ $1 ]
then
	for path in "$@"
	do
		echo $path
		find_risk_file $path
		echo " "
	done
else
	find_risk_file "."
fi

