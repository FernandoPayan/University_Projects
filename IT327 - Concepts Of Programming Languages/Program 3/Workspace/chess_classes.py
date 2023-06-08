""""
Authors: Fernando Payan & Albert Nytko
Description: This files holds all the subclasses of the chess piece class, including: Knight, Rook, WhitePawn, Bishop, and Queen.
IT 327
11/2/2022
"""
from chess_piece import ChessPiece
from board import BoardInfo

# Subclasses
class Knight(ChessPiece):
    # Default Constructor
    def __init__(self, row_num, col_num, color, label):
        ChessPiece.__init__(self, row_num, col_num, color, label)

    # Checks if the Knight's move is legal
    def is_legal_move(self, dest_row, dest_col, board):
        # Defining variables
        row_diff = abs(self._row - dest_row) # Get Row Difference
        col_diff = abs(self._col - dest_col) # Get Column Difference
        square_type = board.get_square_info(dest_row, dest_col) # Get the square type info

        # Checks if the move is legal
        # Knights move can only be up or down one row and left or right two columns or move up or down two rows and left or right one column
        is_legal = ( (row_diff == 1 and col_diff == 2 or row_diff == 2 and col_diff == 1) and 
                     square_type != BoardInfo.WHITE and # Makes sure the square is not a white tile
                     square_type != BoardInfo.OFF_THE_BOARD # Check if we're not off the board
                   )
        
        # Returns if the move was legal or not
        return is_legal

    # Generates the legal moves for Knight
    def generate_legal_moves(self, board_data, board):
        # Initialize variables
        char_label = self._label.value
        board_data[self._row][self._col] = char_label
        
        # Knight can move to two possible spaces in each diagonal direction, 
        # so we must check for each of those two spots in each direction

        # Checks the two possible upper left moves
        # Up one row, left two columns
        if (self.is_legal_move(self._row + 1, self._col - 2, board)):
            board_data[self._row + 1][self._col - 2] = char_label

        # Up two rows, left one column
        if (self.is_legal_move(self._row + 2, self._col - 1, board)):
            board_data[self._row + 2][self._col - 1] = char_label


        # Checks the two possible bottom left moves:
        # Down one row, left two columns
        if (self.is_legal_move(self._row - 1, self._col - 2, board)):
            board_data[self._row - 1][self._col - 2] = char_label

        # Down two rows, left one column
        if (self.is_legal_move(self._row - 2, self._col - 1, board)):
            board_data[self._row - 2][self._col - 1] = char_label


        # Checks the two possible upper right moves
        # Up one row, right two columns
        if (self.is_legal_move(self._row + 1, self._col + 2, board)):
            board_data[self._row + 1][self._col + 2] = char_label
        
        # Up two rows, right one column
        if (self.is_legal_move(self._row + 2, self._col + 1, board)):
            board_data[self._row + 2][self._col + 1] = char_label


        # Check the two possible bottom right moves
        # Down one row, right two columns
        if (self.is_legal_move(self._row - 1, self._col + 2, board)):
            board_data[self._row - 1][self._col + 2] = char_label

        # Down two rows, right one column
        if (self.is_legal_move(self._row - 2, self._col + 1 , board)):
            board_data[self._row - 2][self._col + 1] = char_label

        # Returns the updated board data
        return board_data

class Rook(ChessPiece):
    # Default Constructor
    def __init__(self, row_num, col_num, color, label):
        ChessPiece.__init__(self, row_num, col_num, color, label)

    # Checks if the Rook's move is legal
    def is_legal_move(self, dest_row, dest_col, board):
        # Defining variables
        row_diff = self._row - dest_row # Get Row Difference
        col_diff = self._col - dest_col # Get Column Difference
        square_type = board.get_square_info(dest_row, dest_col) # Get the square type info

        cur_row = self._row # Keeps track of the current row we're on
        cur_col = self._col # Keeps track of the current column we're on
        rook_movement = 1 # Keeps track of the rook's movement
        valid_tile = True # Checks if the square is valid
        
        # A rook can move any number of spaces vertically and horizontally,
        # so we need to check both directions

        if (col_diff == 0): # Vertical Movement for Rook
            while (rook_movement < abs(row_diff)): # Go through each tile for our Rook
                # Tiles North of Rook
                if (row_diff <= 0):
                    # Get info of next top square to see if its empty             
                    curr_square = board.get_square_info(cur_row + 1, cur_col)

                    # If square is not empty
                    if (curr_square != BoardInfo.EMPTY):
                        valid_tile = False
                    
                    # Increment the amount of squares away it is from where it started
                    rook_movement = rook_movement + 1

                    # Update the current row
                    cur_row = cur_row + 1

                else: # Tiles South of Rook
                    # Get info of next bottom square to see if its empty
                    curr_square = board.get_square_info(cur_row - 1, cur_col)

                    # If square is not empty
                    if (curr_square != BoardInfo.EMPTY):
                        valid_tile = False
                        
                    # Increment the amount of squares away it is from where it started
                    rook_movement = rook_movement + 1

                    # Update the current row
                    cur_row = cur_row - 1
                    
        else: # Horizontal Movement for Rook
            while (rook_movement < abs(col_diff)):
                # Tiles West of Rook
                if (col_diff <= 0):
                    # Get info of right square to see if its empty              
                    curr_square = board.get_square_info(cur_row, cur_col + 1)
                    
                    # If square is not empty
                    if (curr_square != BoardInfo.EMPTY):
                        valid_tile = False

                    # Increment the amount of squares away it is from where it started
                    rook_movement = rook_movement + 1

                    # Update the current column
                    cur_col = cur_col + 1
                
                else: # Tiles East of Rook
                    # Get info of left square to see if its empty
                    curr_square = board.get_square_info(cur_row, cur_col - 1)

                    # If square is not empty
                    if (curr_square != BoardInfo.EMPTY):
                        valid_tile = False

                    # Increment the amount of squares away it is from where it started
                    rook_movement = rook_movement + 1

                    # Update the current column
                    cur_col = cur_col - 1
                    
        
        # Checks if the move is legal
        is_legal = ((col_diff == 0 or row_diff == 0) and # Checks if the move vertically or horizontally is possible
                    valid_tile == True and # Makes sure the tile is valid
                    square_type != BoardInfo.WHITE and # Makes sure the tile is not white
                    square_type != BoardInfo.OFF_THE_BOARD # Makes sure we're not off the board
                   )
        
        # Returns if the move was legal or not
        return is_legal

    # Generates the legal moves for Rook
    def generate_legal_moves(self, board_data, board):
        # Intializing Variables
        char_label = self._label.value
        board_data[self._row][self._col] = char_label
        
        # A rook can move any number of spaces vertically and horizontally, so
        # we want to go each direction and check if the tile is valid.

        # Saves the current row and column we started at before calculating any movements
        orig_row = self._row
        orig_col = self._col
        
        # Keeps track of the current row/column we're at for each direction we move
        cur_row: int
        cur_col: int

        # Checks movements to the North
        cur_row = orig_row + 1 # Moves to the row above us
        
        while (self.is_legal_move(cur_row, orig_col, board)): # While loop to check if the tile is legal
            board_data[cur_row][orig_col] = char_label # Updates the board
            cur_row = cur_row + 1 # Moves up one row

        # Checks movements to the East
        cur_col = orig_col + 1 # Moves to the column to our right

        while (self.is_legal_move(orig_row, cur_col, board)): # While loop to check if the tile is legal
            board_data[orig_row][cur_col] = char_label # Updates the board
            cur_col = cur_col + 1 # Moves to the right column

        # Checks movements to the South 
        cur_row = orig_row - 1 # Move to the row below us
        
        while (self.is_legal_move(cur_row, orig_col, board)): # While loop to check if the tile is legal
            board_data[cur_row][orig_col] = char_label # Updates the board
            cur_row = cur_row - 1 # Moves down one row

        # Checks movements to the West
        cur_col = orig_col - 1 # Moves to the column to our left

        while (self.is_legal_move(orig_row, cur_col, board)): # While loop to check if the tile is legal
            board_data[orig_row][cur_col] = char_label # Updates the board
            cur_col = cur_col - 1 # Moves left one column

        # Returns the updated board data
        return board_data

class WhitePawn(ChessPiece):
    # Default Constructor
    def __init__(self, row_num, col_num, color, label):
        ChessPiece.__init__(self, row_num, col_num, color, label)

    # Checks if the WhitePawn's move is legal
    def is_legal_move(self, dest_row, dest_col, board):
        # Defining variables
        row_diff = abs(self._row - dest_row) # Get Row Difference
        col_diff = abs(self._col - dest_col) # Get Column Difference
        square_type = board.get_square_info(dest_row, dest_col) # Get the square type info
        first_move = board.get_square_info(dest_row - 1, dest_col) # Checks if first move condition is valid

        # Checks if the move is legal
        is_legal = ( ( row_diff == 1 and col_diff == 0 and square_type == BoardInfo.EMPTY) # Checking if the tile in front of us is empty
                     or ( row_diff == 1 and col_diff == 1 and square_type == BoardInfo.BLACK) # Checking if the tiles diagonally from pawn are black
                     or ( row_diff == 2 and col_diff == 0 and self._row == 1 and square_type == BoardInfo.EMPTY and first_move == BoardInfo.EMPTY ) # If we do two tile jump
                     )

        # Returns the value of is_legal
        return is_legal
        
    # Generates the legal moves for WhitePawn
    def generate_legal_moves(self, board_data, board):
        # Defining Variables
        char_label = self._label.value
        board_data[self._row][self._col] = char_label
        
        # Moving North
        orig_row = self._row # Keeps the row we started at
        cur_row = orig_row + 1 # Keeps track of the current row we're at
        while (self.is_legal_move(cur_row, self._col, board)): # While loop to check if the tile is legal.
            board_data[cur_row][self._col] = char_label # Updates the board
            cur_row = cur_row + 1
        
        # In addition to moving vertically or horizontially, a pawn could also move diagonally up.
        # We need to check for those diagonal movements

        # Upper Left Move
        # Up one row, left one column
        if (self.is_legal_move(self._row + 1, self._col - 1, board)): # Checks if the tile is legal
            board_data[self._row + 1][self._col - 1] = char_label # Updates the board

        # Upper Right Move
        # Up one row, right one column
        if (self.is_legal_move(self._row + 1, self._col + 1, board)): # Checks if the tile is legal
            board_data[self._row + 1][self._col + 1] = char_label # Updates the board

        # Returns the updated board data
        return board_data

class Bishop(ChessPiece):
    # Default Constructor
    def __init__(self, row_num, col_num, color, label):
        ChessPiece.__init__(self, row_num, col_num, color, label)

    # Checks if the Bishop's move is legal  
    def is_legal_move(self, dest_row, dest_col, board):
        # Defining Variables
        row_diff = self._row-dest_row # Get Row Difference
        col_diff = self._col-dest_col # Get Column Difference
        square_type = board.get_square_info(dest_row, dest_col) # Get the square type info
        
        cur_row = self._row # Keeps track of the current row we're on
        cur_col = self._col # Keeps track of the current column we're on
        bishop_movement = 1 # Keeps track of the bishop's movement
        valid_tile = True # Checks if the square is valid
        
        # A Bishop can move any number of spaces diagonally,
        # so we need to check all four directions
        
        # Bishop tiles diagonally North East
        if (row_diff <= 0):
            while (bishop_movement < abs(row_diff)): # Go through each tile above our Bishop
                if (col_diff < 0):
                # Get info of the of up and one to the right square to see if its empty
                    path_square = board.get_square_info(cur_row + 1, cur_col + 1)

                    # If square is not empty
                    if (path_square != BoardInfo.EMPTY):
                        valid_tile = valid_tile + 1
                    
                    # Increment the amount of squares away it is from where it started
                    bishop_movement = bishop_movement + 1

                    # Update the Rows and Columns
                    cur_row = cur_row + 1
                    cur_col = cur_col - 1
                    
                else: # Bishop diagonally North West  
                    # get info of the of up and one to the left square to see if its empty         
                    path_square = board.get_square_info(cur_row + 1, cur_col - 1)

                    # if square is not empty
                    if (path_square != BoardInfo.EMPTY):
                        valid_tile = valid_tile + 1
                        
                    # Increment the amount of squares away it is from where it started
                    bishop_movement = bishop_movement + 1

                    # Update the Rows and Columns
                    cur_row = cur_row + 1
                    cur_col = cur_col - 1
        else: # Bishop tiles diagonally South East
            while (bishop_movement < abs(row_diff)): # Go through each tile below our Bishop
                if (col_diff < 0):
                    # Get info of the row down and one to the right square to see if its empty
                    path_square = board.get_square_info(cur_row - 1, cur_col + 1)

                    # If square is not empty
                    if (path_square != BoardInfo.EMPTY):
                        valid_tile = False

                    # Increment the amount of squares away it is from where it started
                    bishop_movement = bishop_movement + 1

                    # Update the Rows and Columns
                    cur_row =  cur_row - 1
                    cur_col = cur_col + 1

                else: # Bishop tiles diagonally South West   
                    # Get info of the row down and one to the left square to see if its empty
                    path_square = board.get_square_info(cur_row - 1, cur_col - 1)
                    
                    # If square is not empty
                    if (path_square != BoardInfo.EMPTY):
                        valid_tile = False
                    
                    # Increment the amount of squares away it is from where it started
                    bishop_movement = bishop_movement + 1

                    # Update the Rows and Columns
                    cur_row = cur_row - 1
                    cur_col = cur_col - 1

                    
        # Checks if the move is legal
        is_legal = ( (abs(row_diff) >= 1 and abs(row_diff) == abs(col_diff)) and # Checks the tile diagonal from Bishop
                    valid_tile == True and # If the tile is valid
                    square_type != BoardInfo.WHITE and # Checks if the square is a white tile
                    square_type != BoardInfo.OFF_THE_BOARD # Check if we're not off the board
                    )

        # Returns if the move was legal or not
        return is_legal

    # returns visual representation of legal bishop moves on board
    def generate_legal_moves(self, board_data, board):
        char_label = self._label.value
        board_data[self._row][self._col] = char_label

        # A Bishop can move any number of spaces diagonally, so
        # we want to go each diagonal direction and check if the tile is valid.
    
        # Saves the current row and column we started at before calculating any movements
        orig_row = self._row
        orig_col = self._col
        
        # Keeps track of the current row/column we're at for each direction we move
        cur_row: int
        cur_col: int

        # Checking North East Space
        cur_row = orig_row + 1
        cur_col = orig_col + 1

        while (self.is_legal_move(cur_row, cur_col, board)):
            board_data[cur_row][cur_col] = char_label
            cur_row = cur_row + 1 # Move to the row above
            cur_col = cur_col + 1 # Move column to the right
            
        # Checking North West Space
        cur_row = orig_row + 1
        cur_col = orig_col - 1
        
        while (self.is_legal_move(cur_row, cur_col, board)):
            board_data[cur_row][cur_col] = char_label
            cur_row = cur_row + 1 # Move to the row above
            cur_col = cur_col - 1 # Move column to the left

        # Checking South East Space
        cur_row = orig_row - 1 # Moves to the row below
        cur_col = orig_col + 1 # Moves to the column to the right

        while (self.is_legal_move(cur_row, cur_col, board)): 
            board_data[cur_row][cur_col] = char_label
            cur_row = cur_row - 1 # Move to the row below
            cur_col = cur_col + 1 # Move column to the right

        # Checking South West Space
        cur_row = orig_row - 1
        cur_col = orig_col - 1
        
        while (self.is_legal_move(cur_row, cur_col, board)):
            board_data[cur_row][cur_col] = char_label
            cur_row = cur_row - 1 # Move to the row below
            cur_col = cur_col - 1 # Move column to the left

        # Return the updated board data
        return board_data

class Queen(ChessPiece):
    # Default Constructor
    def __init__(self, row_num, col_num, color, label):
        ChessPiece.__init__(self, row_num, col_num, color, label)

    def is_legal_move(self, dest_row, dest_col, board):

        # A queen can move vertically, horizontially, or diagonally in any direction.
        # Since Rook and Bishop cover these moves, we can just combine them and call
        # them for the Queen to help with code repetition. 

        # Returns true if either Rook or Bishop's is_legal_move is true
        is_legal = ( Rook.is_legal_move(self, dest_row, dest_col, board) or
                     Bishop.is_legal_move(self, dest_row, dest_col, board)
                   )

        return is_legal

    
    def generate_legal_moves(self, board_data, board):
        char_label = self._label.value
        board_data[self._row][self._col] = char_label
        
        # Since a queen does a rook's move and a bishop's move combined,
        # We can just call the Rook and Bishop's moves.

        # Generate the legal moves for diagonal movement
        Bishop.generate_legal_moves(self, board_data, board)

        # Generate the legal moves for vertical & horizontal movement
        Rook.generate_legal_moves(self, board_data, board)

        
        # Return the updated board data
        return board_data