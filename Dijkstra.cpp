#include<cstdlib>
#include<bits/stdc++.h>
#include<ctime>
using namespace std;

class Graph{
 private:
 int V; //number of verticies
 list<pair<int,int>> * array; //An array to contain list of pairs(STL)
 public:
  //Constructor
    Graph(int V)
    {
        this->V=V;
        array=new  list<pair<int,int>>[V];
    }
    //Method to get the number of verticies
    int get_vertex()
    {
        return V;
    }
    //Method to connect the verticies
    void addEdge(int i,int j,int w)
    {
        array[i].push_back(make_pair(j,w));
        array[j].push_back(make_pair(i,w));
    }
    //Method to check if source and destination nodes are connected or not.
    //It returns a boolean true if those are connected or false if not.
    //In this method BFS is used to traverse through the graph.
    bool conected(int src,int dest)
    {
       list<int> l;
       bool visited[V];
       for(int i=0;i<V;i++)
       {
           visited[i]=false; //Initially no vertex is visited
       }
       visited[src]=true; //we start with the source vertex and mark it visited
       l.push_back(src);
       while(!l.empty())
       {
           auto it = l.begin();
           int ParentNode= *it;
           l.pop_front();
           //Now we are going to traverse through neighbours of the parent node
           for(auto i =array[ParentNode].begin();i!=array[ParentNode].end();i++)
           {
               int currNbr=i->first;

               //If a neighbor of the current parent node isn't visited yet, then we visit it and push it to the list. 
               if(!visited[currNbr])
               {
                  visited[currNbr]=true;
                  l.push_back(currNbr);
               }
           }
       }
           if(visited[dest])
           return true;
           else
           return false;                 
    }
 void dijkstra (int src,int dest){

vector<int> distance(V,INT_MAX); //The closed set.It will store the distance of each vertex from source.Initially each distance was set to INT_MAX. 
set<pair<int,int>> open; //open set
int Parent[V];// Array to store parent nodes of each vertex
distance[src]=0; //Distance of source vertex is zero
open.insert(make_pair(0,src)); //First element of a pair in open set is distance and second is node
while(!open.empty())
{
 auto it = open.begin();
 int ParentNode = it->second;
 open.erase(it);
 //We now traverse through the neighbors of Parent node.
 for(auto i =array[ParentNode].begin();i!= array[ParentNode].end();i++)
 {
     int v =i->first;
     int w = i->second;
     //We now check if the current distance is greater than the new calculated distance
     if(distance[v]>(w+distance[ParentNode]))
     {
         // We now check if the current neighbour already exist in the open set or not.
         if(distance[v]!=INT_MAX)
         {
             //if exists then erase it
             open.erase(open.find(make_pair(distance[v],v)));
         }
         //upgrade the distance
         distance[v]=w+distance[ParentNode];
         //insert the upgrded neighbour
         open.insert(make_pair(distance[v],v));
         //upgrade the Parent of the neighbour
         Parent[v]=ParentNode;
     }
 }
}
Parent[0]=-1;
//Print the shortest distance b/w source and destination
cout<<"Shortest distance between node "<<src<<" and node "<<dest<<" is : ";
for(int i=0;i<V;i++)
{
    if(i==dest)
    {
        cout<<distance[i]<<"\n";
        
    }
}
list<int> path; //list to contain the shortest path
int i,j=dest;
while (1)
{
    i=Parent[j];
    if(i==src)
    break;
    else
    path.push_front(i);
    j = Parent[i];
    if(j==src)
    break;
    else
    path.push_front(j);  
}
//Printing shortest path
cout<<"Shortest path : "<< src << " -> ";
for(auto x : path)
{
    cout<<x<<"-> ";
}
cout<<dest<<"\n";

}
//Method to print the adjacency list representation of the graph
   void print()
    {
        for(int i=0;i<V;i++)
        {
            cout<<"Head ("<<i<<")->";
            for(auto j : array[i])
            {
                cout<<"("<<j.first<<")"<<j.second<<"->";
            }
            cout<<"NULL\n";
        }
    }

    };

//Function to genarate a 2D matrix or a graph via random number genaration
int** genarate_graph(int v,double d,int min, int max)
{
    int **arr;
    int x = max-min;
    srand(time(0));
    arr = new int*[v];
    for(int i=0;i<v;i++)
    {
        arr[i]=new int[v];
        for(int j=0;j<v;j++)
        {
         double prob=static_cast<double>(rand())/RAND_MAX;
         if((j>i)&&(prob<=d)) // j>i is taken to avoid getting multiple weights for a same edge
         arr[i][j]=rand()%x + min;
         else
         arr[i][j]=0;           
        }
    }
    return arr;
    
}
//Function to convert an adjacancy matrix graph representation to adjacancy list graph representation
void matrixToList(int ** arr,Graph g)
{
    for(int i=0;i<g.get_vertex();i++)
    {
        for(int j=0;j<g.get_vertex();j++)
        {
            
            if(arr[i][j]!=0)
            {
           g.addEdge(i,j,arr[i][j]);
            }
        }
    
    }

}


int main()
{
    int v,src,dest; 
    cout<<"Enter number of verticies : ";
    cin>>v;
    if(v<=0)
    {
        cerr<<"EROR! enter valid nimber of vertices\n";
        return EXIT_FAILURE;
    }
    Graph a(v);//initialization;
    cout<<"\nEnter the probability of an edge to exist : ";
    double d;
    cin>>d;
    if(d<0||d>1)
    {
        cerr<<"EROR! enter a valid probability (0 < Probability < 1)";
        return EXIT_FAILURE;
    }
    int min_dist,max_dist;
    cout<<"\nEnter minimum distance between two nodes :";
    cin>>min_dist;
    cout<<"\nEnter maximum distance between two nodes :";
    cin>>max_dist;
    int ** p = genarate_graph(v,d,min_dist,max_dist);
    matrixToList(p,a);
    cout<<"\nThe adjacancy list representation of the generated graph :\n";
    a.print();
    cout<<"\nEnter source vertex : ";
    cin>>src;
    cout<<"\nEnter destination vertex : ";
    cin>>dest;
    cout<<"\n";
    if(!a.conected(src,dest))
      a.dijkstra(src,dest);
      else
      {
        cerr<<"The source and destination are not connected in the generated graph\n";
        return EXIT_FAILURE;
      }   
    return EXIT_SUCCESS;

}
