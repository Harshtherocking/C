#include <stdio.h>

// merge operation
void merge (int*arr1, int*arr2, int size1, int size2){
  int l = 0;
  int r = 0; 

  while (l < size1 && r < size2){

    // if left side element is smaller 
    if (*(arr1 + l ) <= *(arr2 + r)){
      l++;
    }

    // if left side element is greater
    else {
      // storing right side element to temp
      int temp = *(arr2 + r);

      // shifting left side elements to one place right
      for (int k = size1-1; k>l; k -- ){
        *(arr1 + k) = *(arr1 + k -1);
      }

      // taking right side element to left side.
      *(arr1 + l ) = temp;

      l++;
      r++;
    }
  }

}

// sort operation
void merge_sort(int * arr, int size){
  // return if a single element
  if (size ==1) return;

  // choosing a midpoint 
  int p = size / 2; 

  // partitioning first half
  merge_sort(arr,p);
  // partitioning second half
  merge_sort(arr+p, size-p);

  // merging
  merge(arr, arr+p, p, size-p);

}

int main (){
  int a [9] = {7,3,8,3,7,5,6,1,6};
  int len = 9;
  merge_sort(a,9);

  for (int i=0; i<9;i++){
    printf("%d ", a[i]);
  }
  printf("\n");
}
