
# Basic parameters
CC     = gcc 
CFLAGS = -std=c99 -Wall -Wextra -pedantic -Wformat-overflow=0 -O3
OBJS   = test.o
DEPS   = CLM_LIBS.h

###############################################################################
#                                                                             #
#  make : to compile the code, update docs, run the tests, clean the folder.  #
#                                                                             #
###############################################################################

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

test: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
	python3 UpdateDocs.py
	valgrind --leak-check=full ./test
	/bin/rm -rf *.o *~
	/bin/rm -rf test
