#! /bin/bash

#make the directory used be the input directory
dir=$1

#create an array that holds all the files in the directory
declare -a files
i=0

for file in .* *;
do
    files[$i]=$file
    (( i++ ))
done

#check for duplicate files and replace with hardlinks
arrSize=${#files[*]}
k=0
j=0
until [ $k == $arrSize ]
do
    until [ $j == $arrSize ]
    do
	z=cmp ${files[ $k ]} ${files[ $j ]}
	if [ $z == 1 ]
	then
	    (( j++ ))
	    z=0
	else
	    ln ${files[ $j ]} ${files[ $k ]}
	    (( j++ ))
	fi
    done
    (( k++ ))
    j=$k
done

