#ifndef MAP_H
#define MAP_H
#include <vector>
#include <iostream>
using namespace std;
struct vertex;  //Struct declaration of vertex

//Struct to store all adjacent vertices to one vertex
struct adjVertex{
    vertex * x;
    int weight; //Store the weight between the vertices
};
//Vertex struct
struct vertex{
    string name;
    bool visited;   //If the vertex has been visited
    int distance;   //Distance from a starting vertex
    vector<adjVertex> adj; //Vector to store all adjacent vertices
    vertex * previous;   //Pointer to point to the previous vertex for use in Dijkstra's algorithm
    int areaIndex; //Integer to store the ID of the vertex district
    int erasedIndex;   //Integer to store if a vertex was erased
};

//Queue vertex used in Dijkstra'a algorithm
struct queueVertex{
    int distance;
    vector<vertex> way;
};

//Map class declaration
class Map{
public:
    Map();    //Constructor
    ~Map();   //Destructor
    void addEdge(string v1, string v2, int weight);   // Add edge to Map
    void addVertex(string name);   //Add vertex to Map
    void breadthFirstSearch(string startbuilding, string endbuilding); //Search the Map using breadth-first search
    void depthFirstTraversal(string startbuilding);  //Search the Map using depth-first search non-recursive
    void dijkstra(string startbuilding, string endbuilding);  //Search the Map and find shortest distance using Dijkstra's algorithm
    void breadthFirstTraversal(string startbuilding);  //Traverse the Map according to the breadth first procedure
    void findAreas(string startbuilding);  //Method to assign all of the vertices a district
    void deleteEdge(string startbuilding, string endbuilding);    //Method to delete an edge between vertices
    void deleteVertex(string building);    //Method to delete a vertex from the Map
    void displayEdges();    //Display all edges and vertices

protected:
private:
    //vector<edge> edges;
    vector<vertex> vertices;   //Vector store all vertices
    int areaIndexIndex;

    void search(vertex x);  //Algorithm used with depth-first search recursive

};
#endif // MAP_H
