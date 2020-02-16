#include <iostream>
#include <string>
#include <queue>
#include <cstring>       //for memcpy
#include <bits/stdc++.h> //
using namespace std;

/****************************************************************/

/*
cost function
c(x) = g(x) + f(x)
g(x) = cost of reaching current node from root #length of path from root to x
f(x) = cost of reaching goal from current node # of non blank tiles not in their goal position
*/

int checkCost(int init[3][3], int goal[3][3])
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            //relational operators have higher precedense
            if (init[i][j] && (init[i][j] != goal[i][j])) //Check this later, WORKS
            {
                count++;
            }
        }
    }
    return count;
}

class Node
{
public:
    Node();                                      //Default constructor
    Node(int[3][3], int r, int c, int pathcost); //Constructor
    int checkCost(int arr[3][3], int goal[3][3]);
    Node &operator=(const Node &rhs)
    {
    }
    int row;    //Row where 0 is
    int column; //Column where 0 is
    int matrix[3][3];
    int depth;
    int cost;
    Node *parent; //pointer to parent

private:
};

Node::Node()
{
}

Node::Node(int arr[3][3], int r, int c, int pathcost)
{
    //Getting the State and setting it as our Node structure.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix[i][j] = arr[i][j];
        }
    }
    row = r;
    column = c;
    cost = pathcost;
}

/******************************************************************/

/********************************************************************/
//This is how we will create new nodes.
//Each time a new node is created this is like a constructor
Node *newNode(int arr[3][3], int x, int y, int newX, int newY, int level, Node *parent)
{
    Node *node = new Node;

    // set pointer for path to root
    node->parent = parent;

    // copy data from parent node to current node
    //http://www.cplusplus.com/reference/cstring/memcpy/
    memcpy(node->matrix, arr, sizeof node->matrix);

    //If we pass in a higher value in newx and newy this will shift
    //the 0 producing a new state
    // move tile by 1 position
    swap(node->matrix[x][y], node->matrix[newX][newY]);

    // set number of misplaced tiles
    //Max cost (infiniti) until proper value is given
    //https://stackoverflow.com/questions/3233054/error-int32-max-was-not-declared-in-this-scope
    node->cost = INT_MAX;

    // The depth of our soulution so far.
    node->depth = level;

    // If we pass in a newx or y coordinate we will update those values
    node->row = newX;
    node->column = newY;

    return node;
}

/***********************************************************************************/

/*******************************************************************/

class Problem
{
public:
    Problem();
    void checkOP(Node temp);                          //This function checks which operation is available on provided node
    void moveLeft(Node arr[3][3], int row, int col);  //Operator move node to the left
    void moveRight(Node arr[3][3], int row, int col); //Operator move node to the right
    void moveDown(Node arr[3][3], int row, int col);  //Operator move node bottom
    void moveUp(Node arr[3][3], int row, int col);    //Operator move node up
};

Problem::Problem()
{
    cout << "A problem has been constructed.\n";
}

//Each node can have max four children left,right,top,or bot as possible operators
int checkOP(int x, int y)
{
    //This function see's what child states are viable
    //from the current state. If possible returns true else false;
    if (x >= 0 && x < 3 && y >= 0 && y < 3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void displayState(int arr[3][3]) //Display State
{
    cout << "Printing Puzzle ---------------\n";

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
}

// print path from root node to destination node
//https://www.dummies.com/programming/cpp/how-to-pass-pointers-to-functions-in-c/
void printPath(Node *root)
{
    //Recursively call self until your reach the root node.
    if (root == NULL)
    {
        return;
    }
    printPath(root->parent);
    displayState(root->matrix);

    printf("\n");
}

/**************************************************************************/

/************************************************************************/
//  Uniform Cost Search
//Initial State:
//Goal State:
//Operators:
//First check for trick problem where inital state is goal state.
//If it's not, need to expand the current state, which means apply each legal action to the current state.
//Which will generate new states

//root node
// 1 3
// 2 0
//Can generate

//branch 1
//1 0
//2 3

//branch 2
//1 3
//0 2

//Here we added two branches to the parent node
//We then consider which to continue branching out from
//We now check to see if it is a goal state, if not expand it

//branch 1b
//0 1
//2 3

//branch 1c
//1 3
//2 0

//We can expand these branch 2 sub nodes or expand branch 2
//branches 1b, 1c, and 2 are in the frontier, we decide which to expand in the frontier
//This process continues until a solution is found or no more states to expand.

// Apply Goal Test when: NOT when when generating a node because could find better nodes by expanding siblings in frontier

//The first is that the goal test is applied to a node when
//it is selected for expansion (as in the generic graph-search algorithm shown in Figure 3.7)
//rather than when it is first generated.

//The second difference is that a test is added in case a better
//path is found to a node currently on the frontier.

/********************************************************************************/

int main()
{
    int option = 0;
    int count = 0;
    while (option != 1 && option != 2)
    {
        cout << "Welcome to Cristian's creye025 8 puzzle solver\n";
        cout << "Type 1 for the default puzzle or 2 to enter your own puzzle\n";
        cin >> option;
    }

    int puzzle[3][3];                              //Ourpuzzle 2D array
    int explored[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //If node contains goal state, add node.number to explaored array
                                                   //if frontier node matches explored node, discard it.

    priority_queue<Node> frontier; //Our frontier is a queue http://www.cplusplus.com/reference/queue/queue/
    int goalState[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 0, 8}};

    if (option == 1)
    { /*
        cout << "Default option selected.\n";
        int eight = 1;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (i == 2 && j == 2)
                {
                    Node temp(0, i, j);
                    puzzle[i][j] = temp; //Goal State
                    cout << "Eight Puzzle assembled.\n";
                }
                else
                {
                    Node temp(eight, i, j);
                    puzzle[i][j] = temp;
                    eight++;
                }
            }
        }*/
    }
    else
    {

        int val = 0;
        int x, y = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << "Enter the number 0-8 you want in position [" << i << "," << j << "], with 0 being the blank space" << endl;
                cin >> val;
                puzzle[i][j] = val;
                if (val == 0)
                {
                    x = i;
                    y = j;
                }
                val = 0;
            }
        }
        int cost = checkCost(puzzle, goalState);

        //This is the initial root node constructed
        //puzzle is initial state, x,y is 0 position, second pair is where to move new nodes
        Node *root = newNode(puzzle, x, y, x, y, 0, NULL);
        cout << checkCost(puzzle, goalState) << " This is the cost\n";
    }

    displayState(puzzle); //Need to send the arrays address https://stackoverflow.com/questions/8767166/passing-a-2d-array-to-a-c-function
    /*
    Problem a1;
    a1.moveDown(puzzle, 1, 2);
    displayState(puzzle, 3);
    a1.moveDown(puzzle, 0, 2);
    displayState(puzzle, 3);
    a1.moveUp(puzzle, 1, 2);
    displayState(puzzle, 3);
    a1.moveRight(puzzle, 0, 1);
    displayState(puzzle, 3);
    a1.moveRight(puzzle, 0, 0);
    displayState(puzzle, 3);
    a1.moveDown(puzzle, 0, 2);
    a1.moveRight(puzzle, 0, 1);
    a1.moveRight(puzzle, 0, 0);
    displayState(puzzle, 3);
    a1.moveUp(puzzle, 1, 0);
    displayState(puzzle, 3);
    */
    /*

    //Reset for next options
    option = 0;
    while (option != 1 && option != 2 && option != 3)
    {
        cout << "\n\nChoose 1, 2, 3, for Solving Algorithim.\n";
        cout << "1) Uniform Cost Search.\n";
        cout << "2) A* Search with the misplaced Tile heuristic.\n";
        cout << "3) A* with the Manhatten Distance heuristic.\n";
        cin >> option;
    }

    switch (option)
    {
    case 1:
        cout << "Selected option a Uniform Cost Search.\n";
        break;
    case 2:
        cout << "A* Search with the misplaced Tile heuristic.\n";
        break;
    case 3:
        cout << "A* with the Manhatten Distance heuristic\n";
        break;
    default:
        break;
    }
    */
    return 0;
}