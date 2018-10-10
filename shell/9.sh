#!/bin/bash
#echo "password for root:"
#read root_pwd
#echo $root_pwd |sudo -s mkdir user1
#mkdir user1
total=0
echo -e "./:\n">content
for file1 in $(ls .)
do
	#echo $file1
	if [ -d $file1 ]
	then
		sum=0
		echo "./$file1">>content
		for file2 in $(ls ./$file1)
		do
			if [[ ${file2##*.} = c || ${file2##*.} = h ]] 
			then
			num=$(echo $(wc -l<./$file1/$file2))
			echo "  $file2  line_num: $num ">>content
			sum=`expr $sum + $num`
			fi
		done
		total=`expr $total + $sum`
		echo -e  "dir_sum:$sum\n">>content
	fi
done
echo "total:$total">>content
