#include <iostream>
#include <string>
#include <vector>

using namespace std;

void printPuzzle(vector<int> puzzle){
    cout << "[" << puzzle.at(0) << ", " << puzzle.at(1) << ", " << puzzle.at(2) << "]\n";
    cout << "[" << puzzle.at(3) << ", " << puzzle.at(4) << ", " << puzzle.at(5) << "]\n";
    cout << "[" << puzzle.at(6) << ", " << puzzle.at(7) << ", " << puzzle.at(8) << "]\n";

}

int main(){
    //1D array that holds the puzzle values
    //Chose a 1D array because it makes it easier for me to piece everything together
    vector<int> puzzle(9);
    // cout <<"vector" << puzzle.size();

    cout << "8-puzzle Solver Program\n";
    cout << "Please enter '1' for a default puzzle or '2' to make your own puzzle\n";
    
    int input;
    cin >> input;
    if(input == 1){
        puzzle.at(0)= 1;
        puzzle.at(1)= 2;
        puzzle.at(2)= 3;
        puzzle.at(3)= 4;
        puzzle.at(4)= 5;
        puzzle.at(5)= 6;
        puzzle.at(6)= 0;
        puzzle.at(7)= 7;
        puzzle.at(8)= 8;

        printPuzzle(puzzle);
    }
    else if(input == 2 ){
        cout << "Please enter your puzzle. Please use 0 to represent the blank. Please enter the numbers with a space inbetween\n";
        string puzzleInput;
        cout << "Enter the first row: ";
        cin >> puzzleInput;
        puzzle.at(0) = int(puzzleInput.at(0)) -48;
        puzzle.at(1) = int(puzzleInput.at(2)) -48;
        puzzle.at(2) = int(puzzleInput.at(4)) -48 ;
        cout << "Enter the second row: ";
        cin >> puzzleInput;
        puzzle.at(3) = int(puzzleInput.at(0)) -48;
        puzzle.at(4) = int(puzzleInput.at(2)) -48 ;
        puzzle.at(5) = int(puzzleInput.at(4)) -48;
        cout << "Enter the third row: ";
        cin >> puzzleInput; 
        puzzle.at(6) = int(puzzleInput.at(0)) -48;
        puzzle.at(7) = int(puzzleInput.at(2)) -48;
        puzzle.at(8) = int(puzzleInput.at(4)) -48;
        printPuzzle(puzzle);
    }
}