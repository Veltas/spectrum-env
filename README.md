Environment for ZX Spectrum
===========================

Building
--------

Prerequisites:

* zasm Z80 assembler  
  https://k1.spdns.de/Develop/Projects/zasm/Distributions/
* SDCC (tested with 3.5.0)  
  http://sdcc.sourceforge.net/
* Make implementation  
  e.g. GNU Make, BSD pmake, Microsoft NMAKE
* zx-spectrum-utils  
  https://sourceforge.net/projects/zxspectrumutils/
* fuse-emulator-utils (only needed to generate audio file)  
  https://sourceforge.net/p/fuse-emulator/code/HEAD/tree/trunk/fuse-utils/

The tools and utilities used to build this project have only been tested on
GNU/Linux and FreeBSD.

SDCC has generated incorrect assembly code on later versions than 3.5.0.

The default make target will build the project, and produce `.tap` and `.wav`
files to run it in an emulator or on the real hardware.

    $ cd zapp-extract-location/
    $ make


Running in an emulator
----------------------

Prerequisites:

* A ZX Spectrum emulator

For UNIX/X11 systems Fuse (the Free Unix Spectrum Emulator) is recommended.  
http://fuse-emulator.sourceforge.net/

The instructions in the 'Building' section produce a `.tap` file, and can
produce a `.wav` file as well. All ZX Spectrum emulators will support the
`.wav`, some will support the `.tap` (and will load the program faster if so).

If loading from the `.wav` you may need to initiate the loading routine
manually:

1. Enter `LOAD ""` (`j`, `sym. shift + p`, `sym. shift + p`) -- `sym. shift`
   key is usally bound to the Alt key in most emulators.
2. Play the audio file.


Running on the ZX Spectrum
--------------------------

Prerequisites:

* Sinclair ZX Spectrum 48K (or better)
* Male-male 3.5mm audio jack / phone connector
* Audio player

Your audio player will need to play the `.wav` file produced in the section
'Building'. This could be e.g. an MP3 player, phone, laptop, or even a cassette
tape, but ultimately will need to plug into the ZX Spectrum's MIC port while
playing the audio.

1. Turn on the ZX Spectrum and connect it to your TV/monitor.
2. Connect the audio player's headphone or line out port to the Spectrum's MIC
   port (ensure the audio player is set to full volume).
3. Enter the Sinclair BASIC command `LOAD ""`.
4. Play the audio file.

* * *

Copyright for files not in `sdcc` directory waived by CC0, see `COPYING` and the
below copyright notice.

### ZX Spectrum Environment

Written in 2017 by Christopher J. Leonard <chris.j.leonard@gmx.com>.

**To the extent possible under law, the author(s) have dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.**

You should have received a copy of the CC0 Public Domain Dedication along with
this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
