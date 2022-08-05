#include "header.h"
#include "proto.h"

void weighted_histo(
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
 int i_ref,
 int j_ref,
 double *hist_arr
)

{

 int hist_ind;
 int mask_i;
 int mask_j;
 int i;
 int j;
 int ind;
 int d;
 int dist_space_squared;
 int dist_color_squared;
 double val;
 double weight;

 for ( hist_ind= 0 ; hist_ind< max_d-min_d+1 ; hist_ind++ )
  hist_arr[hist_ind]= 0;

 for ( mask_i= -radius ; mask_i<= radius ; mask_i++ ) {
    i= i_ref+mask_i;
    if ( i < 0 )
     continue;
    if ( i > (height-1) )
     continue;
    for ( mask_j= -radius ; mask_j<= radius ; mask_j++ ) {
       j= j_ref+mask_j;
       if ( j < 0 )
        continue;
       if ( j > (width-1) )
        continue;
       ind= i*width+j;
       d= disp_arr[ind];
       dist_space_squared= mask_i*mask_i+mask_j*mask_j;
       dist_color_squared= color_distance_squared(
        width,
        height,
        image_arr,
        i_ref,
        j_ref,
        i,
        j
       );
       val= 0.0;
       val+= (double)dist_space_squared/(sigma_space*sigma_space);
       val+= (double)dist_color_squared/(sigma_color*sigma_color);
       weight= exp(-val);
       hist_arr[d-min_d]+= weight;
    }
 }

}
