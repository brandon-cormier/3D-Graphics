#include "box_box_intersect.h"
bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  //verify that for each axis, the maximum corner of each box is larger than the minimum corner of the other
  return A.max_corner[0] > B.min_corner[0] && B.max_corner[0] > A.min_corner[0]
          && A.max_corner[1] > B.min_corner[1] && B.max_corner[1] > A.min_corner[1]
          && A.max_corner[2] > B.min_corner[2] && B.max_corner[2] > A.min_corner[2];


  ////////////////////////////////////////////////////////////////////////////
}

