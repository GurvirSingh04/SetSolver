#ifndef SET_SOLVER_SQUARE_SET_H
#define SET_SOLVER_SQUARE_SET_H

#include <vector>
using std::vector;

class SetSolverSquareSet {
public:
    vector<int> set;

    SetSolverSquareSet() {
        for (int i = 1; i <= 9; ++i) {
            set.push_back(i);
        }
    }

    void setNum(int num) {
        set.clear();
        set.push_back(num);
    }


    int getNum() const {
        return set.empty() ? -1 : set[0];
    }
};

#endif /* SET_SOLVER_SQUARE_SET_H */
