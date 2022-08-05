#include "header.h"
#include "proto.h"

void compute_disparity_maps(
 int width,
 int height,
 int *image1_arr,
 int *image2_arr,
 int min_d,
 int max_d,
 int radius,
 double alpha,
 double max_cost_color,
 double max_cost_gradient,
 int epsilon_int,
 int disp_tol,
 int radius_smooth,
 double sigma_space,
 double sigma_color,
 int ds_factor,
 int **pdisp1_arr,
 int **pdisp2_arr,
 int **pocc1_arr,
 int **pocc2_arr
)

{

 int err_flag;
 int width1;
 int height1;
 int width2;
 int height2;
 FILE *fp;
 int min_d1;
 int max_d1;
 int min_d2;
 int max_d2;
 int *disp1_arr;
 int *normalized_disp1_arr;
 int *disp2_arr;
 int *normalized_disp2_arr;
 int *occ1_arr;
 int *occ2_arr;
 double epsilon;
 int width_ds;
 int height_ds;
 int *image1_ds_arr;
 int *image2_ds_arr;
 int i_ds;
 int j_ds;
 int i;
 int j;
 int *disp1_ds_arr;
 int *disp2_ds_arr;
 int *occ1_ds_arr;
 int *occ2_ds_arr;
 int min_d_ds;
 int max_d_ds;
 int min_d1_ds;
 int max_d1_ds;
 int min_d2_ds;
 int max_d2_ds;
 int radius_ds;
 int *normalized_disp1_ds_arr;
 int *normalized_disp2_ds_arr;
 int pixel_ds;
 int pixel;
 int cind;
 int disp_tol_ds;
 int radius_smooth_ds;
 double sigma_space_ds;
 double factor;

 epsilon= 255*255*pow(10,-epsilon_int);

 min_d1= min_d;
 max_d1= max_d;
 min_d2=-max_d;
 max_d2=-min_d;

 /*
 Downsample the images by a factor of 1/ds_factor
 */

 factor=1/(double)ds_factor;

 dmag5_downsample_image_dimensions(
  width,
  height,
  &width_ds,
  &height_ds,
  factor
 );

 image1_ds_arr= (int *)calloc(width_ds*height_ds,3*sizeof(int));

 dmag5_downsample_rgb_image_int(
  image1_arr,
  width,
  height,
  image1_ds_arr,
  width_ds,
  height_ds,
  factor
 );

 /*
 write_rgb_image_arr(
  "image1_ds.tiff",
  width_ds,
  height_ds,
  image1_ds_arr
 );
 */

 image2_ds_arr= (int *)calloc(width_ds*height_ds,3*sizeof(int));

 dmag5_downsample_rgb_image_int(
  image2_arr,
  width,
  height,
  image2_ds_arr,
  width_ds,
  height_ds,
  factor
 );

 /*
 write_rgb_image_arr(
  "image2_ds.tiff",
  width_ds,
  height_ds,
  image2_ds_arr
 );
 */

 min_d_ds= (int)((double)min_d/(double)ds_factor);
 max_d_ds= (int)((double)max_d/(double)ds_factor);

 min_d1_ds= min_d_ds;
 max_d1_ds= max_d_ds;
 min_d2_ds=-max_d_ds;
 max_d2_ds=-min_d_ds;

 radius_ds= (int)((double)radius/(double)ds_factor);

 disp_tol_ds= (int)((double)disp_tol/(double)ds_factor);

 radius_smooth_ds= (int)((double)radius_smooth/(double)ds_factor);

 sigma_space_ds= sigma_space/(double)ds_factor;

 /*
 Get the disparity map 1
 */

 disp1_ds_arr= (int *)calloc(width_ds*height_ds,sizeof(int));

 fprintf(stdout,"Getting the disparity map for image 1 ...\n");

 fast_cost_volume_filter(
  width_ds,
  height_ds,
  image1_ds_arr,
  image2_ds_arr,
  min_d1_ds,
  max_d1_ds,
  radius_ds,
  alpha,
  max_cost_color,
  max_cost_gradient,
  epsilon,
  disp1_ds_arr
 );

 fprintf(stdout,"Getting the disparity map for image 1 ... done.\n");

 /*
 normalized_disp1_ds_arr= (int *)calloc(width_ds*height_ds,sizeof(int));

 normalize_image(
  disp1_ds_arr,
  normalized_disp1_ds_arr,
  width_ds*height_ds,
  min_d1_ds,
  max_d1_ds
 );

 write_image_arr_into_jpeg(
  "disp1_ds.jpg",
  width_ds,
  height_ds,
  normalized_disp1_ds_arr
 );

 free(normalized_disp1_ds_arr);
 */

 /*
 Get the disparity map 2
 */

 disp2_ds_arr= (int *)calloc(width_ds*height_ds,sizeof(int));

 fprintf(stdout,"Getting the disparity map for image 2 ...\n");

 fast_cost_volume_filter(
  width_ds,
  height_ds,
  image2_ds_arr,
  image1_ds_arr,
  min_d2_ds,
  max_d2_ds,
  radius_ds,
  alpha,
  max_cost_color,
  max_cost_gradient,
  epsilon,
  disp2_ds_arr
 );

 fprintf(stdout,"Getting the disparity map for image 2 ... done.\n");

 /*
 normalized_disp2_ds_arr= (int *)calloc(width_ds*height_ds,sizeof(int));

 normalize_image(
  disp2_ds_arr,
  normalized_disp2_ds_arr,
  width_ds*height_ds,
  min_d2_ds,
  max_d2_ds
 );

 write_image_arr_into_jpeg(
  "disp2_ds.jpg",
  width_ds,
  height_ds,
  normalized_disp2_ds_arr
 );

 free(normalized_disp2_ds_arr);
 */

 /*
 Detect occlusions in image 1
 */

 occ1_ds_arr= (int *)calloc(width_ds*height_ds,sizeof(int));

 fprintf(stdout,"Detecting occlusions in image 1 ...\n");

 detect_occlusion(
  width_ds,
  height_ds,
  disp1_ds_arr,
  disp2_ds_arr,
  min_d1_ds,
  max_d1_ds,
  disp_tol_ds,
  occ1_ds_arr
 );

 fprintf(stdout,"Detecting occlusions in image 1 ... done.\n");

 /*
 write_image_arr_into_jpeg(
  "occ1_ds.jpg",
  width_ds,
  height_ds,
  occ1_ds_arr
 );
 */

 /*
 Detect occlusions in image 2
 */

 occ2_ds_arr= (int *)calloc(width_ds*height_ds,sizeof(int));

 fprintf(stdout,"Detecting occlusions in image 2 ...\n");

 detect_occlusion(
  width_ds,
  height_ds,
  disp2_ds_arr,
  disp1_ds_arr,
  min_d2_ds,
  max_d2_ds,
  disp_tol_ds,
  occ2_ds_arr
 );

 fprintf(stdout,"Detecting occlusions in image 2 ... done.\n");

 /*
 write_image_arr_into_jpeg(
  "occ2_ds.jpg",
  width_ds,
  height_ds,
  occ2_ds_arr
 );
 */

 /*
 Fill occlusions in image 1
 */

 fprintf(stdout,"Filling occlusions in image 1 ...\n");

 fill_occlusion_left_right(
  width_ds,
  height_ds,
  disp1_ds_arr,
  occ1_ds_arr,
  min_d1_ds,
  max_d1_ds
 );

 fprintf(stdout,"Filling occlusions in image 1 ... done.\n");

 /*
 normalized_disp1_ds_arr= (int *)calloc(width_ds*height_ds,sizeof(int));

 normalize_image(
  disp1_ds_arr,
  normalized_disp1_ds_arr,
  width_ds*height_ds,
  min_d1_ds,
  max_d1_ds
 );

 write_image_arr_into_jpeg(
  "disp1_ds.jpg",
  width_ds,
  height_ds,
  normalized_disp1_ds_arr
 );

 free(normalized_disp1_ds_arr);
 */

 /*
 Fill occlusions in image 2
 */

 fprintf(stdout,"Filling occlusions in image 2 ...\n");

 fill_occlusion_right_left(
  width_ds,
  height_ds,
  disp2_ds_arr,
  occ2_ds_arr,
  min_d2_ds,
  max_d2_ds
 );

 fprintf(stdout,"Filling occlusions in image 2 ... done.\n");

 /*
 normalized_disp2_ds_arr= (int *)calloc(width_ds*height_ds,sizeof(int));

 normalize_image(
  disp2_ds_arr,
  normalized_disp2_ds_arr,
  width_ds*height_ds,
  min_d2_ds,
  max_d2_ds
 );

 write_image_arr_into_jpeg(
  "disp2_ds.jpg",
  width_ds,
  height_ds,
  normalized_disp2_ds_arr
 );

 free(normalized_disp2_ds_arr);
 */

 /*
 Smooth (with a bilateral filter) occlusions in image 1
 */

 fprintf(stdout,"Smoothing occlusions in image 1 ...\n");

 smooth_occlusion_weighted_median(
  width_ds,
  height_ds,
  image1_ds_arr,
  disp1_ds_arr,
  occ1_ds_arr,
  min_d1_ds,
  max_d1_ds,
  radius_smooth_ds,
  sigma_space_ds,
  sigma_color
 );

 fprintf(stdout,"Smoothing occlusions in image 1 ... done.\n");

 /*
 normalized_disp1_ds_arr= (int *)calloc(width_ds*height_ds,sizeof(int));

 normalize_image(
  disp1_ds_arr,
  normalized_disp1_ds_arr,
  width_ds*height_ds,
  min_d1_ds,
  max_d1_ds
 );

 write_image_arr_into_jpeg(
  "disp1_ds.jpg",
  width_ds,
  height_ds,
  normalized_disp1_ds_arr
 );

 free(normalized_disp1_ds_arr);
 */

 /*
 Smooth (with a bilateral filter) occlusions in image 2
 */

 fprintf(stdout,"Smoothing occlusions in image 2 ...\n");

 smooth_occlusion_weighted_median(
  width_ds,
  height_ds,
  image2_ds_arr,
  disp2_ds_arr,
  occ2_ds_arr,
  min_d2_ds,
  max_d2_ds,
  radius_smooth_ds,
  sigma_space_ds,
  sigma_color
 );

 fprintf(stdout,"Smoothing occlusions in image 2 ... done.\n");

 /*
 normalized_disp2_ds_arr= (int *)calloc(width_ds*height_ds,sizeof(int));

 normalize_image(
  disp2_ds_arr,
  normalized_disp2_ds_arr,
  width_ds*height_ds,
  min_d2_ds,
  max_d2_ds
 );

 write_image_arr_into_jpeg(
  "disp2_ds.jpg",
  width_ds,
  height_ds,
  normalized_disp2_ds_arr
 );

 free(normalized_disp2_ds_arr);
 */

 /*
 Upsample disp1_ds_arr
 */

 disp1_arr= (int *)calloc(width*height,sizeof(int));

 for ( i= 0 ; i< height ; i++ ) {
    i_ds= (int)((double)i/(double)ds_factor);
    if ( i_ds > height_ds-1 ) {
       i_ds= height_ds-1;
    }
    for ( j= 0 ; j< width ; j++ ) {
       j_ds= (int)((double)j/(double)ds_factor);
       if ( j_ds > width_ds-1 ) {
          j_ds= width_ds-1;
       }
       disp1_arr[i*width+j]= ds_factor*disp1_ds_arr[i_ds*width_ds+j_ds];
    }
 }

 /*
 normalized_disp1_arr= (int *)calloc(width*height,sizeof(int));

 normalize_image(
  disp1_arr,
  normalized_disp1_arr,
  width*height,
  min_d1,
  max_d1
 );

 write_image_arr_into_jpeg(
  "disp1.jpg",
  width,
  height,
  normalized_disp1_arr
 );

 free(normalized_disp1_arr);
 */

 /*
 Upsample disp2_ds_arr
 */

 disp2_arr= (int *)calloc(width*height,sizeof(int));

 for ( i= 0 ; i< height ; i++ ) {
    i_ds= (int)((double)i/(double)ds_factor);
    if ( i_ds > height_ds-1 ) {
       i_ds= height_ds-1;
    }
    for ( j= 0 ; j< width ; j++ ) {
       j_ds= (int)((double)j/(double)ds_factor);
       if ( j_ds > width_ds-1 ) {
          j_ds= width_ds-1;
       }
       disp2_arr[i*width+j]= ds_factor*disp2_ds_arr[i_ds*width_ds+j_ds];
    }
 }

 /*
 normalized_disp2_arr= (int *)calloc(width*height,sizeof(int));

 normalize_image(
  disp2_arr,
  normalized_disp2_arr,
  width*height,
  min_d2,
  max_d2
 );

 write_image_arr_into_jpeg(
  "disp2.jpg",
  width,
  height,
  normalized_disp2_arr
 );

 free(normalized_disp2_arr);
 */

 /*
 Upsample occ1_ds_arr
 */

 occ1_arr= (int *)calloc(width*height,sizeof(int));

 for ( i= 0 ; i< height ; i++ ) {
    i_ds= (int)((double)i/(double)ds_factor);
    if ( i_ds > height_ds-1 ) { 
       i_ds= height_ds-1;
    }
    for ( j= 0 ; j< width ; j++ ) {
       j_ds= (int)((double)j/(double)ds_factor);
       if ( j_ds > width_ds-1 ) {
          j_ds= width_ds-1;
       }
       occ1_arr[i*width+j]= occ1_ds_arr[i_ds*width_ds+j_ds];
    }
 }

 /*
 write_image_arr_into_jpeg( 
  "occ1.jpg",
  width,
  height,
  occ1_arr
 );
 */

 /*
 Upsample occ2_ds_arr
 */

 occ2_arr= (int *)calloc(width*height,sizeof(int));

 for ( i= 0 ; i< height ; i++ ) {
    i_ds= (int)((double)i/(double)ds_factor);
    if ( i_ds > height_ds-1 ) {
       i_ds= height_ds-1;
    }
    for ( j= 0 ; j< width ; j++ ) {
       j_ds= (int)((double)j/(double)ds_factor);
       if ( j_ds > width_ds-1 ) {
          j_ds= width_ds-1;
       }
       occ2_arr[i*width+j]= occ2_ds_arr[i_ds*width_ds+j_ds];
    }
 }

 /*
 write_image_arr_into_jpeg(
  "occ2.jpg",
  width,
  height,
  occ2_arr
 );
 */

 /*
 Free memory
 */

 free(image1_ds_arr);
 free(image2_ds_arr);
 free(disp1_ds_arr);
 free(disp2_ds_arr);
 free(occ1_ds_arr);
 free(occ2_ds_arr);

 (*pdisp1_arr)= disp1_arr;
 (*pdisp2_arr)= disp2_arr;
 (*pocc1_arr)= occ1_arr;
 (*pocc2_arr)= occ2_arr;

}
