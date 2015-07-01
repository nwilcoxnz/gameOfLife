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
			b = rand() % 10; // 1/5 chance a cell will be set to live
			if (b == 4){ cells[pos].setState(true);} 
			pos++;
		}
		pos++;
	}
}

void draw(Cell *cells){ // Draw the grid; dead cells are not drawn; live cells are represented by a diamond (ascii 004)
	int pos = 0;
	for (int i = 0; i < dimension; i++){
		for (int j = 0; j < dimension; j++){
			if (cells[pos].isAlive()) {
				if (pos == 375) cout << "y";
				else cout << "x ";
			}
			else cout << "  ";
			pos++;
		}
		pos++;
		cout << endl;
	}
}

int numNeighbours(Cell *cells, int index){ // Takes an array of cells and returns the number of neighbours at cell 'index'

/*  where d = dimension 
		  x = index

	|x-d-1| x-d |x-d+1|
	-------------------
	| x-1 |  x  | x+1 |
	-------------------
	|x+d-1| x+d |x+d+1|

*/
	int num = 0; // Number of neighbours
	int temp; // Temporary index value
	int d = dimension;

	// Top row
	temp = index - dimension - 1;
	for (int i = 0; i < 3; i++){
		if (temp % ){
			if (cells[temp].isAlive()) num++; // Count this cell if it's alive
			temp++;
		}
	}

	// Middle row
	temp = index - 1;
	for (int i = 0; i < 3; i++){
		if (cells[temp].isAlive()) num++; // Count this cell if it's alive
		temp++;
	}

	// Bottom row
	temp = index + dimension - 1;
	for (int i = 0; i < 3; i++){
		if (cells[temp].isAlive()) num++; // Count this cell if it's alive
		temp++;
	}

	return num;
}

void evaluateNeighbours(Cell *cells){ // Evaluates the number of neighbours of every cell
	int pos = 0;
	for (int i = 0; i < dimension-1; i++){
		for (int j = 0; j < dimension-1; j++){
			cells[pos].setNeighbours(numNeighbours(cells, pos)); // Find the number of neighbours a cell has
			pos++;
		}
		pos++;
	}
}	

void update(Cell *cells){ // Updates which cells should be alive or dead
	for (int i = 0; i < (dimension*dimension)-1; i++){
		if (cells[i].isAlive()){ // If a cell is alive
			if (cells[i].getNeighbours() < 2){ // If a live cell has less than two live neighbours it dies
				cells[i].setState(false);
			}

			 // (Implicit) If a cell has two or three live neighbours it remains alive

			if (cells[i].getNeighbours() > 3){ // If a cell has more than three live neighbours it dies
				cells[i].setState(false);
			}
		}
		else { // If a cell is dead
			if (cells[i].getNeighbours() == 3){ 	// If a cell has exactly three live neighbours it will now be alive
				cells[i].setState(true);
			}
		}
	}
}


int main(){

	Cell *cells = new Cell[400]; // Represents the entire grid

	init(cells);

	for (int i = 0; i < 10; i++){
		draw(cells);
		evaluateNeighbours(cells);
		update(cells);
		cout << "-------------------------------------" << endl << endl << "neighbours: " << numNeighbours(cells,375) << endl;
		getch();
	}

}




