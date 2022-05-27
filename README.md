# Damaniel's Pixel By Number
![Title screen](https://user-images.githubusercontent.com/1784332/170628024-9f7f6ee1-70ab-44e0-99c3-d670a45a9e28.png)

This is an in-progress paint by number game.  Think something like the mobile 
game Cross Stitch World, or something like actual diamond painting.  While the
game is playable, it's far from complete.  

### Requirements

- A 386 or higher (it runs in protected mode)
- Some amount of RAM.  4MB is probably enough in all cases.  Smaller images
  will work with 2.
- A VGA card.  It uses Mode 13 (320x200, 256 colors), supported by all VGAs.
- A copy of CWSDPMI.EXE, either in the program directory or on your PATH.

### Additional tools

There are 2 tools in the 'tools' directory.  You can build them by running 
`make tools` from the root of the main directory.  These tools are:

- convert: The tool that creates picture files from PCX files.  Run convert.exe
           for usage instructions
- expand: takes a PCX saved in 16 color mode and converts it to a 256 color
          version.  This is important since it allows the creation of picture
          files with fewer than 16 colors while maintaining compatibility with
          Allegro.

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

### What's left to do?

Lots. Many of these I'll do, but some probably not.  These include:

- Option screen (continue last, start/continue another)
- Periodic auto-save
- More pictures (and pictures that aren't test/prototype images)!
- MIDI player
- Sound effects
- (and plenty of other stuff I haven't thought of yet)

### Additional notes
- Currently, images can be up to 320x200 pixels in size, with up to 64 colors.

## Screenshots
![In-game](https://user-images.githubusercontent.com/1784332/170628027-d92280e7-9306-422f-be59-8887636a4a65.png)
![Map screen](https://user-images.githubusercontent.com/1784332/170628029-4828cb7b-b659-4449-b493-d449859cda37.png)
![Replay screen](https://user-images.githubusercontent.com/1784332/170628031-a991c332-60d5-4b0f-99f7-2ba5e3a90de8.png)
![Load screen)](https://user-images.githubusercontent.com/1784332/170628033-599bc190-9dc6-4c36-8247-53e2ad28d3d7.png)
![Alternate square style](https://user-images.githubusercontent.com/1784332/170628034-cf7ee08a-1472-43d3-b475-e3036155941f.png)

