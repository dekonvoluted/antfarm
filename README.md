# Introduction

This project implements Langton's Ant, an automaton that follows a simple set of rules while traversing a grid.

# Rules

* The ant traverses a gridded game board on which squares are either black or white.
* If the current square the ant is on is white, the ant will move one step to its right, after toggling the color of the current square.
* If the current square is black, the ant will move one step to its left, and toggle the current square color to white.

# Complications

* Multiple ants can inhabit the same game board.
* Squares can have a cyclic list of colors, each deciding whether the ant turns left or right.
* Turmites which have colors and associated rules for each color.

