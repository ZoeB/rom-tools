#!/usr/local/bin/python3

# MAME Rename
# For Python 3
# By Zoe Blade, 2019-2020

# Renames ROM files as needed; warns which ROM files need to be replaced

import hashlib # For calculating SHA1 digests
import os # For directory listings
import xml.etree.ElementTree as ET

GREEN = '\033[32m'
YELLOW = '\033[33m'
RED = '\033[31m'
OFF = '\033[0m'

rompath = '/Volumes/MAME/roms'

# Parse XML file
tree = ET.parse('mame.xml')
root = tree.getroot()

# For each machine in the roms dir...
for ourMachineName in os.listdir(rompath):
	print(ourMachineName)

	# Try to find its match...
	for theirMachine in root.iter('machine'):
		if theirMachine.get('name') != ourMachineName:
			continue

		# Machine match found

		# For each ROM in the machine's dir...
		for ourRomName in os.listdir(os.path.join(rompath, ourMachineName)):
			romFile = open(os.path.join(rompath, ourMachineName, ourRomName), 'rb')
			romData = romFile.read()
			ourHash = hashlib.sha1(romData).hexdigest()

			# Try to find its match...
			for theirRom in theirMachine.iter('rom'):
				if theirRom.get('sha1') != ourHash:
					continue

				# ROM match found
				theirRomName = theirRom.get('name')

				if theirRomName == ourRomName:
					print(GREEN + ' ' + ourRomName + ' OK' + OFF)
				else:
					print(YELLOW + ' ' + ourRomName + ' -> ' + theirRomName + OFF)
					os.rename(os.path.join(rompath, ourMachineName, ourRomName), os.path.join(rompath, ourMachineName, theirRomName))

				break

			# ROM match not found
			if theirRom.get('sha1') != ourHash:
				print(RED + ' ' + ourRomName + ' obsolete' + OFF)
