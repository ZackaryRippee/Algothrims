#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;



// Generate 10,000 numbers between 0 and 1000, and puts it into a txt file.
void numGenerate(){
  ofstream file("numbers.txt");
  for (int i = 0; i < 10000; i++){
    file << rand() % 1001 << "\n"; //1001 includes 0
  }
  file.close();
}

// load data from file into array
int loadData(int arr[]){
  ifstream file("numbers.txt");
  int count = 0;
  while (file >> arr[count]){
    count++;
  }
  file.close();
  return count;
}

// Save the data to a file
void saveResult(const char* filename, int arr[], int size){
  ofstream file(filename);
  for (int i = 0; i < size; i++){
    file << arr[i] << "\n";
  }
  file.close();
}

void insertionSort(int arr[], int size){
  for (int i = 1; i < size; i++){
    int key = arr[i];
    int j = i - 1;
    while (j >= 0 && arr[j] > key){
      arr[j+1] = arr[j];
      j--;
    }
    arr[j+1] = key;
  }
}


void countingSort(int arr[], int size){
  int count[1001] = {0};
  for (int i = 0; i < size; i++){
    count[arr[i]]++;
  }
  int index = 0;
  for (int i = 0; i <= 1000; i++){
    while (count[i] --> 0){
      arr[index++] =1;
    }
  }
}

void quickSort(int arr[], int left, int right){
  if (left >= right) return;
  int pivot = arr[right];
  int i = left - 1;
  for (int j = left; j < right; j++){
    if (arr[j] < pivot){
      i++;
      int tmp = arr[i];
      arr[i] = arr[j];
      arr[j] = tmp;
    }
  }

  int tmp = arr[i+1];
  arr[i+1] = arr[right];
  arr[right] = tmp;

  quickSort(arr, left, i);
  quickSort(arr, i + 2, right);
}


double measure(void (*sort)(int[], int), int data[], int size){
  clock_t start = clock();
  sort(data, size);
  return (double)(clock() - start) / CLOCKS_PER_SEC;
}

double measureQuick(int arr[], int size){
  clock_t start = clock();
  quickSort(arr,0, size - 1);
  return (double)(clock() - start) / CLOCKS_PER_SEC;
}

//generates all 10000 numbers, creates copies of the random assortment, sorts them all, and shows time
int main(){
  srand(time(0));
  numGenerate();

  int original[10000];
  int size = loadData(original);

  int copy1[10000], copy2[10000], copy3[10000];
  for (int i = 0; i < size; i++){
    copy1[i] = original[i];
    copy2[i] = original[i];
    copy3[i] = original[i];
  }
  double t1 = measure(insertionSort,copy1, size);
  double t2 = measure(countingSort, copy2, size);
  double t3 = measureQuick(copy3, size);

  saveResult("insertion_result.txt", copy1, size);
  saveResult("counting_result.txt", copy2, size);
  saveResult("quick_result.txt", copy3, size);

  cout << "Insertion Sort Time: " << t1 << " seconds\n";
  cout << "Counting Sort Time: " << t2 << " seconds\n";
  cout << "Quick Sort Time: " << t3 << " seconds\n";
  return 0;
}
