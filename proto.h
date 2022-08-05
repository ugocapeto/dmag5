void box_filter(
 int width,
 int height,
 double *image,
 int radius,
 double *filtered_image
);

int color_distance_squared(
 int width,
 int height,
 int *image_arr,
 int i1,
 int j1,
 int i2,
 int j2
);

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
);

double compute_cost_color(
 int width,
 int height,
 double *image1_r,
 double *image1_g,
 double *image1_b,
 double *image2_r,
 double *image2_g,
 double *image2_b,
 int d,
 double max_cost,
 int i,
 int j
);

double compute_cost_gradient(
 int width,
 int height,
 double *gradient1,
 double *gradient2,
 int d,
 double max_cost,
 int i,
 int j
);

void compute_disparity_maps(
 int width,
 int height,
 int *image1_arr,
 int *image2_arr,
 int min_d,
 int max_d,
 int radius,
 double alpha,
 double max_cost_color,
 double max_cost_gradient,
 int epsilon_int,
 int disp_tol,
 int radius_smooth,
 double sigma_space,
 double sigma_color,
 int ds_factor,
 int **pdisp1_arr,
 int **pdisp2_arr,
 int **pocc1_arr,
 int **pocc2_arr
);

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
);

void covariance(
 int width,
 int height,
 double *image1,
 double *mean1,
 double *image2,
 double *mean2,
 int radius,
 double *covar
);

void detect_occlusion(
 int width,
 int height,
 int *disp1_arr,
 int *disp2_arr,
 int min_d,
 int max_d,
 int disp_tol,
 int *occ1_arr
);

void dmag5_downsample_image(
 double *inp_I,
 int inp_xdim,
 int inp_ydim,
 double *out_I,
 int out_xdim,
 int out_ydim,
 double factor
);

void dmag5_downsample_image_dimensions(
 int inp_xdim,
 int inp_ydim,
 int *pout_xdim,
 int *pout_ydim,
 double factor
);

void dmag5_downsample_image_int(
 int *inp_I_int,
 int inp_xdim,
 int inp_ydim,
 int *out_I_int,
 int out_xdim,
 int out_ydim,
 double factor
);

void dmag5_downsample_rgb_image(
 double *inp_I_rgb,
 int inp_xdim,
 int inp_ydim,
 double *out_I_rgb,
 int out_xdim,
 int out_ydim,
 double factor
);

void dmag5_downsample_rgb_image_int(
 int *inp_I_rgb_int,
 int inp_xdim,
 int inp_ydim,
 int *out_I_rgb_int,
 int out_xdim,
 int out_ydim,
 double factor
);

void dmag5_error_handler(
 char* from
);

void fast_cost_volume_filter(
 int width,
 int height,
 int *image1,
 int *image2,
 int min_d,
 int max_d,
 int radius,
 double alpha,
 double max_cost_color,
 double max_cost_gradient,
 double epsilon,
 int *disp_arr
);

void fill_occlusion_left_right(
 int width,
 int height,
 int *disp_arr,
 int *occ_arr,
 int min_d,
 int max_d
);

void fill_occlusion_right_left(
 int width,
 int height,
 int *disp_arr,
 int *occ_arr,
 int min_d,
 int max_d
);

void gaussian_blur_image(
 double *I,
 int xdim,
 int ydim,
 double sigma,
 int precision
);

void gradient_x(
 int width,
 int height,
 double *image,
 double *gradient
);

void inverse_sym_3x3(
 double matrix[9],
 double inverse[9]
);

void median(
 int width,
 int height,
 int *image_arr,
 int radius,
 int *median_arr
);

int median_histo(
 int min_d,
 int max_d,
 double *hist
);

void normalize_image(
 int *inp_I,
 int *out_I,
 int size,
 int min_val,
 int max_val
);

void print_weight_image(
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
 int j_ref
);

void rgb_to_grayscale(
 int width,
 int height,
 double *image_rgb,
 double *image_grayscale
);

void smooth_occlusion_weighted_median(
 int width,
 int height,
 int *image_arr,
 int *disp_arr,
 int *occ_arr,
 int min_d,
 int max_d,
 int radius,
 double sigma_space,
 double sigma_color
);

void weighted_histo(
 int width,
 int height,
 int *image_arr,
 int *disp_arr,
 int *occ_arr,
 int min_d,
 int max_d,
 int radius,
 double sigma_space,
 double sigma_color,
 int i_ref,
 int j_ref,
 double *hist_arr
);

void weighted_median(
 int width,
 int height,
 int *image_arr,
 int *disp_arr,
 int *occ_arr,
 int min_d,
 int max_d,
 int radius,
 double sigma_space,
 double sigma_color,
 int *new_disp_arr
);
