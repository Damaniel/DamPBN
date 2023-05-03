# Generates a manifest file for the DamPBN installer
#
# Usage: generate_manifest.py <directory> <output_file>
#
# For best results, run from the root of the directory that
# the manifest will be generated for.  It should run OK
# from anywhere though.
import os
import sys

# Get the directory to scan from the command line
if len(sys.argv) < 3:
    print("Usage: generate_manifest.py <directory> <manifest_file>")
    sys.exit(1)

# Get the directory to scan
directory = sys.argv[1]
manifest_file = sys.argv[2]

# Recursively scan the directory tree, returning a list of directory names
def scan_directory(directory):
    dir_output = []
    file_output = []
    # Get the list of files and directories in this directory
    files = os.scandir(directory)
    for file in files:
        if file.is_file():
            file_output.append(os.path.join(directory, file.name))
        if file.is_dir():
            dir_output.append(os.path.join(directory, file.name))
            (files, dirs) = scan_directory(os.path.join(directory, file.name))
            for dir in dirs:
                dir_output.append(dir)
            for file in files:
                file_output.append(file)
    return (file_output, dir_output)

(file_output, directory_output) = scan_directory(directory)

final_file_output = []
final_dir_output = []

for dir in directory_output:
    dir = dir.replace("\\\\", "\\")
    dir = dir.replace(directory + '\\', '')
    final_dir_output.append(dir)

for file in file_output:
    file = file.replace("\\\\", "\\")
    file = file.replace(directory + '\\', '')
    final_file_output.append(file)

total_steps = len(final_file_output) + len(final_dir_output)
manifest = open(manifest_file, "w")

manifest.write(f"{total_steps}\n")

for dir in final_dir_output:
    manifest.write(f"MKDIR {dir}\n")
for file in final_file_output:
    # If the file is not in a subdirectory, set the destination to the current directory,
    # otherwise set it to the same as the source (copy will do the right thing)
    if file.find("\\") == -1 and file.find("/") == -1:
        manifest.write(f"COPY {file} .\n")
    else:
        manifest.write(f"COPY {file} {file}\n")

manifest.close()
