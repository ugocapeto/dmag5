#include "header.h"
#include "proto.h"

double compute_cost_gradient(
 int width,
 int height,
 double *gradient1,
 double *gradient2,
 int d,
 double max_cost,
 int i,
 int j
)

{

 int ind1;
 int ind2;
 double g1;
 double g2;
 double diff;
 double cost;

 if ( (j-d) < 0 )
  dmag5_error_handler("compute_cost_gradient"); 
 if ( (j-d) > (width-1) )
  dmag5_error_handler("compute_cost_gradient"); 

 ind1= i*width+j;
 ind2= i*width+(j-d);
 g1= gradient1[ind1];
 g2= gradient2[ind2];
 diff= fabs(g2-g1);
 cost= diff;

 /*
 Apply truncation to reduce the effect of occluded pixels
 */

 if ( cost > max_cost )
  cost= max_cost;

 return cost;

}
