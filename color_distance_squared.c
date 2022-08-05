#include "header.h"
#include "proto.h"

int color_distance_squared(
 int width,
 int height,
 int *image_arr,
 int i1,
 int j1,
 int i2,
 int j2
)

{

 int ind1;
 int ind2;
 int val;
 int val2;
 int dist2;
 int cind;

 ind1= i1*width+j1;
 ind2= i2*width+j2;

 dist2= 0;
 for ( cind= 0 ; cind< 3 ; cind++ ) {
    val= image_arr[3*ind1+cind]-image_arr[3*ind2+cind];
    val2= val*val;
    dist2+= val2;
 }

 return dist2;

}
