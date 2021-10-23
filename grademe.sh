make re BUFFER_SIZE=-10
make re BUFFER_SIZE=0
make re BUFFER_SIZE=1
make re BUFFER_SIZE=10
make re BUFFER_SIZE=42
make re BUFFER_SIZE=1000000
make re BUFFER_SIZE="'42 / 2'"
# This tests may be long, uncomment it if you want
# make re BUFFER_SIZE=INT_MAX
$make re BUFFER_SIZE="'SSIZE_MAX + 1'"

if [[ "$1" == "bonus" ]]; then
    make clean bonus BUFFER_SIZE=-10
    make clean bonus BUFFER_SIZE=0
    make clean bonus BUFFER_SIZE=1
    make clean bonus BUFFER_SIZE=10
    make clean bonus BUFFER_SIZE=42
    make clean bonus BUFFER_SIZE=1000000
    make clean bonus BUFFER_SIZE="'42 / 2'"
    # This tests may be long, uncomment it if you want
    # make clean bonus BUFFER_SIZE=INT_MAX
    # I believe this test should give run-time NULL or compile-time error
    # Try it yourself
    # make clean bonus BUFFER_SIZE="'SSIZE_MAX + 1'"
fi
