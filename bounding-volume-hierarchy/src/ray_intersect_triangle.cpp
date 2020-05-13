#include "ray_intersect_triangle.h"
#include <Eigen/Geometry>

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d c0 = A;
  Eigen::Vector3d c1 = B;
  Eigen::Vector3d c2 = C; //corner values
  Eigen::Vector3d t1 = c1 - c0;  //side 1 of the triangle
  Eigen::Vector3d t2 = c2 - c0; //side 2 of the triangle
  Eigen::Vector3d d = ray.direction; // ray direction
  Eigen::Vector3d e = ray.origin - c0; //ray origin matched with triangle vectors t1 and t2 origin

  Eigen::Matrix3d problem;
  problem << t1[0], t2[0], -d[0],  t1[1], t2[1], -d[1],  t1[2], t2[2], -d[2]; //matrix for the system of equations

  Eigen::Vector3d solution = problem.inverse() * e;  //solution

  
  //solution[0] = alpha, solution[1] = beta, solution[2] = t

  //check that point is within the triangle, and that the t value is greater than t_min
  if (solution[0] + solution[1] > 1 || solution[2] < min_t ||
  solution[2 > max_t] || solution[0] < 0 || solution[1] < 0){
    return false;
  }
  else{ //triangle was hit by ray
    t = solution[2];
    return true;
  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}

