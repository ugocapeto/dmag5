#include "header.h"
#include "proto.h"

void detect_occlusion(
 int width,
 int height,
 int *disp1_arr,
 int *disp2_arr,
 int min_d,
 int max_d,
 int disp_tol,
 int *occ1_arr
)

{

 int i;
 int j;
 int ind;
 int ind2;
 int d;
 int j2;
 int d2;
 int diff;

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;

       /* 
       Get the disparity
       */

       d= disp1_arr[ind];

       if ( d < min_d )
        dmag5_error_handler("detect_occlusion");
       if ( d > max_d )
        dmag5_error_handler("detect_occlusion");

       /*
       Get pixel in image 2
       */

       j2= j-d;
       ind2= i*width+j2;

       /*
       Initialize to occluded (black pixel in occlusion map)
       */ 

       occ1_arr[ind]= 0;

       if ( j2 < 0 )
        continue;
       if ( j2 > (width-1) )
        continue;

       /* 
       Get the disparity
       */

       d2= disp2_arr[ind2];

       if ( d2 < (-max_d) )
        dmag5_error_handler("detect_occlusion");
       if ( d2 > (-min_d) )
        dmag5_error_handler("detect_occlusion");

       /*
       Check if the disparities agree
       */

       diff= abs(d+d2);
       if ( diff > disp_tol )
        continue;

       /*
       If still here, not occluded (white pixel in occlusion map)
       */

       occ1_arr[ind]= 255;
    }
 }

}
