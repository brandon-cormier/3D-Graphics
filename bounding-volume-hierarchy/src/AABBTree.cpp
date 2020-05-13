#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  //Expand this bounding box to hold all objects in children
  for(int i = 0; i < objects.size(); i++){
    insert_box_into_box(objects[i] -> box, this ->box);
  }
  int size = objects.size();

  //leaf node cases
  if (size == 0){
    this ->left = NULL;
    this ->right = NULL;
  }
  else if (size == 1){
    this ->left = objects[0];
    this ->right = NULL;
  }
  else if (size == 2){
    this ->left = objects[0];
    this ->right = objects[1];
  }


  else{
    Eigen::RowVector3d all_axis = this -> box.max_corner - this -> box.min_corner;
    int axis;
    //longest axis
    double max = all_axis.maxCoeff(&axis);
    //center of axis
    double center_axis = this->box.center()[axis];
    std::vector<std::shared_ptr<Object> >  objects_left;
    std::vector<std::shared_ptr<Object> >  objects_right;
    //split objects based via center of longest axis
    for(int i = 0; i < objects.size(); i++){
      if(objects[i]->box.center()[axis] < center_axis){
        objects_left.emplace_back(objects[i]);

      }
      else{
        objects_right.emplace_back(objects[i]);

      }
    }

    //to prevent the edge case where one child is empty
    if (objects_right.size() == 0 && objects_left.size() != 0){
        objects_right.emplace_back(objects_left.back());
        objects_left.pop_back();

    }else if (objects_right.size() != 0 && objects_left.size() == 0){
        objects_left.emplace_back(objects_right.back());
        objects_right.pop_back();
        
    }
    //recursivley create the tree
    this->left = std::make_shared<AABBTree>(objects_left, a_depth+1);
    this->right = std::make_shared<AABBTree>(objects_right, a_depth+1);

  } 


  ////////////////////////////////////////////////////////////////////////////
}

bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  t = 0;
  //null check
  if(descendant == NULL){
    return false;
  }
  //check if the bounding box is hit, if not the whole subtree will be pruned
  if(ray_intersect_box(ray, this ->box, min_t, max_t)){
    double left_t, right_t;
    std::shared_ptr<Object>  left_child, right_child; 
    //recursevily check both child bounding boxes
    bool left = (this ->left != NULL) && this -> left -> ray_intersect(ray, min_t, max_t, left_t, left_child);
    bool right = (this ->right != NULL) && this -> right -> ray_intersect(ray, min_t, max_t, right_t, right_child);
    
    switch (left + right)
    {
      case 0: //no hit
        return false;
    
      case 1: //1 hit
        if (left && !right){
          t = left_t;
          descendant = left_child;
          return true;
        }
        else{
          t = right_t;
          descendant = right_child;
          return true;
        }
      case 2: //both hit, use the closest child
      if(right_t < left_t){
        t = right_t;
        descendant = right_child;
        return true;
      }
      else{
        t = left_t;
        descendant = left_child;
        return true;
      }
    }

  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}
