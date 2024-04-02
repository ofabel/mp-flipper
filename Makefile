# Set the location of the top of the MicroPython repository.
MICROPYTHON_TOP = ./lib/micropython

PACKAGE_DIR = ./lib/micropython-build

SRC_C = ./lib/micropython-port/modflipperzero.c

SRC_QSTR += ./lib/micropython-port/modflipperzero.c

include ./Makefile.micropython

$(PACKAGE_DIR): all

.PHONY: build
build: $(PACKAGE_DIR)
	ufbt build

.PHONY: launch
launch: build
	ufbt launch
