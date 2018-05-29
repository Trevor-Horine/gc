/*This is a program that allows the user to add and remove verticies and edges as well as calculate the minimum distance between 2 \
verticies.
Author: Trevor Horine
5/20/18
*/
#include <iostream>
#include <cstring>
#include <climits>

using namespace std;

// Method to print adj[][]
void print(char* vert[20], int adj[20][20]){
  for(int i = -1; i < 20; i++){
    if(i != -1) {
      if(vert[i]){
        cout << vert[i] << "\t";
      }
    }
    for(int j = 0; j < 20; j++){
      if(i == -1){
        if(vert[j]){
          cout << "\t" << vert[j];
        }
      }
      else{
        if(vert[i] && vert[j]){
          if(adj[i][j] != -1){
            cout << adj[i][j];
          }
          else if(i == j){
            cout << "0";
          }
          else{
            cout << " ";
          }
          cout << "\t";
        }
      }
    }
    if(vert[i]){
      cout << endl;
    }
  }
}

//method to add a vertex to vert[]
void addVertex(char* vert[20]){
  int i = -1;
  while(vert[++i]);
  cout << "Enter the name of the vertex you would like to add." << endl;
  char* in = new char[10];
  cin >> in;
  vert[i] = in;
}

//method to and edge between verticies
void addEdge(char* vert[20], int adj[20][20]){
  char* first = new char[15];
  int firsti = -1;
  char* second = new char[15];
  int secondi = -1;
  int weight = -1;
  cout << "Enter the name of the vertex you want to start at." << endl;
  cin >> first;
  cout << "Enter the name of the vertex you want to end at." << endl;
  cin >> second;
  for(int i = 0; i < 20; i++){
    if(vert[i]){
      if(strcmp(first, vert[i]) == 0){
        firsti = i;
      }
      if(strcmp(second, vert[i]) == 0){
        secondi = i;
      }
    }
  }
  cout << "Enter the weight of the edge you want to make." << endl;
  cin >> weight;
  if(firsti == -1 || secondi == -1 || weight == -1){
    cout << "Something went wrong." << endl;
    return;
  }
  adj[firsti][secondi] = weight;
}

//method to remove vertices
void removeVertex(char* vert[20], int adj[20][20]){
  cout << "Enter the name of the vertex you would like to remove." << \
endl;
  char* in = new char[15];
  cin >> in;
  for(int i = 0; i < 20; i++){
    if(vert[i]){
      if(strcmp(in, vert[i]) == 0){
        delete vert[i];
        vert[i] = NULL;
        for(int j = 0; j < 20; j++){
          adj[i][j] = -1;
          adj[j][i] = -1;
        }
        return;
      }
    }
  }
  cout << "That vertex could not be found." << endl;
}

//method to remove edges between verticies
void removeEdge(char* vert[20], int adj[20][20]){
  char* first = new char[15];
  int firsti = -1;
  char* second = new char[15];
  int sencondi = -1;
  cout << "Enter the name of the beginning of the edge you want to delete." << endl;
  cin >> first;
  cout << "Enter the name of the end of the edge you want to delete." << endl;
  cin >> second;
  for(int i = 0; i < 20; i++){
    if(vert[i]){
      if(strcmp(first, vert[i]) == 0){
        firsti = i;
      }
      if(strcmp(second, vert[i]) == 0){
        sencondi = i;
      }
    }
  }
  if(firsti == -1 || sencondi == -1 || adj[firsti][sencondi] == -1){
    cout << "Something is definatly not right here." << endl;
    return;
  }
  adj[firsti][sencondi] = -1;
}

//method to print the shortest distance and the shortest path
void outputList(char* vert[20], int prev[], int start, bool last = true){
  if(prev[start] != -1){
    outputList(vert, prev, prev[start], false);
  }
  if(vert[start]){
    cout << vert[start];
  }
  if(!last){
    cout << " -> ";
  }
}

//method to find the shortest distance between the 2 verticies
void distance(char* vert[20], int adj[20][20]){
  char* start = new char[15];
  int starti = -1;
  char* end = new char[15];
  int endi = -1;
  cout << "Enter the name of the vertex you want to start at." << endl;
  cin >> start;
  cout << "Enter the name of the vertex you want to end at." << endl;
  cin >> end;
  int maxi = 0;
  for(int i = 0; i < 20; i++){
    if(vert[i])
      maxi = i;
  }
  for(int i = 0; i <= maxi; i++){
    if(vert[i]){
      if(strcmp(start, vert[i]) == 0){
        starti = i;
      }
      if(strcmp(end, vert[i]) == 0){
        endi = i;
      }
    }
  }
  if(starti == -1 || endi == -1){
    cout << "Something is definatly not right here." << endl;
    return;
  }
 bool visited[maxi+1] = {false};
  int dist[maxi+1] = {INT_MAX};
  int prev[maxi+1] = {-1};
  bool remaining = false;
  for(int i = 0; i <= maxi; i++){
    if(vert[i]){
      dist[i] = INT_MAX;
      prev[i] = -1;
      visited[i] = false;
      remaining = true;
    }
    else{
      visited[i] = true;
    }
  }
  dist[starti] = 0;
  while(remaining == true){
    int minDist = INT_MAX;
    int mini = -1;
    for(int i = 0; i <= maxi; i++){
      if(!visited[i] && minDist > dist[i]){
        minDist = dist[i];
        mini = i;
      }
    }
    if(mini == -1){
      break;
    }
    visited[mini] = true;
    for(int i = 0; i <= maxi; i++){
      if(adj[mini][i] != -1){
        int maybe = dist[mini] + adj[mini][i];
        if(maybe < dist[i]){
          dist[i] = maybe;
          prev[i] = mini;
        }
      }
    }
    remaining = false;
    for(int i = 0; i <= maxi; i++){
      if(!visited[i]){
        remaining = true;
      }
    }
  }
  if(dist[endi] == INT_MAX){
    cout << "There is no path between those verticies." << endl;
    return;
  }
  cout << "Minimum distance: " << dist[endi] << endl << "Path: ";
  outputList(vert, prev, endi);
  cout << endl;
}
//main method
int main(){
  char* vert[20] = {(char*)""};
  int adj[20][20] = {{-1}};
  for(int i=0; i < 20; i++){
    vert[i] = NULL;
    for(int j=0; j < 20; j++){
      adj[i][j] = -1;
    }
  }
  bool run = true;
  while(run == true){
    char in[10];
    cout << "would you like to find the distance, add, remove, print, or quit? " << endl;;
    cin >> in;
    for(int i = 0; i < 10; i++){
      in[i] = toupper(in[i]);
    }
    if(strcmp(in, "ADD") == 0){
      cout << "Do you want to add a vertex or edge?" << endl;
      cin >> in;
      for(int i = 0; i < 10; i++){
        in[i] = toupper(in[i]);
      }
      if(strcmp(in, "VERTEX") == 0){
        addVertex(vert);
      }
      else if(strcmp(in, "EDGE") == 0){
        addEdge(vert, adj);
      }
    }
    else if(strcmp(in,"REMOVE") == 0){
      cout << "Do you want to remove a vertex or edge?" << endl;
      cin >> in;
      for(int i = 0; i < 10; i++){
        in[i] = toupper(in[i]);
      }
      if(strcmp(in, "VERTEX") == 0){
        removeVertex(vert, adj);
      }
      else if(strcmp(in, "EDGE") == 0){
        removeEdge(vert, adj);
      }
    }
    else if(strcmp(in, "PRINT") == 0){
      print(vert, adj);
    }
    else if(strcmp(in, "DISTANCE") == 0){
      distance(vert, adj);
    }
    else if(strcmp(in, "QUIT") == 0){
      run = false;
    }
  }
  return 0;
}
