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
      *(arr2 + r) = *(arr1 + size1-1);

      // shifting left side elements to one place right
      for (int k = size1-1; k>l; k --){
        *(arr1 + k) = *(arr1 + k -1);
      }

      // taking right side element to left side.
      *(arr1 + l ) = temp;

      // so that l can iterate more to right side by one 
      size1++;
      l++;
      r++;
    }
  }

}

// sort operation
void merge_sort(int * arr, int size){
  // return if a single element
  if (size == 1) return;

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
  int a [6] = {2,20,25,5,8,17};
  int len = 6;

  printf("before sorting : ");
  for (int i=0; i<len;i++){
    printf("%d ", a[i]);
  }
  printf("\n");

  merge_sort(a,len);

  printf("after sorting : ");
  for (int i=0; i<len;i++){
    printf("%d ", a[i]);
  }
  printf("\n");
}
