# Set the location of the top of the MicroPython repository.
MICROPYTHON_TOP = ./lib/micropython

PACKAGE_DIR = ./build

SRC_C = ./mp_flipper_modflipperzero.c

SRC_QSTR += ./mp_flipper_modflipperzero.c

include ./Makefile.micropython

$(PACKAGE_DIR): all

.PHONY: build
build: $(PACKAGE_DIR)
	cp -r $(PACKAGE_DIR)/extmod ./
	cp -r $(PACKAGE_DIR)/genhdr ./
	rm -rf $(PACKAGE_DIR)/port ./port
	cp -r $(PACKAGE_DIR)/py ./
	cp -r $(PACKAGE_DIR)/shared ./

.PHONY: clear
clear: clean
	rm -rf ./extmod ./genhdr ./py ./shared

.PHONY: publish
publish:
	./publish.sh
