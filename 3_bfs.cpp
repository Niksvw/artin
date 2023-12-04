#include<bits/stdc++.h>
using namespace std;

// A Node class for GBFS Pathfinding
class Node{
public:
    int v, weight;
    Node(int V, int Weight){
        v=V;
        weight=Weight;
    }
};
// pathNode class will help to store
// the path from src to dest.
class pathNode{
public:
    int node;
    pathNode *parent;
    pathNode(int Node){
        node=Node;
        parent=NULL;
    }
    pathNode(int Node, pathNode *Parent){
        node=Node;
        parent=Parent;
    }
};

// Declaring the adjacency list;
static vector<vector<Node*>> adj;

// Function to add edge in the graph.
void addEdge(int u, int v, int weight){
    // Add edge u -> v with weight weight.
    adj[u].push_back(new Node(v, weight));
}

// Greedy best first search algorithm function
vector<int> GBFS(int h[], int V, 
                        int src, int dest){
    /* This function returns a list of 
        integers that denote the shortest
        path found using the GBFS algorithm.
        If no path exists from src to dest, we will return an empty list.
        */
    // Initializing openList and closeList.
    vector<pathNode*> openList;
    vector<pathNode*> closeList;

    // Inserting src in openList.
    openList.push_back(new pathNode(src));

    // Iterating while the openList 
    // is not empty.

    while(!openList.empty()){

        pathNode *currentNode = openList[0];
        int currentIndex = 0;
        // Finding the node with the least 'h' value.

        for(int i = 0; i < openList.size(); i++){
            if(h[openList[i]->node] <
                    h[currentNode->node]){
                currentNode = openList[i];
                currentIndex = i;
            }
        }

        // Removing the currentNode from 
        // the openList and adding it in 
        // the closeList.
        openList.erase(openList.begin() + currentIndex);
        closeList.push_back(currentNode);
        
        // If we have reached the destination node.
        if(currentNode->node == dest){
            // Initializing the 'path' list. 
            vector<int> path;
            pathNode *cur = currentNode;

            // Adding all the nodes in the 
            // path list through which we have
            // reached to dest.
            while(cur != NULL){
                path.push_back(cur->node);
                cur = cur->parent;
            }

            // Reversing the path, because
            // currently it denotes path
            // from dest to src.
            reverse(path.begin(), path.end());
            return path;
        }

        // Iterating over adjacents of 'currentNode'
        // and adding them to openList if 
        // they are neither in openList or closeList.
        for(Node *node: adj[currentNode->node]){
            for(pathNode *x : openList){
                if(x->node == node->v) continue;
            }
            for(pathNode *x : closeList){
                if(x->node == node->v) continue;
            }
            openList.push_back(new pathNode(node->v, currentNode));
        }
    }
    
    return vector<int>();
}
int main(){
    
    /* Making the following graph
                src = 0
                / | \
               /  |  \
              1   2   3
             /\   |   /\
            /  \  |  /  \
           4    5 6 7   8
                   /
                  /
                dest = 9
    */
    // Total number of vertices.
    int V = 10;
    adj.resize(V);

    addEdge(0, 1, 2);
    addEdge(0, 2, 1);
    addEdge(0, 3, 10);
    addEdge(1, 4, 3);
    addEdge(1, 5, 2);
    addEdge(2, 6, 9);
    addEdge(3, 7, 5);
    addEdge(3, 8, 2);
    addEdge(7, 9, 5);
    
    // Defining the heuristic values for each node.
    int h[] = {20, 22, 21, 10, 
            25, 24, 30, 5, 12, 0};
    vector<int> path = GBFS(h, V, 0, 9);
    for(int i = 0; i < path.size() - 1; i++){
        cout << path[i] << " --> ";
    }
    cout << path[path.size()-1] << endl;

    return 0;
}
