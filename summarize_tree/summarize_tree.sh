#!/usr/bin/bash

# Store the first arguement
Directory=$1

# cd into this directory
cd $Directory

# Count of files
files=$(find . -type f|wc -l)

# Count of directories
directories=$(find . -type d|wc -l)


# Print out results
echo "There were $directories directories."
echo "There were $files regular files."
