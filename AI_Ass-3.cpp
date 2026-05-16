#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>
using namespace std;

class DSU {
    vector<int> parent, rankv;
public:
    DSU(int n){
        parent.resize(n);
        rankv.resize(n,0);
        for(int i=0;i<n;i++) parent[i]=i;
    }

    int find(int x){
        if(parent[x]!=x)
            parent[x]=find(parent[x]);
        return parent[x];
    }

    void unite(int a,int b){
        a=find(a);
        b=find(b);
        if(a!=b){
            if(rankv[a]<rankv[b]) swap(a,b);
            parent[b]=a;
            if(rankv[a]==rankv[b]) rankv[a]++;
        }
    }
};

void dijkstra(){
    int V,E;
    cout<<"Enter vertices and edges: ";
    cin>>V>>E;

    vector<vector<pair<int,int>>> adj(V);

    cout<<"Enter edges (u v weight):\n";
    for(int i=0;i<E;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    int src,dst;
    cout<<"Enter source and destination: ";
    cin>>src>>dst;

    priority_queue<pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>> pq;

    vector<int> dist(V,1e9), parent(V);

    for(int i=0;i<V;i++) parent[i]=i;

    dist[src]=0;
    pq.push({0,src});

    while(!pq.empty()){
        auto [d,node]=pq.top();
        pq.pop();

        if(d>dist[node]) continue;

        for(auto &edge:adj[node]){
            int nxt=edge.first;
            int wt=edge.second;

            if(dist[node]+wt<dist[nxt]){
                dist[nxt]=dist[node]+wt;
                pq.push({dist[nxt],nxt});
                parent[nxt]=node;
            }
        }
    }

    if(dist[dst]==1e9){
        cout<<"No path exists\n";
        return;
    }

    cout<<"Shortest distance: "<<dist[dst]<<endl;

    vector<int> path;
    int cur=dst;

    while(parent[cur]!=cur){
        path.push_back(cur);
        cur=parent[cur];
    }
    path.push_back(src);

    reverse(path.begin(),path.end());

    cout<<"Path: ";
    for(int x:path) cout<<x<<" ";
    cout<<endl;
}


void selectionSort(){
    int n;
    cout<<"Enter number of elements: ";
    cin>>n;

    vector<int> arr(n);

    cout<<"Enter elements:\n";
    for(int i=0;i<n;i++)
        cin>>arr[i];

    // Selection Sort
    for(int i=0;i<n-1;i++){
        int minIdx=i;

        for(int j=i+1;j<n;j++){
            if(arr[j]<arr[minIdx])
                minIdx=j;
        }

        swap(arr[i],arr[minIdx]);
    }

    cout<<"Sorted Array: ";
    for(int x:arr)
        cout<<x<<" ";
    cout<<endl;
}


void kruskalMST(){
    int V,E;
    cout<<"Enter vertices and edges: ";
    cin>>V>>E;

    vector<tuple<int,int,int>> edges;

    cout<<"Enter edges (u v weight):\n";
    for(int i=0;i<E;i++){
        int u,v,w;
        cin>>u>>v>>w;
        edges.push_back({w,u,v});
    }

    sort(edges.begin(),edges.end());

    DSU dsu(V);
    int totalCost=0;

    for(auto &e:edges){
        int w,u,v;
        tie(w,u,v)=e;

        if(dsu.find(u)!=dsu.find(v)){
            dsu.unite(u,v);
            totalCost+=w;
        }
    }

    cout<<"Total MST cost (Kruskal): "<<totalCost<<endl;
}


struct Job{
    int id,deadline,profit;
};

bool cmp(Job a,Job b){
    return a.profit>b.profit;
}

void jobScheduling(){
    int n;
    cout<<"Enter number of jobs: ";
    cin>>n;

    vector<Job> jobs(n);
    int maxDeadline=0;

    cout<<"Enter job id, deadline, profit:\n";
    for(int i=0;i<n;i++){
        cin>>jobs[i].id>>jobs[i].deadline>>jobs[i].profit;
        maxDeadline=max(maxDeadline,jobs[i].deadline);
    }

    sort(jobs.begin(),jobs.end(),cmp);

    vector<int> slot(maxDeadline+1,-1);
    int totalProfit=0;

    for(auto &job:jobs){
        for(int j=job.deadline;j>0;j--){
            if(slot[j]==-1){
                slot[j]=job.id;
                totalProfit+=job.profit;
                break;
            }
        }
    }

    cout<<"Selected Jobs: ";
    for(int i=1;i<=maxDeadline;i++)
        if(slot[i]!=-1)
            cout<<slot[i]<<" ";

    cout<<"\nTotal Profit: "<<totalProfit<<endl;
}


int main(){
    int choice;

    do{
        cout<<"\nGreedy Algorithms Menu\n";
        cout<<"1. Dijkstra Shortest Path\n";
        cout<<"2. Selection Sort\n";
        cout<<"3. Kruskal MST\n";
        cout<<"4. Job Scheduling\n";
        cout<<"5. Exit\n";
        cout<<"Enter choice: ";
        cin>>choice;

        switch(choice){
            case 1: 
                dijkstra(); 
                break;
            case 2: 
                selectionSort(); 
                break;
            case 3: 
                kruskalMST(); 
                break;
            case 4: 
                jobScheduling(); 
                break;
            case 5: 
                cout<<"Exiting...\n"; 
                break;
            default: 
                cout<<"Invalid choice\n";
        }

    }while(choice!=5);

    return 0;
}


// This code shifts the focus from Uninformed/Informed Searches to **Greedy Search/Optimization Algorithms**, which falls directly under *Unit 2: Heuristic Search & Greedy Algorithms* in the SPPU AI curriculum. A greedy algorithm makes the locally optimal choice at each stage with the hope of finding a global optimum.

// Here are 15 highly relevant oral (viva) questions focusing strictly on Dijkstra, Job Scheduling, and Selection Sort within the context of AI theory.

// ---

// ## 💡 Category 1: AI Theory & The Greedy Approach

// ### 1. What makes an algorithm "Greedy" in Artificial Intelligence? How do Dijkstra, Job Scheduling, and Selection Sort fit this?

// * **Answer:** A greedy algorithm constructs a solution piece-by-piece, choosing the next option that offers the **most immediate (local) benefit** without considering the long-term consequences.
// * **Dijkstra:** Universally picks the unvisited node with the absolute smallest calculated distance.
// * **Job Scheduling:** Selects jobs sequentially based strictly on the highest profit.
// * **Selection Sort:** Repeatedly finds and extracts the minimum element remaining in the unsorted portion.



// ### 2. Do Greedy Algorithms always guarantee a globally optimal solution in AI environments?

// * **Answer:** No, they do not always yield the global optimum. However, for specific problems that exhibit the **Greedy Choice Property** and **Optimal Substructure**, they do guarantee optimality. For instance, Dijkstra and Job Scheduling (using this specific deadline layout) yield optimal results, whereas greedy heuristics applied to problems like the Traveling Salesperson Problem (TSP) usually yield suboptimal approximations.

// ### 3. How does Dijkstra’s algorithm relate to A* Search?

// * **Answer:** Dijkstra’s algorithm is fundamentally a special, unguided variant of A* Search. In A*, the evaluation function is $f(n) = g(n) + h(n)$. Dijkstra behaves exactly like A* when the heuristic estimation is stripped away entirely ($h(n) = 0$), relying only on the accumulated path cost $g(n)$.

// ---

// ## ⏱️ Category 2: Algorithm Breakdown & Complexities

// ### 4. What is the Time and Space Complexity of your Dijkstra implementation?

// * **Answer:**
// * **Time Complexity:** $O((V + E) \log V)$ because every edge is evaluated, and pushing/popping from the binary min-heap (`priority_queue`) takes $O(\log V)$ time.
// * **Space Complexity:** $O(V + E)$ to store the adjacency list representation alongside the auxiliary structures (`dist`, `parent`, and `pq`).



// ### 5. Why does Dijkstra’s algorithm fail or misbehave if a graph contains negative edge weights?

// * **Answer:** Dijkstra is built on a core greedy assumption: once a node is popped from the priority queue, its shortest path from the source is finalized. If negative weights exist, a longer path found later could actually reduce the overall cost of a finalized node, rendering the greedy choice incorrect.

// ### 6. What is the Time Complexity of your Job Scheduling algorithm?

// * **Answer:**
// * Sorting the $N$ jobs based on profit takes $O(N \log N)$ time.
// * For each job, the code scans backward from its deadline to find an empty time slot, taking $O(N \times \text{maxDeadline})$ in the worst case.
// * Thus, the total time complexity is **$O(N \log N + N \cdot D)$**, where $D$ is the maximum deadline.



// ### 7. What is the Time and Space Complexity of Selection Sort?

// * **Answer:**
// * **Time Complexity:** $\Theta(N^2)$ across the best, average, and worst-case scenarios because the nested loops execute completely regardless of how the initial array is ordered.
// * **Space Complexity:** $O(1)$ auxiliary space, since it sorts the array elements in place without allocating new memory structures.



// ---

// ## 💻 Category 3: Implementation & Code Logic

// ### 8. In Dijkstra, what is the exact purpose of the conditional statement `if (d > dist[node]) continue;`?

// * **Answer:** This line handles obsolete entries inside the priority queue. Since C++'s standard `std::priority_queue` lacks an internal `decreaseKey` operations capability, the code pushes a brand-new pair whenever a shorter path to an existing node is discovered. This check discards the older, outdated distance copies when they are popped.

// ### 9. Why is the `slot` vector in the Job Scheduling method searched in a backward direction (`for (int j=job.deadline; j>0; j--)`)?

// * **Answer:** To maximize total profit, jobs should be delayed as close to their deadlines as possible. Scheduling a job at its latest permissible slot leaves earlier slots open for other high-paying jobs with tighter deadlines.

// ### 10. How does Selection Sort make a "Greedy Choice" during each pass?

// * **Answer:** It splits the array into sorted and unsorted segments. In every pass, it scans the unsorted segment with a pure greedy strategy: *Find the absolute smallest value right now and swap it to the front.* It does not care if this swap messes up the order of the remaining unsorted elements.

// ---

// ## 🎯 Category 4: Structural Alternatives & Comparisons

// ### 11. How can the Time Complexity of the Job Scheduling algorithm be optimized beyond the current approach?

// * **Answer:** The backward search for an empty time slot can be optimized from $O(D)$ down to nearly $O(1)$ by utilizing a **Disjoint Set Union (DSU)** data structure. Each slot can point to the next available vacant slot before it, allowing immediate allocation.

// ### 12. If a graph is unweighted, would you still opt for Dijkstra’s algorithm to find the shortest path?

// * **Answer:** No, for an unweighted graph, **Breadth-First Search (BFS)** is the preferred choice. BFS finds the shortest path in linear time $O(V + E)$, skipping the logarithmic sorting overhead ($O(\log V)$) incurred by Dijkstra's min-priority queue.

// ### 13. Which classic AI strategy is Selection Sort comparable to when visualizing state space exploration?

// * **Answer:** Selection Sort mirrors **Greedy Best-First Search**. It evaluates the remaining unsorted states and instantly commits to the node that seems best according to its basic heuristic (the minimum value), without building out alternative exploration branches.

// ### 14. What would happen in your Job Scheduling program if two entirely different jobs had the exact same profit and deadline?

// * **Answer:** The sorting step (`sort(jobs.begin(), jobs.end(), cmp)`) doesn't enforce strict ordering for identical values. Whichever job appears first in the original input vector will be processed first. It takes the latest available slot, and the second job takes the slot right before it (if available).

// ### 15. In your Dijkstra function, how do you reconstruct and print the actual path sequence rather than just the final distance?

// * **Answer:** The code populates a tracking vector named `parent`, where `parent[nxt] = node` captures the immediate predecessor. Once the algorithm terminates, the program traces backward from `dst` to `src` using this map, storing the sequence in a vector and reversing it to display the path from start to finish.