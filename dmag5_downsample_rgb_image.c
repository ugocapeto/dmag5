#include "header.h"
#include "proto.h"

void dmag5_downsample_rgb_image(
 double *inp_I_rgb,
 int inp_xdim,
 int inp_ydim,
 double *out_I_rgb,
 int out_xdim,
 int out_ydim,
 double factor
)

/*
The output image must be allocated outside the function
*/

{

 int inp_size;
 int out_size;
 double *inp_I;
 double *out_I;
 int cind;
 int i;
 int j;
 int pixel;

 inp_size= inp_xdim*inp_ydim;
 out_size= out_xdim*out_ydim;

 if ( inp_size > 0 )
  inp_I= (double *)calloc(inp_size,sizeof(double));

 if ( out_size > 0 )
  out_I= (double *)calloc(out_size,sizeof(double));

 for ( cind= 0 ; cind< 3 ; cind++ ) {

    for ( i= 0 ; i< inp_ydim ; i++ ) {
       for ( j= 0 ; j< inp_xdim ; j++ ) {
          pixel= i*inp_xdim+j;
          inp_I[pixel]= inp_I_rgb[3*pixel+cind];
       }
    }

    dmag5_downsample_image(
     inp_I,
     inp_xdim,
     inp_ydim,
     out_I,
     out_xdim,
     out_ydim,
     factor
    );

    for ( i= 0 ; i< out_ydim ; i++ ) {
       for ( j= 0 ; j< out_xdim ; j++ ) {
          pixel= i*out_xdim+j;
          out_I_rgb[3*pixel+cind]= out_I[pixel];
       }
    }
 }

 if ( inp_size > 0 )
  free(inp_I);

 if ( out_size > 0 )
  free(out_I);

}
