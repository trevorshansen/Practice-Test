/**

* Trevor Hansen

* Practice Test Maker

*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <assert.h>
#include "List.h"
using namespace std;

void readQuestions(List<string> &questions);
void generateSetOfNumbers(int questionOrder[], int length);
bool testSetOfNumbers(int questionOrder[], int length);
void numOfTests(int &numTests, int &qPerTest, List<string> &questions);
void printPractice(int numTests, int qPerTest, List<string> &questions, int questionOrder[]);

int main() {
	srand(time(0));
	int numTests, qPerTest, length;
	List<string> questions;

	cout << "Welcome to the practice test maker!\n\n";

	readQuestions(questions);
	length = questions.getLength();
	int questionOrder[length];
	generateSetOfNumbers(questionOrder, length);

	numOfTests(numTests, qPerTest, questions);

	string temp;
	while(temp != "q" && temp != "Q"){
		printPractice(numTests, qPerTest, questions, questionOrder);
		cout << "\nWould you like the questions re-shuffled? (Enter Y for yes, N for no or Q to quit) ";
		cin >> temp;
		if(temp == "y" || temp == "Y"){
			generateSetOfNumbers(questionOrder, length);
		}
		if(temp != "q" && temp != "Q"){
			cout << "\nWould you like to change the number of practice tests? (Enter Y for yes, N for no or Q to quit) ";
			cin >> temp;
			if(temp == "y" || temp == "Y"){
				cout << endl;
				numOfTests(numTests, qPerTest, questions);
			}
		}
	}
}

void readQuestions(List<string> &questions){
	string fileName;
	fstream infile;
	cout << "Enter the name of a file containing a list of sample questions: ";
	//cin >> fileName;
	infile.open("midterm1.txt");
	while(!infile){
		cout << "Please enter a valid file name: ";
		cin >> fileName;
		infile.open(fileName);
	}

	string myLine;
	while(getline(infile, myLine, '\n')){
		questions.insertLast(myLine);
	}

	cout << "\nThere are " << questions.getLength() << " lines in your study guide" << endl;
	cout << "The questions are:\n";
	questions.printNumberedList();
}

void generateSetOfNumbers(int questionOrder[], int length)
{
	int p[length];
	for(int i = 0; i < length; i++){
		p[i] = i;
	}
    //shuffle questionOrder[]
    for (int i = length; i > 0; --i){
		//get swap index
		int j = rand() % i;
		//swap p[i] with p[j]
		int temp = p[i-1];
		p[i-1] = p[j];
		p[j] = temp;
    }
    //copy first n elements from p to arr
    for (int i=0; i < length; i++)
    	questionOrder[i] = p[i];

    bool goodSet;
    goodSet = testSetOfNumbers(questionOrder, length);
    if(goodSet)
    	cout << "\nQuestions shuffled!\n";
    else{
    	cout << "\nRandom shuffle not working!\n";
    	assert(goodSet);
    }
}

//Checks that the array all the numbers from 0 to length and that there are no repeats.
bool testSetOfNumbers(int questionOrder[], int length){
	bool outRange = false;
	//Checking if any elements are out of range
	for(int i = 0; i < length; i++){
		if(questionOrder[i] < 0 || questionOrder[i] >= length){
			cout << "Element " << questionOrder[i] << " at index "
				 << i << " is out of range! " << endl;
			outRange = true;
		}
	}
	int index = 0;
	bool found, repeat;
	while(index < length){
		found = repeat = false;
		for(int i = 0; i < length; i++){
			if(questionOrder[i] == index){
				if(found == false)
					found = true;
				else
					repeat = true;
			}
		}
		if(repeat == true){
			cout << index << " is repeated!\n";
		}
		if(found == false){
			cout << index << " is not found!\n";
		}
		index++;
	}
	cout << endl;
	if(repeat == true || found == false || outRange == true)
		return false;
	else
		return true;
}

void numOfTests(int &numTests, int &qPerTest, List<string> &questions){
	string input = "n";
	while(input == "n" || input == "N"){
		cout << "There are " << questions.getLength() << " questions in the study guide, how many practice tests would you like to split them into? ";
		cin >> numTests;
		while(numTests < 1 || numTests > questions.getLength()){
			cout << "\nPlease enter a number less than or equal to " << questions.getLength() << " and greater than 0: ";
			cin >> numTests;
		}
		qPerTest = questions.getLength()/numTests;
		if(questions.getLength()%numTests != 0){
			cout << "\nThis will make " << numTests - 1 << " tests with " << qPerTest << " questions and one test with " << (questions.getLength()%numTests)+qPerTest
				 << " questions. Is that ok? (Enter any key to continue or N to try a new number) ";
		}else{
			cout << "\nThis will make " << numTests << " tests with " << qPerTest << " questions. "
				 << "Is that ok? (Enter any key to continue or N to try a new number) ";
		}
		cin >> input;
	}
}

void printPractice(int numTests, int qPerTest, List<string> &questions, int questionOrder[]){
	string input;
	while(input != "q" && input != "Q"){
		int index = 0;
		for(int i = 0; i < numTests; i++){
			cout << "\nHere is practice test " << i+1 << endl;
			if(i+1 == numTests && questions.getLength()%numTests != 0){
				for(int j = 0; j < (questions.getLength()%numTests)+qPerTest; j++){
					questions.advanceToIndex(questionOrder[index]+1);
					cout << j + 1 << ".\t" << questions.getIterator() << endl;
					index++;
				}
			} else{
				for(int j = 0; j < qPerTest; j++){
					//cout << index <<"\n";
					questions.advanceToIndex(questionOrder[index]+1);
					cout << j + 1 << ".\t" << questions.getIterator() << endl;
					index++;
				}
			}
			if(i+1 == numTests){
				cout << "\nThat's the last practice test!\n";
				input = "q";
			}else{
				cout << "\nEnter Q to quit, or any other key to move on to the next practice test. ";
				cin >> input;
				//cout << endl;
			}
			if(input == "q" || input == "Q"){
				i = numTests;
			}
		}
	}
}
