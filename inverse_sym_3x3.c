#include "header.h"
#include "proto.h"

void inverse_sym_3x3(
 double matrix[9],
 double inverse[9]
)

{

 double det;

 inverse[0] = matrix[4]*matrix[8] - matrix[5]*matrix[7];
 inverse[1] = matrix[2]*matrix[7] - matrix[1]*matrix[8];
 inverse[2] = matrix[1]*matrix[5] - matrix[2]*matrix[4];
 det = matrix[0]*inverse[0]+matrix[3]*inverse[1]+matrix[6]*inverse[2];
 det = 1/det;
 inverse[0] *= det;
 inverse[1] *= det;
 inverse[2] *= det;
 inverse[3] = inverse[1];
 inverse[4] = (matrix[0]*matrix[8] - matrix[2]*matrix[6]) * det;
 inverse[5] = (matrix[2]*matrix[3] - matrix[0]*matrix[5]) * det;
 inverse[6] = inverse[2];
 inverse[7] = inverse[5];
 inverse[8] = (matrix[0]*matrix[4] - matrix[1]*matrix[3]) * det;

}
