#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

struct Node
{
    /* data */
    int x,y;
    int g,h,f;
};

struct Compare{
    bool operator()(Node const& a,Node const& b){
        return a.f>b.f;
    }
};

int heuristic(int sx,int sy,int ex,int ey){
    return abs(sx-ex)+abs(sy-ey);
}

void printPath(int sx,int sy,int ex,int ey,vector<vector<pair<int,int>>> &parent){
    vector<pair<int,int>> path;
    int x=ex;
    int y=ey;
    if(parent[ex][ey].first==-1 && !(sx==ex && sy==ey)){
    cout<<"No path exists\n";
    return;
}
    while(!(x==sx && y==sy)){
        path.push_back({x,y});
        int px = parent[x][y].first;
        int py = parent[x][y].second;

        x = px;
        y = py;
    }
    path.push_back({sx,sy});
    reverse(path.begin(),path.end());
    cout << "\nPath:\n";
    for (auto &p : path)
        cout << "(" << p.first << "," << p.second << ") ";
    cout << endl;

    cout << "Distance: " << path.size() - 1 << endl;
}

int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};

void aStar(int sx,int sy,int ex,int ey,vector<vector<int>>& maze,int n,int m){
    priority_queue<Node,vector<Node>,Compare> open;
    vector<vector<int>> closed(n,vector<int>(m,0));
    vector<vector<int>> gCost(n,vector<int>(m,1e9));
    vector<vector<pair<int,int>>> parent(n,vector<pair<int,int>>(m,{-1,-1}));
    open.push({sx,sy,0,heuristic(sx,sy,ex,ey),heuristic(sx,sy,ex,ey)});
    gCost[sx][sy]=0;
    while(!open.empty()){
        Node top=open.top();
        int x=top.x;
        int y=top.y;
        open.pop();
        if(x==ex && y==ey){
            printPath(sx,sy,ex,ey,parent);
            return;
        }
        if(closed[x][y]==1){
            continue;
        }
        closed[x][y]=1;
        for(int i=0;i<4;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];
            if(nx>=0 && nx<n && ny>=0 && ny<m && maze[nx][ny]==1){
                int newG=gCost[x][y]+1;
                if(gCost[nx][ny]>newG){
                    gCost[nx][ny]=newG;
                    parent[nx][ny]={x,y};
                    int h=heuristic(nx,ny,ex,ey);
                    open.push({nx,ny,newG,h,h+newG});
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

            aStar(sx, sy, ex, ey,maze, n, m);
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
