#include "header.h"
#include "proto.h"

void smooth_occlusion_weighted_median(
 int width,
 int height,
 int *image_arr,
 int *disp_arr,
 int *occ_arr,
 int min_d,
 int max_d,
 int radius,
 double sigma_space,
 double sigma_color
)

{

 int i;
 int j;
 int ind;
 int cind;
 int *image_r_arr;
 int *image_g_arr;
 int *image_b_arr;
 int *median_image_r_arr;
 int *median_image_g_arr;
 int *median_image_b_arr;
 int *median_image_arr;
 int *new_disp_arr;
 int radius2=1;

 /*
 Allocate memory for the red channel of image
 */

 image_r_arr= (int *)calloc(width*height,sizeof(int));

 /*
 Get the red channel of image
 */

 cind= 0;
 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;
       image_r_arr[ind]= image_arr[3*ind+cind];
    }
 }

 /*
 Allocate memory for the green channel of image
 */

 image_g_arr= (int *)calloc(width*height,sizeof(int));

 /*
 Get the green channel of image
 */

 cind= 1;
 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;
       image_g_arr[ind]= image_arr[3*ind+cind];
    }
 }

 /*
 Allocate memory for the blue channel of image
 */

 image_b_arr= (int *)calloc(width*height,sizeof(int));

 /*
 Get the blue channel of image
 */

 cind= 2;
 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;
       image_b_arr[ind]= image_arr[3*ind+cind];
    }
 }

 /*
 Allocate memory for the median red channel of image
 */

 median_image_r_arr= (int *)calloc(width*height,sizeof(int));

 /*
 Get the median red channel of image
 */

 median(
  width,
  height,
  image_r_arr,
  radius2,
  median_image_r_arr
 );

 /*
 Allocate memory for the median green channel of image
 */

 median_image_g_arr= (int *)calloc(width*height,sizeof(int));

 /*
 Get the median green channel of image
 */

 median(
  width,
  height,
  image_g_arr,
  radius2,
  median_image_g_arr
 );

 /*
 Allocate memory for the median blue channel of image
 */

 median_image_b_arr= (int *)calloc(width*height,sizeof(int));

 /*
 Get the median blue channel of image
 */

 median(
  width,
  height,
  image_b_arr,
  radius2,
  median_image_b_arr
 );

 median_image_arr= (int *)calloc(width*height,3*sizeof(int));

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;
       median_image_arr[3*ind+0]= median_image_r_arr[ind];
       median_image_arr[3*ind+1]= median_image_g_arr[ind];
       median_image_arr[3*ind+2]= median_image_b_arr[ind];
    }
 }

 /*
 Comment out if don't want to dump the median image
 */

 /*
 write_rgb_image_arr("duh.tiff",width,height,median_image_arr);
 */

 /*
 Allocate memory for new disparity array
 */

 new_disp_arr= (int *)calloc(width*height,sizeof(int));

 /*
 Apply the bilateral filter
 */

 weighted_median(
  width,
  height,
  median_image_arr, 
  disp_arr,
  occ_arr,
  min_d,
  max_d,
  radius,
  sigma_space,
  sigma_color,
  new_disp_arr
 );

 /*
 Update disp_arr
 */

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;
       disp_arr[ind]= new_disp_arr[ind];
    }
 }

 /*
 Free memory
 */

 free(image_r_arr); 

 free(image_g_arr); 

 free(image_b_arr); 

 free(median_image_r_arr);

 free(median_image_g_arr);

 free(median_image_b_arr);

 free(median_image_arr);

 free(new_disp_arr);

}
