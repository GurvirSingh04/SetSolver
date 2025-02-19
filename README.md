# SetSolver

SetSolver is a number puzzle similar to Sudoku, played on a 9x9 board where white and black cells are partially filled with numbers. The goal is to fill the empty white cells according to specific rules. This program fills the board's empty white cells while adhering to the provided rules.

## Puzzle Rules

- Rows and columns are divided into compartments. A compartment is a series of uninterrupted white cells.
- Each compartment needs to be filled with an unordered but uninterrupted set of numbers (1-9).
- Compartments do not necessarily need to continue each other's numbers.
- Numbers within a compartment can appear in any order.
- No single number can repeat in any row or column (irrespective of compartments).

## Inputs

To represent the board, a vector of strings (`vector<std::string>`) is used. The representation includes:

- Empty black square as `0`
- Empty white square as `*`
- Black square with a number as the negative of that number

### Example Board Representation

```cpp
vector<string> easyBoard = {"00**0-31*0",
                            "*****0**0",
                            "7*003*-5**",
                            "**05**7**",
                            "*0**0*6-9*",
                            "4***650**",
                            "*2-8**00**",
                            "-23*0*****",
                            "043-608*0-1"};
```

## Example Usage

```cpp
unique_ptr<SetSolver> board(new SetSolver());
vector<string> skeletonBoard{ "00**0-31*0",
                              "*****0**0",
                              "7*003*-5**",
                              "**05**7**",
                              "*0**0*6-9*",
                              "4***650**",
                              "*2-8**00**",
                              "-23*0*****",
                              "043-608*0-1"};

board->PopulateBoard(skeletonBoard);
board->Solve();
```

## Output

```
{0,0,6,7,0,-3,1,2,0},
{6,7,5,8,4,0,2,3,0},
{7,8,0,0,3,4,-5,1,2},
{8,9,0,5,2,6,7,4,3},
{5,0,1,2,0,7,6,-9,4},
{4,1,2,3,6,5,0,8,7},
{3,2,-8,4,5,0,0,7,6},
{-2,3,4,0,7,9,8,6,5},
{0,4,3,-6,0,8,9,0,-1}
```

In the output:
- Positive numbers represent filled white squares.
- Negative numbers represent numbered black squares.
- Zeroes represent empty black squares.

