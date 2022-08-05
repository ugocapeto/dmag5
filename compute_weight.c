#include "header.h"
#include "proto.h"

double compute_weight(
 int width,
 int height,
 double *image1_r,
 double *image1_g,
 double *image1_b,
 double *mean1_r,
 double *mean1_g,
 double *mean1_b,
 double *var1_rr,
 double *var1_rg,
 double *var1_rb,
 double *var1_gg,
 double *var1_gb,
 double *var1_bb,
 double epsilon, 
 int radius,
 int i_ref,
 int j_ref,
 int i,
 int j
)

/*
(i_ref,j_ref) represents pixel i
(i,j) represents pixel j
*/

{

 int omega;
 int mask_i;
 int mask_j;
 int k_i;
 int k_j;
 double vec[3];
 double vec2[3];
 double val;
 double weight;
 double S1[9];
 double S2[9];

 /*
 Get number of pixels in window
 */

 omega= (2*radius+1)*(2*radius+1);

 /*
 Initialize the weight
 */

 weight= 0;

 /*
 (k_i,k_j) represents pixel k
 */

 for ( mask_i= -radius ; mask_i<= radius ; mask_i++ ) {
    k_i= i_ref+mask_i;

    if ( k_i < 0 )
     continue;
    if ( k_i > (height-1) )
     continue;

    for ( mask_j= -radius ; mask_j<= radius ; mask_j++ ) {
       k_j= j_ref+mask_j;

       if ( k_j < 0 )
        continue;
       if ( k_j > (width-1) )
        continue;

       /*
       k is in the window centered at (i_ref,j_ref)
       */

       /*
       k must also be in the window centered at (i,j)
       */

       if ( k_i < (i-radius) )
        continue;
       if ( k_i > (i+radius) )
        continue;
       if ( k_j < (j-radius) )
        continue;
       if ( k_j > (j+radius) )
        continue;

       /* 
       k is in the window centered at (i,j)
       */

       /*
       Compute Sigma_k+epsilon*I3
       */

       S1[0]= var1_rr[k_i*width+k_j]+epsilon;
       S1[1]= var1_rg[k_i*width+k_j];
       S1[2]= var1_rb[k_i*width+k_j];

       S1[3]= var1_rg[k_i*width+k_j];
       S1[4]= var1_gg[k_i*width+k_j]+epsilon;
       S1[5]= var1_gb[k_i*width+k_j];

       S1[6]= var1_rb[k_i*width+k_j];
       S1[7]= var1_gb[k_i*width+k_j];
       S1[8]= var1_bb[k_i*width+k_j]+epsilon;

       /*
       Compute the inverse of Sigma_k+epsilon*I3
       */

       inverse_sym_3x3(
        S1,
        S2
       );

       /*
       Compute vector I_j-mu_k
       */

       vec[0]= image1_r[i*width+j]-mean1_r[k_i*width+k_j];
       vec[1]= image1_g[i*width+j]-mean1_g[k_i*width+k_j];
       vec[2]= image1_b[i*width+j]-mean1_b[k_i*width+k_j];

       /*
       Compute vector (Sigma_k+epsilon*I3)^-1*(I_j-mu_k)
       */

       vec2[0]=S2[0]*vec[0]+
               S2[1]*vec[1]+
               S2[2]*vec[2];
       vec2[1]=S2[3]*vec[0]+
               S2[4]*vec[1]+
               S2[5]*vec[2];
       vec2[2]=S2[6]*vec[0]+
               S2[7]*vec[1]+
               S2[8]*vec[2];

       /*
       Compute vector I_i-mu_k
       */

       vec[0]= image1_r[i_ref*width+j_ref]-mean1_r[k_i*width+k_j];
       vec[1]= image1_g[i_ref*width+j_ref]-mean1_g[k_i*width+k_j];
       vec[2]= image1_b[i_ref*width+j_ref]-mean1_b[k_i*width+k_j];

       /* 
       Compute scalar (I_i-mu_k)T*(Sigma_k+epsilon*I3)^-1*(I_j-mu_k)
       */

       val= vec[0]*vec2[0]+
            vec[1]*vec2[1]+
            vec[2]*vec2[2];

       weight+= (1+val);
    }
 }

 weight/= (omega*omega);

 return weight;

}
