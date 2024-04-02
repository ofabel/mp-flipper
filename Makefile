# Set the location of the top of the MicroPython repository.
MICROPYTHON_TOP = ./lib/micropython

PACKAGE_DIR = ./lib/micropython-build

include ./Makefile.micropython

$(PACKAGE_DIR): all

.PHONY: build
build: $(PACKAGE_DIR)
	ufbt build

.PHONY: launch
launch: build
	ufbt launch
