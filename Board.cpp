#include "Board.hpp"
#include <iostream>
using namespace std;
#include <string>
#include <vector>

namespace ariel {
    void Board::resize_board(uint row, uint column, uint max_row, uint max_column) {
        /*
        #################### ↓
        #################### ↓
        ######__Expand_The__ ↓
        ######__Board_Down__ ↓
        */
        while (max_row>largest_filled_row) {
            string temp;
            temp.resize(max(largest_filled_col,max_column)+1-col_space,'_');
            my_board.push_back(temp);
            largest_filled_row++;
        }
        /*
        #################### ↑
        #################### ↑
        ######__Expand_The__ ↑
        ######___Board_Up___ ↑
        */
        while (row<lowest_filled_row) {
            string temp;
            temp.resize(max(largest_filled_col,max_column)+1-col_space,'_');
            my_board.insert(my_board.begin(),temp);
            lowest_filled_row--;
            row_space--;
        }
        /*
        #################### →
        #################### →
        #####__Expand_The___ →
        #####__Board_Right__ →
        */
        if (max_column>largest_filled_col) {
            for (uint i = lowest_filled_row-row_space; i <= largest_filled_row-row_space; i++) {
                my_board[i].resize(max_column+1-col_space,'_');
            }
            /* Assigning a new value to largest_filled_col because max_column>largest_filled_col */
            largest_filled_col = max_column;
        }
        /*
        #################### ←
        #################### ←
        ######__Expand_The__ ←
        ######__Board_Left__ ←
        */
        if (column<lowest_filled_col) {
            string temp;
            temp.resize(lowest_filled_col-column,'_');
            for (uint i = lowest_filled_row-row_space; i <= largest_filled_row-row_space; i++) {
                my_board[i] = temp + my_board[i];
            }
            col_space = col_space - (lowest_filled_col-column);
            /* Assigning a new value to lowest_filled_col because column<lowest_filled_col */
            lowest_filled_col = column;
        }
    }

    void Board::post(uint row, uint column, Direction direction, std::string message) {
        /* No message to put on the board */
        if (message.empty()) {return;}
        /* get max row & max col with the input length */
        if (empty_board) {
            /* Place the board in the appropriate location and init first character */
            col_space = column;
            row_space = row;
            lowest_filled_row = row;
            largest_filled_row = row;
            lowest_filled_col = column;
            largest_filled_col = column;
            my_board.push_back("_");
            empty_board = false;
        }
        /* getting the new board measurement according to the input */
        uint min_row = row;
        uint min_col = column;
        uint max_row = row;
        uint max_col = column;
        uint length = message.length();
        if (direction == Direction::Vertical) {max_row = row + length - 1;}
        else {max_col = column + length - 1;}
        /* resize the current board according to the new board measurement */
        resize_board(row, column, max_row, max_col);
        row_space = lowest_filled_row;
        col_space = lowest_filled_col;
        /* write the string to the board */
        if (direction == Direction::Vertical) {
            for (uint i = 0; i < message.length(); i++) {
               my_board[row+i-row_space][column-col_space] = message[i];
            }
        } else {
            for (uint i = 0; i < message.length(); i++) {
               my_board[row-row_space][column+i-col_space] = message[i];
            }
        }
    }

    std::string Board::read(uint row, uint column, Direction direction, uint length) {
        /* build result string */
        string result;
        if (direction == Direction::Vertical) {
            for (uint i = 0; i < length; i++) {
                if ((row+i)>=lowest_filled_row&&(row+i)<=largest_filled_row
                &&column>=lowest_filled_col&&column<=largest_filled_col) {
                        result+=my_board[row+i-row_space][column-col_space];
                    }
                else {result.append("_");}
            }
        } else { /* horizontal direction */
            for (uint i = 0; i < length; i++) {
                if ((column+i)>=lowest_filled_col&&(column+i)<=largest_filled_col
                &&row>=lowest_filled_row&&row<=largest_filled_row) {
                    result+=my_board[row-row_space][column+i-col_space];
                    }
                else {result.append("_");}
            }
        }
        return result;
    }

    void Board::show() {
        cout << "#> Board Output:" << '\n';
        if (empty_board) {
            cout << " _\n| |\n|_|\n";
            cout << "#> Actual-Rows-Number: 0\n";
            cout << "#> Actual-Cols-Number: 0\n\n";
        }
        else { /* non-empty board */
            uint number_len = to_string(largest_filled_row).length();
            cout << ' ';
            for (uint i = lowest_filled_col; i <= largest_filled_col; i++) {cout << "_";}
            for (uint i = 0; i < number_len+2; i++) {cout << "_";}
            cout << '\n';
            for (uint i = lowest_filled_row; i <= largest_filled_row; i++) {
                string curr_num = to_string(i)+":";
                while (curr_num.length()<number_len+1) {curr_num.append(" ");}
                cout << "|"+curr_num << " "+my_board[i-row_space].substr(lowest_filled_col-col_space,largest_filled_col-col_space+1)+"|" << '\n'; 
            }
            cout << '|';
            for (uint i = lowest_filled_col; i <= largest_filled_col; i++) {cout << "_";}
            for (uint i = 0; i < number_len+2; i++) {cout << "_";}
            cout << "|\n#> Actual-Rows-Number: "+to_string(my_board.size()) << '\n';
            cout << "#> Actual-Cols-Number: "+to_string(my_board[0].size())+"\n\n";
        }
    }
}