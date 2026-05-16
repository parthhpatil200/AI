#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
#include<algorithm>
using namespace std;

struct Node{
    int x,y;
    int g,h,f;
};
struct Compare
{
    bool operator()(const Node& a,const Node& b){
        return a.f>b.f;
    }
};

int heuristic(int sx,int sy,int ex,int ey){
    return abs(sx-ex) + abs(sy-ey);
}

void printPath(int sx,int sy,int ex,int ey,vector<vector<pair<int,int>>> &parent){
    int x=ex,y=ey;
    vector<pair<int,int>> path;
    while(!(x==sx && y==sy)){
        path.push_back({x,y});
        auto p=parent[x][y];
        x=p.first;
        y=p.second;
    }
    reverse(path.begin(),path.end());
    cout << "\nPath:\n";
    for (auto &p : path)
        cout << "(" << p.first << "," << p.second << ") ";
    cout << endl;

    cout << "Distance: " << path.size() - 1 << endl;
}

void aStar(int sx,int sy,int ex,int ey,int n,int m,vector<vector<int>> &maze){
    priority_queue<Node,vector<Node>,Compare> open;
    vector<vector<int>> closed(n,vector<int>(m,0));
    vector<vector<int>> gCost(n,vector<int>(m,1e9));
    vector<vector<pair<int,int>>> parent(n,vector<pair<int,int>>(m,{-1,-1}));
    open.push({sx,sy,0,heuristic(sx,sy,ex,ey),heuristic(sx,sy,ex,ey)});
    gCost[sx][sy]=0;
    int drow[4]={-1,0,1,0};
    int dcol[4]={0,1,0,-1};
    while(!open.empty()){
        Node curr=open.top();
        open.pop();
        int x=curr.x;
        int y=curr.y;
        if(closed[x][y]) continue;
        closed[x][y]=1;
        if(x==ex && y==ey){
            printPath(sx,sy,ex,ey,parent);
            return;
        }
        for(int k=0;k<4;k++){
            int nx=x+drow[k];
            int ny=y+dcol[k];
            if(nx>=0 && ny>=0 && nx<n && ny<m && maze[nx][ny]==1 && !closed[nx][ny]){
                int newG=gCost[x][y]+1;
                if(gCost[nx][ny]>newG){
                    gCost[nx][ny]=newG;
                    int h=heuristic(nx,ny,ex,ey);
                    open.push({nx,ny,newG,h,newG+h});
                    parent[nx][ny]={x,y};
                }
            }
        }
    }

    cout<<"No Path Found"<<endl;
}

int main(){
    
}