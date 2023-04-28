# Given a directory of .pcx files, convert them into the DamPBN file format

# The tool takes 4 command line arguments; an input directory, an output directory, a path to a CSV file
# containing information about each of the images, and an argument that specifies the kind of compression to be used.

import sys, os, PIL.Image

def run_length_encode(data):
    # Given a set of bytes of data, return a list of bytes encoded with the following method
    # If a byte is not repeated, write the byte to the new list
    # If a byte is repeated up to 255 times, write two bytes:
    #   - one byte contains the value of the data byte with the most significant bit set to 1,
    #  - the other byte contains the number of times the byte was repeated
    # Continue until the original list has been fully processed

    output_data = []
    i = 0
    while i < len(data):
        # Get the current byte
        current_byte = data[i]

        # Get the number of times the current byte is repeated
        repeat_count = 1
        while i + repeat_count < len(data) and data[i + repeat_count] == current_byte and repeat_count < 255:
            repeat_count += 1

        # If the current byte is repeated more than once, write the byte with the most significant bit set
        if repeat_count > 1:
            output_data.append(current_byte | 0x80)
            output_data.append(repeat_count)
        else:
            output_data.append(current_byte)
        i += repeat_count

    return output_data

def get_used_colors(color_data):
    # Given a list of RGB triplets, count the number of unique triplets are in the list and return the count
    
    # Create a set to store the unique colors   
    unique_colors = set()

    # For each color in the list - note that each color consists of 3 sequential elements in the list
    for i in range(0, len(color_data), 3):
        # Get the red, green, and blue components of the color
        red = color_data[i]
        green = color_data[i + 1]
        blue = color_data[i + 2]

        # Add the color to the set
        unique_colors.add((red, green, blue))

    # If (0,0,0) is in the set and there are more than 64 colors, remove it
    if (0,0,0) in unique_colors and len(unique_colors) > 64:
        unique_colors.remove((0,0,0))

    # Return the number of unique colors
    return len(unique_colors)

def main():
    # Read 4 command line parameters and store them in variables
    input_dir = sys.argv[1]
    output_dir = sys.argv[2]
    metadata_file = sys.argv[3]
    compression_type = sys.argv[4]

    # Get a list of all files in the input directory with the extension .pcx
    input_files = [f for f in os.listdir(input_dir) if os.path.isfile(os.path.join(input_dir, f)) and f.endswith(".pcx")]

    # Open the metadata file
    metadata = open(metadata_file, "r")

    # Read the CSV data into a list of lines
    metadata_lines = metadata.readlines()

    # Close the metadata file
    metadata.close()

    # for each file in input_files
    for file in input_files:
        # Use PIL to open the file
        image = PIL.Image.open(os.path.join(input_dir, file))

        # Get the width and height of the image
        width, height = image.size

        # If the width of the image is greater than 320 or the height greater than 200, skip the file
        if width > 320 or height > 200:
            print(f"Skipping {file} because it is too big")
            continue

        # Get the pixel data from the image
        pixel_data = list(image.getdata())

        # Get the palette from the image
        palette = image.getpalette()

        num_colors = get_used_colors(palette)
        if num_colors > 64:
            print("Too many colors!")
            continue

        category_id = 0
        displayed_name = ""

        # Find the line in the metadata file where the first field matches the input file name
        for line in metadata_lines:
            # Split the line into a list of fields
            fields = line.split(",")

            # If the first field matches the input file name
            if fields[0] == file:
                # Get the category ID from the second field
                displayed_name = fields[1]
                # Get the displayed name from the third field
                category_id = int(fields[2])
                # Stop searching
                break
    
        # Create a new file with the same name as the input file, but with the extension .pic
        output_file = open(os.path.join(output_dir, file.replace(".pcx", ".pic")), "wb")

        # Write the bytes 'DP' to the file
        output_file.write(b"DP")
        # Write the width and height of the image to the file
        output_file.write(width.to_bytes(2, byteorder="little"))
        output_file.write(height.to_bytes(2, byteorder="little"))
        # Write the category ID (as one byte) to the file
        output_file.write(int(category_id).to_bytes(1, byteorder="little"))
        # If the length of the displayed name is greater than 32, truncate it
        if len(displayed_name) > 32:
            displayed_name = displayed_name[:32]
        # Otherwise, if the length of the displayed name is less than 32, pad it with zeroes
        elif len(displayed_name) < 32:
            displayed_name = displayed_name + "\x00" * (32 - len(displayed_name))
        # Write the displayed name to the file
        output_file.write(bytes(displayed_name, "ascii"))

        rle_data = run_length_encode(pixel_data)

        write_rle = False
        if compression_type == "1":
            write_rle = True
        elif compression_type == "2":
            if len(rle_data) < len(pixel_data):
                write_rle = True


        # Write the number of colors in the palette to the file
        output_file.write(num_colors.to_bytes(1, byteorder="little"))
     
        if write_rle == True:
            output_file.write(b"\x01")
        else:
            output_file.write(b"\x00")

        # divide all values in the palette by 4
        for i in range(0, len(palette)):
            palette[i] = palette[i] // 4
        
        output_file.write(bytes(palette[:192]))

        # Write 23 0 bytes to the file
        output_file.write(b"\x00" * 23)

        if write_rle == False:
            output_file.write(bytes(pixel_data))
        else:
            output_file.write(bytes(rle_data))

        # Close the file
        output_file.close()

if __name__ == "__main__":
    main()

