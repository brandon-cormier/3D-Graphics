#include "insert_triangle_into_box.h"

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  //For each axis, if any of the corner values are smaller than the min corner, grow B's min corner to reach the smallest corner
  //If any values ae larger than B's max corner, grow B's max corner to be the largest corner
  for(int i = 0; i < 3; i++){
    B.min_corner[i] = fmin(fmin(fmin(B.min_corner[i], a[i]), b[i]), c[i]);
    B.max_corner[i] = fmax(fmax(fmax(B.max_corner[i], a[i]), b[i]), c[i]);
  }
  ////////////////////////////////////////////////////////////////////////////
}


