#!/bin/bash
if [ -z $1 ]
then
	SOURCE_FILE=../main.c
else
	SOURCE_FILE=../$1
fi
echo Source file: $SOURCE_FILE
cppcheck --addon=misra --output-file=misra-report2.txt --suppress=*:../lwipopts.h $SOURCE_FILE