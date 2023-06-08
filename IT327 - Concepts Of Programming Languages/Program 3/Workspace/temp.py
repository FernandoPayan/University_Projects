from chess_piece import ChessPiece
from board import BoardInfo

# class for the knight chess piece
class Knight(ChessPiece):
    def __init__(self, row_num, col_num, color, label):
        super().__init__(row_num, col_num, color, label)

    # returns true if knight can move to specified location on board    
    def is_legal_move(self, dest_row, dest_col, board):
        row_diff = abs(self._row-dest_row)
        col_diff = abs(self._col-dest_col)
        square_type = board.get_square_info(dest_row, dest_col)

        is_legal = ((row_diff == 1 and col_diff == 2 
                    or row_diff == 2 and col_diff == 1) 
                    and square_type != self._color 
                    and square_type != BoardInfo.OFF_THE_BOARD)
        return is_legal

    # returns visual representation of legal knight moves on board
    def generate_legal_moves(self, board_data, board):
        char_label = self._label.value
        board_data[self._row][self._col] = char_label
        
        # handle up and right moves
        row = self._row - 2
        col = self._col + 1
        if self.is_legal_move(row, col, board):
            board_data[row][col] = char_label

        row = self._row - 1
        col = self._col + 2
        if self.is_legal_move(row, col, board):
            board_data[row][col] = char_label

        # handle up and left moves
        row = self._row - 2
        col = self._col - 1
        if self.is_legal_move(row, col, board):
            board_data[row][col] = char_label

        row = self._row - 1
        col = self._col - 2
        if self.is_legal_move(row, col, board):
            board_data[row][col] = char_label

        # handle down and left moves
        row = self._row + 2
        col = self._col - 1
        if self.is_legal_move(row, col, board):
            board_data[row][col] = char_label

        row = self._row + 1
        col = self._col - 2
        if self.is_legal_move(row, col, board):
            board_data[row][col] = char_label

        # handle down and right moves
        row = self._row + 2
        col = self._col + 1
        if self.is_legal_move(row, col, board):
            board_data[row][col] = char_label

        row = self._row + 1
        col = self._col + 2
        if self.is_legal_move(row, col, board):
            board_data[row][col] = char_label

        return board_data