#!/bin/sh

# Utility script to copy DLL files required by a binary.
#
# Copyright (C) 2022, 2026  Dirk Stolle
#
# License: GNU GPL 3+

# first parameter: binary file
if [ -z "$1" ]
then
  echo "First parameter must be path to executable file!"
  exit 1
fi
EXECUTABLE="$1"

# second parameter: output directory
if [ -z "$2" ]
then
  echo "Second parameter must be path to output directory!"
  exit 1
fi
if [ ! -d "$2" ]
then
  echo "Given path $2 is not a directory!"
  exit 1
fi
OUTPUT="$2"

LIBRARIES=$(ldd "$EXECUTABLE" | grep -vi Windows | sort | cut -d ' ' -f 3 | uniq)
for f in $LIBRARIES
do
  echo "Copying library file $f to $OUTPUT ..."
  cp "$f" "$OUTPUT"
  if [ $? -ne 0 ]
  then
    echo "Error: Copying of file $f failed!"
    exit 2
  fi
done

real_exe=$(realpath "$EXECUTABLE")
dest_exe=$(realpath "$OUTPUT"/$(basename "$EXECUTABLE"))
if [ "$real_exe" != "$dest_exe" ]
then
  echo "Copying executable $EXECUTABLE to $OUTPUT ..."
  cp "$EXECUTABLE" "$OUTPUT"
  if [ $? -ne 0 ]
  then
    echo "Error: Copying of executable $EXECUTABLE failed!"
    exit 3
  fi
else
  echo "Skipping copy of $EXECUTABLE to $OUTPUT, because it's the same file."
fi

exit 0
