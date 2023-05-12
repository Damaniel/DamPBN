# Damaniel's Pixel By Number
![Title screen](https://user-images.githubusercontent.com/1784332/170628024-9f7f6ee1-70ab-44e0-99c3-d670a45a9e28.png)

This is a paint by number game.  Think something like the mobile game Cross Stitch World, or something like actual diamond painting.

While I'm not ready to call the game 'complete', I believe that all of the planned functionality is in.

### Requirements

- A 386 or higher (it runs in protected mode)
- Some amount of RAM.  4MB is probably enough in all cases.  Smaller images
  will work with 2.
- A VGA card.  It uses Mode 13 (320x200, 256 colors), supported by all VGAs.
- A copy of CWSDPMI.EXE, either in the program directory or on your PATH.

### Additional tools

There are some tools in the 'tools' directory.  You can build the C programs
them by running `make tools` from the root of the main directory.  These tools are:

- convert: The tool that creates picture files from PCX files.  Run convert.exe
           for usage instructions
- expand: takes a PCX saved in 16 color mode and converts it to a 256 color
          version.  This is important since it allows the creation of picture
          files with fewer than 16 colors while maintaining compatibility with
          Allegro.
- installer: creates an installer for the game, meant for copying files from a floppy
             disk to (presumably) a hard drive

The python tools are some batch converters that I'm using to make larger collections.
They are:

- batch_convert.py: takes a directory of image files and creates a set of DamPBN picture
                    files in a separate output directory.  Supported image file formats
                    are JPG, PNG and PCX.  This converter will also adjust the image
                    size and color palette if needed, so any images can be used without
                    preprocessing.
- image_process.py: takes 2 directories of identical files - one with original names, one
                    with numbered names, and makes a metadata file for batch_convert.py
- image_split.py: takes a pile of images and divides them into groups of 50, putting each
                  group into sequentially numbered directories

An additional python tool is present:

- generate_manifest.py: creates a manifest for the installer.  Scans a directory tree
                        and generates a file that tells the installer what directories to
                        make and what files to copy

### Build requirements

This program can be built in one of two ways:

- A modern version of DJGPP and Allegro (9.3.0 and 4.2.2 respectively).
- My 'old' toolchain (gcc 2.95.2 and Allegro 3.12)

The modern version is the default.  Running `make` will generate this version
of the program.  If you want to build the old version, running 
`make -f Makefile.295` will do that instead.

Also note that the 2.9.x toolchain isn't widely available - I have a bespoke
setup on my PC for it.  The main reason to use it is compile speed - it builds
much faster on older hardware and generates smaller executables.  The newer
version also loads a fair bit slower on older hardware, though seems to run
more or less at the same speed.  For playing around on DOSBox, the default
build is fine - the 'old' build will probably just be offered as binary
packages for now.

Note that the upx call in `make prod` in the modern DJGPP build will fail
on DOSbox due to the compiler setting the executable read-only.  For now,
until I figure out what to do about it, just run upx on it manually if
desired. 

### Deployment

The steps required to deploy a copy of the game is:

- Build the code
- Build the tools
- (If needed) Build the installer
- Copy the required distribution files to a target directory and compress them as needed
- Run the manifest generator in the target directory
- Take the resulting directory and use a tool like WinImage to make a floppy image file from it

One issue is that the first 4 steps need to be done from a DOS environment, while the last 2
need to be done in an environment with a copy of Python and a copy of WinImage (or some other tool
that can generate floppy images from a directory tree).  As a result, my current workflow is to:

- Run 'make' or 'make -f Makefile.295 prod' from the DamPBN directory
- Run 'make tools' from the DamPBN\tools directory
- Run 'build' from the DamPBN\tools\install directory
- Copy the relevant files (binaries, cwsdpmi.exe, resources, pic files) to a DIST directory
- Run UPX on all the binaries that need it (dampbn.exe, install.exe, covert.exe, expand.exe) in DIST
- Run the manifest generator from DIST
- Use WinImage to make a disk from the contents of DIST

Not very convenient (and it certainly could be more automatable with some work), but I make releases
so infrequently that I don't mind doing a couple manual steps once or twice a year.

### What's done

- Logo screen, title screen
- Save / Load
- Mouse support
- Funcional timer
- 'Mark' (highlight) function
- 3 different pixel styles
- Overview 'map' showing overall progress
- High level overview on the main game screen
- Load picture menu
- Help screen
- Replay of draw progress on screen when picture is complete
- Auto save on exit
- The ability to watch completed replays from the image select screen
- An installer (and a floppy image that uses it)
- An experimental MIDI player
- Option screen (continue last, start/continue another), with configuration save
- Periodic auto-save

Note that the MIDI player itself isn't experimental (it's just using Allegro code), the behavior is.
It currently plays through a series of MIDI files that are placed into RES/MUSIC, as long as
the player is working on an image.  It doesn't play on the title screen, loading screen 
(when coming from the title screen), or the image complete screen, since if I were to provide MIDI files,
there would be separate ones for each of those.  I'm sure I'll come up with
something better and I'm planning to add keys to play the previous/next song in the list. 

### What's left to do?

Right now, the only other feature I might add is some sound effects, but I don't think that would
add very much.  Functionally, I think the game is complete.

Outside of the game, I need to finish up the manual, which is mainly adding the option section, make the
terminology more consistent ('Image' instead of 'Picture'), and check for typos/incorrect stuff.

### Current bugs to fix
- None that I know of, but I'm sure there's plenty.

### Additional notes
Currently, images can be up to 320x200 pixels in size, with up to 64 colors.  There are two Image versions:
 - version 1 only supports square/rectangular images (i.e. every square in a X x Y region needs to be a color)
 - version 2 allows non-square/irregular images.  The tools that create these use a transparency mask to
   determine which squares will need to be colored and which won't.
 - Version 2 is backward and forward compatible.  The version 1 reader will skip version 2 data, and 
   the version 2 reader treats the version 1 files like earlier versions of the game.

## Screenshots
![In-game](https://user-images.githubusercontent.com/1784332/170628027-d92280e7-9306-422f-be59-8887636a4a65.png)
![Map screen](https://user-images.githubusercontent.com/1784332/170628029-4828cb7b-b659-4449-b493-d449859cda37.png)
![Replay screen](https://user-images.githubusercontent.com/1784332/170628031-a991c332-60d5-4b0f-99f7-2ba5e3a90de8.png)
![Load screen)](https://user-images.githubusercontent.com/1784332/170628033-599bc190-9dc6-4c36-8247-53e2ad28d3d7.png)
![Alternate square style](https://user-images.githubusercontent.com/1784332/170628034-cf7ee08a-1472-43d3-b475-e3036155941f.png)

