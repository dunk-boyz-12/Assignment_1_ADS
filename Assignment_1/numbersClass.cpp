#include <iostream>
#include <fstream>
#include "customErrorClass.h"

using namespace std;

class C_Numbers{
    public:
        C_Numbers();
        ~C_Numbers();
    
        void readFile(char[100]);
        void printArray();
        void sortArray();

    private:
        int *p_numArray;
        int p_arraySize;
        int tempSwapValue;

        void p_readFile(char[100]);
        void p_printArray();
        void p_sortArray();
        void p_insertionSort();
        void p_swap(int& smallerNum, int& biggerNum);
};

/*
**    Author: Alex Wollman & Nick Buras
**    Function Purpose: initialize p_numArray and p_arraySize variables.
**        
**    Function Output: Nothing.
**    Side Effects: An object of C_Numbers Class is created
*/
C_Numbers::C_Numbers(){
    this->p_numArray = NULL;
    this->p_arraySize = 0;
}

/*
**    Author: Alex Wollman & Nick Buras
**    Function Purpose: Delete C_Numbers Class object, along with its allocated memory
**        
**    Function Output: Nothing.
**    Side Effects: An object of C_Numbers Class is destroyed and dynamically allocated memory is freed back to the heap.
*/
C_Numbers::~C_Numbers(){
    delete[] this->p_numArray;
}

/*
**    Author: Nick Buras
**    Function Purpose: Call private method, p_printArray, to print sorted array.
**        
**    Function Output: Sorted array values from p_numArray are printed to the console in ascending order.
**    Side Effects: p_printArray is called to print sorted array, p_numArray values are printed to the console.
*/
void C_Numbers::printArray(void){
    //call to private function
    this->p_printArray();
}

/*
**    Author: Nick Buras
**    Function Purpose: Call private readFile method, p_readFile(), to read input file, input.dat, and fill array
**        with the values from the file.
**    Function Output: Nothing.
**    Side Effects: private readFile method, p_readFile(), is called.
*/
void C_Numbers::readFile(char fileName[100]){
    //call to private function
    this->p_readFile(fileName);
}

/*
**    Author: Nick Buras
**    Function Purpose: To sort values in ascending order within p_numArray array.
**
**    Function Output: Nothing.
**    Side Effects: private method, p_sortArray(), is called to sort array values in ascending order.
*/
void C_Numbers::sortArray(){
    //call to private function
    this->p_sortArray();
}

/*
**    Author: Nick Buras
**    Function Purpose: To sort values in p_numArray array in ascending order.
**
**    Function Output: Nothing.
**    Side Effects: private sorting implementation is called, p_insertionSort(), array values are sorted in ascending order in place.
**
*/
void C_Numbers::p_sortArray(){
    //call private sort method of choice, insertion sort
    this->p_insertionSort();
}

/*
**    Author: Nick Buras
**    Function Purpose: Implementation of insertion sort, array values are sorted in ascending order.
**
**    Function Output: Nothing.
**    Side Effects: Array values are sorted in ascending order, private helper function p_swap() is
**      called to swap numbers in the array in place that are out of order.
*/
void C_Numbers::p_insertionSort(){
    //vars to store current place within array
    int arrayIndexCtr = 1;
    //index for numbers for comparison
    int currNumIndex;
    int numToCompIndex;
    //loop through entire array
    for(arrayIndexCtr; arrayIndexCtr < this->p_arraySize; arrayIndexCtr++){
        //set index for current value to check and the number to compare it to
        currNumIndex = arrayIndexCtr;
        numToCompIndex = currNumIndex - 1;
        //backtrack from current array index, checking if numbers are in the right place
        //swap out of order numbers
        while(numToCompIndex >= 0){
            if(this->p_numArray[currNumIndex] < this->p_numArray[numToCompIndex]){
                this->p_swap(this->p_numArray[currNumIndex], this->p_numArray[numToCompIndex]);
            } else {
                //break out of while loop, no need to check rest values, already sorted
                break;
            }
            //decrement index to check numbers all the way back to front of list if necessary
            numToCompIndex--;
            currNumIndex--;
        }
    }
}

/*
**    Author: Nick Buras
**    Function Purpose: Swap number values that are out of order within the p_numArray array.
**
**    Function Output: Nothing.
**    Side Effects: Numbers within the p_numArray array are swapped in place to put them in ascending order, temp int value is
**      populated/changed.
*/
void C_Numbers::p_swap(int& smallerNum, int& biggerNum){
    //store smaller value in temp variable
    this->tempSwapValue = smallerNum;
    //swap numbers in place
    smallerNum = biggerNum;
    biggerNum = this->tempSwapValue;
}

/*
**    Author: Nick Buras
**    Function Purpose: Print sorted p_numArray values in ascending order the console.
**        
**    Function Output: p_numArray values in ascending order.
**    Side Effects: p_numArray values are printed to the console for the user to see.
*/
void C_Numbers::p_printArray(void){
    for(int index = 0; index < this->p_arraySize; index++) {
        cout << this->p_numArray[index] << " ";
    }
    cout << endl;
}

/*
**    Author: Nick Buras
**    Function Purpose: Open input File, input.dat, update p_arraySize variable, and populate p_numArray array.
**
**    Function Output: Nothing.
**    Side Effects: Input file, input.dat, is opened/closed, memory is allocated for p_numbersArray array with file content(integers),
**      and p_arraySize variable is updated to contain the size of the newly created array.
*/
void C_Numbers::p_readFile(char fileName[100]){
    //initialize stream object and open input file
    fstream inFile(fileName);
    
    //make sure file was opened correctly
    if(!inFile.is_open()) {
        throw MyException("The input file could not be opened. Bye !");
    } else {
        //update array size variable
        inFile >> this->p_arraySize;
        //allocate memory for numbers array
        this->p_numArray = new int[this->p_arraySize];
        //populate array with numbers from file
        for(int index = 0; index < this->p_arraySize; index++) {
            inFile >> this->p_numArray[index];
        }
        //close input file
        inFile.close();
    }
}


/*
**    Author: Nick Buras
**    Function Purpose: Run Assignment 1 program to read in values from an input file into an array, sort the array, and print the values
**        in ascending order to the console for the user.
**    Function Output: Values within the C_Numbers Class object array are printed to the console in ascending order.
**    Side Effects: console is opened and values within the C_Numbers Class object array are printed to the console.
*/
int main(int argc, char *argv[]){
    
    //create Numbers Class instance & file name array
    C_Numbers myNumbers;
    char inputFileName[] = "input.dat";
    
    try {
        //read input File and populate class array
        myNumbers.readFile(inputFileName);
        //sort class array in ascending order
        myNumbers.sortArray();
        //print sorted class array values to the console
        myNumbers.printArray();
        //catch all custom exceptions that might have been thrown
    } catch(MyException &error) {
        cout << error.what();
    } catch(exception &error) {
        cout << error.what();
    }

    //return 0;
}
