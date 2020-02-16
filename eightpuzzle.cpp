#include <iostream>
#include <string>
using namespace std;

/****************************************************************/

class Node
{
public:
    Node();                      //Default constructor
    Node(int val, int r, int c); //Constructor
    const int getNumber() const; //Display number is just the visual title
    const int getRow() const;
    const int getColumn() const;
    void setRow(int x);
    void setColumn(int x);
    Node &operator=(const Node &rhs)
    {
        if (this != &rhs)
        {
            this->number = rhs.getNumber();
            this->row = rhs.getRow();
            this->column = rhs.getColumn();
        }
        return *this;
    }

private:
    int number; // title of the node
    int row;
    int column;
    Node *parent; //pointer to parent
};

Node::Node()
{
    number = 0;
}

Node::Node(int val, int r, int c)
{
    //cout << "Node value is : " << val << "\n";
    number = val;
    row = r;
    column = c;
}

const int Node::getNumber() const
{
    return number;
}

const int Node::getRow() const
{
    return row;
}

const int Node::getColumn() const
{
    return column;
}

void Node::setRow(int x)
{
    row = x;
}
void Node::setColumn(int x)
{
    column = x;
}

/******************************************************************/

/*******************************************************************/

class Problem
{
public:
    Problem();
    Node *initialState;
    Node *goalState;
    void setInitialState(Node temp);                  //Insert node to be initialstate;
    void setGoalState(Node temp);                     //Insert node to be initialstate;
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

void Problem::setInitialState(Node temp)
{
    initialState = &temp;
}

void Problem::setGoalState(Node temp)
{
    goalState = &temp;
}

void Problem::checkOP(Node temp)
{
    //if

    //elseif

    //elseif

    //elseif
}

void Problem::moveUp(Node arr[3][3], int row, int col)
{

    if (row <= 0) //Can't move if at index 0 would be out
    {
        cout << "Can't move that tile Up.\n";
        return;
    }
    else if (arr[row - 1][col].getNumber() == 0)
    {
        Node shifting = arr[row - 1][col]; //Save 0 to temp
        arr[row - 1][col] = arr[row][col]; //assign appropriate to 0 spot
        arr[row][col] = shifting;          //temp in old spot
        cout << "Moved " << arr[row - 1][col].getNumber() << " up.\n";
    }
    else
    {
        cout << "No blank space available to move towards.\n";
    }
}

void Problem::moveDown(Node arr[3][3], int row, int col)
{

    if (row >= 2)
    {
        cout << "Can't move that tile down.\n";
        return;
    }
    else if (arr[row + 1][col].getNumber() == 0)
    {
        Node shifting = arr[row + 1][col];
        arr[row + 1][col] = arr[row][col];
        arr[row][col] = shifting;
        cout << "Moved " << arr[row + 1][col].getNumber() << " down.\n";
    }
    else
    {
        cout << "No blank space available to move towards.\n";
    }
}

void Problem::moveLeft(Node arr[3][3], int row, int col)
{

    if (col <= 0)
    {
        cout << "Can't move that tile Left.\n";
        return;
    }
    else if (arr[row][col - 1].getNumber() == 0)
    {
        Node shifting = arr[row][col - 1];
        arr[row][col - 1] = arr[row][col];
        arr[row][col] = shifting;
        cout << "Moved " << arr[row][col - 1].getNumber() << " Left.\n";
    }
    else
    {
        cout << "No blank space available to move towards.\n";
    }
}

void Problem::moveRight(Node arr[3][3], int row, int col)
{

    if (col >= 2)
    {
        cout << "Can't move that tile Right.\n";
        return;
    }
    else if (arr[row][col + 1].getNumber() == 0)
    {
        Node shifting = arr[row][col + 1];
        arr[row][col + 1] = arr[row][col];
        arr[row][col] = shifting;
        cout << "Moved " << arr[row][col + 1].getNumber() << " Right.\n";
    }
    else
    {
        cout << "No blank space available to move towards.\n";
    }
}

void displayState(Node arr[3][3], int size) //Display State
{
    cout << "Printing Puzzle ---------------\n";

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << arr[i][j].getNumber() << " ";
        }
        cout << "\n";
    }
}

/**************************************************************************/

/************************************************************************/
//  Uniform Cost Search
//Initial State:
//Goal State:
//Operators:
// Apply Goal Test when: NOT when when generating a node because could find better nodes by expanding siblings in frontier

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

    Node puzzle[3][3]; //Ourpuzzle 2D array

    if (option == 1)
    {
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
                    /*cout << "--Entered in Array "
                         << "[" << i << "]"
                         << ","
                         << "[" << j << "]"
                         << " the value " << puzzle[i][j].displayNumber() << "\n";*/
                    eight++;
                }
            }
        }
    }
    else
    {
        while (count < 0 || count > 8)
        {
            cout << "Welcome to Cristian's creye025 8 puzzle solver\n";
            cout << "Type 1 for the default puzzle or 2 to enter your own puzzle\n";
            cout << "Eight Puzzle Solver\n";
        }
    }

    displayState(puzzle, 3); //Need to send the arrays address https://stackoverflow.com/questions/8767166/passing-a-2d-array-to-a-c-function

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