# dmag5

Written and tested on Ubuntu 22.04.

Creates a depth map (disparity map) from a stereo pair using local matching (guided filter).

This repo is an implementation of:

[Fast Cost-Volume Filtering for Visual Correspondence and Beyond by Christoph Rhemann, Asmaa Hosni, Michael Bleyer, Carsten Rother, and Margrit Gelautz](http://research.microsoft.com/pubs/147301/rhemannetal.pdf)

To create the executable, compile the code in directory "dmag5" using "make -f Makefile_g/Makefile_O" and then go into the "main" directory and create the exec using "make".

Test cases are given in the "test" directory.

Info about dmag5 (theory behind it and how to use it) can be found here:

[Depth Map Automatic Generator 5 (DMAG5)](https://3dstereophoto.blogspot.com/2014/05/depth-map-automatic-generator-5-dmag5.html)

[Fast Cost Volume Filtering for Stereo Matching](https://3dstereophoto.blogspot.com/2014/05/fast-cost-volume-filtering-for-stereo.html)

[Guided Image Filtering](https://3dstereophoto.blogspot.com/2014/05/guided-image-filtering.html)

Dependencies (check the Makefiles):

"common" repo
