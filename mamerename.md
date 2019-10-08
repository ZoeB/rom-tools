# MAME ROM renamer

* Parse XML file
* For each [machine] directory in roms directory:
	* Look the machine up in the XML file; find its ROM SHA1s
	* If the machine isn't in the XML file, or has no ROMs, list it in red as missing
	* For each [rom] file in [machine] directory:
		* Compare it to that machine's known ROM SHA1s
			* If it doesn't exist, list it in red as deleted
			* If it exists with the same ROM name, list it in green as OK
			* If it exists with a different ROM name, list it in yellow as renamed