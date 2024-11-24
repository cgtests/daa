//Randomized quick sort

#include <iostream>
#include <random>

//utility function to swap elements:
void swap(int*, int*);

//partitioning function
int partition(int A[], int low, int high)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the mersenne twister 19937
    std::uniform_int_distribution<> mcs(low, high);
    int pIndex = mcs(gen);
    int pivot = A[pIndex];
    swap(&A[pIndex], &A[high]); // Move pivot to the end
    int i = low - 1;

  for (int j = low; j < high; j++) {
        if (A[j] <= pivot) {
            i++;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i + 1], &A[high]);  //move pivot to it's correct position

    return i+1; //return partition index
    

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

    quickSort(A, 0, n-1);

    std::cout << '\n' << "Output: ";
    
    for(int i{0}; i<n; ++i)
        std::cout << A[i] << " ";

    std::cout << '\n';
    return 0;
}

void swap(int* a, int*  b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
