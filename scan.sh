#!/bin/sh

# chkrootkit
echo "Scanning with chkrootkit..."


# rkhunter
echo "Scanning with rkhunter..."


# clamav
echo "Scanning with clamav..."


# Unload the rootkit
rmmod rootkit

# Clean the directory
make clean

# Uninstall the malware scanning tools
apt-get --yes purge chkrootkit
apt-get --yes purge rkhunter
apt-get --yes purge clamav