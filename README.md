# Albegmi_CSCI2270_FinalProject


### Project:
## Created by Bandar Albegmi
My project is going to be about our campus map and is going to
include many known building that a student wants to walk around them
so it is going to be including

 - Norlin
 - Engineering
 - Recreation center
 - UMC
 - Business
 - Fleming

 My project will have two methods we studyed in class graphing method and Queue Method
 so it will have a search method(queueing) where student goes from certain building to another
 building and i'm going to use(dijkestra's) the shortest path to certain building to walk to.
simply i will apply these method in my project :
- Add Vertex:
    add edge to map
- Add Edge:
    Add vertex to graph
- Breadth_First_Search:
    searching in map using Breadth_First_Search
- Depth_First_Traversal:
    printing all the vertices depth first traversal procedure
- Depth_First_Traversal_Recursive:
    printing all the vertices within depth first recursive traversal procedure.
- Search:
    printing all the adjacent vertices within depth first recursive traversal procedure
- Breadth_First_Traversal:
    prints all the vertices within breadth first traversal procedure
- Dijkstra:
    finding the shortest weighted path between two buildings in the map
- Delete Edge:
    deleting an edge between vertices
- Delete Vertex:
    deleting a vertex from the map.
- Display Edges

I am going to have a struct like vertex which going to incude for example: name of building ,a visited boolen, distance,
vector <adjV> adj is Vector where you can store all adjacent vertices and
a previousV which is a pointer where we can use it in Dijkstra algrathim
