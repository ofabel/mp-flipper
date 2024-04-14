.PHONY: build
build:
	ufbt build

.PHONY: launch
launch: build
	ufbt launch
