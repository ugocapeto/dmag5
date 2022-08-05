#include "header.h"
#include "proto.h"

void fill_occlusion_left_right(
 int width,
 int height,
 int *disp_arr,
 int *occ_arr,
 int min_d,
 int max_d
)

{

 int i;
 int j;
 int ind;
 int occ;
 int ind0;
 int d0;
 int occ0;
 int ind1;
 int d1;
 int occ1;
 int j0;
 int j1;
 int d;

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;
       occ= occ_arr[ind];
       if ( occ == 255 )
        continue;

       /*
       If here,
       pixel is occluded
       */

       /* 
       Go to the left to find closest non occluded pixel
       */

       for ( j0= j-1 ; j0 >= 0 ; j0-- ) {
          ind0= i*width+j0;
          d0= disp_arr[ind0];
          occ0= occ_arr[ind0];
          if ( occ0 == 0 )
           continue;

          /*
          If here,
          pixel is not occluded
          */

          break;
       }

       /*
       Go to the right to find closest non occluded pixel
       */

       for ( j1= j+1 ; j1 < width ; j1++ ) {
          ind1= i*width+j1;
          d1= disp_arr[ind1];
          occ1= occ_arr[ind1];
          if ( occ1 == 0 )
           continue;

          /*
          If here, 
          pixel is not occluded
          */

          break;
       }

       /*
       Take the smallest disparity among the left and right disparities
       */ 

       d= max_d+1;
       if ( j0 >= 0 ) {

          /*
          We have found a pixel on the left that's not occluded
          */ 

          if ( d0 < d )
           d= d0;
       }
       if ( j1 <= (width-1) ) {

          /*
          We have found a pixel on the right that's not occluded
          */ 

          if ( d1 < d )
           d= d1;
       }
       if ( d == (max_d+1) ) {

          /*
          We have found no non-occluded pixel on the left or right
          */

          d= min_d;
       }

       disp_arr[ind]= d;
    }
 }

}
