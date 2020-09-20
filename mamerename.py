#!/usr/local/bin/python3

# MAME Rename
# For Python 3
# By Zoe Blade, 2019

# Warns which ROM files need to be renamed or replaced
# for the given version of MAME

# TODO: skip .hidden and .chd files
# TODO: in the other direction, warn which ROMs are missing
# TODO: make this work across directories, in case a file has been moved to another dir.  Rename it, don't delete it.  Note that one ROM might appear in multiple directories, so don't create new directories and half-setup all the clones.  (See 813cecf44bf5464b1aed64b36f5047e4c79ba176, for instance, which currently appears three times in MAME.)  We need three main lists: MAME's ROM hashes, and their multiple full paths (so the path as key); our local file hashes, and their multiple full paths (ditto); and our local directories (machines), so we can ignore hashes that don't belong to them.

# Step 1: list our local directories (machines)
# Step 2: list all our files (ROMs), including their full paths, and their hashes.  This is where we're copying/renaming from.
# Step 3: list all our locally desired machines' ROMs in MAME, including their full paths, and their hashes.  This is where we're copying/renaming to.

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
		theirRoms = theirMachine.iter('rom')

		# For each ROM in the machine's dir...
		for ourRomName in os.listdir(os.path.join(rompath, ourMachineName)):
			romFile = open(os.path.join(rompath, ourMachineName, ourRomName), 'rb')
			romData = romFile.read()
			ourHash = hashlib.sha1(romData).hexdigest()

			# Try to find its match...
			for theirRom in theirRoms:
				if theirRom.get('sha1') != ourHash:
					print(ourRomName + ' != ' + theirRom.get('name')) # This reveals the problem: it's not resetting to the start of the list each time, on line 52.  I think I need to choose between iter() and for-in.
					continue

				# ROM match found
				theirRomName = theirRom.get('name')

				if theirRomName == ourRomName:
					print(GREEN + ' ' + ourRomName + ' OK' + OFF)
				else:
					print(YELLOW + ' ' + ourRomName + ' -> ' + theirRomName + OFF)

				break

			# ROM match not found
			if theirRom.get('sha1') != ourHash:
				print(RED + ' ' + ourRomName + ' obsolete' + OFF)
