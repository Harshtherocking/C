#include <omp.h>
#include  <stdlib.h>
#include <stdio.h> 
#include <time.h>

#define NT 16


void swap (int *x, int *y){
  int temp = *x;
  *x = *y;
  *y = temp;
}


/*
to merge to sorted arrays in parallel 
*/
void merge (int*arr1 , int *arr2, int s1, int s2){
  int l =0;
  int r =0;
  while (l<s1 && r<s2){
    if (arr1[l] > arr2[r]){
      int temp = arr2[r];
      arr2[r] = arr1[s1-1];

      int i = s1-1;
      while (i<l){
        swap(arr1 + i, arr1 + i-1);
        i--;
      }

      arr1[l] = temp;
      r++;
    }
    l++;
  }
}



// sequential bubble sort 
void bubble_sort(int *arr, int len){
  int sorted = 0;
  while(!sorted){
    sorted = 1;
    for (int i=0; i<len-1; i++){
      if (arr[i] > arr[i+1]){
        swap(arr+i, arr+i+1);
        sorted = 0;
      } 
    }
  }
}


void parallel_bubble_sort (int * arr, int arr_len){

  // defining chunk
  int chunk_size = 0;
  chunk_size = arr_len/NT;
  if (!chunk_size) chunk_size = 2;


  //to divide array into chunks and sort each chunk in parallel
  #pragma omp parallel shared (arr,arr_len,chunk_size)
  {
    // to eliminate out of bound
    if (omp_get_thread_num() > arr_len) exit(0);
    
    // defining start and end for bubble sorting for each thread
    int start_idx = omp_get_thread_num() * chunk_size;
    int end_idx = start_idx + chunk_size -1 ;
    if (omp_get_thread_num() == NT-1) end_idx = arr_len-1;

    // length of subarray for each thread
    int len = end_idx - start_idx + 1;
    bubble_sort(arr + start_idx, len);
  }

  // to merge the arrays in parallel
  #pragma omp parallel shared(arr, arr_len, chunk_size)
  {
  }

}



int main (){
  // initialising array
  int arr_len = 1000;
  int * arr = (int*)malloc(sizeof(int) * arr_len);

  // filling up array in decreasing order
  for (int i=0; i<arr_len; i++) arr[arr_len-i-1] =i+1;

  parallel_bubble_sort(arr, arr_len);
}
