# Set the location of the top of the MicroPython repository.
MICROPYTHON_TOP = ./lib/micropython

PACKAGE_DIR = ./lib/micropython-build

# Include the main makefile fragment to build the MicroPython component.
include $(MICROPYTHON_TOP)/ports/embed/embed.mk

$(PACKAGE_DIR): all

.PHONY: build
build: $(PACKAGE_DIR)
	ufbt build

.PHONY: launch
launch: build
	ufbt launch
