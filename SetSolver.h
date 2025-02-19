#ifndef SET_SOLVER_H
#define SET_SOLVER_H

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include "SetSolverSquareSet.h"

using std::vector;
using std::string;

class SetSolver {
private:
    int boardSize = 9;
    vector<vector<SetSolverSquareSet>> board;
    vector<vector<int>> x_used;
    vector<vector<int>> y_used = vector<vector<int>>(boardSize);

public:
    void Solve() {
        SolveSetSolver();
    }

    // Populates the board from a skeleton representation
    void PopulateBoard(const vector<string>& skeletonBoard) {
        for (const auto& row : skeletonBoard) {
            vector<int> x_used_row;
            vector<SetSolverSquareSet> new_row;
            int is_negative = 1;
            int y_counter = 0;

            for (char ch : row) {
                SetSolverSquareSet square;
                if (ch == '*') {
                    square.setNum(99);
                } else if (ch == '0') {
                    square.setNum(0);
                } else if (ch == '-') {
                    is_negative = -1;
                    continue;
                } else {
                    int val = ch - '0';
                    square.setNum(is_negative * val);
                    is_negative = 1;
                    x_used_row.push_back(val);
                    y_used[y_counter % boardSize].push_back(val);
                }
                y_counter++;
                new_row.push_back(square);
            }
            board.push_back(new_row);
            x_used.push_back(x_used_row);
        }
    }

    // Returns the value of a cell
    int ReturnValue(size_t row, size_t col) const {
        return board[row][col].getNum();
    }

private:
    bool SolveSetSolver() {
        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardSize; ++col) {
                if (board[row][col].getNum() == 99) {
                    for (int num = 1; num <= 9; ++num) {
                        if (IsValidMove(row, col, num)) {
                            board[row][col].setNum(num);
                            x_used[row].push_back(num);
                            y_used[col].push_back(num);

                            if (SolveSetSolver()) {
                                return true;
                            }

                            board[row][col].setNum(99);
                            x_used[row].pop_back();
                            y_used[col].pop_back();
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    // Checks if a move is valid
    bool IsValidMove(int row, int col, int num) const {
        auto subgrids = GetSubgrid(row, col);
        return !Contains(x_used[row], num) &&
               !Contains(y_used[col], num) &&
               IsContinuous(subgrids[0], num) &&
               IsContinuous(subgrids[1], num);
    }

    // Retrieves subgrids for continuity checking
    vector<vector<int>> GetSubgrid(int row, int col) const {
        vector<int> x_subgrid;
        vector<int> y_subgrid;

        CollectSubgrid(row, col, x_subgrid, true);
        CollectSubgrid(row, col, y_subgrid, false);

        return {x_subgrid, y_subgrid};
    }

    void CollectSubgrid(int row, int col, vector<int>& subgrid, bool isRow) const {
        int limit = boardSize;
        bool foundCompartment = false;

        for (int i = 0; i < limit; ++i) {
            int num = isRow ? board[row][i].getNum() : board[i][col].getNum();

            if ((isRow ? i : row) == (isRow ? col : i) && num > 0) {
                subgrid.push_back(num);
                foundCompartment = true;
            } else if (num <= 0 && !foundCompartment) {
                subgrid.clear();
            } else if (num <= 0 && foundCompartment) {
                break;
            } else if (num > 0) {
                subgrid.push_back(num);
            }
        }
    }

    // Checks if a subgrid is continuous
    bool IsContinuous(const vector<int>& subgrid, int n) const {
        int max = 0;
        int min = 1000;

        for (int num : subgrid) {
            if (num != 99) {
                if (num > max) max = num;
                if (num < min) min = num;
            }
        }

        int upper_bound = min + subgrid.size() - 1;
        int lower_bound = max - subgrid.size() + 1;
        return lower_bound <= n && n <= upper_bound;
    }

    // Checks if a vector contains a number
    bool Contains(const vector<int>& vec, int num) const {
        for (int element : vec) {
            if (element == num) {
                return true;
            }
        }
        return false;
    }
};

#endif // SET_SOLVER_H
