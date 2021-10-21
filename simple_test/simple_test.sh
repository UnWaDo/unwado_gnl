#!/bin/bash

CLR_KO='\033[0;31m'
CLR_OK='\033[32m'
CLR_NC='\033[0m'

INPUT_FILES="empty short_line short_no_nl single_newline \
	43_with_nl several_lines long_text"
for file in $INPUT_FILES; do
	leaks --atExit -- ./simple_test texts/$file texts/$file.output > leaks.log
	leak=$?
	diff=$(diff texts/$file texts/$file.output)
	if [[ "$diff" = "" && $leak -eq 0 ]]; then
		echo -e $CLR_OK"$file: OK"$CLR_NC
	elif [[ "$diff" = "" && $leak -ne 0 ]]; then
		echo -e $CLR_OK"$file: OK"$CLR_KO, but leaks!$CLR_NC
	else
		echo -e $CLR_KO"$file: KO"$CLR_NC
		printf "\n--Simple test $file--\n$diff" >> ../errors.log
	fi
done
echo Note that for invalid BUFFER_SIZE this check fails
echo Errors are logged to errors.log
