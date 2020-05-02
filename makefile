CC = gcc
RM = rm -f

CFLAGS = -std=c99 -pedantic -Wall -O2
PKGS = `pkg-config --libs --cflags gtk+-3.0 liblightdm-gobject-1 gmodule-export-2.0`
LIBS = `pkg-config --libs gtk+-3.0 liblightdm-gobject-1 gmodule-export-2.0`

TARGET = lightdm-sandbox
.PHONY: all


all: $(TARGET)

$(TARGET): lightdm_sandbox_greeter.o
	$(CC) -o $@ $^ $(LIBS)

lightdm_sandbox_greeter.o: lightdm_sandbox_greeter.c
	$(CC) $(CFLAGS) -c $^ $(PKGS)


clean:
	$(RM) *.o
