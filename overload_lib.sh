#/bin/sh
HOSTTYPE=$(uname -m)_$(uname -s)
NAME=libft_malloc_$HOSTTYPE.so
export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES=$NAME
export DYLD_FORCE_FLAT_NAMESPACE=1
./test
