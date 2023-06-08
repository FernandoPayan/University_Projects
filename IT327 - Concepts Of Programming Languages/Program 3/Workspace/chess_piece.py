""""
Authors: Fernando Payan & Albert Nytko
Description: This files holds the parent class for the chess pieces
IT 327
11/2/2022
"""

class ChessPiece():
    _row: int # An integer specifying the row of the board the piece is on
    _col: int # An integer specifying the column of the board the piece is on
    _label: str # The enum that represents that piece's label (PieceInfo.EMPTY by default)
    _color: str # The enum that represents the piece's color (BoardInfo.WHITE or BoardInfo.BLACK)

    # Default Constructor - Takes in values for all four instance variables
    def __init__(self, _row, _col, _color, _label):
        self._col = _col
        self._row = _row
        self._label = _label
        self._color = _color

    # Takes the new row and column as parameters and updates the 
    # piece's location instance variables
    def move(self, _row, _col):
        self._row = _row
        self._col = _col

    # Returns _color
    def get_color(self):
        return self._color
    
    # Returns _label and takes no parameters 
    def get_label(self):
        return self._label

    # Returns false and takes three parameters: An integer representing the destination row,
    # an integer representing the destination column, and a Board object, which is the chess board
    # we're using.
    def is_legal_move(self, destRow, destCol, board):
        return False

    # Takes two parameters: a 2D list of characters that we will use for showing where
    # the piece can move and a Board object. The method will simply return the 2D list
    # of characters.
    def generate_legal_moves(self, list, board):
        return list