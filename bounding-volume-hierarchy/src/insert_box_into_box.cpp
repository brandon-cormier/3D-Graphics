#include "insert_box_into_box.h"

void insert_box_into_box(
  const BoundingBox & A,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  //for each axis, if the min corner of A is smaller than B, grow B's min corner along that axis to equal A's min corner
  //then if the max corner for that axis is larger, grow B's max corner along that axis to equal A's max corner
  for(int i = 0; i < 3; i++){
    if(B.min_corner[i] > A.min_corner[i]){
      B.min_corner[i] = A.min_corner[i];
    }
    if(B.max_corner[i] < A.max_corner[i]){
      B.max_corner[i] = A.max_corner[i];
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}

