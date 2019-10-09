#!/usr/bin/python

# MAME Rename
# For Python 3
# By Zoe Blade, 2019

# Warns which ROM files need to be renamed or replaced
# for the given version of MAME

import xml.etree.ElementTree as ET
import os

# Parse XML file
tree = ET.parse('mame.xml')
root = tree.getroot()

# For each machine in the roms dir...
for ourMachine in os.listdir('roms'):
	print ourMachine

	# Try to find its match...
	for theirMachine in root.iter('machine'):
		if theirMachine.get('name') != ourMachine:
			continue

		theirRoms = theirMachine.iter('rom')
		ourRoms = os.listdir(os.path.join('roms', ourMachine))
		print(theirRoms)
		print(ourRoms)
		exit()

exit()