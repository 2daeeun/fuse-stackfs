all: StackFS_ll

StackFS_ll: StackFS_LowLevel.c
	gcc -Wall StackFS_LowLevel.c `pkg-config fuse --cflags --libs` -o StackFS_ll

clean:
	rm -rf StackFS_ll
