// Harrison Downs - B01256060
// Steven Simmermon
// May 2024
// CSCI 2320 Final Project

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <windows.h>

using namespace std;

void merge(vector<int>& dataCopy, int low, int mid, int high);
vector<int> readData(const string& filename);
vector<int> readSample(const string& filename, int sampleSize);
void displayData(const vector<int>& v);
vector<int> insertionSort(vector<int> v);
void mergeSort(vector<int>& dataCopy, int low, int high);
void merge(vector<int>& dataCopy, int low, int mid, int high);
void swap(int& x, int& y);
int split(vector<int>& v, int first, int last);
void quickSort(vector<int>& v, int low, int high);
void countingSort(vector<int>& v, int low, int high);

int main() {
    srand(time(0));

    string filename = "CSCI2320_final_project_dataset.txt";

    vector<int> data = readSample(filename, 100000); // Read a random sample of items from file (the file contains 500k elements)
    vector<int> countingSample = data;
    vector<int> mergeSample = data;
    vector<int> insertionSortSample;
    vector<int> quickSortSample = data;
    
    cout << "Data has been read.\n";
    Sleep(5000);

    /*
    displayData(data);
    cout << "Data has been displayed.\n";
    Sleep(5000);*/

    //Testing Perposes
    cout << "Ready" << endl;
    countingSort(countingSample, 0, countingSample.size() - 1);

    //cout << "Merge Sort" << endl;
    mergeSort(mergeSample, 0, mergeSample.size() - 1);

    //cout << "Insertion Sort" << endl;
    insertionSortSample = insertionSort(data);

    //cout << "Quick Sort" << endl;
    quickSort(quickSortSample, 0, mergeSample.size() - 1);
    
    

    /* THE PRETTY OUTPUT
    //Counting Sort
    cout << "Counting Sort:\n";
    countingSort(countingSample);
    cout << "Data has been sorted.\n";
    Sleep(5000);

    cout << "Min: " << countingSample[0] << endl;
    cout << "Max: " << countingSample[countingSample.size() - 1] << endl;
    Sleep(5000);

    displayData(countingSample);
    cout << "Data sorted by Counting Sort\n\n\n";
    Sleep(5000);

    cout << "/////////////////////////////////////////\n\n\n";

    //Merge Sort  
    
    cout << "Merge Sort:\n";
    mergeSort(mergeSample, 0, mergeSample.size()-1);
    cout << "Data has been sorted.\n";
    Sleep(5000);

    cout << "Min: " << mergeSample[0] << endl;
    cout << "Max: " << mergeSample[mergeSample.size() - 1] << endl;
    Sleep(5000);

    displayData(mergeSample);
    cout << "Data sorted by Merge Sort\n\n\n";
    Sleep(5000);

    cout << "/////////////////////////////////////////\n\n\n";
    
    //Insertion Sort
    cout << "Insertion Sort:\n";
    insertionSortSample = insertionSort(data);
    cout << "Data has been sorted.\n";
    Sleep(5000);

    cout << "Min: " << insertionSortSample[0] << endl;
    cout << "Max: " << insertionSortSample[insertionSortSample.size() - 1] << endl;
    Sleep(5000);

    displayData(insertionSortSample);
    cout << "Data sorted by Insertion Sort\n\n\n";
    Sleep(5000);

    cout << "/////////////////////////////////////////\n\n\n";

    //Quick Sort
    cout << "Quick Sort:\n";
    quickSort(quickSortSample, 0, mergeSample.size() - 1);
    cout << "Data has been sorted.\n";
    Sleep(5000);

    cout << "Min: " << quickSortSample[0] << endl;
    cout << "Max: " << quickSortSample[quickSortSample.size() - 1] << endl;
    Sleep(5000);

    displayData(quickSortSample);
    cout << "Data sorted by Quick Sort\n";
    Sleep(5000);*/

    return 0;
}

vector<int> readData(const string& filename) {
    ifstream inputFile(filename);
    vector<int> data;

    if (!inputFile) {
        cerr << "Error opening file: " << filename << endl;
        return data;
    }

    int value;
    while (inputFile >> value) {
        data.push_back(value);
    }

    inputFile.close();
    return data;
}
vector<int> readSample(const string& filename, int sampleSize)
{
    auto n = (rand() % (500000 - sampleSize)) * sizeof(int);   // Finds a random starting point for data collection & calculates byte offset
    fstream inputFile(filename);
    vector<int> data;

    if (!inputFile) {
        cerr << "Error opening file: " << filename << endl;
        return data;
    }

    // Set reading position to n
    inputFile.seekg(n, ios::beg);

    int value;
    int count = 0;
    while (inputFile >> value && count < sampleSize) {
        data.push_back(value);
        count++;
    }

    inputFile.close();
    return data;
}
void displayData(const vector<int>& v)  // Displays contents of a vector in sequential order
{
    if (v.empty())
    {
        cout << "No data or error reading the file." << endl;
    }
    else
    {
        cout << "Data read from file:" << endl;

        for (int num : v)
            cout << num << endl;

        cout << endl;
    }
}
vector<int> insertionSort(vector<int> v)
{
    int count = 0;
    int report_interval = v.size() / 10;

    for (int p = 1; p < v.size(); p++)  // n - 1 iterations (first element in v is skipped)
    {
        int temp = v[p];
        int j = 0;

        for (j = p; j > 0 && temp < v[j - 1]; j--)  // Find the exact position for key value
        {
            v[j] = v[j - 1];    // Shift elements backwards to make room for key value
        }

        if (count % report_interval == 0 && count != 0)   // Display progress message
            cout << (count / report_interval * 10) << "% sorted..." << endl;

        v[j] = temp;    // Now that position has been set, insert key value
        count++;
    }

    return v;
}
void mergeSort(vector<int>& dataCopy, int low, int high)
{
    int mid = 0;
    if (low < high)
    {
        mid = (low + high) / 2;
        mergeSort(dataCopy, low, mid);
        mergeSort(dataCopy, mid + 1, high);
        merge(dataCopy, low, mid, high);
    }
}
void merge(vector<int>& dataCopy, int low, int mid, int high) {
    vector<int> left(dataCopy.begin() + low, dataCopy.begin() + mid + 1);  //temp left vector
    vector<int> right(dataCopy.begin() + mid + 1, dataCopy.begin() + high + 1);  //temp right vector

    int i = 0, j = 0, k = low;
    while (i < left.size() && j < right.size()) //sorting data vector from the left and right vector until one side is equal to itself
    {
        if (left[i] <= right[j]) {
            dataCopy[k++] = left[i++];
        }
        else {
            dataCopy[k++] = right[j++];
        }
    }
    while (i < left.size())//fill in the spaces of data that didn't get filled
    {
        dataCopy[k++] = left[i++];
    }
    while (j < right.size()) //same thing
    {
        dataCopy[k++] = right[j++];
    }
}
void swap(int& x, int& y)
{
    int temp = x;
    x = y;
    y = temp;
}
int split(vector<int>& v, int first, int last)
{
    int pivot = v[first];
    int left = first, right = last;

    while (left < right)
    {
        while (pivot < v[right])
            right--;
        while (left < right && v[left] <= pivot)
            left++;
        if (left < right)
            swap(v[left], v[right]);
    }

    int pos = right;
    swap(v[first], v[pos]);

    return pos;
}
void quickSort(vector<int>& v, int low, int high)
{
    if (low < high)
    {
        int piv = split(v, low, high);
        quickSort(v, low, piv - 1);
        quickSort(v, piv + 1, high);
    }
}
void countingSort(vector<int>& v, int low, int high)
{
    int maxSize = 10000000;//Max size of Data
    vector<int> keys;

    for (int i = low; i <= maxSize; i++)   // Allocate an empty element for each int between low and high (inclusive)
        keys.push_back(0);

    for (const int& n : v)  // For each element in v, increment keys's corresponding index.
        keys[n - low]++;

    v.clear();

    for (int i = 0; i < keys.size(); i++)   // Reconstruct v
    {
        for (int j = 0; j < keys[i]; j++)
            v.push_back(i + low);
    }
}