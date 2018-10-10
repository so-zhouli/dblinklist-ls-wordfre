#!/bin/bash
:<< !
str=abc
echo hello
echo 'hello'
echo "hello"
echo 'hello\nhello'
echo -e "hello\nhello"
echo '$str'
echo "$str"
printf "%s\n" abc1
printf "%s\n" abc2 abc3
printf %s abc4 
printf abc5
!




:<< !   
// << ! need spaces
for i in "$*";do
	echo $i//相当于一个参数
done
for i in "$@";do
	echo $i//相当于n个参数
done  //传递参数
!

:<< !
val=`expr 2 + 2`
echo $val
//运算
!

:<< !
file="/home/zhouli/debug/content"
echo   "hello\nworld" > /home/zhouli/debug/content
#echo "world" > $file
echo  "hello\nworld 1" >/home/zhouli/debug/content
//输出至文件，但第二次会覆盖第一次的
!
:<< !
a=0
for file in $(ls -a /home)
do
	a=`expr $a + 1`
	echo $file
done
echo $a
!

:<< !
a=0
for file in $(ls -a /home)
do
	let "a++"
#let command exit in bash,not sh
	echo $file
done
echo $a
!

:<< !
echo 'input number between 1 to 4'
read num
case $num in
	1) echo 'choose 1'
	;;
	2) echo 'choose 2'
	;;
	3) echo 'choose 3'
	;;
	4) echo 'choose 4'
	;;
	*) echo 'other number'
	;;
esac
!



:<< !
funwithparam()
{
	echo "first param $1 !"
	echo "second param $2 !"
	echo "3rd param $3 !"
	echo "10th param ${10}"
#more then 10 need {}
	echo "11th param ${11} !"
	echo "total:$#"
	echo -e "$*\n$@"
	echo "$?"
	num1=1
	num2=2
	return $((`expr $num1 + $num2`))
}
funwithparam 1 2 3 4 5 67 8 0 4 55 33 2 3 
echo "returned num :$? !"
!


:<< !
who > content
cat content
echo "end" >> content
!

:<<
read str
wc -c << EOF
$str
EOF
echo $str |tr a-z A-Z
!

:<<
i=1
filename=user$i
echo $filename
!


:<<
ls -a .
cd /home
ls -a.
!



:<<
cd /home
echo "password for root"
read root_pwd
echo $$root_pwd |sudo -s mkdir filename
!

:<< !
i=0
a=2
array[$i]=0
array[$i]=`expr $a\*$a`
echo ${array[*]}//显示内容 2*2



i=0
a=2
array[$i]=0
array[$i]=$((`expr $a\*$a`))
echo ${array[*]}//显示4
!


:<< !
file=1.sh
extention=${file##*.}//获取后缀名
filename=${file%.*}//获取文件名

echo $extention #sh
echo $filename  #1
!

:<< !
i=-1
i=`expr 0 - $i`   #取反
echo $i
! 

















