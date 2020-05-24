#!/bin/sh

# chkrootkit
#echo "Scanning with chkrootkit... (this might take a while)"
#echo "Done scanning with chkrootkit"
#echo "\n"

# rkhunter
echo "Scanning with rkhunter... (this might take a while)"
rkhunter --check
echo "Done scanning with rkhunter"
echo "Rootkit scanning results of rkhunter:"
cat /var/log/rkhunter.log | grep "Possible rootkits:"
echo "\n"

# clamav
echo "Scanning with clamav... (this might take a while)"
clamscan -r --bell -i . > clamav.log
echo "Done scanning with clamav"
echo "Malware scanning results of clamav:"
cat clamav.log | grep "Infected files:"
echo "\n"

# Unload the rootkit
#rmmod rootkit

# Clean the directory
echo "Cleaning the directory..."
make clean

# Uninstall the malware scanning tools
echo "Uninstalling the malware scanning tools..."
apt-get --yes purge chkrootkit
apt-get --yes purge rkhunter
apt-get --yes purge clamav