/*

GAME OF LIFE

RULES:
Any live cell with fewer than two live neighbours dies, as if caused by under-population.
Any live cell with two or three live neighbours lives on to the next generation.
Any live cell with more than three live neighbours dies, as if by overcrowding.
Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

*/

#include <iostream>
#include <stdlib.h>
#include "conio.h"

using namespace std;

int dimension = 20; // The grid will always be square

////////////////////////// CELL CLASS //////////////////////////
class Cell {
private:
	bool state; // true = alive and false = dead
	int numNeighbours;
public:
	Cell(){ state = false; numNeighbours = 0;} // Constructor
	bool isAlive();
	void setState(bool s);
	void setNeighbours(int n);
	int getNeighbours();
};

// Member functions
void Cell::setState(bool s){
	this->state = s;
}

bool Cell::isAlive(){
	if (this->state == true) return true;
	return false;
}

void Cell::setNeighbours(int n){
	numNeighbours = n;
}

int Cell::getNeighbours(){
	return numNeighbours;
}
//////////////////////////////////////////////////////////////////

void init(Cell *cells){ // Randomly initialise a few cells to be alive
	// int a = rand() % 25 + 10; // Have between 10 and 25 live cells
	int b; 
	int pos = 0;
	for (int i = 0; i < dimension; i++){
		for (int j = 0; j < dimension; j++){
			// srand(time(0));
			b = rand() % 8; // 1/5 chance a cell will be set to live
			if (b == 4){ cells[pos].setState(true);} 
			pos++;
		}
	}
}

void draw(Cell *cells){ // Draw the grid; dead cells are not drawn; live cells are represented by a diamond (ascii 004)
	int pos = 0;
	for (int i = 0; i < dimension; i++){
		cout << i << " ";
		for (int j = 0; j < dimension; j++){
			if (cells[pos].isAlive()) {
				cout << "x ";
			}
			else cout << "  ";
			pos++;
		}
		cout << endl;
	}
}

int numNeighbours(Cell *cells, int index){ // Takes an array of cells and returns the number of neighbours at a single cell in that array (at index 'index')

/*  where d = dimension 
		  x = index

	|x-d-1| x-d |x-d+1|
	-------------------
	| x-1 |  x  | x+1 |
	-------------------
	|x+d-1| x+d |x+d+1|

*/
	int num = 0; // Number of neighbours
	int temp; // Temporary index value - determines where in the array the neighbours of cell[index] are
	int d = dimension;
	int numLoops = 3; // Determines how many neighbour cells need to be evaluated - helps when a cell is on the outside of the board 

	// If we are looking at one of the four corner cells
	if (index == 0 || index == dimension-1 || index == ((dimension*dimension)-dimension) || index == (dimension*dimension)-1){
		if (index == 0){ // If we're looking at the top-left cell
			// going anti-clockwise check all neighbours 
			if (cells[(dimension*dimension)-1].isAlive()) num++; // Top-left corner neighbour
			if (cells[dimension-1].isAlive()) num++; // Left neighbour
			if (cells[(dimension*2)-1].isAlive()) num++; // Bottom-left corner neighbour
			if (cells[dimension].isAlive()) num++; // Bottom neighbour
			if (cells[dimension+1].isAlive()) num++; // Bottom right corner neighbour
			if (cells[1].isAlive()) num++; // Right neighbour
			if (cells[(dimension*dimension)-dimension+1].isAlive()) num++; // Top-right neighbour
			if (cells[(dimension*dimension)-dimension].isAlive()) num++; // Top neighbour
		}

		else if (index == dimension-1){ // If we're looking at the top right-hand cell
			// going anti-clockwise check all neighbours 
			if (cells[(dimension*dimension)-2].isAlive()) num++; // Top-left corner neighbour
			if (cells[dimension-2].isAlive()) num++; // Left neighbour
			if (cells[(dimension*2)-2].isAlive()) num++; // Bottom-left corner neighbour
			if (cells[(dimension*2)-1].isAlive()) num++; // Bottom neighbour
			if (cells[dimension].isAlive()) num++; // Bottom right corner neighbour
			if (cells[0].isAlive()) num++; // Right neighbour
			if (cells[(dimension*dimension)-dimension].isAlive()) num++; // Top-right neighbour
			if (cells[(dimension*dimension)-1].isAlive()) num++; // Top neighbour
		}

		else if (index == ((dimension*dimension)-dimension)){ // If we're looking at the bottom-left cell
			// going anti-clockwise check all neighbours 
			if (cells[index-1].isAlive()) num++; // Top-left corner neighbour
			if (cells[(dimension*dimension)-1].isAlive()) num++; // Left neighbour
			if (cells[dimension-1].isAlive()) num++; // Bottom-left corner neighbour
			if (cells[0].isAlive()) num++; // Bottom neighbour
			if (cells[1].isAlive()) num++; // Bottom right corner neighbour
			if (cells[index+1].isAlive()) num++; // Right neighbour
			if (cells[index-dimension+1].isAlive()) num++; // Top-right neighbour
			if (cells[index-dimension].isAlive()) num++; // Top neighbour
		}

		else if (index == ((dimension*dimension)-1)){ // If we're looking at the bottom-right cell
			// going anti-clockwise check all neighbours 
			if (cells[index-dimension-1].isAlive()) num++; // Top-left corner neighbour
			if (cells[index-1].isAlive()) num++; // Left neighbour
			if (cells[dimension-2].isAlive()) num++; // Bottom-left corner neighbour
			if (cells[dimension-1].isAlive()) num++; // Bottom neighbour
			if (cells[0].isAlive()) num++; // Bottom right corner neighbour
			if (cells[index-dimension+1].isAlive()) num++; // Right neighbour
			if (cells[index-(dimension*2)+1].isAlive()) num++; // Top-right neighbour
			if (cells[index-dimension].isAlive()) num++; // Top neighbour
		}
		if (num != 0 && cells[index].isAlive()) cout << "Cell " << index << " has " << num << " neighbours" << endl;
		return num; // We don't need to carry on 
	}

	//////// Top row ////////
	// SET POSITION OF TOP LEFT-HAND CORNER (i.e. x-d-1)
	// To account for wrapping
	if (index < dimension){ // If cell is on the outer top of the board
		temp = index + ((dimension*dimension)-dimension) - 1;
	}

	else if (index % dimension == 0){ // If cell is on the outer left-hand side of the board
		if (cells[index-1].isAlive()) num++; // Count the top left cell if it's alive
		temp = index - dimension; // Set the position to count the other cells
		numLoops = 2;
	}

	else if ((index+1) % dimension == 0){ // If cell is on the outer right-hand side of the board
		if (cells[index-(dimension*2)+1].isAlive()) num++; // Count the top right cell if it's alive
		temp = index - dimension -1;
		numLoops = 2;
	}

	else {// If cell is not on the outside of the board (i.e. will not need to wrap)
		temp = index - dimension - 1;
	}

	for (int i = 0; i < numLoops; i++){
		if (cells[temp].isAlive()) num++; // Count this cell if it's alive
		temp++;
	}
	//////////////////////////

	numLoops = 3; // Reset

	//////// Middle row ////////

	if (index % dimension == 0){ // If cell is on far left-hand side
		if (cells[index+dimension-1].isAlive()) num++;
		numLoops = 1;
		temp = index + 1;
	}

	else if ((index+1) % dimension == 0){ // If cell is on far right hand side
		if (cells[index-dimension+1].isAlive()) num++;
		temp = index - 1;
		numLoops = 1;
	}

	else { // Else if cell is in middle of board (not on the outside)
		temp = index - 1;
	}

	for (int i = 0; i < numLoops; i++){
		if (cells[temp].isAlive() && temp != index) num++; // Count this cell if it's alive (don't include centre cell as it is the actual cell we are looking at, not a neighbour)
		temp++;
	}
	//////////////////////////

	numLoops = 3; // Reset

	//////// Bottom row ////////

	if (index % dimension == 0){ // If cell is on far left-hand side
		if (cells[index+(dimension*2)-1].isAlive()) num++; // Count the bottom left cell if it's alive
		temp = index + dimension; // Set the position to count the other cells
		numLoops = 2;
	}

	else if ((index+1) % dimension == 0){ // If cell is on far right-hand side
		if (cells[index+1].isAlive()) num++; // Count the bottom right cell if it's alive
		temp = index + dimension-1; // Set the position to count the other cells
		numLoops = 2;
	}

	else if (index > (dimension*dimension)-dimension){ // If cell is on the outer bottom 
		if (cells[index-400+19].isAlive()) num++;
		if (cells[index-400+20].isAlive()) num++;
		if (cells[index-400+21].isAlive()) num++;
		return num;
		// temp = index - ((dimension*dimension)+dimension-1);
		// numLoops = 3;
	}

	else temp = index + dimension - 1; // Else if cell is in middle of board (not on the outside)

	for (int i = 0; i < numLoops; i++){
		if (cells[temp].isAlive()) num++; // Count this cell if it's alive
		temp++;
	}
	//////////////////////////
	// if (index == 398) cout << "naybuz " << num << endl;
	// if (num != 0 && cells[index].isAlive()) cout << "Cell " << index << " has " << num << " neighbours" << endl;
	return num;
}

void evaluateNeighbours(Cell *cells){ // Evaluates the number of neighbours of every cell
	int pos = 0;
	for (int i = 0; i < dimension; i++){
		for (int j = 0; j < dimension; j++){
			cells[pos].setNeighbours(numNeighbours(cells, pos)); // Find the number of neighbours a cell has
			pos++;
		}
	}
}	

void update(Cell *cells){ // Updates which cells should be alive or dead
	for (int i = 0; i < 420; i++){
		if (cells[i].isAlive()){ // If a cell is alive
			if (cells[i].getNeighbours() < 2){ // If a live cell has less than two live neighbours it dies
				cells[i].setState(false);
				// cout << "setting cell " << i << " to false" << endl;
			}

			// (Implicit) If a live cell has two or three live neighbours it remains alive

			else if (cells[i].getNeighbours() > 3){ // If a live cell has more than three live neighbours it dies
				cells[i].setState(false);
				// cout << "setting cell " << i << " to false" << endl;
			}
		}
		else { // If a cell is dead
			if (cells[i].getNeighbours() == 3){ 	// If a cell has exactly three live neighbours it will now be alive
				cells[i].setState(true);
				// cout << "setting cell " << i << " to true" << endl;
			}
		}
	}
}

int main(){

	Cell *cells = new Cell[400]; // Represents the entire grid
	// init(cells);
	cells[2].setState(true);
	cells[20].setState(true);
	cells[22].setState(true);
	cells[41].setState(true);
	cells[42].setState(true);

	for (int i = 0; i < 200; i++){
		draw(cells);
		evaluateNeighbours(cells);
		update(cells);
		cout << "------------------------------------------" << endl << endl;
		cout << " cell 359 has " << cells[359].getNeighbours() << " neighbours";
		if (cells[359].isAlive()) cout << " and is alive" << endl;
		else cout << " and is dead" << endl;
		getch();
	}

}
