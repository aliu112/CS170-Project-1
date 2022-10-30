#include <iostream>
#include <string>
#include <vector>

using namespace std;

//making struct to keep track of state which includes puzzle and costs of g(n) and h(n)
struct state{
    vector<int> puzzle;
    int g_n;
    int h_n;
};

//checks to see if the given puzzle has reached the end state
bool CheckIfFinished(vector<int> puzzle){
    vector<int> finalState {1,2,3,4,5,6,7,8,9,0};
    bool isFinished =true;
    for(int i=0; i<9; i++){
        if( puzzle.at(i) != finalState.at(i) )
        {
            isFinished = false; 
        }
    }
    return isFinished; 
}

//calcuating misplaced tiles heuristic
int CountingMisplacedTiles(vector<int> puzzle){
    int cost =0;
    for(int i=0; i<9; i++){ //checks how many tiles are out of place
        if(puzzle.at(i) != i+1){
            if(puzzle.at(i) == 0) //if that misplaced tile is 0 don't increase cost because we don't count a misplaced zero for this heuristic
            {
                break;
            }
            ++cost;
        }
    }
    return cost;
}

void printPuzzle(vector<int> puzzle){
    cout << "[" << puzzle.at(0) << ", " << puzzle.at(1) << ", " << puzzle.at(2) << "]\n";
    cout << "[" << puzzle.at(3) << ", " << puzzle.at(4) << ", " << puzzle.at(5) << "]\n";
    cout << "[" << puzzle.at(6) << ", " << puzzle.at(7) << ", " << puzzle.at(8) << "]\n";

}

int main(){
    //1D array that holds the puzzle values
    //Chose a 1D array because it makes it easier for me to piece everything together
    state newPuzzle;
    newPuzzle.puzzle = vector<int> (9);

    // cout <<"vector" << puzzle.size();

    cout << "8-puzzle Solver Program\n";
    cout << "Please enter '1' for a default puzzle or '2' to make your own puzzle\n";
    
    int input;
    cin >> input;
    //creates default puzzle
    if(input == 1){
        newPuzzle.puzzle.at(0)= 1;
        newPuzzle.puzzle.at(1)= 2;
        newPuzzle.puzzle.at(2)= 3;
        newPuzzle.puzzle.at(3)= 4;
        newPuzzle.puzzle.at(4)= 5;
        newPuzzle.puzzle.at(5)= 6;
        newPuzzle.puzzle.at(6)= 0;
        newPuzzle.puzzle.at(7)= 7;
        newPuzzle.puzzle.at(8)= 8;

        printPuzzle(newPuzzle.puzzle);
    }
    //gets user input to create the puzzle
    else if(input == 2 ){
        cout << "Please enter your puzzle. Please use 0 to represent the blank. Please enter the numbers with a space inbetween\n";
        string puzzleInput;
        cout << "Enter the first row: ";
        cin.ignore();
        getline(cin,puzzleInput);
        newPuzzle.puzzle.at(0) = int(puzzleInput.at(0)) -48; //gets input as a string and converts to int
        newPuzzle.puzzle.at(1) = int(puzzleInput.at(2)) -48;
        newPuzzle.puzzle.at(2) = int(puzzleInput.at(4)) -48;
        puzzleInput="";
        cout << "Enter the second row: ";
        getline(cin,puzzleInput);
        newPuzzle.puzzle.at(3) = int(puzzleInput.at(0)) -48;
        newPuzzle.puzzle.at(4) = int(puzzleInput.at(2)) -48;
        newPuzzle.puzzle.at(5) = int(puzzleInput.at(4)) -48;
        puzzleInput="";
        cout << "Enter the third row: ";
        getline(cin,puzzleInput);
        newPuzzle.puzzle.at(6) = int(puzzleInput.at(0)) -48;
        newPuzzle.puzzle.at(7) = int(puzzleInput.at(2)) -48;
        newPuzzle.puzzle.at(8) = int(puzzleInput.at(4)) -48;
        printPuzzle(newPuzzle.puzzle);
    }

    cout << "Select algorithm: \n";
    cout << "(1) Uniform Search Cost\n(2) Misplaced Tile Heuristic\n(3)Manhattan Distance Heuristic\n";
    int algoInput;
    cin >> algoInput;
    
    //general search algo goes below


}