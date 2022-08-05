#include "header.h"
#include "proto.h"

void covariance(
 int width,
 int height,
 double *image1,
 double *mean1,
 double *image2,
 double *mean2,
 int radius,
 double *covar
)

{

 double *image_product;
 int i;
 int j;
 int ind;
 double *filtered_image;
 double *mean_product;

 /*
 Allocate memory for the product of the 2 images
 */

 image_product= (double *)calloc(width*height,sizeof(double));

 /*
 Compute the product of the 2 images
 */

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;
       image_product[ind]= image1[ind]*image2[ind];
    }
 }

 /*
 Allocate memory for the filtered image
 */

 filtered_image= (double *)calloc(width*height,sizeof(double));

 /*
 Apply the box filter to the product of the 2 images
 */

 box_filter(
  width,
  height,
  image_product,
  radius,
  filtered_image
 );

 /*
 Allocate memory for the product of the 2 means
 */

 mean_product= (double *)calloc(width*height,sizeof(double));

 /*
 Compute the product of the 2 means
 */

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;
       mean_product[ind]= mean1[ind]*mean2[ind];
    }
 }

 /*
 Fill in the covariance array
 */

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;
       covar[ind]= filtered_image[ind]-mean_product[ind];
    }
 }

 /*
 Free memory for the product of the 2 images
 */

 free(image_product);

 /*
 Free memory for the filtered image
 */

 free(filtered_image);

 /*
 Free memory for the product of the 2 means
 */

 free(mean_product);

}
