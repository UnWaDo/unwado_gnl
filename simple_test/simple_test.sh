#!/bin/bash

./simple_test
v=$(diff exp res)
if [ "$v" = "" ]; then
	echo Grade: OK
else
	echo Grade: KO, diff is logged to errors.log
	printf "\n--Simple test--\n$v" >> ../errors.log
fi