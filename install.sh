#!/bin/bash

# ArionsAV Installer

# NOTES:
#	- Mar_01-21: To make it cross-platform, perform different installation commands like yum (ignoring errors)
#	- Mar_01-21: Check if commands succeed or failed to stop installer or continue
#	- Mar_01-21: Separate apt-get installs a bit, so if a package fails, install the rest somehow (any option to ignore errors?)

echo "[INFO] Checking root access...";

if [ "$EUID" -ne 0 ]
  then echo "[ERROR] The installer must run as root."
  exit
fi

echo "[OK] Script running as root.";

echo "[INFO] Installing ArionsAV dependencies...";

APT_MAIN_DEP="gcc make"
APT_LIB_DEP=""

sudo apt-get install $APT_MAIN_DEP $APT_LIB_DEP

echo "[OK] Dependencies installed.";

echo "[INFO] Compiling ArionsAV source code...";

./compile

echo "[OK] ArionsAV source code compiled.";

echo "[INFO] Installing ArionsAV...";

sudo make install

echo "[DONE] ArionsAV has been installed.";
echo "[INFO] Report any issue found to the GitHub repository.";
