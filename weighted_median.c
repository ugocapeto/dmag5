#include "header.h"
#include "proto.h"

void weighted_median(
 int width,
 int height,
 int *image_arr,
 int *disp_arr,
 int *occ_arr,
 int min_d,
 int max_d,
 int radius,
 double sigma_space,
 double sigma_color,
 int *new_disp_arr
)

{

 int size;
 double *hist_arr;
 int i;
 int j;
 int ind;
 int occ;
 int hist_ind;

 /*
 Allocate memory for the disparity histogram
 */

 size= max_d-min_d+1;

 hist_arr= (double *)calloc(size,sizeof(double)); 

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;

       /* 
       Check if occluded
       */

       occ= occ_arr[ind];
       if ( occ == 255 ) {

          /*
          Not occluded
          */

          new_disp_arr[ind]= disp_arr[ind];
          continue;
       }

       /*
       If here,
       pixel is occluded
       */

       /*
       Smooth the disparity using a bilateral filter
       */

       /*
       Get disparity histogram
       */

       weighted_histo(
        width,
        height,
        image_arr,
        disp_arr,
        occ_arr,
        min_d,
        max_d, 
        radius,
        sigma_space,
        sigma_color,
        i,
        j,
        hist_arr
       );

       /*
       Get histogram median
       */

       hist_ind= median_histo(
        min_d,
        max_d,
        hist_arr
       );

       new_disp_arr[ind]= min_d+hist_ind;
    }
 }

 /*
 Free disparity histogram
 */
 
 free(hist_arr);

}
