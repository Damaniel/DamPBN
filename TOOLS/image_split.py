# Given a directory of files, divide the files into groups of 50, placing each of them into sequential directories
# starting with 0001

import sys, os, shutil, random

# Get the path to the directory containing the files
input_dir = sys.argv[1]

# Get a list of all files in the directory
input_files = [file for file in os.listdir(input_dir)]

# randomly sort the files
random.shuffle(input_files)

# Create groups of 50 files
groups = [input_files[i:i + 50] for i in range(0, len(input_files), 50)]

# For each group
for i in range(len(groups)):
    # Create a directory with a name that is 4 digits long, padded with zeros
    directory_name = str(i + 1).zfill(4)
    os.mkdir(directory_name)

    # For each file in the group
    for file in groups[i]:
        # Copy the file into the directory
        shutil.copy(os.path.join(input_dir, file), directory_name)
