#Programming for the Puzzled -- Srini Devadas
#You Will Never Want to Play Sudoku Again
#Given a partially filled in Sudoku board, complete the puzzle
#obeying the rules of Sudoku

# This version try to mimics the human heurstic when solving the puzzle,
# if we combine the heuristics with the computer power, it becomes
# easy and trivial the solve sudoku puzzle.What matters the most in
# Backtracing problem is to undo the damage you have done during the process.
backtracks = 0

#x varies from entry1 to entry2 - 1, y varies from entry3 to entry4 - 1
# This stores the starting index and end index coordinates of each sectors.
# Which would get used later.
sectors = [ [0, 3, 0, 3], [3, 6, 0, 3], [6, 9, 0, 3],
            [0, 3, 3, 6], [3, 6, 3, 6], [6, 9, 3, 6],
            [0, 3, 6, 9], [3, 6, 6, 9], [6, 9, 6, 9] ]

#This procedure finds the next empty square to fill on the Sudoku grid
def findNextCellToFill(grid):
    #Look for an unfilled grid location
    #This remains the same, the findNextCellToFill function.
    for x in range(0, 9):
        for y in range(0, 9):
            if grid[x][y] == 0:
                return x,y
    return -1,-1

#This procedure checks if setting the (i, j) square to e is valid
def isValid(grid, i, j, e):
    rowOk = all([e != grid[i][x] for x in range(9)])
    if rowOk:
        columnOk = all([e != grid[x][j] for x in range(9)])
        if columnOk:
            #finding the top left x,y co-ordinates of
            #the section or sub-grid containing the i,j cell
            secTopX, secTopY = 3 *(i//3), 3 *(j//3)
            for x in range(secTopX, secTopX+3):
                for y in range(secTopY, secTopY+3):
                    if grid[x][y] == e:
                        return False
            return True
    return False


#This procedure makes implications based on existing numbers on squares
def makeImplications(grid, i, j, e):
    # This implications can actually be replaced by other human heuristics.
    # Making implications from grid[i][j] if it is filled with element e.
    global sectors

    grid[i][j] = e
    impl = [(i, j, e)]

    for k in range(len(sectors)): # Searching through all 9 sectors

        sectinfo = []
        # Each sector has their own sector info for each
        # grid within the sector.

        #find missing elements in ith sector
        # This set maintains the possible value within a sector.
        vset = {1, 2, 3, 4, 5, 6, 7, 8, 9}# set object
        # Searching through each sectors
        # e.g. sector1 coordinates ranging from x = (0~3),y = (0~3)
        for x in range(sectors[k][0], sectors[k][1]):
            #x ranging from the x start of this sectors to the x end of
            # this sectors
            for y in range(sectors[k][2], sectors[k][3]):
                #y ranging from the y start of this sectors to the y end of
                # this sectors

                if grid[x][y] != 0: # If that section has a value.
                    vset.remove(grid[x][y]) # Remove that value away from sets.

        #attach copy of vset to each missing square in ith sector
        for x in range(sectors[k][0], sectors[k][1]):
            for y in range(sectors[k][2], sectors[k][3]):
                if grid[x][y] == 0:
                    # Attach the possible sets info to
                    # each grid location
                    # of the sector, appending the x,y info, also the
                    # Corresponding search set.
                    sectinfo.append([x, y, vset.copy()])

        # Start searching through the sectorInfo list.
        for m in range(len(sectinfo)):
            sin = sectinfo[m]
            # For the mth serach info of the sectinfo list.

            #find the set of elements on the
            # row corresponding to m and remove them
            rowv = set() # This creates a set object, {1,2,3,4}...
            for y in range(9):
                # The sin[0] contains position of the grid.
                # sets for a particular possible
                # grid. sin contatins the (x,y,vset)
                # Thus sin[0] is the x coordinate of that grid.
                rowv.add(grid[sin[0]][y])

            # sin[2] is the vset. left is the difference of rowv
            # since we search through the possible row, to include the row
            # elements into the set. We can then perform the set operations
            # To indicates which should be kept and which should be left.
            left = sin[2].difference(rowv)

            #find the set of elements on the column corresponding to m and remove them
            colv = set()
            # Instatiating colv as set, to indicate the possible set element
            for x in range(9):
                # sin (x,y,vset), sin[1] is the y coordinate of the sectorinfo sin
                colv.add(grid[x][sin[1]])
            # Going through the set operations again to remove the impossible
            # location in terms of columns.
            left = left.difference(colv)

            #check if the vset is a singleton
            #Keep pruning until vset is a singleton for this grid.
            if len(left) == 1:
                # The value within the left, is the result.
                val = left.pop()
                # Check if valid(grid,x,y,val)
                if isValid(grid, sin[0], sin[1], val):
                    # If valid, assign it to the grid.
                    grid[sin[0]][sin[1]] = val
                    # Append this (x,y,val) to undo the damage later.
                    impl.append((sin[0], sin[1], val))

    return impl

#This procedure undoes all the implications
def undoImplications(grid, impl):
    # Simply from the implication made before, reset the location of
    # implications to 0.
    for i in range(len(impl)):
        grid[impl[i][0]][impl[i][1]] = 0
    return


#This procedure fills in the missing squares of a Sudoku puzzle
#obeying the Sudoku rules by guessing when it has to and performing
#implications when it can
def solveSudokuOpt(grid, i = 0, j = 0):
    # Main driver of solving sudoku recursive calling and backtracking.
    global backtracks

    #find the next empty cell to fill
    i, j = findNextCellToFill(grid)
    if i == -1:
        return True

    for e in range(1, 10):
        #Try different values in i, j location
        if isValid(grid, i, j, e):

            # This makes implications, comparing to simply filling up
            # the grid[i][j] = e, now we try to make implications on all
            # possible elements within sudoku.
            impl = makeImplications(grid, i, j, e)

            if solveSudokuOpt(grid, i, j):
                return True
            #Undo the current cell for backtracking
            backtracks += 1
            # Remember to undo the damage, this time, all implications
            # you have made must be resolved!
            undoImplications(grid, impl)

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


solveSudokuOpt(inp2)
printSudoku(inp2)
print ('Backtracks = ', backtracks)


backtracks = 0
print(solveSudokuOpt(hard))
printSudoku(hard)
print ('Backtracks = ', backtracks)

backtracks = 0
printSudoku(diff)
print(solveSudokuOpt(diff))
printSudoku(diff)
print ('Backtracks = ', backtracks)
