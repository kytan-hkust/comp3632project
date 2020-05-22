#!/bin/sh

apt-get --yes update
apt-get --yes upgrade

# Install essential tools for compilation
apt --yes install gcc
apt --yes install make

# Install malware scanning tools
apt --yes install chkrootkit
apt --yes install rkhunter
apt --yes install clamav

# Compile the rootkit and trojan
make