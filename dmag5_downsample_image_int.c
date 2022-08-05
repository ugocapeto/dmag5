#include "header.h"
#include "proto.h"

void dmag5_downsample_image_int(
 int *inp_I_int,
 int inp_xdim,
 int inp_ydim,
 int *out_I_int,
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
 int i;
 int j;
 int pixel;
 double val_dbl;
 int val_int;

 inp_size= inp_xdim*inp_ydim;
 out_size= out_xdim*out_ydim;

 if ( inp_size > 0 )
  inp_I= (double *)calloc(inp_size,sizeof(double));

 if ( out_size > 0 )
  out_I= (double *)calloc(out_size,sizeof(double));

 for ( i= 0 ; i< inp_ydim ; i++ ) {
    for ( j= 0 ; j< inp_xdim ; j++ ) {
       pixel= i*inp_xdim+j;
       inp_I[pixel]= (double)inp_I_int[pixel];
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
       val_dbl= out_I[pixel];
       if ( val_dbl >= 0 )
        val_int= (int)(val_dbl+0.5);
       else
        val_int= (int)(val_dbl-0.5);
       if ( val_int < 0 )
        val_int= 0;
       if ( val_int > 255 )
        val_int= 255;
       out_I_int[pixel]= val_int;
    }
 }

 if ( inp_size > 0 )
  free(inp_I);

 if ( out_size > 0 )
  free(out_I);

}
