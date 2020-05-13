#include "point_triangle_squared_distance.h"
#include <Eigen/Geometry>

double point_triangle_squared_distance(
  const Eigen::RowVector3d & query,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  Eigen::RowVector3d & bary)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  Eigen::Vector3d a = A - C;
  Eigen::Vector3d b = B - C;
  Eigen::Vector3d normal = a.cross(b);
  Eigen::Vector3d query_ = query - C; //shift point to trangle's space

  //Barycentric values for the shifted point
  double gamma = a.cross(query_).dot(normal)/ normal.dot(normal);
  double beta = query_.cross(b).dot(normal)/normal.dot(normal);
  double alpha = 1 - gamma - beta;

  double beta_prime, gamma_prime, alpha_prime;

  bary = Eigen::RowVector3d (query_[0] * alpha, query_[1] * beta, query_[2]*gamma);

  //Check if the barycentric point is on the triangle
  if ((0 <= alpha) && (alpha <= 1) &&
            (0 <= beta)  && (beta  <= 1) &&
            (0 <= gamma) && (gamma <= 1)){
              Eigen::Vector3d distance = query - bary;
              return distance.squaredNorm();
              
            }

  //if the barycentric point is not on the triangle, 3 cases for finding the nearest point on the triangle to the shifted barycentric query
  else if(alpha >= 0 && beta < 0){ 
    if (gamma < 0 && (bary-A).dot(B-A) > 0){
        beta_prime = fmin(1, ((bary - A).dot(B-A))/(B-A).dot(B-A)); 
        gamma_prime = 0;
    }
    else{
      gamma_prime = fmin(1, ((bary - A).dot(C-A))/(C-A).dot(C-A));
      beta_prime = 0;
    }
    
  }
  else if(beta >= 0 && gamma < 0){
    if (alpha < 0 && (bary-B).dot(A-B) > 0){
        beta_prime = fmin(1, ((bary - B).dot(A-B))/(A-B).dot(A-B));
        gamma_prime = 0;
    }
    else{
      gamma_prime = fmin(1, ((bary - B).dot(C-B))/(C-B).dot(C-B));
      beta_prime = 0;
    }
  }
  else if(gamma >= 0 && alpha < 0){
    if (beta < 0 && (bary-C).dot(A-C) > 0){
        beta_prime = fmin(1, ((bary - C).dot(A-C))/(A-C).dot(A-C));
        gamma_prime = 0;
    }
    else{
      gamma_prime = fmin(1, ((bary - C).dot(B-C))/(B-C).dot(B-C));
      beta_prime = 0;
    }
  }
  alpha_prime = 1 - gamma_prime;
  bary = alpha_prime * A + beta_prime * B + gamma_prime * C;

  Eigen::Vector3d distance = query - bary;
  return distance.squaredNorm();
  ////////////////////////////////////////////////////////////////////////////
}
