#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

struct Node {
    int x, y;
    int g, h, f;
};

struct Compare {
    bool operator()(Node const& a, Node const& b) {
        return a.f > b.f;
    }
};

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2); // Manhattan distance
}

void printPath(vector<vector<pair<int,int>>> &parent,
               int sx, int sy, int ex, int ey) {

    vector<pair<int,int>> path;
    int x = ex, y = ey;

    while (!(x == sx && y == sy)) {
        path.push_back({x, y});
        auto p = parent[x][y];
        x = p.first;
        y = p.second;
    }

    path.push_back({sx, sy});
    reverse(path.begin(), path.end());

    cout << "\nPath:\n";
    for (auto &p : path)
        cout << "(" << p.first << "," << p.second << ") ";
    cout << endl;

    cout << "Distance: " << path.size() - 1 << endl;
}

void aStar(vector<vector<int>> &maze, int n, int m,
           int sx, int sy, int ex, int ey) {

    priority_queue<Node, vector<Node>, Compare> open;
    vector<vector<int>> closed(n, vector<int>(m, 0));
    vector<vector<int>> gCost(n, vector<int>(m, 1e9));
    vector<vector<pair<int,int>>> parent(n,
        vector<pair<int,int>>(m, {-1,-1}));

    open.push({sx, sy, 0,
               heuristic(sx, sy, ex, ey),
               heuristic(sx, sy, ex, ey)});

    gCost[sx][sy] = 0;

    while (!open.empty()) {
        Node curr = open.top();
        open.pop();

        int x = curr.x;
        int y = curr.y;

        if (closed[x][y]) continue;
        closed[x][y] = 1;

        if (x == ex && y == ey) {
            printPath(parent, sx, sy, ex, ey);
            return;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < n && ny < m &&
                maze[nx][ny] == 1 && !closed[nx][ny]) {

                int newG = gCost[x][y] + 1;

                if (newG < gCost[nx][ny]) {
                    gCost[nx][ny] = newG;
                    int h = heuristic(nx, ny, ex, ey);

                    open.push({nx, ny, newG, h, newG + h});
                    parent[nx][ny] = {x, y};
                }
            }
        }
    }

    cout << "No path found.\n";
}

int main() {
    int n, m;
    vector<vector<int>> maze;
    int choice;

    while (true) {
        cout << "\n--- MENU ---\n";
        cout << "1. Enter Maze\n";
        cout << "2. Find Shortest Path\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter rows and columns: ";
            cin >> n >> m;

            maze.assign(n, vector<int>(m));

            cout << "Enter maze (0 = wall, 1 = path):\n";
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    cin >> maze[i][j];
        }
        else if (choice == 2) {
            if (maze.empty()) {
                cout << "Enter maze first.\n";
                continue;
            }

            int sx, sy, ex, ey;
            cout << "Enter start cell (row col): ";
            cin >> sx >> sy;

            cout << "Enter end cell (row col): ";
            cin >> ex >> ey;

            if (maze[sx][sy] == 0 || maze[ex][ey] == 0) {
                cout << "Start or end is blocked.\n";
                continue;
            }

            aStar(maze, n, m, sx, sy, ex, ey);
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}


// Moving into **Informed Search Strategies**, this code implements the **A* Search Algorithm** to solve a grid-based maze. This is a core topic in SPPU’s Artificial Intelligence curriculum under *Heuristic Search Techniques*.

// Here are 15 highly relevant oral (viva) questions regarding this implementation to help you prepare.

// ---

// ## 💡 Category 1: Core Heuristic & Evaluation Functions

// ### 1. What is the evaluation function of the A* algorithm? Explain the components used in your code.

// * **Answer:** The evaluation function is $f(n) = g(n) + h(n)$.
// * $g(n)$ is the actual cost incurred to reach the current cell `(x, y)` from the starting cell.
// * $h(n)$ is the heuristic value—an estimated cost from the current cell to the goal cell.
// * $f(n)$ is the total estimated cost of the cheapest solution passing through node $n$.



// ### 2. Your code uses "Manhattan Distance" as the heuristic. Why was this specific metric chosen?

// * **Answer:** Manhattan distance is defined as $|x_1 - x_2| + |y_1 - y_2|$. It is selected because the movement vectors in the code (`dx` and `dy`) restrict transitions to **4 directions** (Up, Down, Left, Right) with no diagonal movement allowed.

// ### 3. What alternative heuristic functions could be used if diagonal movement *was* allowed?

// * **Answer:** If diagonal movement were enabled, we could use:
// * **Euclidean Distance:** $\sqrt{(x_1 - x_2)^2 + (y_1 - y_2)^2}$ (straight-line distance).
// * **Chebyshev / Diagonal Distance:** $\max(|x_1 - x_2|, |y_1 - y_2|)$ if diagonal steps cost the same as orthogonal steps.



// ### 4. What does it mean for a heuristic to be "Admissible"? Is Manhattan distance admissible here?

// * **Answer:** A heuristic is **admissible** if it never overestimates the true cost to reach the goal (it is optimistic). Yes, Manhattan distance is admissible here because, in a grid environment with 4-directional movement and obstacles, the absolute minimum steps required to reach the goal will always be greater than or equal to the straight grid distance.

// ### 5. What does it mean for a heuristic to be "Consistent" (or Monotone)?

// * **Answer:** A heuristic is **consistent** if, for every node $n$ and every successor $n'$ generated by action $a$, the estimated cost of reaching the goal from $n$ is no greater than the step cost of getting to $n'$ plus the estimated cost from $n'$ to the goal: $h(n) \le c(n, a, n') + h(n')$. An admissible heuristic on a grid map like this is almost always consistent.

// ---

// ## ⏱️ Category 2: Algorithm Behavior & Complexities

// ### 6. Under what conditions is the A* algorithm guaranteed to find the optimal path?

// * **Answer:** A* guarantees an optimal solution if:
// * The state space tree/graph has a finite branching factor.
// * Step costs are strictly positive ($c > 0$).
// * The heuristic function $h(n)$ is **admissible** (when using a tree search or maintaining a closed list properly) and **consistent** (for graph search).



// ### 7. What happens to the behavior of A* if you set the heuristic function $h(n) = 0$ everywhere?

// * **Answer:** If $h(n) = 0$, the evaluation function simplifies to $f(n) = g(n)$. At this point, A* drops its intelligence and behaves exactly like **Dijkstra’s Algorithm** (or Breadth-First Search if all edge costs are 1), exploring radially in all directions.

// ### 8. What happens if the heuristic overestimates the cost ($h(n)$ is NOT admissible)?

// * **Answer:** If $h(n)$ overestimates the true cost, the algorithm may prioritize paths that look shorter on paper but are actually sub-optimal. It sacrifices its **optimality** guarantee to run faster, acting more like a Greedy Best-First Search.

// ### 9. What is the worst-case Time and Space Complexity of A* search?

// * **Answer:** In the worst-case scenario (where the heuristic is uninformative), both time and space complexities are **$O(b^d)$**, where $b$ is the branching factor (up to 4 in this grid) and $d$ is the depth of the solution. This is because it may have to store and explore all states in memory.

// ---

// ## 💻 Category 3: Data Structures & Implementation Details

// ### 10. Why did you use a `priority_queue` with a custom `Compare` structure instead of a standard `queue`?

// * **Answer:** A standard queue expands nodes blindly in a First-In, First-Out manner (BFS). A* is an *informed* best-first search; it must always expand the node with the **lowest $f$-cost** first. The `priority_queue` functions as a min-heap, allowing us to extract the node with the minimum $f$ value in $O(\log N)$ time.

// ### 11. What is the role of the `closed` matrix in your function?

// * **Answer:** The `closed` matrix keeps track of nodes that have already been popped from the priority queue and fully evaluated. This prevents processing duplicate paths to the same cell, optimizing the algorithm into a **Graph Search** rather than a Tree Search, which eliminates infinite loops caused by cycles in the grid.

// ### 12. Explain the purpose of the conditional check `if (newG < gCost[nx][ny])`.

// * **Answer:** This check evaluates whether the newly discovered path to the neighbor node `(nx, ny)` through the current cell is cheaper than any previously discovered path to that same neighbor. If it is shorter, we update its `gCost`, recalculate its $f$-value, push the updated node into the open list, and update its `parent` pointer.

// ---

// ## 🎯 Category 4: AI Variations & Comparison Questions

// ### 13. How does A* differ fundamentally from Greedy Best-First Search (GBFS)?

// * **Answer:**
// * **GBFS** evaluates nodes using *only* the heuristic function ($f(n) = h(n)$). It tries to get to the goal as fast as possible, making it faster but prone to suboptimal paths and false leads.
// * **A*** balances historical path cost and future estimates ($f(n) = g(n) + h(n)$), making it mathematically proven to find the shortest path.



// ### 14. What are the main memory limitations of A* search in large-scale AI environments, and how can they be mitigated?

// * **Answer:** Because A* stores all generated nodes in the open and closed structures, it easily runs out of memory on large state spaces long before it runs out of execution time. This can be mitigated using memory-bounded variants like **IDA*** (Iterative Deepening A*) or **SMA*** (Simplified Memory-Bounded A*).

// ### 15. How would you adjust this code to handle varying terrain costs (e.g., muddy cells that cost 5 steps to cross instead of 1)?

// * **Answer:** I would change the value added to `newG`. Instead of a hardcoded increment of `+ 1` (`int newG = gCost[x][y] + 1;`), I would dynamically fetch the terrain cost of the destination cell from the maze matrix, setting `int newG = gCost[x][y] + maze[nx][ny];` (where different non-zero integers represent different movement costs).