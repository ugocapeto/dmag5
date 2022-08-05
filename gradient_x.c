#include "header.h"
#include "proto.h"

void gradient_x(
 int width,
 int height,
 double *image,
 double *gradient
)

{

 int i;
 int j;
 double I;
 double I_left;
 double I_right;
 int ind;
 int ind_left;
 int ind_right;
 int j_left;
 int j_right;

 for ( i= 0 ; i< height ; i++ ) {

    /*
    Let's take care of left most pixel
    */

    j= 0; 
    ind= i*width+j;
    I= image[ind];
    j_right= j+1;
    ind_right= i*width+j_right;
    I_right= image[ind_right];
    gradient[ind]= (I_right-I)/1;

    /*
    General case
    */

    for ( j= 1 ; j< width-1 ; j++ ) {
       ind= i*width+j;
       I= image[ind];
       j_right= j+1;
       ind_right= i*width+j_right;
       I_right= image[ind_right];
       j_left= j-1;
       ind_left= i*width+j_left;
       I_left= image[ind_left];
       gradient[ind]= (I_right-I_left)/2;
    }

    /*
    Let's take care of right most pixel
    */

    j= width-1; 
    ind= i*width+j;
    I= image[ind];
    j_left= j-1;
    ind_left= i*width+j_left;
    I_left= image[ind_left];
    gradient[ind]= (I-I_left)/1;
 }

}
