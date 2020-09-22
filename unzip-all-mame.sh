#!/bin/sh
for file in *.zip
do
	mkdir ${file%.zip}
	unzip $file -d ${file%.zip}/
	rm $file
done
