#include "header.h"
#include "proto.h"

void print_weight_image(
 int width,
 int height,
 double *image1_r,
 double *image1_g,
 double *image1_b,
 double *mean1_r,
 double *mean1_g,
 double *mean1_b,
 double *var1_rr,
 double *var1_rg,
 double *var1_rb,
 double *var1_gg,
 double *var1_gb,
 double *var1_bb,
 double epsilon,
 int radius,
 int i_ref,
 int j_ref
)

/*
(i_ref,j_ref) represents pixel i
*/

{

 int *image_arr;
 int index;
 int mask_i;
 int mask_j;
 int i;
 int j;
 int I;
 int window_size;
 double weight;
 double I_dbl;
 double sum_weight;
 double min_weight;
 double max_weight;
 double *weight_arr;

 window_size= (2*radius+1)*(2*radius+1);

 weight_arr= (double *)calloc(window_size,sizeof(double));

 image_arr= (int *)calloc(window_size,sizeof(int));

 index= 0;
 for ( mask_i= -radius ; mask_i<= radius ; mask_i++ ) {
    i= i_ref+mask_i;

    if ( i < 0 ) {
       index+= (2*radius+1);
       continue;
    }
    if ( i > (height-1) ) {
       index+= (2*radius+1);
       continue;
    }

    for ( mask_j= -radius ; mask_j<= radius ; mask_j++ ) {
       j= j_ref+mask_j;

       if ( j < 0 ) {
          index++;
          continue;
       }
       if ( j > (width-1) ) {
          index++;
          continue;
       }

       /*
       Compute weight for that pixel
       */

       weight= compute_weight(
        width,
        height,
        image1_r,
        image1_g,
        image1_b,
        mean1_r,
        mean1_g,
        mean1_b,
        var1_rr,
        var1_rg,
        var1_rb,
        var1_gg,
        var1_gb,
        var1_bb,
        epsilon,
        radius,
        i_ref,
        j_ref,
        i,
        j
       );

       weight_arr[index]= weight;
       index++;
    }
 }

 sum_weight= 0;
 min_weight= 1.0e32;
 max_weight=-1.0e32;
 for ( index= 0 ; index< window_size ; index++ ) {
    weight= weight_arr[index];
    sum_weight+= weight;
    if ( weight < min_weight )
     min_weight= weight;
    if ( weight > max_weight )
     max_weight= weight;
 }

 for ( index= 0 ; index< window_size ; index++ ) {
    weight= weight_arr[index];
    I_dbl= 255*(weight-min_weight)/(max_weight-min_weight);
    I= (int)(I_dbl+.5);
    if ( I < 0 )
     I= 0;
    if ( I > 255 )
     I= 255;
    image_arr[index]= I;
 }

 /*
 Comment out so that qt can link
 */

 /*
 write_image_arr_into_tiff("duh.tiff",2*radius+1,2*radius+1,image_arr);
 */

 free(weight_arr);

 free(image_arr);

}
