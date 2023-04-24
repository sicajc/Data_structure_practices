# Maze problem
## Problem Specification:
- Given an NxN maze with one entry and one ending point.
- Goal is to find the path from input to output, later display the path on the screen.

## Procedures
1. [READ_DATA]Read in the maze, also its start point and its end point.
2. [ONE_PADDING_THE_MAZE]One-padded the maze using STL algorithm, so that boundary conditions do not needed to be concerned.
3. [DIRECTION_TABLE] Build the direction(move) table, corresponding to the possible moves you can perform when traversing the maze.
4. [MARK] Build a table of size NxN which marks the place you have been to before.
5. [LOOP] Start Traversing the maze from start point to end point.
   1. [CONSULTING_LIST] Taking out one Position from list
      1. Remove the position from list

   2. [LOOP] Traverse for all possible directions from a certain position using the move table.
        - Add the possible move to current position.
        - Check if this position is the end point or not, if yes, I found the end point, no need to search anymore.
        - If the move to a certain position is valid, add the position to a list of traversal, I will pick the possible new position from that list later.
        -  Mark this position as traversed in the mark table.
        - Mark this position as I have been here before within the Maze map.
        - Move into that possible position
   3. [KEEP_TRYING] BACK TO 5.

6. [TERMINATION_CONDITION] Keep doing this until the list with possible positions are empty. Then no path can be found, there must be something wrong with the map.

## EXAMPLE INPUTS & OUTPUTS
1. Create one possible input and output for tracing, draw it out.

## PseudoCode

```python



```
