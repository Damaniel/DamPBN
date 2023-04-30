# Given a directory of image file (.jpg, .png and/or .pcx), convert them into DamPBN format files.
#
# If the images are larger than 320x200, they will be scaled by a ratio necessary to make them at most that size,
# while preserving the aspect ratio.
# Any images with >64 colors will be quantized to 64 colors with dithering
#
# The tool takes 5 command line arguments; an input directory, an output directory, a path to a CSV file
# containing information about each of the images, an argument that specifies the kind of compression to be used,
# and an argument specifing whether files should be created using the v2 format (with transparency)

# About the CSV file:
#
# The CSV file should contain a series of lines, each with 3 values:
#  - The name of the file
#  - A description of the image (will be truncated to 32 characters)
#  - A category ID
#
# Any images without these entries in the CSV file will be given an uncategorized ID and name of 'Default Image'.
#
# This code was written with the help of Github Copilot.  'Help' is a bit of a stretch though - it wrote 99% of
# the code, and I only had to make a couple small changes (mainly due to a PIL bug, not a Copilot issue) to get
# it all working.  Amazing stuff.
 
import sys, os, PIL.Image

# If True, also writes a copy of the converted image as a PNG for inspection
debug_output = False

def resize(input_file):
    # Get the width and height of the image
    width, height = input_file.size

    ratio = 1.0

    # If the width of the image is greater than 320, calculate the ratio to scale it down to 320
    if width > 320:
        ratio = 320.0 / width

    # If the resulting image is still too tall, calculate the ratio to scale it down to 200
    if height * ratio > 200:
        ratio = 200.0 / height

    # Calculate the new width and height
    new_width = int(width * ratio)
    new_height = int(height * ratio)

    # Resize the image
    if ratio != 1.0:
        input_file = input_file.resize((new_width, new_height), PIL.Image.BILINEAR)

    return input_file

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
    use_transparency = sys.argv[5]

    # Get a list of all files in the input directory with the extension .pcx, .jpg, or .png
    input_files = [file for file in os.listdir(input_dir) if file.endswith(".pcx") or file.endswith(".jpg") or file.endswith(".png")]

    # Open the metadata file
    metadata = open(metadata_file, "r")

    # Read the CSV data into a list of lines
    metadata_lines = metadata.readlines()

    # Close the metadata file
    metadata.close()

    # for each file in input_files
    for file in input_files:
        print(f"Processing {file}...")

        # Get the name of the file without the extension
        file_name = os.path.splitext(file)[0]

        # Use PIL to open the file
        image = PIL.Image.open(os.path.join(input_dir, file))

        # resize it if needed
        image = resize(image)

        # if the image has a palette or is grayscale, we'll still convert to RGB/RGBA depending on if
        # it has a alpha channel or not
        if image.mode == 'P' or image.mode == 'L':
            if 'transparency' in image.info:
                image = image.convert('RGBA')
            else:
                image = image.convert('RGB')


        # If the picture has an alpha channel, extract it for future use, then 
        # flatten the image, using white pixels where the transparency used to be
        alpha_channel = []
        if image.mode == 'RGBA':
            # Extract the alpha channel for now since we might use it
            alpha_channel = image.getchannel('A')
            temp_image = PIL.Image.new('RGBA', image.size, (255, 255,255, 255))
            temp_image.paste(image, mask=alpha_channel)
            # Convert the image to RGB
            image = temp_image.convert('RGB')
            # After flattening the image using the alpha mask, mark the alpha channel either 
            # 0 for transparent or 1 for opaque to make it easier on the other side
            for j in range(alpha_channel.height):
                for i in range(alpha_channel.width):
                    if alpha_channel.getpixel((i,j)) != 0:
                        alpha_channel.putpixel((i, j), 1)

        # Get the palette from the image (or 'None' if it's RGB)
        palette = image.getpalette()

        # At this point, the image should have a palette of None, since everything
        # has been converted to RGB.  If not, this will all still work, but images
        # with palettes of more than 64 colors will be skipped later.
        # Quantize to 64 colors
        if palette == None:
            # Quantize the image to 64 colors
            pal = image.quantize(64)
            image = image.quantize(64, palette=pal, dither=PIL.Image.Dither.FLOYDSTEINBERG)
            palette = image.getpalette()
        
        # Now the image should have a palette.  Find how many colors it has.
        # If there's more than 64 of them, skip the image
        num_colors = get_used_colors(palette)
        print(f" This image has {num_colors} colors")
        if num_colors > 64:
            print(f"WARNING: {file} still has more than 64 colors, skipping...")
            continue

        # This step is tricky.  If we're using transparency, we need to count the pixels in the 
        # image and determine if there are any pixels in the image with value (255, 255, 255)
        # that aren't part of the transparency mask
        # If there are, then do nothing; we can use the image as is
        # On the other hand, if there aren't:
        #  - Get the index of (255, 255, 255)
        #  - Remove it and shift all values past it up one
        #  - Scan the whole image, and for all values that were shifted, change the value of the
        #    pixel to (pixel value - 1)
        #  - Set num_colors to num_colors - 1
        #
        # Note - in the alpha mask, 0 is transparent and 255 is opaque
        if use_transparency == "1":
            white_count = 0
            index = -1
            # get the index of (255, 255, 255) in palette, or -1 if it's not there
            for i in range(0, len(palette), 3):
                if palette[i] == 255 and palette[i+1] == 255 and palette[i+2] == 255:
                    index = int(i/3)
            for j in range(alpha_channel.height):
                for i in range(alpha_channel.width):
                    if alpha_channel.getpixel((i, j)) == 255 and image.getpixel((i, j)) == index:
                        white_count = white_count + 1
            print(f"There are {white_count} non-transparent white pixels")
            if white_count == 0:
                print(f"No other white pixels found - shifting palette...")
                print(f"White palette entry found at {index}")
                # If it's -1, then there was never any white to begin with
                # (and presumably, never any transparent pixels to begin with, since that's the only way
                # we'd get zero white pixels without a palette entry)
                if index == -1:
                    use_transparency = '0'
                else:
                    # Take all values after the index and shift them up one
                    for i in range(index * 3, len(palette)-6, 3):
                        palette[i] = palette[i+3]
                        palette[i+1] = palette[i+4]
                        palette[i+2] = palette[i+5]
                    palette[len(palette)-3] = 0
                    palette[len(palette)-2] = 0
                    palette[len(palette)-1] = 0
                    # Scan the whole image and change all values that were shifted
                    for j in range(image.height):
                        for i in range(image.width):
                            if image.getpixel((i, j)) > index:
                                image.putpixel((i, j), image.getpixel((i, j)) - 1)
                    image.putpalette(palette)
                    num_colors = num_colors - 1

        # Get the width and height of the image
        width, height = image.size

        # Get the pixel data from the image
        pixel_data = list(image.getdata())

        category_id = 0
        displayed_name = "Default Image"

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
        output_file = open(os.path.join(output_dir, file_name + '.pic'), "wb")

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

        if use_transparency == "1":
            # Count the number of zeroes in alpha_channel
            num_playable_squares = 0
            for j in range(alpha_channel.height):
                for i in range(alpha_channel.width):
                    if alpha_channel.getpixel((i, j)) != 0:
                        num_playable_squares = num_playable_squares + 1
            # Write the transparency flag, non-transparent_squares and 22 0 bytes to the file
            output_file.write(b"\x01")
            output_file.write(num_playable_squares.to_bytes(2, byteorder="little"))
            output_file.write(b"\x00" * 20)
        else:
            # Write 23 0 bytes to the file
            output_file.write(b"\x00" * 23)

        if write_rle == False:
            output_file.write(bytes(pixel_data))
        else:
            output_file.write(bytes(rle_data))

        if use_transparency == "1":
            alpha_pixels = list(alpha_channel.getdata())
            if write_rle == False:
                output_file.write(bytes(alpha_pixels))
            else:
                alpha_rle_pixels = run_length_encode(alpha_pixels)
                output_file.write(bytes(alpha_rle_pixels))

        # Close the file
        output_file.close()

        if debug_output == True:
            image.save(os.path.join(output_dir, file_name + '_converted' + '.png'), "PNG")

if __name__ == "__main__":
    main()

