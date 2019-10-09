# MAME ROM renamer

* Parse XML file [DONE]
* For each [machine] directory in roms directory: [DONE]
	* Look the machine up in the XML file [DONE]; find its ROM SHA1s [DONE]
	* If the machine isn't in the XML file, or has no ROMs, list it in red as missing [TODO]
	* For each [rom] file in [machine] directory: [DONE]
		* Compare it to that machine's known ROM SHA1s [DONE]
			* If it doesn't exist, list it in red as obsolete [TODO]
			* If it exists with the same ROM name, list it in green as OK [IN PROGRESS]
			* If it exists with a different ROM name, list it in yellow as renamed [IN PROGRESS]