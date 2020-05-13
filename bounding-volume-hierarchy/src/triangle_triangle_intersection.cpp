#include "triangle_triangle_intersection.h"
#include "Ray.h"
#include "ray_intersect_triangle.h"

bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  //project a ray along the side of each triangle, from 0 to 1 so that only the edge of the triangle is used. 
  //then, check if the ray that corresponds to the side of the triangle intersects with the other triangle
  //if any of these rays, from 0 to 1, intersects with the other triangle, then the two triangles intersect 
  double t;
  return ray_intersect_triangle(Ray(A0, A1-A0), B0, B1, B2, 0, 1, t)||
           ray_intersect_triangle(Ray(A1, A2-A1), B0, B1, B2, 0, 1, t) ||
           ray_intersect_triangle(Ray(A2, A0-A2), B0, B1, B2, 0, 1, t) ||
           ray_intersect_triangle(Ray(B0, B1-B0), A0, A1, A2, 0, 1, t) ||
           ray_intersect_triangle(Ray(B1, B2-B1), A0, A1, A2, 0, 1, t) ||
           ray_intersect_triangle(Ray(B2, B0-B2), A0, A1, A2, 0, 1, t);



 ////////////////////////////////////////////////////////////////////////////
}
