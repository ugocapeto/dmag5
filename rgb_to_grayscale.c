#include "header.h"
#include "proto.h"

void rgb_to_grayscale(
 int width,
 int height,
 double *image_rgb,
 double *image_grayscale
)

{

 int i;
 int j;
 int ind;
 double r_dbl;
 double g_dbl;
 double b_dbl;
 double I_dbl;

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;
       r_dbl= image_rgb[3*ind+0];
       g_dbl= image_rgb[3*ind+1];
       b_dbl= image_rgb[3*ind+2];
       I_dbl= (6969*r_dbl+23434*g_dbl+2365*b_dbl)/32768;
       image_grayscale[ind]= I_dbl;
    }
 }

}
