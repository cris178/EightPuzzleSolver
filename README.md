# EightPuzzleSolver
AI assignment Eight Puzzle Solver using Uniform Cost Search and A* Search


The program is now complete. This Eight Puzzle solver is written in C++. While I tried to stay in an Object Orientated domain, I quickly relapsed after just wanting to iterate fast. You'll notice I copy and pasted the main algorithims as their own functions instead of trying to neatly make them a unified class. 


## Running the Program

Since it's a simple C++ program you should be able to compile it with your prefferred compiler. I used G++ using Linux for Windows and Visual Studio code. 

![VSCode](https://imgur.com/HOnckBk)


* Console Command
g++ -std=c++14 eightpuzzle.cpp -o Eight

## Understanding the Code

Some of you looking at my code will be trying to understand how it works. Simply put know that all these algorithims build off of Breadth First Search. Breadth First Search << Uniform Cost Search << Greedy Search << A* Search

The frontier is a priority queue and how you sort it is what differentiates each one of the above. 

If you're a student reading this and it somehow helped you pass a class ... follow me on twitter and instagram! @cris178 or CristiantheWriter


