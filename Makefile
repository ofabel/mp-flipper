.PHONY: update
update:
	git submodule update --remote lib/micropython && git add lib/micropython

.PHONY: build
build: update
	ufbt build

.PHONY: launch
launch: build
	ufbt launch
