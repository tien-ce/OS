#!/bin/bash
history_file=/home/tien/Desktop/file_txt/history.txt
while true; do
echo -n "Nhap phep tinh: "
read -r num1 op num2 
#echo "num1 = $num1"
#echo "op = $op"
#echo "num2 = $num2"
#if [[ $input =~ ^([0-9]+)[[:space:]]*([+\-/%\*])[:space:]*([0-9]+)$ ]]; then
if [[ $num1 == "HISTORY" ]]; then
	cat $history_file
fi
if [[ $num1 == "EXIT" ]]; then
	exit 0
fi
if [[ $num1 == "ANS" ]]; then
	num1="$ANS"
fi
if [[ $op == "*" ]]; then
	export ANS=$(echo "$num1 * $num2" | bc)
elif [[ $op == "+" ]]; then
	ANS=$(echo "$num1 + $num2" | bc)
elif [[ $op == "-" ]]; then
	ANS=$(echo "$num1 - $num2" | bc)
elif [[ $op == "/" ]]; then
	if [[ $num2 == "0" ]]; then
 	   	echo "MATH ERROR"
	   	return 0
	else
	   ANS=$(echo "scale=2; $num1 / $num2" | bc)
	fi
elif [[ $op == "%" ]]; then
	ANS=$(echo "$num1 % $num2" | bc)
else
	echo "SYNTAX ERROR"
	exit 1
fi 
	echo "$num1 $op $num2 = $ANS" >> "$history_file"
	tail -n 5 "$history_file" > /home/tien/Desktop/file_txt/temp_history.txt && mv /home/tien/Desktop/file_txt/temp_history.txt "$history_file"
	echo "$ANS"
read  -n 1 anything
clear
done