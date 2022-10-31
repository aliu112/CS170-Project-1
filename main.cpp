#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

//making struct to keep track of state which includes puzzle and costs of g(n) and h(n)
struct puzzleNode{
    vector<int> puzzle;
    int g_n;
    int h_n;
    int f_n;

    //overloaded operator to make priority queue a min heap 
    //again used https://medium.com/@taohidulii/min-priority-queue-in-c-7e64bd01359c#:~:text=Save-,Min%20priority_queue%20in%20C%2B%2B,(returns%20the%20largest%20element).&text=Here%2C%20we're%20getting%20the,by%20applying%20some%20interesting%20tricks.
    // as a resource to do so
    bool operator< (const puzzleNode & a) const 
    {
    if(f_n == a.f_n) //if it's a tie, just pick the first node
        {
            return g_n > a.g_n;
        }else { //else pick the lowest cost node
            return f_n > a.f_n;
        }
    }

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

//Thining about hard coding it, can't think of a formula that would work for caluclating manhattan 
int ManhattanDistance(vector<int> puzzle ){

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

//
bool isInBounds(int zeroIndex, string direction){
    if(direction == "up"){
        if(zeroIndex == 0 || zeroIndex == 1 || zeroIndex == 2)
        {
            return false;
        }
        else {
            return true;
        }
    }
    else if(direction =="down"){
        if(zeroIndex == 6 || zeroIndex == 7 || zeroIndex == 8){
            return false;
        }
        else{
            return true;
        }
    }
    else if(direction =="right"){
        if( (zeroIndex -2) %3 == 0){
            return false;
        }
        else{
            return true;
        }
    }
    else if(direction == "left"){
        if(zeroIndex%3 == 0){
            return false;
        }
        else{
            return true;
        }
    }
    return false;
}

void expandNode(puzzleNode chosenNode, priority_queue<puzzleNode> &pq, int algoType){
    int zeroIndex=0; 
    //finds the index that holds zero so that we can decide where to move
    for(int i=0; i<9; ++i){ 
        if(chosenNode.puzzle.at(i) == 0)
        {
            zeroIndex = i;
        }
    }

    //making new puzzle that moves the blank space up
    if(isInBounds(zeroIndex, "up")){
        //NOTE TO SELF: check to see if the values correctly copy over
        puzzleNode newPuzzle = chosenNode;
        swap(newPuzzle.puzzle.at(zeroIndex), newPuzzle.puzzle.at(zeroIndex-3));
        if(algoType ==0){
            newPuzzle.g_n += 1;
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        else if(algoType == 1){
            newPuzzle.g_n +=1;
            newPuzzle.h_n = CountingMisplacedTiles(newPuzzle.puzzle);
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        else if(algoType == 2){
            newPuzzle.g_n +=1;
            newPuzzle.h_n = ManhattanDistance(newPuzzle.puzzle);
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        pq.push(newPuzzle);
    }

    //making new puzzle that moves the blank space down
    if(isInBounds(zeroIndex, "down")){
        puzzleNode newPuzzle = chosenNode;
        swap(newPuzzle.puzzle.at(zeroIndex), newPuzzle.puzzle.at(zeroIndex+3));
        if(algoType ==0){
            newPuzzle.g_n += 1;
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        else if(algoType == 1){
            newPuzzle.g_n +=1;
            newPuzzle.h_n = CountingMisplacedTiles(newPuzzle.puzzle);
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        else if(algoType == 2){
            newPuzzle.g_n +=1;
            newPuzzle.h_n = ManhattanDistance(newPuzzle.puzzle);
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        pq.push(newPuzzle);
    }

    if(isInBounds(zeroIndex, "right")){
        puzzleNode newPuzzle = chosenNode;
        swap(newPuzzle.puzzle.at(zeroIndex), newPuzzle.puzzle.at(zeroIndex+1));
        if(algoType ==0){
            newPuzzle.g_n += 1;
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        else if(algoType == 1){
            newPuzzle.g_n +=1;
            newPuzzle.h_n = CountingMisplacedTiles(newPuzzle.puzzle);
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        else if(algoType == 2){
            newPuzzle.g_n +=1;
            newPuzzle.h_n = ManhattanDistance(newPuzzle.puzzle);
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        pq.push(newPuzzle);
    }

    if(isInBounds(zeroIndex, "left")){
        puzzleNode newPuzzle = chosenNode;
        swap(newPuzzle.puzzle.at(zeroIndex), newPuzzle.puzzle.at(zeroIndex-1));
        if(algoType ==0){
            newPuzzle.g_n += 1;
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        else if(algoType == 1){
            newPuzzle.g_n +=1;
            newPuzzle.h_n = CountingMisplacedTiles(newPuzzle.puzzle);
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        else if(algoType == 2){
            newPuzzle.g_n +=1;
            newPuzzle.h_n = ManhattanDistance(newPuzzle.puzzle);
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        pq.push(newPuzzle);
    }



}

void printPuzzle(vector<int> puzzle){
    cout << "[" << puzzle.at(0) << ", " << puzzle.at(1) << ", " << puzzle.at(2) << "]\n";
    cout << "[" << puzzle.at(3) << ", " << puzzle.at(4) << ", " << puzzle.at(5) << "]\n";
    cout << "[" << puzzle.at(6) << ", " << puzzle.at(7) << ", " << puzzle.at(8) << "]\n";

}




int main(){
    //1D array that holds the puzzle values
    //Chose a 1D array because it makes it easier for me to piece everything together
    puzzleNode newPuzzle;
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
    //used below link to create min heap with priority queue so I could use it for selecting the lowest cost node
    //https://medium.com/@taohidulii/min-priority-queue-in-c-7e64bd01359c#:~:text=Save-,Min%20priority_queue%20in%20C%2B%2B,(returns%20the%20largest%20element).&text=Here%2C%20we're%20getting%20the,by%20applying%20some%20interesting%20tricks.
    priority_queue<puzzleNode> pq; //chooses best node to expand
    queue<puzzleNode> orderExpanded; //keeps track of which node is expanded
    pq.push(newPuzzle); 
    bool didFinish = false;
    int maxSize=0;
    while(!pq.empty()){
        int tempSize = pq.size();
        maxSize = max(maxSize, tempSize);
        puzzleNode temp = pq.top();
        pq.pop();
        if(CheckIfFinished(temp.puzzle)){
            //Function call to print order of the nodes selected by the algorithm 
            orderExpanded.push(temp);
            cout << "Solution depth was" << temp.g_n << endl; //we can use g_n for solution depth bc cost of g_n is 1 
            cout << "Number of nodes expanded: " << orderExpanded.size() << endl;
            cout << "Max queue size: " << maxSize << endl;
            didFinish = true;
            break;
        }
        expandNode(temp,pq, algoInput);
        if(pq.size() != 0){
            orderExpanded.push(temp);
        }
        
    }
    if(didFinish == false){
        cout << "No solution found\n";
        cout << "";
    }

    return 0;

}