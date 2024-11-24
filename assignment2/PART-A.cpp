#include <iostream>

//utility function to swap elements:
void swap(int*, int*);

//partitioning function
int partition(int A[], int low, int high)
{
   int pivot{A[low]};
  
   int i{low}, j{high};

   do
   {
       /* code */
       do{i++;} while(A[i]<=pivot); //skip smaller elements from left since they are on correct side
       do{j--;} while(A[j]>pivot); // skip larger elements from right since they are on correct side

       if(i<j) swap(&A[i], &A[j]);  // swap i and j when misplaced elements are encountered

   } while(i<j);

   swap(&A[low], &A[j]); //move pivot to it's correct position

   return j; //return partition index
  

}

void quickSort(int A[], int low, int high)
{
   int pi{};

   if(low < high)
   {
       pi = partition(A, low, high); // find partition index
       quickSort(A, low, pi-1); // apply quickSort on left subarray
       quickSort(A, pi+1, high); //apply quickSort on right subarray
   }
}
int main()
{

   int* A{};
 int n{};

   std::cout << "Enter input size: ";
   std::cin >> n;

   A = new int[n];
  
   std::cout << "Enter data: ";
  
   for(int i{0}; i<n; ++i)
       std::cin >> A[i];

   quickSort(A, 0, n);

   std::cout << '\n' << "Output: ";
  
   for(int i{0}; i<n; ++i)
       std::cout << A[i] << " ";

   std::cout << '\n';

}

void swap(int* a, int*  b)
{
   int temp = *a;
   *a = *b;
   *b = temp;
}
