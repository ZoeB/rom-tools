#!/bin/sh
for file in *
do
	if [[ -d $file ]]; then
		echo "Archive:  $file.zip"
		zip -j -9 $file.zip $file/*
		rm $file/*
		rmdir $file
	fi
done
