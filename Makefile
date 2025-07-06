.PHONY: all kernel user shared clean cmd

all: shared user cmd kernel
	@echo "Build complete."
	bash createfs

shared:
	$(MAKE) -C shared

user:
	$(MAKE) -C user

cmd:
	$(MAKE) -C cmd

kernel:
	$(MAKE) -C kernel

clean:
	$(MAKE) -C shared clean
	$(MAKE) -C kernel clean
	$(MAKE) -C user clean
	$(MAKE) -C cmd clean

run: all
	bash run

debug: all
	bash rundebug
