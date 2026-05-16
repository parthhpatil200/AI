#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class SocialNetwork{
    int V;
    vector<vector<int>> adj;
    public:
    SocialNetwork(int v){
        V=v;
        adj.resize(V);
    }

    void addFriendship(int u,int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void DFSUtil(int start){
        vector<bool> visited(V,false);
        DFS(start,visited);
        cout<<endl;
    }
    void DFS(int node,vector<bool>& visited){
        visited[node]=true;
        cout<<node<<" ";
        for(int neighbour:adj[node]){
            if(!visited[neighbour]){
                DFS(neighbour,visited);
            }
        }
    }

    void BFS(int start){
        vector<bool> visited(V,false);
        queue<int> q;
        q.push(start);
        visited[start]=true;
        while(!q.empty()){
            int front=q.front();
            q.pop();
            cout<<front<<" ";
            for(int neighbour:adj[front]){
                if(!visited[neighbour]){
                    visited[neighbour]=true;
                    q.push(neighbour);
                }
            }
        }
    }
};

int main(){
    int users,choice;
    cout<<"Enter the number of users in the network: ";
    cin>>users;
    SocialNetwork network(users);
    while(true){
        cout<<"=====SOCIAL NETWORK MENU======"<<endl;
        cout<<"1. Add friendship in the network."<<endl;
        cout<<"2. Perform the DFS traversal."<<endl;
        cout<<"3. Perform the BFS traversal."<<endl;
        cout<<"4. Exit "<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice){
            case 1:
                int u,v;
                cout<<"Enter the numbers for the 2 users to be add friendship between them: ";
                cin>>u>>v;
                if(u>=0 && u<users && v>=0 && v<users){
                    network.addFriendship(u,v);
                }
                else{
                    cout<<"Invalid user ids!"<<endl;
                }
                break;
            case 2:
                cout<<"Enter the user id from where DFS traversal needs to start: ";
                int n;
                cin>>n;
                if(n>=0 && n<users){
                    network.DFSUtil(n);
                }
                else{
                    cout<<"Invalid user id!"<<endl;
                }
                break;
            case 3:
                cout<<"Enter the user id from where BFS traversal needs to start: ";
                int n;
                cin>>n;
                if(n>=0 && n<users){
                    network.BFS(n);
                }
                else{
                    cout<<"Invalid user id!"<<endl;
                }
                break;
            case 4:
                cout<<"Exiting......"<<endl;
                return 0;
            default:
                cout<<"Invalid input!"<<endl;
                break;
        }
    }
}