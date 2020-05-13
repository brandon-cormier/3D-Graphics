#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  //Implementation of method shown in class
  double Min [3];
  double Max [3];

  for(int i = 0; i < 3; i++){
    double multiplier = 1/ray.direction(i);
    double min_corner = box.min_corner(i) - ray.origin(i);
    double max_corner = box.max_corner(i) - ray.origin(i);
    if(1/ray.direction(i) >= i){
      Min[i] = multiplier * min_corner;
      Max[i] = multiplier * max_corner;
    }
    else{
      Min[i] = multiplier * max_corner;
      Max[i] = multiplier * min_corner;
    }
  }

  double min = fmax(fmax(fmax(Min[0], Min[1]), Min[2]), max_t);
  double max = fmin(fmin(fmin(Min[0], Min[1]), Min[2]), min_t);

  if(min < max){
    return true;
  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}
