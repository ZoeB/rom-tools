#!/usr/bin/python

# MAME Rename
# For Python 3
# By Zoe Blade, 2019

# Warns which ROM files need to be renamed or replaced
# for the given version of MAME

import hashlib # For calculating SHA1 digests
import os # For directory listings
import xml.etree.ElementTree as ET

# Parse XML file
tree = ET.parse('mame.xml')
root = tree.getroot()

# For each machine in the roms dir...
for ourMachineName in os.listdir('roms'):
	print ourMachineName

	# Try to find its match...
	for theirMachine in root.iter('machine'):
		if theirMachine.get('name') != ourMachineName:
			continue

		theirRoms = theirMachine.iter('rom')
		for ourRomName in os.listdir(os.path.join('roms', ourMachineName)):
			print ' ' + ourRomName
			romFile = open(os.path.join('roms', ourMachineName, ourRomName), 'rb')
			romData = romFile.read()
			ourHash = hashlib.sha1(romData).hexdigest()
			print(ourHash)

			for theirRom in theirRoms:
				if theirRom.get('sha1') != ourHash:
					continue

				theirRomName = theirRom.get('name')
				print(ourRomName + ' ' + theirRomName)
				exit()
exit()