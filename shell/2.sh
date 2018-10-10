#!/bin/bash
i=1
cd /home
#echo "password for root:"
#read root_pwd
while(( $i<=$1 ))
do 
	filename=user$i
	if  [ -e $filename ]
	then
		let "i++"
		continue
	else
		echo 111111 |sudo -s mkdir $filename
	fi
	echo 111111 |sudo -s chmod 754 $filename
	let "i++"
done
ls -l .
echo "delete y/n"
i=1
read operate
if [ $operate = y ]
then
	while (( $i<=$1 ))
	do
		filename=user$i
		echo 111111 |sudo -s rm -rf $filename
		let "i++"
	done
fi
ls -l .
#rm -rf $filename

