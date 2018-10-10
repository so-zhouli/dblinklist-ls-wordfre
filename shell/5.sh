#!/bin/bash
i=0
array[$i]=0
sum=0
for val in "$@"
do
	array[$i]=$((`expr $val\*val`))
	sum=`expr $sum + ${array[$i]}`
	let "i++"
done
echo ${array[*]}
echo $sum
