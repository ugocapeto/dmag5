#include "header.h"
#include "proto.h"

void box_filter(
 int width,
 int height,
 double *image,
 int radius,
 double *filtered_image
)

/*
The purpose of a box filter is to compute means
over a square window
*/

{

 double *sum_arr;
 double sum;
 int i;
 int j;
 double I;
 int i_lr;
 int j_lr;
 int i_ul;
 int j_ul;
 int i_b;
 int j_b;
 int ind;
 int ind_b;
 int count;
 double sum_j;
 double sum2;
 int i2;
 int j2;
 double I2;
 int ind2;
 double mean;
 int mask_i;
 int mask_j;
 double mean2;
 int count2;

 /*
 Allocate memory for the running cumulative sum
 */

 sum_arr= (double *)calloc(width*height,sizeof(double));

 /*
 Compute the cumulative sum
 */

 /*
 Sum along j
 */

 for ( i= 0 ; i< height ; i++ ) {
    sum= 0;
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;
       I= image[ind];
       sum+= I;
       sum_arr[ind]= sum;
    }
 }

 /*
 Sum what was summed along j
 but this time along i
 */

 for ( j= 0 ; j< width ; j++ ) {
    sum= sum_arr[0*width+j];
    for ( i= 1 ; i< height ; i++ ) {
       ind= i*width+j;
       sum_j= sum_arr[ind];
       sum+= sum_j;
       sum_arr[ind]= sum;  
    }
 }

 /*
 Check!
 */

 /*
 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;
       sum= sum_arr[ind];

       sum2= 0;
       for ( i2= 0 ; i2<= i ; i2++ ) {
          for ( j2= 0 ; j2<= j ; j2++ ) {
             ind2= i2*width+j2;
             I2= image[ind2];
             sum2+= I2;
          }
       }

       if ( sum2 != sum )
        dmag5_error_handler("box_filter");
    }
 }
 */

 /*
 Compute the mean at each pixel
 */

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;

       /* 
       Define the box by its
       lower right corner (i_lr,j_lr) and
       upper left corner (i_ul,j_ul)
       */

       i_lr= i+radius;
       if ( i_lr > (height-1) )
        i_lr= height-1;

       j_lr= j+radius;
       if ( j_lr > (width-1) )
        j_lr= width-1;

       i_ul= i-radius;
       if ( i_ul < 0 )
        i_ul= 0;
       j_ul= j-radius;
       if ( j_ul < 0 )
        j_ul= 0;

       /*
       Get sum at lower right corner of box
       */

       i_b= i_lr;

       j_b= j_lr;

       ind_b= i_b*width+j_b;
       sum= sum_arr[ind_b];

       /*
       Subtract sum at upper right corner of box
       (i_ul-1,j_lr)
       */

       i_b= i_ul-1;

       j_b= j_lr;

       if ( i_b >= 0 ) {
          ind_b= i_b*width+j_b;
          sum-= sum_arr[ind_b];
       }

       /*
       Subtract sum at lower left corner of box
       (i_lr,j_ul-1)
       */

       i_b= i_lr;

       j_b= j_ul-1;

       if ( j_b >= 0 ) {
          ind_b= i_b*width+j_b;
          sum-= sum_arr[ind_b];
       }

       /*
       Add sum at upper left corner of box
       (i_ul-1,j_ul-1)
       */

       i_b= i_ul-1;

       j_b= j_ul-1;

       if ( i_b >= 0 && j_b >= 0 ) {
          ind_b= i_b*width+j_b;
          sum+= sum_arr[ind_b];
       }

       /*
       Get number of pixels in box
       */

       count= (i_lr-i_ul+1)*(j_lr-j_ul+1);
 
       /* 
       Divide sum by nbr of pixels involved
       to get the mean
       */

       mean= sum/(double)count;

       /*
       Store in filtered image
       */

       filtered_image[ind]= mean;

       /*
       Check!
       */

       /*
       sum2= 0;
       count2= 0;
       for ( mask_i= -radius ; mask_i<= radius ; mask_i++ ) {
          i2= i+mask_i;
          if ( i2 < 0 )
           continue;
          if ( i2 > (height-1) )
           continue;
          for ( mask_j= -radius ; mask_j<= radius ; mask_j++ ) {
             j2= j+mask_j;
             if ( j2 < 0 )
              continue;
             if ( j2 > (width-1) )
              continue;
             ind2= i2*width+j2;
             I2= image[ind2];
             sum2+= I2;
             count2++;
          }
       }
       mean2= sum2/(double)count2;

       if ( count2 != count )
        dmag5_error_handler("box_filter");
       if ( mean2 != mean )
        dmag5_error_handler("box_filter");
       */
    }
 }

 /*
 Free memory for the running cumulative sum
 */

 free(sum_arr);

}
