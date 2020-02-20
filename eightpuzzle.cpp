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

    bool returnStatus = false;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (matrix[i][j] == goalState[i][j])
            {
                returnStatus = true;
            }
            else
            {
                cout << "isGoal... \t\tfalse\n";
                return false;
            }
        }
    }
    cout << "isGoal... \t\tTrue\n";
    return returnStatus;
    /*
    //https://stackoverflow.com/questions/25787366/c-compare-two-multidimensional-arrays
    if (memcmp(matrix, goalState, sizeof(matrix)) == 0)
    {
        //Equal
        cout << "isGoal: True \n";
        return true;
    }
    else
    {
        cout << "isGoa... False \n";
        return false;
    }*/
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
    cout << "Checking possible operations..." << endl;
    //This function see's what child states are viable
    //from the current state. If possible returns true else false;
    if (x >= 0 && x < 3 && y >= 0 && y < 3)
    {
        return 1;
    }
    else
    {
        cout << "Row x Col: " << x << "," << y << " Not a valid operation" << endl;
        return 0;
    }
}

/*******************************************************************/
//This function compares two nodes could be childXexplored or childXfrontier
bool compareStates(const int puzzle[3][3], const int explored[3][3])
{
    //https://www.geeksforgeeks.org/stdmemcmp-in-cpp/
    bool returnStatus = false;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (puzzle[i][j] == explored[i][j])
            {
                returnStatus = true;
            }
            else
            {
                return false;
            }
        }
    }
    return returnStatus;
    /*
//https://stackoverflow.com/questions/25787366/c-compare-two-multidimensional-arrays
if (memcmp(puzzle, explored, 3 * sizeof(puzzle)) == 0)
{
    //Equal
    cout << "Both states are the same \n";
    return true;
}
else
{
    cout << "Both states not the same \n";
    return false;
}*/
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

        //in the frontier we expand the cheapest node(based on path cost), meaning cheapest node should be at the front.
        //https://www.geeksforgeeks.org/stl-priority-queue-for-structure-or-class/
        return (lhs->cost) > (rhs->cost);
    }
};

struct listComparator
{
    // Compare 2 Player objects using name
    bool operator()(const Node lhs, const Node rhs)
    {

        return lhs.cost < rhs.cost;
    }
};

//Helpful guide
////http://www.cs.umsl.edu/~sanjiv/classes/cs5130/lectures/bb.pdf
void Problem(int init[3][3], int r, int c)
{
    cout << "Starting Uniform Cost Search...\n";
    //Create Root node, row and col set to 0 position, no operations applied, depth of 0, and parent pointer to null
    //Node <- a node with State = Problem.Initial-State, Path-Cost =0
    Node *root = newNode(init, r, c, r, c, 0, NULL);
    root->cost = checkCost(init);
    int maxQueue = 0;
    int nodesExpanded = 0;

    //frontier <- a priority_queue ordered by Path-Cost, with Node as the only element.
    //We will have a priority queue of node pointers which will form the path from root to goal
    priority_queue<Node *, std::vector<Node *>, comp> frontier; //Our frontier is a queue http://www.cplusplus.com/reference/queue/queue/ https://prismoskills.appspot.com/lessons/Algorithms/Chapter_03_-_Queue_Dequeue_and_Priority_Queue.jsp
    //g(n) == to path cost see pdf

    //explored <- an empty set
    list<Node> explored;

    frontier.push(root);

    //Stop only until the tree is fully searched return solution(path to goal) or no solution when you pop the final node and it's not the goal state
    //Uniform Cost continues even after goal found, checks lower cost path too
    while (!frontier.empty()) //if Empty?(frontier) then return failure
    {
        if (frontier.size() > maxQueue)
        {
            maxQueue = frontier.size();
        }

        //Uniform Cost expands node with smalles cost first.
        Node *minCost = frontier.top();

        cout << "New Node in Frontier Being Explored\n";
        displayState(minCost->matrix);
        cout << "cost is: " << minCost->cost << endl;

        //Remove the node from the frontier
        frontier.pop();

        //if problem Goal test(node.State) then return solution
        if (minCost->isGoal())
        {
            cout << "\n -----Found Goal State-----\n";
            cout << "* Max priority queue size is: " << maxQueue << endl;
            cout << "* Total Nodes expanded is: " << nodesExpanded << endl;
            printPath(minCost); //FIX

            return;
        }

        //Add node->State to explored
        //cout << "----------\n";
        cout << "Pushing Current Node to Explored \t\t...Invalid future state " << endl;
        explored.push_back(*minCost);
        explored.sort(listComparator());
        cout << "Current Top in Explored is: \n";
        displayState(explored.front().matrix);
        cout << "With Cost...\t\t" << explored.front().cost << "\n";

        //cout << "Pushed this new state to explored" << endl;
        //displayState(explored.back().matrix);
        //cout << "----------\n";

        int expanded = 0;

        cout << "Checking possible operators...\n";
        //No matter the size of the board it can at most generate 4 new states so we have a max of four children for a node
        for (int i = 0; i < 4; i++) //Expand the node and add them to the frontier
        {
            cout << "Loop compares should go four times: " << i << endl;

            //Go through each operator for 0 moveUp, moveDown, moveLeft, moveRight and check if save.
            //cout << "Will Add row " << minCost->row << " with possible operation " << row[i] << endl;
            if (checkOP(minCost->row + row[i], minCost->column + col[i]))
            {
                if (i == 0)
                {
                    cout << "Move Down Possible... \t\tNew State Generated\n";
                }
                else if (i == 1)
                {
                    cout << "Move Left Possible... \t\tNew State Generated\n";
                }
                else if (i == 2)
                {
                    cout << "Move Up Possible... \t\tNew State Generated\n";
                }
                else if (i == 3)
                {
                    cout << "Move Right Possible... \t\tNew State Generated\n";
                }

                //Because we know this operation is valid we will create the node,
                //see if it's already in explored or frontier if already in explored or frontier forget this node and move on to next node,
                //or see if it's already in the frontier with a higher cost so we can replace with this node
                Node *child = newNode(minCost->matrix, minCost->row, minCost->column, minCost->row + row[i], minCost->column + col[i], minCost->depth + 1, minCost);
                child->cost = checkCost(child->matrix);
                cout << "Node created with cost : " << child->cost << endl;
                displayState(child->matrix);
                cout << "----------\n";
                cout << "This is the cost >>>" << checkCost(child->matrix) << endl;

                //Here we check If child.state not in explored or frontier then add to frontier so we can expand it later
                cout << "Check Explored and Frontier--------\n";
                bool inExplored = false;
                bool inFrontier = false;

                for (auto v : explored) //Check if child is in entire explored list
                {
                    //cout << "Explored list doesn't need to be organized from lest to greatest \n";

                    /*
                    cout << "Comparing current state with other in explored -----------\n\n";
                    displayState(child->matrix);
                    displayState(v.matrix);
                    cout << "Comparing current state with other in explored -----------\n\n";
                    */
                    if (compareStates(child->matrix, v.matrix) == true)
                    {

                        cout << "inExplored... True";
                        inExplored = true;
                        break;
                    }
                    else
                    {
                        if (v.cost > child->cost)
                        {
                            cout << "inExplored.... \t\tFalse. Cost to high to be same state\n";
                            break;
                        }
                    }
                }

                if (inExplored == false)
                {
                    cout << "Checking if in Frontier...\n";

                    if (compareStates(child->matrix, frontier.top()->matrix) == false) //if returns 0 it's in frontier
                    {
                        cout << "In Frontier?.... \t\tFalse\n";
                        cout << "Never before seen in Explored or Frontier....\n";
                        cout << "Adding Child to frontier.\n";
                        displayState(child->matrix);
                        cout << "Frontier: TOP Cost---------------\n\n";
                        displayState(frontier.top()->matrix);
                        cout << "Frontier: --------------TOP COST" << frontier.top()->cost << endl;
                        frontier.push(child);
                        expanded++;
                        if (expanded == 1)
                        {
                            nodesExpanded++;
                        }
                        //break; //Don't need to continue search
                    }
                }
                if (compareStates(child->matrix, frontier.top()->matrix) == true) //But the costs are the same if same state.
                {                                                                 //else if child.STATE is in frontier with higher PATH-COST then
                    cout << "child is in frontier, check if better if this child has better cost\n";
                    if (child->cost < frontier.top()->cost)
                    {
                        cout << "Better Cost.... True\n";
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
    int x, y = 0;
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
        x, y = 0;
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
                    cout << "Placed blank in position " << x << "," << y << endl;
                }
                val = 0;
            }
        }

        //This is the initial root node constructed
        //puzzle is initial state, x,y is 0 position, second pair is where to move new nodes
        //Node *root = newNode(puzzle, x, y, x, y, 0, NULL);
        //cout << "checking blank placement " << root->row << "," << root->column << endl;
    }
    /*
    cout << "EXAMPLE" << endl;
    int arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 0, 8}};
    int arrg[3][3] = {{1, 2, 3}, {4, 0, 6}, {7, 5, 8}};
    if (compareStates(arr, arrg))
    {
        cout << "SAME\n";
    }
    else
    {
        cout << "NOT SAME\n";
    }*/

    displayState(puzzle); //Need to send the arrays address https://stackoverflow.com/questions/8767166/passing-a-2d-array-to-a-c-function
    cout << "This is the cost: " << checkCost(puzzle) << endl;
    //Should return solution which is path to goal state.
    Problem(puzzle, x, y);

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