#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

//making struct to keep track of state which includes puzzle and costs of g(n) and h(n)
struct puzzleNode{
    vector<int> puzzle;
    int g_n=0;
    int h_n=0;
    int f_n=0;

    //overloaded operator to make priority queue a min heap 
    //again used https://medium.com/@taohidulii/min-priority-queue-in-c-7e64bd01359c#:~:text=Save-,Min%20priority_queue%20in%20C%2B%2B,(returns%20the%20largest%20element).&text=Here%2C%20we're%20getting%20the,by%20applying%20some%20interesting%20tricks.
    // as a resource to do so
    bool operator< (const puzzleNode & a) const 
    {
        if(f_n == a.f_n) //if it's a tie, just pick the lowest g(n)
        {
            return g_n > a.g_n;
        }else { //else pick the lowest cost node
            return f_n > a.f_n;
        }
    }

    puzzleNode(){
        int g_n=0;
        int h_n=0;
        int f_n=0;
    }

};

//checks to see if the given puzzle has reached the end state
bool CheckIfFinished(vector<int> puzzle){
    vector<int> finalState {1,2,3,4,5,6,7,8,0};
    bool isFinished =true;
    for(int i=0; i<9; i++){
        if( puzzle.at(i) != finalState.at(i) )
        {
            isFinished = false; 
        }
    }
    return isFinished; 
}

//calculating manhattan distance by hard code
int ManhattanDistance(vector<int> puzzle ){
    int cost =0;
    if(puzzle.at(0) != 1){
        if(puzzle.at(0) == 2){
            cost += 1; 
        }
        else if(puzzle.at(0) == 3)
        {
            cost +=2;
        }
        else if(puzzle.at(0) == 4){
            cost +=1;
        }
        else if(puzzle.at(0) == 5){
            cost += 2;
        }
        else if(puzzle.at(0) == 6){
            cost += 3;
        }
        else if(puzzle.at(0) == 7){
            cost += 2;
        }
        else if(puzzle.at(0) == 8){
            cost += 3;
        }
    }
    if( puzzle.at(1) != 2){
         if(puzzle.at(1) == 1){
            cost += 1; 
        }
        else if(puzzle.at(1) == 3)
        {
            cost +=1;
        }
        else if(puzzle.at(1) == 4){
            cost +=2;
        }
        else if(puzzle.at(1) == 5){
            cost += 1;
        }
        else if(puzzle.at(1) == 6){
            cost += 2;
        }
        else if(puzzle.at(1) == 7){
            cost += 3;
        }
        else if(puzzle.at(1) == 8){
            cost += 2;
        }
    }
    if( puzzle.at(2) != 3){
         if(puzzle.at(2) == 1){
            cost += 2; 
        }
        else if(puzzle.at(2) == 2)
        {
            cost += 1;
        }
        else if(puzzle.at(2) == 4){
            cost += 3;
        }
        else if(puzzle.at(2) == 5){
            cost += 2;
        }
        else if(puzzle.at(2) == 6){
            cost += 1;
        }
        else if(puzzle.at(2) == 7){
            cost += 4;
        }
        else if(puzzle.at(2) == 8){
            cost += 3;
        }
    }
    if( puzzle.at(3) != 4){
         if(puzzle.at(3) == 1){
            cost += 1; 
        }
        else if(puzzle.at(3) == 2)
        {
            cost += 2;
        }
        else if(puzzle.at(3) == 3){
            cost += 3;
        }
        else if(puzzle.at(3) == 5){
            cost += 1;
        }
        else if(puzzle.at(3) == 6){
            cost += 2;
        }
        else if(puzzle.at(3) == 7){
            cost += 1;
        }
        else if(puzzle.at(3) == 8){
            cost += 2;
        }
    }
    if( puzzle.at(4) != 5){
         if(puzzle.at(4) == 1){
            cost += 2; 
        }
        else if(puzzle.at(4) == 2)
        {
            cost +=1;
        }
        else if(puzzle.at(4) == 3){
            cost +=2;
        }
        else if(puzzle.at(4) == 4){
            cost += 1;
        }
        else if(puzzle.at(4) == 6){
            cost += 1;
        }
        else if(puzzle.at(4) == 7){
            cost += 2;
        }
        else if(puzzle.at(4) == 8){
            cost += 1;
        }
    }
    if( puzzle.at(5) != 6){
         if(puzzle.at(5) == 1){
            cost += 3; 
        }
        else if(puzzle.at(5) == 2)
        {
            cost +=2;
        }
        else if(puzzle.at(5) == 3){
            cost +=1;
        }
        else if(puzzle.at(5) == 4){
            cost += 2;
        }
        else if(puzzle.at(5) == 5){
            cost += 1;
        }
        else if(puzzle.at(5) == 7){
            cost += 3;
        }
        else if(puzzle.at(5) == 8){
            cost += 2;
        }
    }
    if( puzzle.at(6) != 7){
         if(puzzle.at(6) == 1){
            cost += 2; 
        }
        else if(puzzle.at(6) == 2)
        {
            cost += 3;
        }
        else if(puzzle.at(6) == 3){
            cost += 4;
        }
        else if(puzzle.at(6) == 4){
            cost += 1;
        }
        else if(puzzle.at(6) == 5){
            cost += 2;
        }
        else if(puzzle.at(6) == 6){
            cost += 3;
        }
        else if(puzzle.at(6) == 8){
            cost += 1;
        }
    }
    if( puzzle.at(7) != 8){
         if(puzzle.at(7) == 1){
            cost += 3; 
        }
        else if(puzzle.at(7) == 2)
        {
            cost += 2;
        }
        else if(puzzle.at(7) == 3){
            cost += 3;
        }
        else if(puzzle.at(7) == 4){
            cost += 2;
        }
        else if(puzzle.at(7) == 5){
            cost += 1;
        }
        else if(puzzle.at(7) == 6){
            cost += 2;
        }
        else if(puzzle.at(7) == 7){
            cost += 1;
        }
    }
    if( puzzle.at(8) != 0){
         if(puzzle.at(8) == 1){
            cost += 4; 
        }
        else if(puzzle.at(8) == 2)
        {
            cost += 3;
        }
        else if(puzzle.at(8) == 3){
            cost +=2;
        }
        else if(puzzle.at(8) == 4){
            cost += 3;
        }
        else if(puzzle.at(8) == 5){
            cost += 2;
        }
        else if(puzzle.at(8) == 6){
            cost += 1;
        }
        else if(puzzle.at(8) == 7){
            cost += 2;
        }
        else if(puzzle.at(8) == 8){
            cost += 1;
        }
    }
    return cost;
}

//calcuating misplaced tiles heuristic
int CountingMisplacedTiles(vector<int> puzzle){
    int cost =0;
    for(int i=0; i<9; i++){ //checks how many tiles are out of place
        if(puzzle.at(i) != i+1){
            if( puzzle.at(i) != 0) //if that misplaced tile is 0 don't increase cost because we don't count a misplaced zero for this heuristic
            {
                ++cost;
            }
        }
    }
    // cout<< "cost: " << cost << endl;
    return cost;
}

//checks to see moving in a certain direction is in bounds
bool isInBounds(int zeroIndex, string direction){
    //if you want to move up, it's only illegal to move upwards if your index is between 0-2
    if(direction == "up"){
        if(zeroIndex == 0 || zeroIndex == 1 || zeroIndex == 2)
        {
            return false;
        }
        else {
            return true;
        }
    }
    //if you want to move down, it's only illegal to move upwards if your index is between 6-8
    else if(direction =="down"){
        if(zeroIndex == 6 || zeroIndex == 7 || zeroIndex == 8){
            return false;
        }
        else{
            return true;
        }
    }
    //if you want to mvoe right, it's only illegal to move right if your index -2 mod 3 is 0.
    else if(direction =="right"){
        if( (zeroIndex -2) %3 == 0){
            return false;
        }
        else{
            return true;
        }
    }
    //if you want to mvoe right, it's only illegal to move right if your index mod 3 is 0
    //noticed that the whole left row was a multiple of 3
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

void printPuzzle(vector<int> puzzle){
    cout << "[" << puzzle.at(0) << ", " << puzzle.at(1) << ", " << puzzle.at(2) << "]\n";
    cout << "[" << puzzle.at(3) << ", " << puzzle.at(4) << ", " << puzzle.at(5) << "]\n";
    cout << "[" << puzzle.at(6) << ", " << puzzle.at(7) << ", " << puzzle.at(8) << "]\n";

}


void expandNode(puzzleNode chosenNode, priority_queue<puzzleNode> &pq, int algoType, map<vector<int>,int> &visited){
    visited[chosenNode.puzzle] = 1; // mark node as visited 

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
        puzzleNode newPuzzle;
        newPuzzle.puzzle = chosenNode.puzzle;
        newPuzzle.g_n = chosenNode.g_n;
        newPuzzle.h_n = chosenNode.h_n;
        newPuzzle.f_n = chosenNode.f_n;
        swap(newPuzzle.puzzle.at(zeroIndex), newPuzzle.puzzle.at(zeroIndex-3));
        if(algoType ==1){
            newPuzzle.g_n += 1;
            newPuzzle.h_n=0;
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        else if(algoType == 2){
            newPuzzle.g_n +=1;
            newPuzzle.h_n = CountingMisplacedTiles(newPuzzle.puzzle);
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        else if(algoType == 3){
            newPuzzle.g_n +=1;
            newPuzzle.h_n = ManhattanDistance(newPuzzle.puzzle);
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        if (! (visited.find(newPuzzle.puzzle) != visited.end() )) {
            pq.push(newPuzzle);
        }
        
    }

    //making new puzzle that moves the blank space down
    if(isInBounds(zeroIndex, "down")){
        puzzleNode newPuzzle;
        newPuzzle.puzzle = chosenNode.puzzle;
        newPuzzle.g_n = chosenNode.g_n;
        newPuzzle.h_n = chosenNode.h_n;
        newPuzzle.f_n = chosenNode.f_n;
        swap(newPuzzle.puzzle.at(zeroIndex), newPuzzle.puzzle.at(zeroIndex+3));

        if(algoType == 1){
            newPuzzle.g_n += 1;
            newPuzzle.h_n=0;
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        else if(algoType == 2){
            newPuzzle.g_n +=1;
            newPuzzle.h_n = CountingMisplacedTiles(newPuzzle.puzzle);
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        else if(algoType == 3){
            newPuzzle.g_n +=1;
            newPuzzle.h_n = ManhattanDistance(newPuzzle.puzzle);
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        if (! (visited.find(newPuzzle.puzzle) != visited.end() )) {
            pq.push(newPuzzle);
        }
    }

    //making new puzzle that moves the blank space right
    if(isInBounds(zeroIndex, "right")){
        puzzleNode newPuzzle;
        newPuzzle.puzzle = chosenNode.puzzle;
        newPuzzle.g_n = chosenNode.g_n;
        newPuzzle.h_n = chosenNode.h_n;
        newPuzzle.f_n = chosenNode.f_n;
        swap(newPuzzle.puzzle.at(zeroIndex), newPuzzle.puzzle.at(zeroIndex+1));
        if(algoType == 1){
            newPuzzle.g_n += 1;
            newPuzzle.h_n=0;
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        else if(algoType == 2){
            newPuzzle.g_n +=1;
            newPuzzle.h_n = CountingMisplacedTiles(newPuzzle.puzzle);
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        else if(algoType == 3){
            newPuzzle.g_n +=1;
            newPuzzle.h_n = ManhattanDistance(newPuzzle.puzzle);
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        if (! (visited.find(newPuzzle.puzzle) != visited.end() )) {
            pq.push(newPuzzle);
        }
    }

    //making new puzzle that moves the blank space left
    if(isInBounds(zeroIndex, "left")){
        puzzleNode newPuzzle;
        newPuzzle.puzzle = chosenNode.puzzle;
        newPuzzle.g_n = chosenNode.g_n;
        newPuzzle.h_n = chosenNode.h_n;
        newPuzzle.f_n = chosenNode.f_n;
        swap(newPuzzle.puzzle.at(zeroIndex), newPuzzle.puzzle.at(zeroIndex-1));
        if(algoType ==1){
            newPuzzle.g_n += 1;
            newPuzzle.h_n=0;
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        else if(algoType ==2){
            newPuzzle.g_n +=1;
            newPuzzle.h_n = CountingMisplacedTiles(newPuzzle.puzzle);
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        else if(algoType == 3){
            newPuzzle.g_n +=1;
            newPuzzle.h_n = ManhattanDistance(newPuzzle.puzzle);
            newPuzzle.f_n = newPuzzle.g_n + newPuzzle.h_n;
        }
        if (! (visited.find(newPuzzle.puzzle) != visited.end() )) {
            pq.push(newPuzzle);
        }
    }

}

void printTraceBack(queue<puzzleNode> orderExpanded){
    cout << "Starting puzzle: \n";
    printPuzzle(orderExpanded.front().puzzle);
    orderExpanded.pop();
    while(!orderExpanded.empty())
    {
        cout << "The best state to expand with g(n) = " << orderExpanded.front().g_n << " and h(n) = " << orderExpanded.front().h_n << " is...\n";
        printPuzzle(orderExpanded.front().puzzle);
        orderExpanded.pop();
    }
    
}




int main(){
    //1D array that holds the puzzle values
    //Chose a 1D array because it makes it easier for me to piece everything together
    puzzleNode newPuzzle;
    newPuzzle.puzzle = vector<int> (9);
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
    cout << "(1) Uniform Search Cost\n(2) Misplaced Tile Heuristic\n(3) Manhattan Distance Heuristic\n";
    int algoInput;
    cin >> algoInput;
    auto start = high_resolution_clock::now(); // used https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
    //general search algo goes below
    //used below link to create min heap with priority queue so I could use it for selecting the lowest cost node
    //https://medium.com/@taohidulii/min-priority-queue-in-c-7e64bd01359c#:~:text=Save-,Min%20priority_queue%20in%20C%2B%2B,(returns%20the%20largest%20element).&text=Here%2C%20we're%20getting%20the,by%20applying%20some%20interesting%20tricks.
    priority_queue<puzzleNode> pq; //chooses best node to expand
    queue<puzzleNode> orderExpanded; //keeps track of which node is expanded
    map<vector<int>,int> visited; //used for repeating states https://www.geeksforgeeks.org/map-of-vectors-in-c-stl-with-examples/ 
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
            auto stop = high_resolution_clock::now();
            orderExpanded.push(temp);
            printTraceBack(orderExpanded);
            cout << "Goal state!\n";
            cout << "Solution depth was " << temp.g_n << endl; //we can use g_n for solution depth bc cost of g_n is 1 
            cout << "Number of nodes expanded: " << orderExpanded.size()-1 << endl; //-1 because orderExpanded also has the initial state included 
            cout << "Max queue size: " << maxSize << endl;
            auto duration = duration_cast<microseconds>(stop-start);
            cout << "The algorithm ran for " << duration.count() << " microseconds\n";
            didFinish = true;
            break;
        }
        expandNode(temp,pq, algoInput,visited);
        orderExpanded.push(temp);
        
    }
    if(didFinish == false){
        cout << "No solution found\n";
    }

    return 0;

}