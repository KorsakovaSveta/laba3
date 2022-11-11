#!/bin/bash

urlPattern="^http(s)?:\/\/(\S)+\.((png)|(jpg)|(webp)|(gif)|(heif)|(svg))$"

output="./"

for (( path=1; path<=$#; path++ ));
do
	if [[ "${!path}" == "-d" ]]; then
		(( path++ ))
		output="${!path}";

	elif [[ ${!path} =~ $urlPattern ]]; then
		wget -q ${!path} -P $output

	else
		cp ${!path} $output
	fi
done

#------------------
# ,_.-.			  |
# `--; `------.   |
#	 \  ,..., ,\  |
#------------------	 

