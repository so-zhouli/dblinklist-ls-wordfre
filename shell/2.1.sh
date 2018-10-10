#!/bin/bash
i=1
user=$USER
#echo $user
cd /home/$user
while(( $i<=$1 ))
do
	filename=user$i
	if [ -e $filename ]
	then 
		let "i++"
		continue
	else
		mkdir $filename
	fi
	chmod 754 $filename
done
ls -l
echo "delete y/n"
i=1
read operate
if [ $operate = y ]
then
	while (( $i<= $1 ))
	do
		filename=user$i
		rm -rf $filename
		let "i++"
	done
fi
ls -l
