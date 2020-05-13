#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  Eigen::Vector3d distance(0, 0, 0);
  //for each axis, go from the query point to the nearest axis on the box, if inside the box, 0 distance is used
  for(int i = 0; i < 3; i++){
    distance[i] = fmax(0, fmax(box.min_corner(i)-query(i), query(i)-box.max_corner(i)));
  }
  return distance.squaredNorm();
  ////////////////////////////////////////////////////////////////////////////
}
