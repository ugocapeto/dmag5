#include "header.h"
#include "proto.h"

void dmag5_downsample_rgb_image_int(
 int *inp_I_rgb_int,
 int inp_xdim,
 int inp_ydim,
 int *out_I_rgb_int,
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
 int *inp_I_int;
 int *out_I_int;
 int cind;
 int i;
 int j;
 int pixel;

 inp_size= inp_xdim*inp_ydim;
 out_size= out_xdim*out_ydim;

 if ( inp_size > 0 )
  inp_I_int= (int *)calloc(inp_size,sizeof(int));

 if ( out_size > 0 )
  out_I_int= (int *)calloc(out_size,sizeof(int));

 for ( cind= 0 ; cind< 3 ; cind++ ) {

    for ( i= 0 ; i< inp_ydim ; i++ ) {
       for ( j= 0 ; j< inp_xdim ; j++ ) {
          pixel= i*inp_xdim+j;
          inp_I_int[pixel]= inp_I_rgb_int[3*pixel+cind];
       }
    }

    dmag5_downsample_image_int(
     inp_I_int,
     inp_xdim,
     inp_ydim,
     out_I_int,
     out_xdim,
     out_ydim,
     factor
    );

    for ( i= 0 ; i< out_ydim ; i++ ) {
       for ( j= 0 ; j< out_xdim ; j++ ) {
          pixel= i*out_xdim+j;
          out_I_rgb_int[3*pixel+cind]= out_I_int[pixel];
       }
    }
 }

 if ( inp_size > 0 )
  free(inp_I_int);

 if ( out_size > 0 )
  free(out_I_int);

}
