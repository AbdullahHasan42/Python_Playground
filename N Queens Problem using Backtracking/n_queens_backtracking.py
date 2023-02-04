import time
import pandas as pd
import matplotlib.pyplot as plt
from pylab import rcParams
rcParams['figure.figsize'] = 15, 8


def solverFunctionHelper(board, board_size, col):
    # base case: If all queens are placed then return true
    if col >= board_size:
        return True

    # Consider this column and try placing this queen in all rows one by one
    for i in range(board_size):

        if isSafe(board, i, col):
            # Place this queen in board[i][col]
            board[i][col] = 1

            # recur to place rest of the queens
            if solverFunctionHelper(board, board_size, col + 1) is True:
                return True
            board[i][col] = 0
    return False

# This function solves the N Queen problem using Backtracking. It uses solverFunctionHelper()


def solverFunction(board_size, print_iterations):
    board = [[0] * board_size for i in range(board_size)]

    if solverFunctionHelper(board, board_size, 0) is False:
        print("Solution does not exist")
        return False
    if print_iterations is True:
        printSolution(board)
    return True



def isSafe(board, row, col):

    # Check this row on left side
    for i in range(col):
        if board[row][i] == 1:
            return False

    # Check upper diagonal on left side
    for i, j in zip(range(row, -1, -1), range(col, -1, -1)):
        if board[i][j] == 1:
            return False

    # Check lower diagonal on left side
    for i, j in zip(range(row, board_size, 1), range(col, -1, -1)):
        if board[i][j] == 1:
            return False

    return True

def printSolution(board):
    for i in range(board_size):
        for j in range(board_size):
            print(board[i][j], end=' ')
        print()
    pass



combinations = []

# Set this var to True, if you'd like to print the board at each step
print_iterations = False

for board_size in range(4, 21):
    start_T = time.time()
    solverFunction(board_size, print_iterations)
    combinations.append([board_size, round((time.time() - start_T)*1000, 3)])



combinations = pd.DataFrame(combinations, columns=['Board Size', 'Time Taken (millisecs)'])
combinations.set_index('Board Size', inplace=True)

combinations.plot()
plt.ylabel('Time (Milliseconds')
plt.grid()