
check_online: src/check_online.c
	gcc -Wall -Wextra -o check_online src/check_online.c
	
all: check_online

.PHONY: all