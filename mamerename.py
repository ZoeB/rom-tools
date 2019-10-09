#!/usr/local/bin/python3

# MAME Rename
# For Python 3
# By Zoe Blade, 2019

# Warns which ROM files need to be renamed or replaced
# for the given version of MAME

import hashlib # For calculating SHA1 digests
import os # For directory listings
import xml.etree.ElementTree as ET

GREEN = '\033[32m'
YELLOW = '\033[33m'
RED = '\033[31m'
OFF = '\033[0m'

# Parse XML file
tree = ET.parse('mame.xml')
root = tree.getroot()

# For each machine in the roms dir...
for ourMachineName in os.listdir('roms'):
	print(ourMachineName)

	# Try to find its match...
	for theirMachine in root.iter('machine'):
		if theirMachine.get('name') != ourMachineName:
			continue

		# Machine match found
		theirRoms = theirMachine.iter('rom')

		# For each ROM in the machine's dir...
		for ourRomName in os.listdir(os.path.join('roms', ourMachineName)):
			print(' ' + ourRomName)
			romFile = open(os.path.join('roms', ourMachineName, ourRomName), 'rb')
			romData = romFile.read()
			ourHash = hashlib.sha1(romData).hexdigest()

			# Try to find its match...
			for theirRom in theirRoms:
				if theirRom.get('sha1') != ourHash:
					continue

				# ROM match found
				theirRomName = theirRom.get('name')

				if theirRomName == ourRomName:
					print(GREEN + 'OK' + OFF)
				else:
					print(YELLOW + 'Rename ' + ourRomName + ' to ' + theirRomName + OFF)

				break

			# ROM match not found
			if theirRom.get('sha1') != ourHash:
				print(RED + 'Obsolete' + OFF)