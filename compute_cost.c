#include "header.h"
#include "proto.h"

void compute_cost(
 int width,
 int height,
 double *image1_r,
 double *image1_g,
 double *image1_b,
 double *image2_r,
 double *image2_g,
 double *image2_b,
 double *gradient1,
 double *gradient2,
 int d,
 double max_cost_color,
 double max_cost_gradient,
 double alpha,
 double *cost_arr
)

{

 int i;
 int j;
 int ind;
 int j2;
 double cost_color;
 double cost_gradient;
 double cost;

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;

       j2= j-d;

       /*
       Initialize the cost to be the max cost 
       */

       cost_color= max_cost_color;
       cost_gradient= max_cost_gradient;

       cost= (1-alpha)*cost_color+alpha*cost_gradient;

       if ( j2 < 0 ) {
          cost_arr[ind]= cost;
          continue;
       }
       if ( j2 > (width-1) ) {
          cost_arr[ind]= cost;
          continue;
       }

       cost_color= compute_cost_color(
        width,
        height,
        image1_r,
        image1_g,
        image1_b,
        image2_r,
        image2_g,
        image2_b,
        d,
        max_cost_color,
        i,
        j
       );

       cost_gradient= compute_cost_gradient(
        width,
        height,
        gradient1,
        gradient2,
        d,
        max_cost_gradient,
        i,
        j
       );

       cost= (1-alpha)*cost_color+alpha*cost_gradient;

       cost_arr[ind]= cost;
    }
 }

}
