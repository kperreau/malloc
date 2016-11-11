#/bin/sh
HOSTTYPE=$(uname -m)_$(uname -s)
NAME=libft_malloc_$HOSTTYPE.so
export LD_PRELOAD="/home/kperreau/share/malloc/"$NAME
./test
