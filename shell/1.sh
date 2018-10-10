#!/bin/bash
:<< !
echo 'select operate:lower| upper | quit | exit'
read operate
case $operate in
	lower) 
	echo "input string please"
	read str >content
	cat content |tr A-Z a-z
	cat content
	upper)
	quit)
	exit)break
!
:<< !
converse()
{
	echo "first param :$1"
	echo "input string"
	read str
	echo $str >content
	if [ $1 = upper ]
	then
		echo "result:$(cat content |tr a-z A-Z)"
	else
		echo "result:$(cat content |tr [:upper:] [:lower:])"
	fi
	echo "char number:"
	num1=$(wc -c< content)
	echo "total char num:$num1"
	echo $(cat content |tr -d " ")>content
	#echo $str >content
	num2=$(wc -c < content)
	echo "exclude space :$num2"
	echo "exclude space and NULL :$((`expr $num2 - 1`))"
}
!

converse()
{
	echo "input string"
	read str
	if [ $1 = upper ]
	then
		echo $str |tr a-z A-Z
	else
		echo $str |tr A-Z a-z
	fi
	str=$(echo $str |tr -d " ")
	echo ${#str}

}

while :
do
	echo "select operate"
	read operate
	case $operate in
		lower)
		converse $operate
		;;
		upper)
		converse $operate
		;;
		quit|exit|*)break
		;;
	esac
done




























