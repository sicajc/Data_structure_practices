#Programming for the Puzzled -- Srini Devadas
#You Will Never Want to Play Sudoku Again
#Given a partially filled in Sudoku board, complete the puzzle
#obeying the rules of Sudoku

#Global variable set to 0
backtracks = 0

#This procedure finds the next empty square to fill on the Sudoku grid
# Notice they always break each movements into sub-procedures
# So that one can focus on that particular function's implementation
def findNextCellToFill(grid):
    #Look for an unfilled grid location
    for x in range(0, 9):
        for y in range(0, 9): # Traversing the whole 9x9 grid.
            if grid[x][y] == 0: #That grid is empty.
                return x, y #Gives the coordinate of that grid.
    return -1, -1


#This procedure checks if setting the (i, j) square to e is valid
def isValid(grid, i, j, e):
    # Note violation of row, column or sector results in inValid,
    # Thus we can code it as a nested loop.
    rowOk = all([e != grid[i][x] for x in range(9)])
    # Checking row alright, by maintaing a boolean string, if 1 element in boolean
    # is already in the row, rowOk is false
    if rowOk: # Check column only if rowOk
        columnOk = all([e != grid[x][j] for x in range(9)])
        # Check for the whole column
        if columnOk:#Check for sector only if column is alright
            #finding the top left x,y co-ordinates of
            #the section or sub-grid containing the i,j cell
            secTopX, secTopY = 3 *(i//3), 3 *(j//3)
            for x in range(secTopX, secTopX+3):
                for y in range(secTopY, secTopY+3):
                    # Traversing from the Found Topleft x,y coordinates.
                    if grid[x][y] == e:#If you found the element within sector
                        return False
            # Return True iff no element in correspondent position's row,
            # column and sector!
            return True
    return False

#This procedure fills in the missing squares of a Sudoku puzzle
#obeying the Sudoku rules through brute-force guessing and checking
def solveSudoku(grid, i=0, j=0):

    # Global variable backtracks to indicate the number of
    # backtracing occurs while searching for a solution in this
    # Sudoku puzzle.
    global backtracks

    #find the next cell to fill
    i, j = findNextCellToFill(grid)
    if i == -1: #Once you search all possibilities, i is -1, thus end seraching
        return True

    # Trying to fill in the elements e for this grid[i][j]
    for e in range(1, 10):
        #Try different values in i, j location
        if isValid(grid, i, j, e):
            grid[i][j] = e
            # Recursive calls ask the function to solve sudoku again.
            # If successfully solved the sudoku, return true.
            # Otherwise, undo the damage.
            if solveSudoku(grid, i, j):
                return True

            # Undo the current cell for backtracking
            # The most important step in backtracking!!
            # Undoing the damage!
            backtracks += 1
            grid[i][j] = 0

    return False


def printSudoku(grid):
    numrow = 0
    for row in grid:
        if numrow % 3 == 0 and numrow != 0:
            print (' ')
        print (row[0:3], ' ', row[3:6], ' ', row[6:9])
        numrow += 1
    return

input = [[5,1,7,6,0,0,0,3,4],
         [2,8,9,0,0,4,0,0,0],
         [3,4,6,2,0,5,0,9,0],
         [6,0,2,0,0,0,0,1,0],
         [0,3,8,0,0,6,0,4,7],
         [0,0,0,0,0,0,0,0,0],
         [0,9,0,0,0,0,0,7,8],
         [7,0,3,4,0,0,5,6,0],
         [0,0,0,0,0,0,0,0,0]]

inp2  = [[5,1,7,6,0,0,0,3,4],
         [0,8,9,0,0,4,0,0,0],
         [3,0,6,2,0,5,0,9,0],
         [6,0,0,0,0,0,0,1,0],
         [0,3,0,0,0,6,0,4,7],
         [0,0,0,0,0,0,0,0,0],
         [0,9,0,0,0,0,0,7,8],
         [7,0,3,4,0,0,5,6,0],
         [0,0,0,0,0,0,0,0,0]]

inpd  = [[1,0,5,7,0,2,6,3,8],
         [2,0,0,0,0,6,0,0,5],
         [0,6,3,8,4,0,2,1,0],
         [0,5,9,2,0,1,3,8,0],
         [0,0,2,0,5,8,0,0,9],
         [7,1,0,0,3,0,5,0,2],
         [0,0,4,5,6,0,7,2,0],
         [5,0,0,0,0,4,0,6,3],
         [3,2,6,1,0,7,0,0,4]]

hard  = [[8,5,0,0,0,2,4,0,0],
         [7,2,0,0,0,0,0,0,9],
         [0,0,4,0,0,0,0,0,0],
         [0,0,0,1,0,7,0,0,2],
         [3,0,5,0,0,0,9,0,0],
         [0,4,0,0,0,0,0,0,0],
         [0,0,0,0,8,0,0,7,0],
         [0,1,7,0,0,0,0,0,0],
         [0,0,0,0,3,6,0,4,0]]

diff  = [[0,0,5,3,0,0,0,0,0],
         [8,0,0,0,0,0,0,2,0],
         [0,7,0,0,1,0,5,0,0],
         [4,0,0,0,0,5,3,0,0],
         [0,1,0,0,7,0,0,0,6],
         [0,0,3,2,0,0,0,8,0],
         [0,6,0,5,0,0,0,0,9],
         [0,0,4,0,0,0,0,3,0],
         [0,0,0,0,0,9,7,0,0]]



print(solveSudoku(input))
printSudoku(input)
print ('Backtracks = ', backtracks)

backtracks = 0
print(solveSudoku(inp2))
printSudoku(inp2)
print ('Backtracks = ', backtracks)

backtracks = 0
printSudoku(hard)
print(solveSudoku(hard))
printSudoku(hard)
print ('Backtracks = ', backtracks)

backtracks = 0
printSudoku(diff)
print(solveSudoku(diff))
printSudoku(hard)
print ('Backtracks = ', backtracks)
