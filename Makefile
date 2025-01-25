all: check_online

check_online: src/check_online.c
	gcc -Wall -Wextra -o check_online src/check_online.c
	

.PHONY: all