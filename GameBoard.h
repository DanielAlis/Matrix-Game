//
// Created by Alis Daniel on 19/06/2021.
//

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

namespace mtm {
    template<class T>
    class GameBoard {
        const int row;
        const int column;
        T** board;
    public:
        GameBoard(const int row, const int col, T data = T());
        GameBoard(const GameBoard&);
        ~GameBoard();
        const int getRow() const;
        const int getColumn() const;
        T& operator()(int row,int col);
        GameBoard<T>& operator=(const GameBoard<T>& game_board);
    };
}


/** constructor:  creates an GameBoard according the columns and rows given, containing the data.
 * @param row- number of rows on the GameBoard .
 * @param column- number of columns on the GameBoard.
 * @param data- the data that the GameBoard contain.
*/
template<class T>
mtm::GameBoard<T>::GameBoard(const int row, const int column, T data) :
        row(row), column(column)
        {
    board = new T * [row];
    for (int i = 0; i < row; i++)
    {
        board[i] = new T[column];
        for (int j = 0; j < column; j++)
        {
            board[i][j] = data;
        }
    }
}


/** copy constructor:  creates a copy of the GameBoard its been given.
 * @param board- the GameBoard it copies.
*/
template<class T>
mtm::GameBoard<T>::GameBoard(const GameBoard<T>& board) :
        row(board.row), column(board.column) {
    this->board = new T * [row];
    for (int i = 0; i < board.row; i++) {
        this->board[i] = new T[column];
        for (int j = 0; j < board.column; j++) {
            this->board[i][j] = board.board[i][j];
        }
    }
}

//Destructor for board<T> - deletes the board and deallocates it from memory
template <class T>
mtm::GameBoard<T>::~GameBoard()
{
    for (int i = 0; i < this->row; i++)
    {
        delete[] board[i];
    }
    delete[] board;
}



/** getRow: fetches the the number of rows in board
 * @return
 * the number of rows in board<T>.
*/
template<class T>
const int mtm::GameBoard<T>::getRow() const {
    return this->row;
}

/** getRow: fetches the the number of columns in board
 * @return
 * the number of columns in board<T>.
*/
template<class T>
const int mtm::GameBoard<T>::getColumn() const {
    return this->column;
}

/** operator(): Accessing a board<T> cell by (row, column)
 * @param row_index- the row index of the data on the GameBoard.
 * @param column_index- the column index of the data on the GameBoard.
 *
 * @return
 * it returns the data on the GameBoard cell.
*/
template <class T>
T& mtm::GameBoard<T>::operator()(int row_index, int column_index)
        {
    return this->board[row_index][column_index];
}


/** operator=: Returns a reference to a new gameBoard.
 * @param game_board- the GameBoard it copies to this.
 *
 * @return
 * it returns a copy of the game.
*/
template<class T>
mtm::GameBoard<T>& mtm::GameBoard<T>::operator=(const mtm::GameBoard<T>& game_board)
        {
    if (this == &game_board) {
        return *this;
    }
    for (int i = 0; i < this->row; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
    this->board = new T * [game_board.row];
    for (int i = 0; i < game_board.row; i++) {
        this->board[i] = new T[game_board.column];
        for (int j = 0; j < game_board.column; j++) {
            this->board[i][j] = game_board.board[i][j];
        }
    }
    return *this;
}

#endif //GAMEBOARD_H