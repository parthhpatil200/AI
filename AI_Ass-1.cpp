#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class SocialNetwork {
    int V;
    vector<vector<int>> adj;

public:
/*************  ✨ Windsurf Command ⭐  *************/
/**
 * Constructor for SocialNetwork
 * @param V Number of users in the social network
 */
/*******  7735d265-9288-4709-bdea-9fa89f71c331  *******/
    SocialNetwork(int V) {
        this->V = V;
        adj.resize(V);
    }

    // Add friendship (undirected)
    void addFriendship(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // ---------------- DFS (Recursive) ----------------
    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }

    void DFS(int start) {
        vector<bool> visited(V, false);
        cout << "\nDFS Traversal starting from user " << start << ": ";
        DFSUtil(start, visited);
        cout << endl;
    }

    // ---------------- BFS ----------------
    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "\nBFS Traversal starting from user " << start << ": ";

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (int neighbor : adj[v]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }
};

// ---------------- MAIN FUNCTION ----------------
int main() {
    int users, choice, u, v, start;

    cout << "Enter number of users in the social network: ";
    cin >> users;

    SocialNetwork network(users);

    while (true) {
        cout << "\n===== SOCIAL NETWORK MENU =====";
        cout << "\n1. Add Friendship";
        cout << "\n2. Perform DFS";
        cout << "\n3. Perform BFS";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter two users (u v) to add friendship: ";
                cin >> u >> v;

                if (u >= 0 && u < users && v >= 0 && v < users) {
                    network.addFriendship(u, v);
                    cout << "Friendship added successfully.\n";
                } else {
                    cout << "Invalid user IDs!\n";
                }
                break;

            case 2:
                cout << "Enter starting user for DFS: ";
                cin >> start;

                if (start >= 0 && start < users) {
                    network.DFS(start);
                } else {
                    cout << "Invalid starting user!\n";
                }
                break;

            case 3:
                cout << "Enter starting user for BFS: ";
                cin >> start;

                if (start >= 0 && start < users) {
                    network.BFS(start);
                } else {
                    cout << "Invalid starting user!\n";
                }
                break;

            case 4:
                cout << "Exiting program...\n";
                return 0;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}



// This is definitely a classic Data Structures & Algorithms (DSA) problem, but it serves as the foundational bedrock for **Artificial Intelligence** (especially in the SPPU syllabus under *Unit 1: Introduction & Search Strategies*). In AI, graphs represent **State Spaces**, and DFS/BFS are categorized as **Uninformed (Blind) Search Strategies**.

// Here are 15 highly relevant oral (viva) questions tailored to the SPPU AI curriculum, split by category to help you ace your evaluation.

// ---

// ## 💡 Category 1: AI Theory & Search Strategies

// ### 1. Why is this DSA program considered a part of the Artificial Intelligence lab?

// * **Answer:** In AI, problem-solving can be modeled as a **State Space Search**. The users in this social network represent *states*, and the friendships represent *actions/transitions* between states. BFS and DFS are fundamental **Uninformed Search Strategies** used to navigate these state spaces to find a path from an initial state to a goal state.

// ### 2. Differentiate between Uninformed (Blind) and Informed (Heuristic) Search. Where do BFS and DFS fit?

// * **Answer:**
// * **Uninformed Search:** Has no additional information about the distance or cost from the current state to the goal (e.g., BFS, DFS). They explore blindly based only on the graph's structure.
// * **Informed Search:** Uses a evaluation function or heuristic ($h(n)$) to estimate how close a state is to the goal (e.g., A* Search, Greedy Best-First Search).



// ### 3. Is BFS "Complete" and "Optimal"? What about DFS?

// * **Answer:**
// * **BFS:** It is **Complete** (it will always find a solution if one exists, provided the branching factor is finite) and **Optimal** if all edge costs are equal (it finds the shallowest goal).
// * **DFS:** It is **Not Complete** in infinite spaces (it can get stuck in an infinite path/loop if not careful) and **Not Optimal** (it returns the first path it finds, which might be much longer than the shortest path).



// ### 4. What is the "Branching Factor" ($b$) and "Depth" ($d$) in AI search trees? How do they relate to this code?

// * **Answer:**
// * **Branching Factor ($b$):** The maximum number of successors (neighbors) any node can have. In your code, this corresponds to the maximum degree of a user node in the `adj` list.
// * **Depth ($d$):** The length of the shortest path from the root node to the goal node.



// ### 5. What are the major drawbacks of DFS in AI applications? How do we fix them?

// * **Answer:** DFS can get trapped down an infinitely deep or dead-end path, wasting time and resources. In AI, this is fixed using **Depth-Limited Search (DLS)** (setting a maximum depth limit) or **Iterative Deepening DFS (IDDFS)**, which combines the space benefits of DFS with the optimality of BFS.

// ---

// ## ⏱️ Category 2: Complexity Analysis (SPPU Favorites)

// ### 6. What is the Time Complexity of BFS and DFS in this implementation?

// * **Answer:** The time complexity for both is $O(V + E)$, where $V$ is the number of vertices (users) and $E$ is the number of edges (friendships). Every vertex is visited once, and every edge is traversed twice (for an undirected graph) during the adjacency list scan.

// ### 7. What is the Time Complexity of BFS and DFS expressed in AI terms ($b$ and $d$)?

// * **Answer:**
// * **BFS:** $O(b^d)$ because it explores every single node up to depth $d$.
// * **DFS:** $O(b^m)$, where $m$ is the maximum depth of the state space. If $m$ is much larger than $d$, DFS can take significantly longer than BFS.



// ### 8. What is the Space Complexity of your BFS implementation? Explain using AI parameters.

// * **Answer:**
// * **In standard graph terms:** $O(V)$ to store the `visited` array and the `queue`.
// * **In AI terms:** $O(b^d)$ because, in the worst-case scenario, the queue needs to hold all the leaf nodes of the current search depth level. This high memory requirement is BFS's biggest weakness.



// ### 9. What is the Space Complexity of your DFS implementation? Explain using AI parameters.

// * **Answer:**
// * **In standard graph terms:** $O(V)$ for the `visited` array and the recursive call stack.
// * **In AI terms:** $O(b \cdot m)$, where $b$ is the branching factor and $m$ is the maximum depth. DFS only needs to store the current path from the root to the leaf, along with the unchosen sibling nodes for each node on the path. This makes DFS highly memory efficient compared to BFS.



// ---

// ## 💻 Category 3: Code Implementation & Logic

// ### 10. Why did you use a `std::queue` for BFS and Recursion for DFS?

// * **Answer:**
// * BFS explores level-by-level (**FIFO** structure), making a queue the perfect fit to process nodes in the exact order they were discovered.
// * DFS explores depth-first (**LIFO** structure). Recursion naturally utilizes the system's runtime stack to pause execution and dive deeper into a neighbor node before returning back (backtracking).



// ### 11. What is the role of the `visited` vector in your code? What happens if you remove it?

// * **Answer:** The `visited` vector tracks whether a user has already been processed. Since a social network is a cyclic graph (e.g., User A is friends with B, B with C, and C with A), removing the `visited` array would cause both BFS and DFS to fall into an **infinite loop**, resulting in a Segmentation Fault (Stack Overflow) in DFS.

// ### 12. How does your code represent the graph? What is the advantage of this representation?

// * **Answer:** It uses an **Adjacency List** (`vector<vector<int>> adj`).
// * **Advantage:** It is memory efficient ($O(V + E)$) compared to an Adjacency Matrix ($O(V^2)$), especially for a social network which is typically a *sparse graph* (most users are only friends with a tiny fraction of the total user base).



// ---

// ## 🎯 Category 4: Real-World Scenarios & Modifications

// ### 13. If you want to build a "Mutual Friends Suggestion" feature (People You May Know), would you use BFS or DFS? Why?

// * **Answer:** You would use **BFS**. Social connections are based on degrees of separation. Your closest recommendations are friends-of-friends (exactly 2 steps away). BFS naturally explores nodes level-by-level, making it trivial to extract all users at exactly depth 2.

// ### 14. What changes would you make to this code if the social network was "Directed" (like Twitter/X followers instead of Facebook friends)?

// * **Answer:** In the `addFriendship(int u, int v)` function, I would remove the line `adj[v].push_back(u);`. This ensures that the edge only goes one way (from $u$ to $v$), representing that user $u$ follows user $v$, but not necessarily vice versa.

// ### 15. How would you modify your BFS or DFS if you were asked to find the *shortest path* between two users?

// * **Answer:** I would use **BFS** because it guarantees finding the shortest path in an unweighted graph. I would modify the BFS function to maintain a `parent` array where `parent[neighbor] = v`. Once the destination user is found, I can backtrack from the destination to the source using the `parent` array to print the exact path.