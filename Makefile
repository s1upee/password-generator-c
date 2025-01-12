CC = gcc
CFLAGS = -Wall -Wextra -pedantic
TARGET = password_generator

all: $(TARGET)

$(TARGET): password_generator.c
	$(CC) $(CFLAGS) password_generator.c -o $(TARGET) -lssl -lcrypto

clean:
	rm -f $(TARGET)