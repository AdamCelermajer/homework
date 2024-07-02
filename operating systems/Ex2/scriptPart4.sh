#!/bin/bash

# Create source_directory structure
mkdir -p source_directory/subdir1
mkdir -p source_directory/subdir2

echo "This is file1.txt" > source_directory/file1.txt
echo "This is file2.txt" > source_directory/file2.txt
echo "This is file3.txt" > source_directory/subdir1/file3.txt
echo "This is file4.txt" > source_directory/subdir1/file4.txt
echo "This is file5.txt" > source_directory/subdir2/file5.txt

ln -s ../file1.txt source_directory/subdir2/link_to_file1

# Compile the library and the main program
gcc -c copytree.c -o copytree.o
ar rcs libcopytree.a copytree.o
gcc part4.c -L. -lcopytree -o part4_program


# Run the program
./part4_program "./source_directory" "./destination_directory"

# Verify the results
echo "Verification of copied structure:"
tree destination_directory

echo "Verification complete."