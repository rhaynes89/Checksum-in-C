#!/bin/bash
case $1 in
checksum.c)
	rm a.out
	gcc checksum.c 
	EXE="./a.out"
	;;
checksum.cpp)
	rm a.out
	g++ checksum.cpp
	EXE="./a.out"
	;;
checksum.java)
	rm checksum.class
	javac checksum.java
	EXE="java checksum"
	;;
*)
    echo "Invalid source file name"
    echo "->  should be checksum.c, checksum.cpp, or checksum.java"
	exit 1
esac


for i in $(ls i?.txt); do
   echo Processing: $i
   eval $EXE $i 8   # comment this line out by placing a # in front of eval...
   eval $EXE $i 16  # comment this line out by placing a # in front of eval...
   eval $EXE $i 32  # comment this line out by placing a # in front of eval...
done
