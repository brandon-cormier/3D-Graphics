#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue
#include <functional>

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  //following the pseudo-code in the handout
  std::priority_queue<std::pair<double,std::shared_ptr<AABBTree>> , std::vector<std::pair<double, std::shared_ptr<AABBTree>>>, std::greater<std::pair<double, std::shared_ptr<AABBTree>>>> Q;
  double d_r = point_box_squared_distance(query, root ->box);

  Q.emplace(std::make_pair(d_r, root));

  sqrd = std::numeric_limits<double>::infinity();
  //loop through the tree, pruning subtrees with bounding box distances larger than the current minium, until either all nodes are pruned or visited
  while(!Q.empty()){
    double d_s = Q.top().first;
    std::shared_ptr<AABBTree> subtree = Q.top().second;
    Q.pop();
    if (d_s < sqrd){
      //leaf check
      if(subtree ->num_leaves <= 2){
        double curr_sqrd;
        std::shared_ptr<Object> curr_desc;
        if (subtree -> left != NULL && subtree ->left ->point_squared_distance(query, min_sqrd, max_sqrd, curr_sqrd, curr_desc)){
          if(curr_sqrd < sqrd && curr_sqrd > min_sqrd && curr_sqrd < max_sqrd ){
            sqrd = curr_sqrd;
            descendant = subtree ->left; 
          }
        }
        if (subtree -> right !=NULL && subtree ->right ->point_squared_distance(query, min_sqrd, max_sqrd, curr_sqrd, curr_desc)){
          if(curr_sqrd < sqrd && curr_sqrd > min_sqrd && curr_sqrd < max_sqrd ){
            sqrd = curr_sqrd;
            descendant = subtree ->right; 
          }
        }
      }
      //not a leaf
      else{
        if (subtree -> left != NULL){
          double d_left = point_box_squared_distance(query, subtree -> left -> box);
          Q.emplace(std::make_pair(d_left, std::static_pointer_cast<AABBTree>(subtree -> left)));
        }
        if (subtree -> right != NULL){
          double d_right = point_box_squared_distance(query, subtree -> right -> box);
          Q.emplace(std::make_pair(d_right, std::static_pointer_cast<AABBTree>(subtree -> right)));
        }
      }
    }
    

    
  }

  return sqrd < std::numeric_limits<double>::infinity();

  ////////////////////////////////////////////////////////////////////////////
}
