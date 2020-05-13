#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

  int min_index;
  double curr_t = std::numeric_limits<double>::infinity();
  //loop through every trangle in the mesh and check for intersection
  //if an intersection is found, use the closest intersection found
  for (int i = 0; i < F.rows(); i++){
    const Eigen::RowVector3d &A = V.row(F(i,0));
    const Eigen::RowVector3d &B = V.row(F(i,0));
    const Eigen::RowVector3d &C = V.row(F(i,0));
    
    if(ray_intersect_triangle(ray, A, B, C, min_t, max_t, hit_t) && hit_t < curr_t){
      curr_t = hit_t;
      min_index = i;
    }

  }

  if (curr_t < std::numeric_limits<double>::infinity()){
    hit_t = curr_t;
    return true;
    
  }

  hit_t = 0;
  hit_f = 0;
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
