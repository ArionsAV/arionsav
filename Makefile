# Makefile for ArionsAV

all:
	gcc src/whatever -o build/whatever
install:
	mkdir /opt/arions-files/
	cp build/watchdog /opt/arions-files/watchdog
	cp build/arions-service /opt/arions-files/arions-service
	cp build/arionsav /usr/bin/arionsav
	# --- load kernel module ---
clean:
	rm .tmp/*.o
