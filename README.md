# dmag2

Written and tested on Ubuntu 22.04.

Creates a depth map (disparity map) from a stereo pair using local matching.

This repo is an implementation of

[Adaptive Support-Weight Approach for Correspondence Search by Kuk-Jin Yoon et al.](https://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.899.2691&rep=rep1&type=pdf).

To create the executable, compile the code in directory "dmag2" using "make -f Makefile_g/Makefile_O" and then go into the "main" directory and create the exec using "make".

Test cases are given in the "test" directory.

Info about dmag2 (theory behind it and how to use it) can be found here:

[Depth Map Automatic Generator 2 (DMAG2)](https://3dstereophoto.blogspot.com/2013/06/depth-map-automatic-generator-2-dmag2.html)

[Stereo Matching - Local Methods](https://3dstereophoto.blogspot.com/2012/01/stereo-matching-local-methods.html)

[Weighted Windows for Stereo Correspondence Search](https://3dstereophoto.blogspot.com/2013/09/weighted-windows-for-stereo.html)

Dependencies (check the Makefiles):

"common" repo
