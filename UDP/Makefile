CC = gcc

all: $(TARGET1) $(TARGET2)
	gcc -o c cmain.c client.c
	gcc -o s smain.c server.c

clean:
	rm -f c s dst.jpg
