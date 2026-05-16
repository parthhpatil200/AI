#include <iostream>
#include <vector>
using namespace std;

class NQueens {
private:
    int N;
    vector<vector<int>> board;

    vector<bool> column;
    vector<bool> diag1;   
    vector<bool> diag2;   
    vector<vector<string>> solutions;


    void solve(int row) {
        if (row == N) {
            vector<string> temp;
            for (int i = 0; i < N; i++) {
                string s = "";
                for (int j = 0; j < N; j++) {
                    s += (board[i][j] ? 'Q' : '.');
                }
                temp.push_back(s);
            }
            solutions.push_back(temp);
            return;
        }

        
        for (int col = 0; col < N; col++) {

            if (column[col] || diag1[row - col + N - 1] || diag2[row + col])
                continue;

            board[row][col] = 1;
            column[col] = true;
            diag1[row - col + N - 1] = true;
            diag2[row + col] = true;

            solve(row + 1);

            board[row][col] = 0;
            column[col] = false;
            diag1[row - col + N - 1] = false;
            diag2[row + col] = false;
        }
    }

public:
    NQueens(int n) {
        N = n;
        board.assign(N, vector<int>(N, 0));
        column.assign(N, false);
        diag1.assign(2 * N - 1, false);
        diag2.assign(2 * N - 1, false);
    }

    void run() {
        solve(0);

        cout << "Total Solutions: " << solutions.size() << "\n\n";

        for (int k = 0; k < solutions.size(); k++) {
            cout << "Solution " << k + 1 << ":\n";
            for (auto row : solutions[k])
                cout << row << endl;
            cout << endl;
        }
    }
};

int main() {
    int n;
    cout << "Enter value of N: ";
    cin >> n;

    NQueens obj(n);
    obj.run();

    return 0;
}


// This code moves into **Constraint Satisfaction Problems (CSPs)** and **Backtracking Search**, which belongs to *Unit 3: Advanced Search Topics / Constraint Satisfaction Problems* in the SPPU Artificial Intelligence syllabus. The N-Queens problem is the absolute textbook example used to explain how AI agents explore state spaces while satisfying global constraints.

// Here are 15 tailored oral (viva) questions focusing on the AI and architectural concepts of this assignment.

// ---

// ## 💡 Category 1: AI Theory & Constraint Satisfaction Problems (CSPs)

// ### 1. How is the N-Queens problem defined as a Constraint Satisfaction Problem (CSP) in AI?

// * **Answer:** A CSP consists of three components: Variables ($X$), Domains ($D$), and Constraints ($C$).
// * **Variables:** The $N$ queens, where each variable $X_i$ represents the queen in row $i$.
// * **Domains:** The column indices $\{0, 1, \dots, N-1\}$ that each queen can occupy.
// * **Constraints:** No two queens can share the same column, primary diagonal, or secondary diagonal.



// ### 2. What search strategy does this code use? How does it differ from a brute-force search?

// * **Answer:** It uses **Backtracking Search**, which is a Depth-First Search variant tailored for CSPs.
// * A **brute-force** search would generate all possible board configurations ($N^{N}$ or even $\binom{N^2}{N}$) and check them at the end.
// * **Backtracking** evaluates constraints incrementally. If a partial assignment violates a constraint, it immediately discards that entire branch (pruning), saving immense computation time.



// ### 3. What is "Pruning" in a state-space tree, and how is it happening in this code?

// * **Answer:** Pruning means cutting off branches of the search tree that are guaranteed to not lead to a valid solution. In your code, the `if (column[col] || diag1[...] || diag2[...]) continue;` statement performs pruning. If a clash is detected, the recursive call `solve(row + 1)` is skipped, effectively dropping that entire subtree.

// ### 4. How does N-Queens differ from the traveling salesperson or short-path optimization tasks we looked at earlier?

// * **Answer:** Pathfinding and optimization tasks look for an *optimal sequence of actions* to achieve a target goal state with minimum cost. CSPs like N-Queens care strictly about the *final goal state* itself. The steps taken to reach the configuration do not matter; the state must simply satisfy all constraints.

// ---

// ## ⏱️ Category 2: Complexity Analysis (SPPU Edge Cases)

// ### 5. What is the worst-case Time Complexity of this N-Queens implementation?

// * **Answer:** The upper bound is $O(N!)$. In the first row, you have $N$ choices; in the second row, at most $N-1$ choices; in the third, $N-2$, and so on. While pruning lowers the average number of states visited drastically, the mathematical upper bound remains factorial.

// ### 6. What is the Space Complexity of your implementation? What contributes to it?

// * **Answer:** The space complexity is **$O(N^2)$** to store the board and the list of successful solutions. If we only consider the runtime memory needed to solve the puzzle, it is $O(N)$ for the lookup vectors (`column`, `diag1`, `diag2`) and the recursive call stack which caps at a depth of $N$.

// ### 7. Why is N-Queens considered a hard computational problem in AI?

// * **Answer:** It belongs to the class of problems where the state space explodes combinatorially as $N$ increases. For example, $N=4$ has only 2 solutions, but $N=8$ has 92, and $N=16$ has over 14.7 million solutions. Finding all solutions quickly becomes intractable for classical backtracking.

// ---

// ## 💻 Category 3: Code Logic & CSP Optimizations

// ### 8. Explain the mathematical logic behind the index calculation for `diag1[row - col + N - 1]`.

// * **Answer:** In a 2D matrix, all cells along any given major diagonal (top-left to bottom-right) share the same value for the expression $(row - col)$. The value of $(row - col)$ ranges from $-(N-1)$ to $(N-1)$. Since array indices cannot be negative, we add an offset of $(N - 1)$ to map these values perfectly to a safe 0-indexed range of $0$ to $2N-2$.

// ### 9. Explain the mathematical logic behind the index calculation for `diag2[row + col]`.

// * **Answer:** All cells along any minor diagonal (top-right to bottom-left) share a constant sum of their coordinates, meaning $(row + col)$ is identical for every cell on that diagonal line. The minimum sum is $0$ (top-left corner) and the maximum sum is $2N - 2$ (bottom-right corner), fitting perfectly into a vector of size $2N - 1$.

// ### 10. Why are these boolean arrays (`column`, `diag1`, `diag2`) used instead of a traditional loop validation function?

// * **Answer:** A traditional approach loops backward through preceding rows to verify safety, requiring $O(N)$ operations per placement. By using these lookup vectors as hash maps, validating whether a cell is safe drops to an **$O(1)$ constant time lookup**, significantly speeding up execution.

// ### 11. What part of the code represents the actual "Backtracking" mechanism?

// * **Answer:** Backtracking occurs right after the recursive statement returns:
// ```cpp
// board[row][col] = 0;
// column[col] = false;
// diag1[...] = false;
// diag2[...] = false;

// ```


// When `solve(row + 1)` finishes exploring all paths stemming from the current choice, these lines undo the allocations (reverting them to false/0) to clean up the state before evaluating the next column option.

// ---

// ## 🎯 Category 4: Advanced AI Concepts & Variations

// ### 12. Which CSP heuristic could change the way loops select columns or rows to optimize performance?

// * **Answer:**
// * **Minimum Remaining Values (MRV) Heuristic:** Always select the variable (row) that has the fewest legal values (columns) left.
// * **Degree Heuristic:** Select the variable involved in the largest number of constraints with other unassigned variables.



// ### 13. What is the "Forward Checking" technique in CSPs? Does your code use it?

// * **Answer:** Forward checking looks ahead whenever a variable is assigned, tracking and eliminating conflicting options from the domains of all unassigned variables. Your code doesn't strictly use forward checking; it evaluates constraints reactively at the moment of placement rather than pro-actively narrowing down domain sets ahead of time.

// ### 14. For massive inputs (like $N=1000$), backtracking stalls. What alternative AI search approaches can solve it?

// * **Answer:** For very large values of $N$, local search strategies like **Hill Climbing**, **Simulated Annealing**, or **Genetic Algorithms** are used alongside a min-conflicts heuristic. They start with a random arrangement of all $N$ queens and iteratively shift conflicting queens to reduce hits, solving huge configurations in seconds.

// ### 15. How would you alter this program if the problem statement asked to print only the *first* valid solution instead of *all* solutions?

// * **Answer:** I would change the return type of the `solve` function from `void` to `bool`. Once a base case (`row == N`) is triggered, it would return `true`. Inside the placement loop, I would check if the child call returns true: `if (solve(row + 1)) return true;`. This unrolls the call stack instantly, halting further exploration.

// ```

// // ```