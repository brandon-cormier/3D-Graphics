#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  sqrD = std::numeric_limits<double>::infinity();
  ///for each point
  for (int i = 0; i < points.rows(); i++){
      //check distance from the query to the point
      double curr_dist = (query - points.row(i)).squaredNorm();
      //If it's smaller than the previous minimum, record it
      if(sqrD > curr_dist){
        sqrD = curr_dist;
        I = i;
      }
  }

  ////////////////////////////////////////////////////////////////////////////
}
