#include "header.h"
#include "proto.h"

int main(
 int argc,
 char* argv[]
)

{

 FILE *fp;
 char filename[80];
 char filename1[80];
 char filename2[80];
 char filename_disp1[80];
 char filename_disp2[80];
 char filename_occ1[80];
 char filename_occ2[80];
 int width;
 int height;
 int *I1_arr;
 int *I2_arr;
 int *disp1_arr;
 int *disp2_arr;
 int *disp1_normalized_arr;
 int *disp2_normalized_arr;
 int *occ1_arr;
 int *occ2_arr;
 int min_d1;
 int max_d1;
 int radius;
 double alpha;
 double max_cost_color;
 double max_cost_gradient;
 double epsilon;
 int epsilon_int;
 int disp_tol;
 int radius_smooth;
 double sigma_space;
 double sigma_color;
 int min_d2;
 int max_d2;
 int ds_factor;
 int err_flag;

 /*
 Let's read in the input file
 */

 fp= fopen("dmag5_input.txt","r");
 if ( fp == 0 ) {
    fprintf(stdout,"dmag5_input.txt not found!\n");
    return 1;
 }

 /*
 Get filename for image 1
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"image 1 = %s\n",filename);

 strcpy(filename1,filename);

 /*
 Get filename for image 2
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"image 2 = %s\n",filename);

 strcpy(filename2,filename);

 /*
 Get min disparity for image 1
 */

 fscanf(fp,"%d",&min_d1);

 fprintf(stdout,"min disparity for image 1 = %d\n",min_d1);

 /*
 Get max disparity for image 1
 */

 fscanf(fp,"%d",&max_d1);

 fprintf(stdout,"max disparity for image 1 = %d\n",max_d1);

 min_d2= -max_d1;
 max_d2= -min_d1;

 /*
 Get filename for disparity map for image 1
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"disparity map for image 1 = %s\n",filename);

 strcpy(filename_disp1,filename);

 /*
 Get filename for disparity map for image 2
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"disparity map for image 2 = %s\n",filename);

 strcpy(filename_disp2,filename);

 /*
 Get filename for occluded pixel map for image 1
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"occluded pixel map for image 1 = %s\n",filename);

 strcpy(filename_occ1,filename);

 /*
 Get filename for occluded pixel map for image 2
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"occluded pixel map for image 2 = %s\n",filename);

 strcpy(filename_occ2,filename);

 /*
 Get radius used to smooth the cost
 */

 fscanf(fp,"%d",&radius);

 fprintf(stdout,"radius = %d\n",radius);

 /*
 Get alpha
 */

 fscanf(fp,"%lg",&alpha);

 fprintf(stdout,"alpha = %g\n",alpha);

 /*
 Get truncation value for color cost
 */

 fscanf(fp,"%lg",&max_cost_color);

 fprintf(stdout,"truncation (color) = %g\n",max_cost_color);

 /*
 Get truncation value for gradient cost
 */

 fscanf(fp,"%lg",&max_cost_gradient);

 fprintf(stdout,"truncation (gradient) = %g\n",max_cost_gradient);

 /*
 Get epsilon
 */

 fscanf(fp,"%d",&epsilon_int);

 fprintf(stdout,"epsilon = 255^2*10^-%d\n",epsilon_int);

 epsilon= 255*255*pow(10,-epsilon_int);

 /*
 Get the disparity tolerance used to detect occlusions
 */

 fscanf(fp,"%d",&disp_tol);

 fprintf(stdout,"disparity tolerance = %d\n",disp_tol);

 /*
 Get the radius used to smooth occlusions
 */

 fscanf(fp,"%d",&radius_smooth);

 fprintf(stdout,"radius to smooth occlusions = %d\n",radius_smooth);

 /*
 Get sigma space
 */

 fscanf(fp,"%lg",&sigma_space);

 fprintf(stdout,"sigma_space = %g\n",sigma_space);

 /*
 Get sigma_color
 */

 fscanf(fp,"%lg",&sigma_color);

 fprintf(stdout,"sigma_color = %g\n",sigma_color);

 /*
 Get the downsampling factor
 */

 fscanf(fp,"%d",&ds_factor);

 fprintf(stdout,"downsampling factor = %d\n",ds_factor);

 /*
 Done reading the input file
 */

 fclose(fp);

 /*
 Load image 1
 */

 err_flag= load_rgb_image(
  filename1,
  &I1_arr,
  &width,
  &height
 );

 if ( err_flag == 1 )
  return 1;

 /*
 Load image 2
 */

 err_flag= load_rgb_image(
  filename2,
  &I2_arr,
  &width,
  &height
 );

 if ( err_flag == 1 ) {
    return 1;
 }

 /*
 Compute the disparity maps and the occlusion maps
 */

 compute_disparity_maps(
  width,
  height,
  I1_arr,
  I2_arr,
  min_d1,
  max_d1,
  radius,
  alpha,
  max_cost_color,
  max_cost_gradient,
  epsilon_int,
  disp_tol,
  radius_smooth,
  sigma_space,
  sigma_color,
  ds_factor,
  &disp1_arr,
  &disp2_arr,
  &occ1_arr,
  &occ2_arr
 );

 /*
 Let's dump the disparity map for image 1
 */

 disp1_normalized_arr= (int *)calloc(width*height,sizeof(int));

 normalize_image(
  disp1_arr,
  disp1_normalized_arr,
  width*height,
  min_d1,
  max_d1
 );

 err_flag= write_image(
  filename_disp1,
  disp1_normalized_arr,
  width,
  height
 );

 if ( err_flag == 1 ) {
    return 1;
 }

 free(disp1_normalized_arr);

 /*
 Let's dump the disparity map for image 2
 */

 disp2_normalized_arr= (int *)calloc(width*height,sizeof(int));

 normalize_image(
  disp2_arr,
  disp2_normalized_arr,
  width*height,
  min_d2,
  max_d2
 );

 err_flag= write_image(
  filename_disp2,
  disp2_normalized_arr,
  width,
  height
 );

 if ( err_flag == 1 ) {
    return 1;
 }
    
 free(disp2_normalized_arr);

 /*
 Let's dump the occlusion map for image 1
 */

 err_flag= write_image(
  filename_occ1,
  occ1_arr,
  width,
  height
 );

 if ( err_flag == 1 ) {
    return 1;
 }

 /*
 Let's dump the occlusion map for image 2
 */

 err_flag= write_image(
  filename_occ2,
  occ2_arr,
  width,
  height
 );

 if ( err_flag == 1 ) {
    return 1;
 }
 
 /*
 Free memory
 */

 free(I1_arr);
 free(I2_arr);

 free(disp1_arr);
 free(disp2_arr);

 free(occ1_arr);
 free(occ2_arr);

 return 0;

}
