#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 



void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  std::list<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object> > > queue;
  if(box_box_intersect(rootA ->box, rootB ->box)){
    queue.emplace_back(rootA, rootB);
  }
  std::shared_ptr<AABBTree> A;
  std::shared_ptr<AABBTree> B;

  //keep filling the list with children of A and B to get to the roots of both, prune out any children who's boxes don't intersect
  while(!queue.empty()){
    A = std::static_pointer_cast<AABBTree>(queue.front().first);
    B = std::static_pointer_cast<AABBTree>(queue.front().second);
    queue.pop_front();

    //Both A and B have leaves for children or are leaves
    if (A->num_leaves <= 2 && B->num_leaves <= 2){
      if(A -> left && B->left){
        if(box_box_intersect(A ->left ->box, B ->left ->box)){
          leaf_pairs.emplace_back(A -> left, B ->left);
        }
      }
      if(A -> right != NULL && B->right != NULL){
        if(box_box_intersect(A ->right ->box, B ->right ->box)){
          leaf_pairs.emplace_back(A -> right, B ->right);
        }
      }
      if(A -> right != NULL && B->left != NULL){
        if(box_box_intersect(A ->right ->box, B ->left ->box)){
          leaf_pairs.emplace_back(A -> right, B ->left);
        }
      }
      if(A -> left != NULL && B->right != NULL){
        if(box_box_intersect(A ->left ->box, B ->right ->box)){
          leaf_pairs.emplace_back(A -> left, B ->right);
        }
      }
    }
    //Only A's children are leaves
    else if (A -> num_leaves <= 2){
      if(B ->left != NULL && box_box_intersect(A ->box, B ->left ->box)){
        queue.emplace_back(A, B -> left);
      }
      if(B ->right != NULL && box_box_intersect(A ->box, B ->right ->box)){
        queue.emplace_back(A, B -> right);
      }
    }
    //Only B's children are leaves
    else if(B -> num_leaves <= 2){
      if(A ->left != NULL && box_box_intersect(B ->box, A ->left ->box)){
        queue.emplace_back(A ->left, B);
      }
      if(A ->right != NULL && box_box_intersect(B ->box, A ->right ->box)){
        queue.emplace_back(A -> right, B);
      }
    }
    //Neither are leaves, add all possible configurations into the queue, but check if their bounding boxes intersect first to prune them
    else{
      if(A ->left != NULL &&  B -> left != NULL && box_box_intersect(A -> left ->box, B ->left ->box)){
        queue.emplace_back(A -> left, B->left);
      }
      if(A ->left != NULL && B -> right != NULL && box_box_intersect(A -> left ->box, B ->right ->box)){
        queue.emplace_back(A -> left, B->right);
      }
      if(A ->right != NULL && B -> left != NULL && box_box_intersect(B -> left ->box, A ->right ->box)){
        queue.emplace_back(A -> right, B->left);
      }
      if(A ->right != NULL && B -> right != NULL && box_box_intersect(B ->right ->box, A ->right ->box)){
        queue.emplace_back(A -> right, B->right);
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
