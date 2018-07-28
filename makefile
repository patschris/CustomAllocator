CC		= gcc
CFLAGS	= -g -Wall
SRCS	= bank.c list.c myallocator.c bitvector.c hashmap.c
OBJS	= bank.o list.o myallocator.o bitvector.o hashmap.o

make:
	$(CC) $(CFLAGS) -c bank.c
	$(CC) $(CFLAGS) -c list.c
	$(CC) $(CFLAGS) -c myallocator.c
	$(CC) $(CFLAGS) -c bitvector.c
	$(CC) $(CFLAGS) -c hashmap.c

clean:
	rm -rf $(OBJS)