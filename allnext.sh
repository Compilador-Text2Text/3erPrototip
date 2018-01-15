#!/bin/bash

s=$1
i=0

while [[ 0 != ${#s} ]]
do
	printf "%s	%3d\n" $s $i
	s=`./interpret -f codi/next.my_obj -q -a 1 $s`
	i=$((i+1))
done
