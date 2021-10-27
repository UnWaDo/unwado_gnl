CLR_KO='\033[0;31m'
CLR_OK='\033[32m'
CLR_NC='\033[0m'

cwd=$1
test_file=$2
if [[ "$test_file" == "" ]]; then
	cwd=""
	test_file=$1
fi
if [[ "$test_file" == "" ]]; then
	printf $CLR_KO"no test_file stated\n"$CLR_NC
	exit 1
fi

if ! command -v valgrind &> /dev/null; then
	if ! command -v leaks &> /dev/null; then
		printf $CLR_KO"no valgrind or leaks available\n"$CLR_NC
		exit 1
	else
		memchecker="leaks -q --atExit --"
	fi
else
	memchecker="valgrind -q --vgdb=no"
fi

if [[ "$cwd" != "" ]]; then
	cd $cwd
fi

$memchecker $test_file > leaks.log
while read line
do
	if [[ "$line" == "leaks Report"* || "$line" == "Process "* ]]; then
		if [[ "$line" == *"leaks for "*"total leaked bytes"* ]]; then
			if [[ "$line" == *"0 leaks for 0 total leaked bytes"* ]]; then
				printf $CLR_OK"Leaks: OK\n"$CLR_NC
			else
				printf $CLR_KO"Leaks: KO\n"$CLR_NC
			fi			
		fi
	else
		printf "$line\n"
	fi
done < "leaks.log"
rm leaks.log