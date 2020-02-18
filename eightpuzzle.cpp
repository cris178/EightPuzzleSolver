#include <iostream>
#include <string>
#include <queue>
#include <cstring> //for memcpy
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include <bits/stdc++.h> //
using namespace std;

/****************************************************************/

/*
cost function
c(x) = g(x) + f(x)
g(x) = cost of reaching current node from root #length of path from root to x
f(x) = cost of reaching goal from current node # of non blank tiles not in their goal position
*/

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

int checkCost(int init[3][3])
{
    int count = 0;
    int goalState[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 0, 8}};

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            //relational operators have higher precedense
            //Will take into account if 0 is not in correct place as well
            if (init[i][j] != goalState[i][j]) //Check this later, WORKS
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
    //Node();                                      //Default constructor
    //Node(int[3][3], int r, int c, int pathcost); //Constructor
    //int checkCost(int arr[3][3], int goal[3][3]);
    Node &operator=(const Node &rhs)
    {
    }
    int row;    //Row where 0 is
    int column; //Column where 0 is
    int matrix[3][3];
    int depth;
    int cost;
    Node *parent; //pointer to parent
    bool isGoal();

private:
};

bool Node::isGoal()
{
    int goalState[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 0, 8}};
    bool goalTest = false;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (matrix[i][j] == goalState[i][j])
            {
                goalTest = true;
            }
            else
            {
                return false;
            }
        }
    }
    cout << "Reached the goal \n";
    return goalTest;
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
/* Pointer Node will handle construction of Node
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
    cost = checkCost(matrix);
}
*/
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
    //get current position of 0 and swap it to new viable location
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
/*
Checking Valid Operation moves. 
When we are checking for valid moves a better way to check if valid is not
to check if the numbers can move, but if the blank can move, according to slides.

Range of valid operations are index positions 0 - 3
Anything past that, or below that is an invalid state change.
We will test if a valid state change is made by taking the current state and moving 
it in all four possible locations, left, right, top, and bot.
Moving top = current row -1, current column + 0
Moving bot = current row +1, current column + 0
Moving left = current row + 0, current column -1
Moving right = current row + 0, current column +1
*/
/**********************************************************************************/

// botton, left, top, right
int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};

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

/*******************************************************************/
//This function compares two nodes could be childXexplored or childXfrontier
bool compareStates(const int puzzle[3][3], const int explored[3][3])
{
    //https://www.geeksforgeeks.org/stdmemcmp-in-cpp/
    bool returnStatus = false;

    //https://stackoverflow.com/questions/25787366/c-compare-two-multidimensional-arrays
    if (memcmp(puzzle, explored, sizeof(puzzle)) == 0)
    {
        //Equal
        return true;
    }
    else
    {
        return false;
    }
}

/**********
 * 
 * 
 * MIGHT NEED A COMPARE FRONTIER FUNCTION
 * COMPARE FRONTIER MAY NEED TO CHECK ALL VALUES OF FRONTIER
 * 
 * ***************/

//Need to organize the priority queu using this structure
//http://www.cplusplus.com/reference/queue/priority_queue/priority_queue/
//Making your own comporator
//http://neutrofoton.github.io/blog/2016/12/29/c-plus-plus-priority-queue-with-comparator/
struct comp
{
    //Overide
    bool operator()(const Node *lhs, const Node *rhs) const
    {
        //return (lhs->cost + lhs->depth) > (rhs->cost + rhs->depth);
        //in the frontier we expand the cheapest node(based on path cost), meaning cheapest node should be at the front.
        //https://www.geeksforgeeks.org/stl-priority-queue-for-structure-or-class/
        return (lhs->cost) > (rhs->cost);
    }
};

//Helpful guide
////http://www.cs.umsl.edu/~sanjiv/classes/cs5130/lectures/bb.pdf
void Problem(int init[3][3], int r, int c)
{
    //Create Root node, row and col set to 0 position, no operations applied, depth of 0, and parent pointer to null
    //Node <- a node with State = Problem.Initial-State, Path-Cost =0
    Node *root = newNode(init, r, c, r, c, 0, NULL);
    root->cost = checkCost(init);

    //frontier <- a priority_queue ordered by Path-Cost, with Node as the only element.
    //We will have a priority queue of node pointers which will form the path from root to goal
    priority_queue<Node *, vector<Node *>, comp> frontier; //Our frontier is a queue http://www.cplusplus.com/reference/queue/queue/ https://prismoskills.appspot.com/lessons/Algorithms/Chapter_03_-_Queue_Dequeue_and_Priority_Queue.jsp
    //g(n) == to path cost see pdf

    //explored <- an empty set
    list<Node> explored;

    frontier.push(root);

    //Stop only until the tree is fully searched return solution(path to goal) or no solution when you pop the final node and it's not the goal state
    //Uniform Cost continues even after goal found, checks lower cost path too
    while (!frontier.empty()) //if Empty?(frontier) then return failure
    {
        //Uniform Cost expands node with smalles cost first.
        Node *minCost = frontier.top();

        //Remove the node from the frontier
        frontier.pop();

        //if problem Goal test(node.State) then return solution
        if (minCost->isGoal())
        {
            printPath(minCost); //FIX
        }

        //Add node->State to explored
        cout << "----------\n";
        cout << "Adding repeated state to explored list and showing list: " << endl;
        explored.push_back(minCost);
        cout << "Pushed this new state to explored" << endl;
        displayState(explored.back().matrix);
        cout << "----------\n";

        //No matter the size of the board it can at most generate 4 new states so we have a max of four children for a node
        for (int i = 0; i < 4; i++)
        {
            //Go through each operator for 0 moveUp, moveDown, moveLeft, moveRight and check if save.
            if (checkOP(minCost->row + row[i], minCost->column + col[i]))
            {
                //Valid state found create a new node with this new state
                Node *child = newNode(minCost->matrix, minCost->row, minCost->column, minCost->row + row[i], minCost->column + col[i], minCost->depth + 1, minCost);
                child->cost = checkCost(child->matrix);

                bool notInExplored = false;
                bool notInFrontier = false;

                //If child.state not in explored or frontier then
                for (auto v : explored)
                {
                    if (compareStates(child->matrix, v.matrix) != 0) //See if current child is in explored list. If returns 0 they are equal and in explored
                    {
                        notInExplored = true;
                        if (compareStates(child->matrix, frontier.top()->matrix) != 0) //if returns 0 it's in frontier
                        {
                            //frontier <- insert(child,frontier)
                            notInFrontier = true;
                            frontier.push(child);
                        }
                    }
                }
                if (notInFrontier == false)
                { //else if child.STATE is in frontier with higher PATH-COST then
                    if (child->cost < frontier.top()->cost)
                    {
                        frontier.pop();
                        frontier.push(child);
                    }
                }
            }
        }
    }
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

    int puzzle[3][3]; //Ourpuzzle 2D array

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
        int cost = checkCost(puzzle);

        //This is the initial root node constructed
        //puzzle is initial state, x,y is 0 position, second pair is where to move new nodes
        Node *root = newNode(puzzle, x, y, x, y, 0, NULL);
        cout << checkCost(puzzle) << " This is the cost\n";
    }

    displayState(puzzle); //Need to send the arrays address https://stackoverflow.com/questions/8767166/passing-a-2d-array-to-a-c-function

    //Should return solution which is path to goal state.
    Problem(puzzle, 3, 3);

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