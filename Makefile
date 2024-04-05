# Set the location of the top of the MicroPython repository.
MICROPYTHON_TOP = ./lib/micropython

PACKAGE_DIR = ./build

SRC_C = ./modflipperzero.c

SRC_QSTR += ./modflipperzero.c

include ./Makefile.micropython

$(PACKAGE_DIR): all

.PHONY: build
build: $(PACKAGE_DIR)
	cp -r $(PACKAGE_DIR)/extmod ./
	cp -r $(PACKAGE_DIR)/genhdr ./
	cp -r $(PACKAGE_DIR)/port ./
	cp -r $(PACKAGE_DIR)/py ./
	cp -r $(PACKAGE_DIR)/shared ./

.PHONY: clear
clear: clean
	rm -rf ./extmod ./genhdr ./port ./py ./shared
