#!/usr/bin/python

# MAME Rename
# For Python 3
# By Zoe Blade, 2019

# Warns which ROM files need to be renamed or replaced
# for the given version of MAME

import xml.etree.ElementTree as ET
tree = ET.parse('mame.xml')
root = tree.getroot()
exit()