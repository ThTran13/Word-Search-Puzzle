#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>

using namespace std;

// implement class heap using class's code
template <typename T>
class heap
{
    vector<T> &vect;

public: //members of heap
    heap(){};
    heap(vector<T> &v) : vect(v) {}

    int parent(int i); //returns parent node
    int left(int i); //returns left subtree
    int right(int i); //returns right subtree
    T getItem(int n); //getting item in dictionary at n
    void initializeMaxHeap(); //largest element has highest priority
    void maxHeapify(int index, int heapSize); //finding largest heap and then changing directions
    void buildMaxHeap(); 
    void heapSort();
    int compareString(string, string); //compares strings
};

template <typename T>
int heap<T>::compareString(string a, string b) // compares two string a and b
{
    int len = a.size();
    for (int i = 0; i < len; i++)
    {
        if ((a > b) > 0) // returns 1 if true
        {
            return true;
        }
    }
    return false;
}

template <typename T>
int heap<T>::parent(int i)
{
    return floor(i / 2); // parent node
}

template <typename T>
int heap<T>::left(int i)
{
    return 2 * i; // left subtree
}

template <typename T>
int heap<T>::right(int i)
{
    return 2 * i + 1; // right subtree
}

template <typename T>
T heap<T>::getItem(int n)
{
    return vect[n]; // get item in dictionary at index n
}

template <typename T>
void heap<T>::initializeMaxHeap()
{
    for (int i = parent(vect.size() - 1); i >= 0; i--)
    {
        maxHeapify(i, vect.size());
    }
}

template <typename T>
void heap<T>::maxHeapify(int index, int heapSize) //finding leargest heap & changing directions
{
    int l = left(index);
    int r = right(index);
    int largest = index;

    if (l < heapSize && compareString(vect[l], vect[largest]))
    {
        largest = l;
    }

    if (r < heapSize && compareString(vect[r], vect[largest]))
    {
        largest = r;
    }

    if (largest != index)
    {
        swap(vect[index], vect[largest]);
        maxHeapify(largest, heapSize);
    }
}

template <typename T>
void heap<T>::buildMaxHeap()
{
    initializeMaxHeap();
}

template <typename T>
void heap<T>::heapSort()
{
    buildMaxHeap();

    int heapSize = vect.size();
    for (int i = vect.size() - 1; i > 0; i--)
    {
        swap(vect[0], vect[i]);
        heapSize--;
        maxHeapify(0, heapSize);
    }
}

class dictionary
{

public:
    dictionary(){};
    vector<string> mydictionary;
    void readWords(); //reading words fromi dictionary
    void printWords();//printing dictionary words
    void selectionSort(); //sorting using swap and compare strings
    void quicksortRecursion(vector<string> &, int, int); //recursive function for quicksort algorithm
    void quicksort(vector<string> &, int length); //uses quicksortRecursion
    int partition(vector<string> &, int, int); //setting quicksort recursion and quicksort function using pivotpoints and swap
    string binarySearch(int, int, string);
    bool compareString(string, string);
    void heapSort();
};
void dictionary ::readWords() // Fucntion for inputting file into C++
{
    string filename = "dictionary-2";

    ifstream inputFile(filename);


    if (inputFile.is_open())
    {

        string line;
        while (getline(inputFile, line))
        {
            mydictionary.push_back(line); // place words from line into mydictionary vector
        }

        inputFile.close();
    }
}

void dictionary ::printWords()
{
    // print out the content of the file (dictionary-2)
    for (string i : mydictionary)
    {
        cout << i << ", ";
    }
    cout << endl;
}

// function to compare 2 strings. Return true if the words are alphabetically not in order
bool dictionary ::compareString(string a, string b)
{
    int len = a.size();
    if (a < b) {
        return true;
    }
    return false;
}

void dictionary ::selectionSort() // Sorts strings in vector alphabetical order
{
    cout << "Begin selection sort";
    for (int i = 0; i < mydictionary.size() - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < mydictionary.size(); j++)
        {
            // if the two strings are not in order
            if (compareString(mydictionary[j], mydictionary[min]))
            {
                min = j;
            }
        }
        // swap
        if (min != i) {
            //cout << mydictionary[min] << endl;
            swap(mydictionary[min], mydictionary[i]);
        }
        
    }
}
int dictionary::partition(vector<string> &vect, int lowin, int highin) //finding pivotpoints using compare strings and then swaps using that point
{
    string pivot_value = vect[highin];
    int i = lowin - 1;
    for (int g = lowin; g < highin; g++)
    {

        if (compareString(vect[g], pivot_value))
        {
            i++;
            swap(vect[i], vect[g]);
        }
    }

    swap(vect[i + 1], vect[highin]);

    return i + 1;
}

void dictionary::quicksortRecursion(vector<string> &vect, int lowin, int highin) //recursive function for quicksort
{
    if (lowin < highin)
    {
        int pivot_index = partition(vect, lowin, highin);

        quicksortRecursion(vect, lowin, pivot_index - 1);
        quicksortRecursion(vect, pivot_index + 1, highin);
    }
}

void dictionary::quicksort(vector<string> &vect, int length) //performing the quicksort function
{
    quicksortRecursion(vect, 0, length - 1);
}

// implemenenting binarySearch using class's code
string dictionary ::binarySearch(int first, int last, string word) //binary search for word lookups
{
    heapSort();
    int mid;
    string midValue;
    while (first <= last) // if first is smaller or equals to the last value after sorting
    {
        mid = floor((first + last) / 2); // find the middle value

        midValue = mydictionary[mid];
        if (word == midValue)
        {
            return mydictionary[mid]; // find the target (match mid)
        }
        else if (word < midValue)
        // search lower sublist
        {
            last = mid - 1;
        }
        else // search upper sublist
        {
            first = mid + 1;
        }
    }

    return ""; // word not found
}

void dictionary ::heapSort() //heapsort algorithm
{
    heap<string> heap_sort(mydictionary);
    heap_sort.heapSort();
}

class grid
{
public: //members of grid
    grid(){};
    int size;
    vector<string> dict[26][26][26];
    string **createMatrix(string);
    int charToAlphabetIndex(char); //converting characters to part of alphabet
    bool checkEmpty(int); //check empty functions for first and second dimension for dic vector
    bool checkEmpty2(int, int); //^^
    void search(int, int, int, string **grids, int, int, int, int); //searching grid & comparing word to dictionary word
    void traverse(int, int, string **grid); //traversing through grid 
    void setSize(int n) //setting size
    {
        size = n;
    }
    int getSize() //getting size
    {
        return size;
    }
};

string **grid::createMatrix(string fileName) //generating matrix from input files 
{

    string firstWord;
    int n; // size of matrix
    ifstream inputFile(fileName);
    if(!inputFile.is_open()){
        cout << "file does not found" << endl;
    }

    if (inputFile.is_open())
    {
        string line;
        getline(inputFile, line);
        firstWord = line.substr(0, line.find(" "));
        n = stoi(firstWord); // string to integer
        setSize(n);

        // create an array nxn
        cout << "create grid: " << n << "x" << n << endl;

        string **matrix = new string *[n];
        for (int i = 0; i < n; ++i)
        {
            matrix[i] = new string[n];
        }

        string chars;
        for (int i = 0; i < n; i++)
        {
            getline(inputFile, line);

            for (int j = 0; j < n; j++)
            {
                chars = line.substr(j * 2, line.find(" "));
                matrix[i][j] = chars;
                cout << chars << " "; //outputting characters for matrix
            }
            cout << endl;
        }
        inputFile.close();

        return matrix;//creating matrix
    }
    else
    {
        return nullptr;
    }
}

int grid ::charToAlphabetIndex(char ch) //conversion of character to letter
{
    // Convert the character to lowercase
    ch = tolower(ch);

    // Check if it's a lowercase letter
    if (ch < 'a' || ch > 'z')
    {
        // If not a lowercase letter, return -1 or handle the error accordingly
        return -1;
    }

    // Return the index in the alphabetical order
    return ch - 'a' + 1;
}

void grid::search(int index1, int index2, int index3, string **grids, int y, int x, int posy, int posx) //searching grid
{
    string word_match = grids[x][y];
    int dict_size = dict[index1][index2][index3].size();
    int size = getSize();

    for (int i = 0; i < dict_size; i++)
    {
        string word = dict[index1][index2][index3][i];

        // cout << word << endl;

        int len = word.size();
        if ((x + len * posx < size) && (y + len * posy < size) && (x + len * posx > 0) && (y + len * posy > 0))
        {
            word_match = "";
            for (int j = 0; j < len; j++)
            {
                word_match.append(grids[y + j * posy][x + j * posx]);
            }
            // cout << x << " " << y << " : " << word_match << endl;
            if (word == word_match)
            {
                cout << word << endl; //outputting word match
            }
        }
    }
}
bool grid ::checkEmpty(int index) //check empty function for first dimension of dict vector
{
    for (int i = 0; i < 26; ++i)
    {
        for (int j = 0; j < 26; ++j)
        {
            if (!dict[index][i][j].empty())
            {
                // cout << "true" <<endl;
                return true; // Return true if any element is not empty
            }
        }
    }
    // cout << "false" << endl;
    return false; // Return false if all elements are empty
}
bool grid ::checkEmpty2(int index1, int index2) //check empty function for second dimension of dict vector
{

    for (int i = 0; i < 26; i++)
    {
        if (!dict[index1][index2][i].empty())
        {
            return true; // Return true if any element is not empty
        }
    }

    return false;
}

void grid::traverse(int y, int x, string **grids) //traversing through grid
{
    int posx, posy, posx_2, posy_2;

    int size = getSize();

    char letter = grids[y][x][0]; // let the first letter in the grid

    int index = charToAlphabetIndex(letter) - 1;
    // cout << "l1: " << letter << index << endl;

    for (int m = -1; m < 2; m++)
    // m = - 1, x goes backward
    // m = 0 stays the same
    // m = 1, x goes forward
    {
        for (int n = -1; n < 2; n++)
        // n = - 1; y goes up
        // n = 0 y stays the same
        // n = 1; y goes down
        {
            posx = x + m;
            posy = y + n;
            posx_2 = x + 2 * m;
            posy_2 = y + 2 * n;

            if ((n != 0) || (m != 0))
            {
                // cout << x <<"," << y<< " " << posx <<"," << posy << " " << posx_2 <<"," << posy_2 << endl;
                if (checkEmpty(index)) // check if there is word begins with the char letter in the dictionary
                {
                    if ((posx_2 < size) && (posy_2 < size) && (posx_2 > 0) && (posy_2 > 0))
                    { // Ensure within grid bounds
                        char letter_2 = grids[posy][posx][0];
                        int index2 = charToAlphabetIndex(letter_2) - 1;
                        // cout << "l2 : " << letter_2 << index2 << endl;
                        if (checkEmpty2(index, index2))
                        {
                            char letter_3 = grids[posy_2][posx_2][0];
                            int index3 = charToAlphabetIndex(letter_3) - 1;
                            // cout << "l3: " << letter_3 << index3<< endl;
                            search(index, index2, index3, grids, y, x, n, m);
                        }
                    }
                }
            }
        }
        // cout << endl;
    }
}

void findMatches(const vector<string> &dictionary, string **grids, int size) 
{   // function to sort the dictionary based on its first char, second char and third char
    //  to reduce search time while find words in the grid
    grid g;

    for (const string &word : dictionary)
    {
        // Get the first character of a string in dictionary
        char firstChar = word[0];
        char secondChar;
        char thirdChar;

        if (word.size() > 1)
        {
            // get second character
            secondChar = word[1];
        }
        else
        {
            secondChar = '\0'; // null character
        }
        if (word.size() > 2)
        {
            // get third character
            thirdChar = word[2];
        }
        else
        {
            thirdChar = '\0'; // null character
        }

        // Calculate the indices for the array
        int firstIndex = g.charToAlphabetIndex(firstChar) - 1; // -1 since dictionary iterated starting by 0
        int secondIndex = g.charToAlphabetIndex(secondChar) - 1;
        int thirdIndex = g.charToAlphabetIndex(thirdChar) - 1;

        // Check if indices are valid
        if (firstIndex >= 0 && firstIndex < 26 && secondIndex >= 0 && secondIndex < 26 && thirdIndex >= 0 && thirdIndex < 26 && word.size() > 4)
        {
            // append in a 26 x 26 x 26 vector
            g.dict[firstIndex][secondIndex][thirdIndex].push_back(word); // Push word into the appropriate vector
        }
    }

    g.setSize(size); 
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            // calling traverse
            g.traverse(i, j, grids);
        }
    }
}

void search(int num) //global search function inputting which sorting function to use
{
    string fname;
    dictionary sorting;

    sorting.readWords();

    if (num == 1)
    {   //selectionsort
        cout << "selection sort might took up to 3 minutes." << endl;
        sorting.selectionSort();   
    }

    else if (num == 2)
    {
        // quicksort
        sorting.quicksort(sorting.mydictionary, sorting.mydictionary.size());
    }

    else if (num == 3)
    {
        // heapsort
        sorting.heapSort();
    }
    sorting.printWords();

    cout << "Type the file name: " << endl;
    cin >> fname;
    
    grid solve;
    string **grids;
    grids = solve.createMatrix(fname);
    int length = solve.getSize();
    
    findMatches(sorting.mydictionary, grids, length);
}

int main()
{
    int sortChoice;
    bool choice = false;

    while (choice == false)
    {
        cout << "Choose which sort algorithm to use: " << '\n'
             << "1: Selection Sort" << '\n'
             << "2: Quick Sort" << '\n'
             << "3: Heap Sort" << endl;

        cin >> sortChoice;
        if (sortChoice == 1 || sortChoice == 2 || sortChoice == 3 )
        {
            search(sortChoice);
            choice = true;
        }
        else
        {
            cout << "wrong input, choose again: " << endl;
            choice = false;
        }
    }
    return 0;
}