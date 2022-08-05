#include "header.h"
#include "proto.h"

double compute_cost_color(
 int width,
 int height,
 double *image1_r,
 double *image1_g,
 double *image1_b,
 double *image2_r,
 double *image2_g,
 double *image2_b,
 int d,
 double max_cost,
 int i,
 int j
)

{

 double cost;
 int ind1;
 int ind2;
 int cind;
 double I1_dbl;
 double I2_dbl;
 double diff;

 if ( (j-d) < 0 )
  dmag5_error_handler("compute_cost_color"); 
 if ( (j-d) > (width-1) )
  dmag5_error_handler("compute_cost_color"); 

 cost= 0;
 ind1= i*width+j;
 ind2= i*width+(j-d);

 I1_dbl= image1_r[ind1];
 I2_dbl= image2_r[ind2];
 diff= fabs(I2_dbl-I1_dbl);
 cost+= diff;

 I1_dbl= image1_g[ind1];
 I2_dbl= image2_g[ind2];
 diff= fabs(I2_dbl-I1_dbl);
 cost+= diff;

 I1_dbl= image1_b[ind1];
 I2_dbl= image2_b[ind2];
 diff= fabs(I2_dbl-I1_dbl);
 cost+= diff;

 cost/= 3;

 /*
 Apply truncation to reduce the effect of occluded pixels
 */

 if ( cost > max_cost )
  cost= max_cost;

 return cost;

}
