# Given a path to a set of images with names, and a set of images with numerically sequential names,
# create a CSV file that maps the two

import sys, os

# The two paths are set as command line arguments
image_path = sys.argv[1]
numbered_image_path = sys.argv[2]

# Get a list of all files in the image path
image_files = [file for file in os.listdir(image_path)]

# Get a list of all files in the numbered image path
numbered_image_files = [file for file in os.listdir(numbered_image_path)]

# For each item in image_files, remove the extension
for i in range(len(image_files)):
    image_files[i] = os.path.splitext(image_files[i])[0]

# For each item in image_files, replace underscores with spaces
for i in range(len(image_files)):
    image_files[i] = image_files[i].replace("_", " ")

# For each item in image files, make the first letter of each word uppercase
for i in range(len(image_files)):
    image_files[i] = image_files[i].title()

# Open a CSV file for writing
csv_file = open("image_map.csv", "w")

# For each file index in the numbered image path
for i in range(len(numbered_image_files)):
    # Write the following 3 values: the value of numbered_image_file[i], the value of image_files[i], and the value 1
    csv_file.write(f"{numbered_image_files[i]},{image_files[i]},1\n")

# close the CSV file
csv_file.close()