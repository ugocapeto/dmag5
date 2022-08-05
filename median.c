#include "header.h"
#include "proto.h"

void median(
 int width,
 int height,
 int *image_arr,
 int radius,
 int *median_arr
)

{

 int size;
 int *var_arr;
 int i;
 int j;
 int ind;
 int nbr;
 int mask_i;
 int mask_j;
 int i2;
 int j2;
 int ind2;
 int k;
 int k2;
 int vtemp;

 size= (2*radius+1);
 size*= size;

 var_arr= (int *)calloc(size,sizeof(int));

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;

       /*
       Store image_arr values into var_arr
       */

       nbr= 0;
       for ( mask_i= -radius ; mask_i<= radius ; mask_i++ ) {
          i2= i+mask_i;
          if ( i2 < 0 ) 
           continue;
          if ( i2 > (height-1) ) 
           continue;
          for ( mask_j= -radius ; mask_j<= radius ; mask_j++ ) {
             j2= j+mask_j;
             if ( j2 < 0 ) 
              continue;
             if ( j2 > (width-1) ) 
              continue;
             ind2= i2*width+j2;
             var_arr[nbr]= image_arr[ind2];
             nbr++;
          }
       }

       /*
       Sort var_arr
       */

       for ( k= 0 ; k< nbr ; k++ ) {
          for ( k2= k+1 ; k2< nbr ; k2++ ) {
             if ( var_arr[k2] < var_arr[k] ) {
                vtemp= var_arr[k];
                var_arr[k]= var_arr[k2];
                var_arr[k2]= vtemp;
             }
          }
       }

       /*
       Check!
       */

       for ( k= 0 ; k< nbr ; k++ ) {
          for ( k2= k+1 ; k2< nbr ; k2++ ) {
             if ( var_arr[k2] < var_arr[k] )
              dmag5_error_handler("median");
          }
       }
          
       /*
       Store the median_arr value
       */

       median_arr[ind]= var_arr[nbr/2];
    }
 }

 free(var_arr);

}
