EXES	=execve getdents sleep getcwd

.PHONY: all test


all: ${EXES}

test:
	@for i in $(EXES); \
	do \
		(echo "--------------testing " $$i":"); \
		(./$$i); \
	done

clean:
	-rm ${EXES} *.o > /dev/null 2>&1
