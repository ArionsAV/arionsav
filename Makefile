# Makefile for ArionsAV

AGNT_OBJECT_FILES="build/whatever.o build/whatever2.o"
SRV_OBJECT_FILES="build/whatever.o build/whatever2.o"
WDG_OBJECT_FILES="build/whatever.o build/whatever2.o"
MNGR_OBJECT_FILES="build/manager.o"

all:
	gcc -c src/service_status.c src/service_status.h -o build/service_status.o
	gcc -c src/log_manager.c src/log_manager.h -o build/log_manager.o
	# 1) Compile agent source
	gcc -c src/manager.c src/manager.h -o build/manager.o
	gcc src/arions_agent.c $AGNT_OBJECT_FILES -o build/arions-agent
	# 2) Compile service source
	gcc src/service.c $SRV_OBJECT_FILES -o build/arions-service
	# 3) Compile watchdog source
	gcc src/watchdog.c $WDG_OBJECT_FILES -o build/arionswdg
	# 4) Compile manager source
	gcc src/arionsav.c $MNGR_OBJECT_FILES -o build/
	# time to install! Compilation done!
	
install:
	# create ArionsAV environment directories
	sudo mkdir /opt/arionsav/
	sudo mkdir /var/log/arionsav/
	sudo mkdir /var/log/arionsav/watchdog/
	sudo mkdir /var/log/arionsav/service/
	sudo mkdir /var/log/arionsav/agent/
	# ArionsAV binaries installation
	sudo cp build/arions-agent /opt/arionsav/arions-agent
	sudo cp build/arions-service /opt/arionsav/arions-service
	sudo cp build/arionswdg /opt/arionsav/arionswdg
	sudo cp build/arionsav /usr/bin/arionsav
	# Load ArionsAV kernel module (driver)
	sudo echo "arionsavx" >> /etc/modules
	sudo cp build/arionsavx.ko /lib/modules/$(uname -r)/kernel/drivers/platform/arionsavx.ko
	sudo depmod
	# time to reboot! Installation done!
	
clean:
	rm build/*
