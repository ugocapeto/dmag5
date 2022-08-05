#include "header.h"
#include "proto.h"

int median_histo(
 int min_d, 
 int max_d,
 double *hist_arr
)

{

 double sum;
 int hist_ind;
 double cumul;
 int d;

 sum= 0;
 for ( hist_ind= 0 ; hist_ind< max_d-min_d+1 ; hist_ind++ )
  sum+= hist_arr[hist_ind];
 sum/= 2;

 cumul= 0;
 for ( hist_ind= 0 ; ; hist_ind++ ) {
    cumul+= hist_arr[hist_ind];
    if ( !(cumul<sum) )
     break; 
 }

 if ( !(hist_ind < max_d-min_d+1) ) {
    dmag5_error_handler("median_histo");
 }

 /*
 Check if same as stereo-adaptive-weights_1.0 code
 */

 d=-1;
 for (cumul=0; cumul<sum;)
  cumul += hist_arr[++d];

 if ( d != hist_ind ) {
    dmag5_error_handler("median_histo");
 }

 return hist_ind;

}
