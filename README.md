Game of Life
============

This is an implementation of Conway's game of life. 

The rules are as follows:

0. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
0. Any live cell with two or three live neighbours lives on to the next generation.
0. Any live cell with more than three live neighbours dies, as if by overcrowding.
0. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

See [wikipedia](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) for more information.

Implementation
--------------

* Currently the board is 20 x 20 cells wide (this can be modified) 
* The board consists of a one-dimensional array of Cell objects which have various member functions and attributes
* The cells do wrap around but further testing is required to ensure the behaviour is completely correct
