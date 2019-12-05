#!/bin/bash

rm -rf build 

mkdir build

cd build 

if [ "$1" = "-r" ]; then
	echo Release Mode
	cmake .. -DCMAKE_BUILD_TYPE=Release
else
 	cmake .. -DCMAKE_BUILD_TYPE=Debug
fi

make

# if [$1 = "r"]; then
# 	echo "Release"
# 	cmake .. -DCMAKE_BUILD_TYPE=Release
# else
# 	cmake .. -DCMAKE_BUILD_TYPE=Debug
# fi
# make
