#include "header.h"
#include "proto.h"

void fast_cost_volume_filter(
 int width,
 int height,
 int *image1,
 int *image2,
 int min_d,
 int max_d,
 int radius,
 double alpha,
 double max_cost_color,
 double max_cost_gradient,
 double epsilon,
 int *disp_arr
)

{

 double *image1_r;
 double *image1_g;
 double *image1_b;
 double *image2_r;
 double *image2_g;
 double *image2_b;
 double *image1_grayscale;
 double *image2_grayscale;
 double *gradient1;
 double *gradient2;
 double *mean1_r;
 double *mean1_g;
 double *mean1_b;
 double *mean2_r;
 double *mean2_g;
 double *mean2_b;
 double *var1_rr;
 double *var1_rg;
 double *var1_rb;
 double *var1_gg;
 double *var1_gb;
 double *var1_bb;
 double *a_k_r;
 double *a_k_g;
 double *a_k_b;
 double *cost;
 double *mean_cost;
 double *covar1_r_cost;
 double *covar1_g_cost;
 double *covar1_b_cost;
 double *b;
 int d;
 double *dummy_dbl;
 double *image1_dbl;
 double *image2_dbl;
 int i;
 int j;
 int ind;
 int cind;
 double S1[9];
 double S2[9];
 double *min_cost;
 double *b_k;
 double *a_r;
 double *a_g;
 double *a_b;
 double *filtered_cost;

 /*
 Before we start,
 initialize the disparity to min_d-1
 */

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;
       disp_arr[ind]=min_d-1;
    }
 }

 /*
 Allocate memory for the double precision version of image1
 */

 image1_dbl= (double *)calloc(width*height,3*sizeof(double));

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;
       for ( cind= 0 ; cind< 3 ; cind++ )
        image1_dbl[3*ind+cind]= (double)image1[3*ind+cind];
    }
 }

 /*
 Allocate memory for the double precision version of image2
 */

 image2_dbl= (double *)calloc(width*height,3*sizeof(double));

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;
       for ( cind= 0 ; cind< 3 ; cind++ )
        image2_dbl[3*ind+cind]= (double)image2[3*ind+cind];
    }
 }

 /*
 Allocate memory for the red channel of image1
 */

 image1_r= (double *)calloc(width*height,sizeof(double));

 /*
 Get the red channel of image1
 */

 cind= 0;
 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;
       image1_r[ind]= image1_dbl[3*ind+cind];
    }
 }

 /*
 Allocate memory for the green channel of image1
 */

 image1_g= (double *)calloc(width*height,sizeof(double));

 /*
 Get the green channel of image1
 */

 cind= 1;
 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;
       image1_g[ind]= image1_dbl[3*ind+cind];
    }
 }

 /*
 Allocate memory for the blue channel of image1
 */

 image1_b= (double *)calloc(width*height,sizeof(double));

 /*
 Get the blue channel of image1
 */

 cind= 2;
 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;
       image1_b[ind]= image1_dbl[3*ind+cind];
    }
 }

 /*
 Allocate memory for the red channel of image2
 */

 image2_r= (double *)calloc(width*height,sizeof(double));

 /*
 Get the red channel of image2
 */

 cind= 0;
 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;
       image2_r[ind]= image2_dbl[3*ind+cind];
    }
 }

 /*
 Allocate memory for the green channel of image2
 */

 image2_g= (double *)calloc(width*height,sizeof(double));

 /*
 Get the green channel of image2
 */

 cind= 1;
 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;
       image2_g[ind]= image2_dbl[3*ind+cind];
    }
 }

 /*
 Allocate memory for the blue channel of image2
 */

 image2_b= (double *)calloc(width*height,sizeof(double));

 /*
 Get the blue channel of image2
 */

 cind= 2;
 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;
       image2_b[ind]= image2_dbl[3*ind+cind];
    }
 }

 /*
 Allocate memory for the grayscale version of image1
 */

 image1_grayscale= (double *)calloc(width*height,sizeof(double));

 /*
 Get the grayscale version of image1
 */

 rgb_to_grayscale(
  width,
  height,
  image1_dbl,
  image1_grayscale
 );

 /*
 Allocate memory for the grayscale version of image2
 */

 image2_grayscale= (double *)calloc(width*height,sizeof(double));

 /*
 Get the grayscale version of image2
 */

 rgb_to_grayscale(
  width,
  height,
  image2_dbl,
  image2_grayscale
 );

 /*
 Allocate memory for the gradient in the x direction of image1
 */

 gradient1= (double *)calloc(width*height,sizeof(double));

 /*
 Get the gradient in the x direction for image1
 */

 gradient_x(
  width,
  height,
  image1_grayscale,
  gradient1
 );

 /*
 Allocate memory for the gradient in the x direction of image2
 */

 gradient2= (double *)calloc(width*height,sizeof(double));

 /*
 Get the gradient in the x direction for image2
 */

 gradient_x(
  width,
  height,
  image2_grayscale,
  gradient2
 );

 /*
 Allocate memory for the mean of image1's red channel
 */

 mean1_r= (double *)calloc(width*height,sizeof(double));

 /*
 Compute the mean of image1's red channel
 */

 box_filter(
  width,
  height,
  image1_r,
  radius,
  mean1_r
 );

 /*
 Allocate memory for the mean of image1's green channel
 */

 mean1_g= (double *)calloc(width*height,sizeof(double));

 /*
 Compute the mean of image1's green channel
 */

 box_filter(
  width,
  height,
  image1_g,
  radius,
  mean1_g
 );

 /*
 Allocate memory for the mean of image1's blue channel
 */

 mean1_b= (double *)calloc(width*height,sizeof(double));

 /*
 Compute the mean of image1's blue channel
 */

 box_filter(
  width,
  height,
  image1_b,
  radius,
  mean1_b
 );

 /*
 Allocate memory for the covariance of image1's red/red channels
 */

 var1_rr= (double *)calloc(width*height,sizeof(double));

 /*
 Compute the covariance of image1's red/red channels
 */

 covariance(
  width,
  height,
  image1_r,
  mean1_r,
  image1_r,
  mean1_r,
  radius,
  var1_rr
 );

 /*
 Allocate memory for the covariance of image1's red/green channels
 */

 var1_rg= (double *)calloc(width*height,sizeof(double));

 /*
 Compute the covariance of image1's red/green channels
 */

 covariance(
  width,
  height,
  image1_r,
  mean1_r,
  image1_g,
  mean1_g,
  radius, 
  var1_rg
 );

 /*
 Allocate memory for the covariance of image1's red/blue channels
 */

 var1_rb= (double *)calloc(width*height,sizeof(double));

 /*
 Compute the covariance of image1's red/blue channels
 */

 covariance(
  width,
  height,
  image1_r,
  mean1_r,
  image1_b,
  mean1_b,
  radius,
  var1_rb
 );

 /*
 Allocate memory for the covariance of image1's green/green channels
 */

 var1_gg= (double *)calloc(width*height,sizeof(double));

 /*
 Compute the covariance of image1's green/green channels
 */

 covariance(
  width,
  height,
  image1_g,
  mean1_g,
  image1_g,
  mean1_g,
  radius,
  var1_gg
 );

 /*
 Allocate memory for the covariance of image1's green/blue channels
 */

 var1_gb= (double *)calloc(width*height,sizeof(double));

 /*
 Compute the covariance of image1's green/blue channels
 */

 covariance(
  width,
  height,
  image1_g,
  mean1_g,
  image1_b,
  mean1_b,
  radius,
  var1_gb
 );

 /*
 Allocate memory for the covariance of image1's blue/blue channels
 */

 var1_bb= (double *)calloc(width*height,sizeof(double));

 /*
 Compute the covariance of image1's blue/blue channels
 */

 covariance(
  width,
  height,
  image1_b,
  mean1_b,
  image1_b,
  mean1_b,
  radius,
  var1_bb
 );

 /*
 Allocate memory for the red channel a coefficients
 */

 a_k_r= (double *)calloc(width*height,sizeof(double));

 /*
 Allocate memory for the green channel a coefficients
 */

 a_k_g= (double *)calloc(width*height,sizeof(double));

 /*
 Allocate memory for the blue channel a coefficients
 */

 a_k_b= (double *)calloc(width*height,sizeof(double));

 /*
 Allocate memory for the cost
 */

 cost= (double *)calloc(width*height,sizeof(double));

 /*
 Allocate memory for the mean of the cost
 */

 mean_cost= (double *)calloc(width*height,sizeof(double));

 /*
 Allocate memory for the covariance image1_r/mean_cost
 */

 covar1_r_cost= (double *)calloc(width*height,sizeof(double));

 /*
 Allocate memory for the covariance image1_g/mean_cost
 */

 covar1_g_cost= (double *)calloc(width*height,sizeof(double));

 /*
 Allocate memory for the covariance image1_b/mean_cost
 */

 covar1_b_cost= (double *)calloc(width*height,sizeof(double));

 /*
 Allocate memory for the b coefficients
 */

 b= (double *)calloc(width*height,sizeof(double));

 /*
 Allocate memory for b_k array
 */

 b_k= (double *)calloc(width*height,sizeof(double));

 /*
 Allocate memory for the a_r coefficients
 */

 a_r= (double *)calloc(width*height,sizeof(double));

 /*
 Allocate memory for the a_g coefficients
 */

 a_g= (double *)calloc(width*height,sizeof(double));

 /*
 Allocate memory for the a_b coefficients
 */

 a_b= (double *)calloc(width*height,sizeof(double));

 /*
 Allocate memory for the filtered cost
 */

 filtered_cost= (double *)calloc(width*height,sizeof(double));

 /*
 Allocate memory for the min cost
 */

 min_cost= (double *)calloc(width*height,sizeof(double));

 /*
 Comment out if you don't want to print the filter weights
 for a given (i,j)
 */

 /*
 i= 82;
 j= 534;
 print_weight_image(
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
  i,
  j
 );
 */

 /*
 Initialize the min cost
 */

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;
       min_cost[ind]= 1.0e32;
    }
 }

 for ( d= min_d ; d<= max_d ; d++ ) {

    /*
    Compute cost
    That's p(i)
    */

    compute_cost(
     width,
     height,
     image1_r,
     image1_g,
     image1_b,
     image2_r,
     image2_g,
     image2_b,
     gradient1,
     gradient2,
     d,
     max_cost_color,
     max_cost_gradient, 
     alpha,
     cost
    );

    /*
    Get the mean cost
    That's p_k_bar
    */

    box_filter(
     width,
     height,
     cost,
     radius,
     mean_cost
    );

    /*
    Get the covariance image1_r/cost
    That's gonna be used to compute a_k_r
    */

    covariance(
     width,
     height,
     image1_r,
     mean1_r,
     cost,
     mean_cost,
     radius,
     covar1_r_cost
    );

    /*
    Get the covariance image1_g/cost
    That's gonna be used to compute a_k_g
    */

    covariance(
     width,
     height,
     image1_g,
     mean1_g,
     cost,
     mean_cost,
     radius,
     covar1_g_cost
    );

    /*
    Get the covariance image1_b/cost
    That's gonna be used to compute a_k_b 
    */

    covariance(
     width,
     height,
     image1_b,
     mean1_b,
     cost,
     mean_cost,
     radius, 
     covar1_b_cost
    );

    for ( i= 0 ; i< height ; i++ ) {
       for ( j= 0 ; j< width ; j++ ) {
          ind= i*width+j;

          /*
          Compute Sigma_k+epsilon*I3
          */

          S1[0]= var1_rr[ind]+epsilon;
          S1[1]= var1_rg[ind];
          S1[2]= var1_rb[ind];

          S1[3]= var1_rg[ind];
          S1[4]= var1_gg[ind]+epsilon;
          S1[5]= var1_gb[ind];

          S1[6]= var1_rb[ind];
          S1[7]= var1_gb[ind];
          S1[8]= var1_bb[ind]+epsilon;

          /*
          Compute the inverse of Sigma_k+epsilon*I3
          */

          inverse_sym_3x3(
           S1,
           S2
          );

          /*
          Compute the red channel a coefficient
          That's a_k_r
          */

          a_k_r[ind]= covar1_r_cost[ind]*S2[0]+
                    covar1_g_cost[ind]*S2[1]+
                    covar1_b_cost[ind]*S2[2];

          /*
          Compute the green channel a coefficient
          That's a_k_g
          */

          a_k_g[ind]= covar1_r_cost[ind]*S2[3]+
                    covar1_g_cost[ind]*S2[4]+
                    covar1_b_cost[ind]*S2[5];

          /*
          Compute the blue channel a coefficient
          That's a_k_b
          */

          a_k_b[ind]= covar1_r_cost[ind]*S2[6]+
                    covar1_g_cost[ind]*S2[7]+
                    covar1_b_cost[ind]*S2[8];
       }
    }

    /*
    Compute the b coefficients
    That's b_k
    */

    for ( i= 0 ; i< height ; i++ ) {
       for ( j= 0 ; j< width ; j++ ) {
          ind= i*width+j;

          b_k[ind]= mean_cost[ind]-
                          a_k_r[ind]*mean1_r[ind]-
                          a_k_g[ind]*mean1_g[ind]-
                          a_k_b[ind]*mean1_b[ind];
       }
    }

    /*
    Average b_k to get b_i_bar
    */

    box_filter(
     width,
     height,
     b_k,
     radius,
     b
    );

    /*
    Average a_k to get a_i_bar
    for each color channel
    */

    box_filter(
     width,
     height,
     a_k_r,
     radius,
     a_r
    );

    box_filter(
     width,
     height,
     a_k_g,
     radius,
     a_g
    );

    box_filter(
     width,
     height,
     a_k_b,
     radius,
     a_b
    );

    /*
    Now, we can compute the filtered cost
    That's q(i)
    */

    for ( i= 0 ; i< height ; i++ ) {
       for ( j= 0 ; j< width ; j++ ) {
          ind= i*width+j;
          filtered_cost[ind]= a_r[ind]*image1_r[ind]+
                              a_g[ind]*image1_g[ind]+
                              a_b[ind]*image1_b[ind]+
                              b[ind];
       }
    }

    /*
    Get the disparity using winner takes all
    */

    for ( i= 0 ; i< height ; i++ ) {
       for ( j= 0 ; j< width ; j++ ) {
          ind= i*width+j;
          if ( min_cost[ind] >= filtered_cost[ind] ) {
             min_cost[ind]= filtered_cost[ind]; 
             disp_arr[ind]= d;
          }
       }
    }
 }

 /*
 Free memory
 */

 free(image1_dbl);

 free(image2_dbl);

 free(image1_r);

 free(image1_g);

 free(image1_b);

 free(image2_r);

 free(image2_g);

 free(image2_b);

 free(image1_grayscale);

 free(image2_grayscale);

 free(gradient1);

 free(gradient2);

 free(mean1_r);

 free(mean1_g);

 free(mean1_b);

 free(var1_rr);

 free(var1_rg);

 free(var1_rb);

 free(var1_gg);

 free(var1_gb);

 free(var1_bb);

 free(a_k_r);

 free(a_k_g);

 free(a_k_b);

 free(cost);

 free(mean_cost);

 free(covar1_r_cost);

 free(covar1_g_cost);

 free(covar1_b_cost);

 free(b);

 free(b_k);

 free(a_r);

 free(a_g);

 free(a_b);

 free(filtered_cost);

 free(min_cost);

}
