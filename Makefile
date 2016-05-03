SUBDIR1 = dpdk
SUBDIR2	= twister
RTE_TARGET = x86_64-native-linuxapp-gcc

DEB_DEPENDS  = make gcc

.PHONY: help bootstrap build clean all install install-lib uninstall rebuild-lib

help:
	@echo "Make Targets:"
	@echo " bootstrap   - prepare system for twister installation"
	@echo " clean       - wipe all the package "
	@echo " all	     - wipe and build the whole package"
	@echo " install     - build and install the whole twister package"
	@echo " uninstall   - wipe and clean the system"
	@echo " build       - wipe and build the whole twister package"
	@echo " rebuild-lib - wipe and build the twister"
	@echo " install-lib - build and install the twister"

bootstrap:
ifeq ("$(shell lsb_release -si)", "Ubuntu")
	@MISSING=$$(apt-get install -y -qq -s $(DEB_DEPENDS) | grep "^Inst ") ; \
	if [ -n "$$MISSING" ] ; then \
	  echo "\nPlease install missing packages: \n$$MISSING\n" ; \
	  exit 1 ; \
	fi ; \
	exit 0
endif
	./configure

build:
	$(MAKE) -C $(SUBDIR1);
	cp -R $(SUBDIR1)/build $(SUBDIR1)/$(RTE_TARGET);
	$(MAKE) -C $(SUBDIR2);

rebuild-lib:
	rm -rf $(SUBDIR2)/build;
	$(MAKE) -C $(SUBDIR2);

install-lib: rebuild-lib
	cp $(SUBDIR2)/build/libtwister.a /home/twister/.
	echo 'install all twister headers'
	cp $(SUBDIR2)/include/*.h /home/twister/include
	
clean:
	rm -rf $(SUBDIR2)/build;
	rm -rf $(SUBDIR1)/$(RTE_TARGET);

all: clean bootstrap build

install: all
	cp $(SUBDIR2)/build/libtwister.a /home/twister/.
	cp $(SUBDIR1)/$(RTE_TARGET)/lib/* /home/twister/
	echo 'install all twister headers'
	cp $(SUBDIR2)/include/*.h /home/twister/include
	cp $(SUBDIR1)/$(RTE_TARGET)/include/*.h /home/twister/include
	cp $(SUBDIR1)/$(RTE_TARGET)/include/generic/*.h /home/twister/include/generic/
	cp $(SUBDIR1)/$(RTE_TARGET)/include/exec-env/*.h /home/twister/include/exec-env/
	./post-install

uninstall: clean
	rm -rf /home/twister/*
