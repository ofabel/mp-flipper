# Set the location of the top of the MicroPython repository.
MICROPYTHON_TOP = ./lib/micropython

PACKAGE_DIR = ./build

SRC_C = ./mp_flipper_modflipperzero.c

SRC_QSTR += ./mp_flipper_modflipperzero.c

MICROPY_ROM_TEXT_COMPRESSION = 0

include ./Makefile.micropython

.PHONY: _init-firmware
_init-firmware:
	cp ./mp_flipper_config_firmware.h ./mpconfigport.h

.PHONY: _init-fap
_init-fap:
	cp ./mp_flipper_config_fap.h ./mpconfigport.h

$(PACKAGE_DIR): all

.PHONY: _build
_build: $(PACKAGE_DIR)
	cp -r $(PACKAGE_DIR)/extmod ./
	cp -r $(PACKAGE_DIR)/genhdr ./
	rm -rf $(PACKAGE_DIR)/port ./port
	cp -r $(PACKAGE_DIR)/py ./
	cp -r $(PACKAGE_DIR)/shared ./

.PHONY: build-firmware
build-firmware: clear _init-firmware _build

.PHONY: clear
clear: clean
	rm -rf ./extmod ./genhdr ./py ./shared ./temp ./mpconfigport.h

.PHONY: publish-firmware
publish-firmware: clear _init-firmware _build
	./publish.sh lib-release-firmware

.PHONY: publish-fap
publish-fap: clear _init-fap _build
	./publish.sh lib-release-fap
