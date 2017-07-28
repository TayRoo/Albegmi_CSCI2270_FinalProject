#include "Map.h"
#include <string>
#include <iostream>
#include <queue>
#include <stack>
#include <limits.h>

using namespace std;

Map::Map(){
    areaIndexIndex = 1;    //Index to keep track of how many Areas
}
Map::~Map(){
}
void Map::addVertex(string name){
    bool found = false; //Variable to check if the vertex has been already created
    //Loop through all of the vertices
    for(int i = 0; i < vertices.size(); i++){
        //If the name has been associated with a vertex
        if(vertices[i].name == name){
            found = true;
            cout<<"======| "<< vertices[i].name<<" is found  |======"<<endl;
        }
    }
    //If the name was not already associated with a vertex
    //Add it to vertices and update the vertex information via the vertex struct
    if(found == false){
        vertex x;
        x.name = name;
        x.distance = 0;
        x.areaIndex = -1;
        vertices.push_back(x);
    }
}
void Map::addEdge(string v1, string v2, int weight){
    for(int i = 0; i < vertices.size(); i++){
        //when starting building matches v1
        if(vertices[i].name == v1){
            // looking for v2
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex adjV;
                    adjV.x = &vertices[j];
                    adjV.weight = weight;
                    vertices[i].adj.push_back(adjV);
                    adjVertex adjX;
                    adjX.x = &vertices[i];
                    adjX.weight = weight;
                    vertices[j].adj.push_back(adjX);
                }
            }
        }
    }
}
void Map::breadthFirstSearch(string building1, string building2){
    vector<vertex> way;    //Vector to store the current way of shortest way
    int distance;   //Integer to store tmporary distance of way

    vertex *startingbuilding = NULL;
    vertex *endingbuilding = NULL;

    vertex y;

    //Boolean to storing when building A and B were found
    bool buildings1 = false;
    bool buildings2 = false;

    queue<queueVertex> shortestwayQueue;   //Queue to store the current way and distance

    //looking for building A and B
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].name == building1)
        {
            buildings1 = true;
            startingbuilding = &vertices[i];
        }
        else if (vertices[i].name == building2){
            buildings2 = true;
            endingbuilding = &vertices[i];
        }
    }

    if (buildings1 == false || buildings2 == false){
        cout << "Same buildings or one or more buildings doesn't exist " << endl;
    }
    if(startingbuilding->areaIndex == -1){
        cout << "Areas have not been initialized" << endl;
    }
    else if(startingbuilding->areaIndex != endingbuilding->areaIndex){
        cout << "The two buildings are in different Areas" << endl;
    }

    if (buildings1 && buildings2){
        // Set the starting building to visited and the rest to the not visited
        for (int i = 0; i < vertices.size(); i++){
            if (vertices[i].name != startingbuilding->name){
                vertices[i].visited = false;
            }
            else {
                vertices[i].visited = true;
            }

        }
        startingbuilding->visited = true;

        queueVertex qx;

        qx.distance = 0;
        qx.way.push_back(*startingbuilding);

        shortestwayQueue.push(qx);

        while (!(shortestwayQueue.empty())){
            qx = shortestwayQueue.front();
            shortestwayQueue.pop();

            vertex * x = NULL;

            int endway = qx.way.size();

            for (int i = 0; i < qx.way[endway-1].adj.size(); i++){
                x = qx.way[endway-1].adj[i].x;

                if (x->visited == false){
                    way = qx.way;
                    x->visited = true;

                    distance = qx.distance + 1;
                    way.push_back(*x);

                    // tmp queue vertex with the new way and distance
                    queueVertex tmp;
                    tmp.way = way;
                    tmp.distance = distance;

                    //when the end vertex has been found
                    if (x->name == building2){
                        cout << tmp.distance << ", "; //returning tmp
                        for (int j = 0; j < tmp.way.size(); j++){
                            if(j != tmp.way.size()-1)
                                cout << " " << tmp.way[j].name << ", ";
                            else
                                cout << " " << tmp.way[j].name;
                        }
                    }
                    else{
                        //Add the tmp way to the queue
                        shortestwayQueue.push(tmp);
                    }

                }
            }
        }
        cout << endl;
    }
}
void Map::depthFirstTraversal(string startbuilding){
    int tracker = 0;    //Integer to store the number of vertices visited
    vertex *startingbuilding = NULL;   //Vertex to store the starting vertex

    bool building1 = false;

    for (int i = 0; i < vertices.size(); i ++){
        vertices[i].visited = false;

        if (vertices[i].name == startbuilding){
            startingbuilding = &vertices[i];
            vertices[i].visited = true;
            building1 = true;
        }
    }
    if(building1 == false){
        cout << "The building was not found" << endl;
        return;
    }

    if(startingbuilding->areaIndex == -1){
        cout << "Areas have not been initialized" << endl;
        return;
    }
    vertex y;
    stack<vertex> depthStack;
    depthStack.push(*startingbuilding);

    while (!(depthStack.empty())){
        y = depthStack.top();
        depthStack.pop();

        tracker++;
        if (tracker == 10){
            cout << y.areaIndex << ":" << y.name << endl;
        }
        else{
            cout << y.areaIndex << ":" << y.name << " ";
        }

        for (int i = 0; i < y.adj.size(); i++){
            if (y.adj[i].x->visited == false){
                y.adj[i].x->visited = true;
                depthStack.push(*y.adj[i].x);
            }
        }
    }
    cout << endl;
}
void Map::search(vertex y){
    y.visited = true;   //Set the sent in vertex to be visited

    //Loop through all adjacent vertices to y
    for (int i = 0; i < y.adj.size(); i++){
        if (y.adj[i].x->visited == false){
            y.adj[i].x->visited = true;

            bool visited = true;
            for (int i = 0; i < vertices.size(); i ++){
                if (vertices[i].visited == false){
                    visited = false;
                }
            }
            if (visited){
                cout << y.adj[i].x->areaIndex << ":" << y.adj[i].x->name << endl;
            }
            else {
                cout << y.adj[i].x->areaIndex << ":" << y.adj[i].x->name << " ";
            }
            search(*y.adj[i].x);
        }
    }
}
void Map::breadthFirstTraversal(string startbuilding){
    vertex *startingbuilding = NULL;

    bool building1 = false;

    for (int i = 0; i < vertices.size(); i ++){
        vertices[i].visited = false;
        if (vertices[i].name == startbuilding){
            startingbuilding = &vertices[i];
            vertices[i].visited = true;
            building1 = true;
        }
    }
    if(building1 == false){
        cout << "The building was not found" << endl;
        return;
    }

    if(startingbuilding->areaIndex == -1){
        cout << "Areas have not been initialized" << endl;
        return;
    }
    cout << startingbuilding->areaIndex << ":" << startingbuilding->name << " ";

    vertex y;

    queue<vertex> breadthQueue;
    breadthQueue.push(*startingbuilding);

    while (!(breadthQueue.empty())){
        y = breadthQueue.front();
        breadthQueue.pop();
        for (int i = 0; i < y.adj.size(); i++){
            if (y.adj[i].x->visited == false){
                y.adj[i].x->visited = true;

                bool visited = true;

                for (int i = 0; i < vertices.size(); i ++){
                    if (vertices[i].visited == false){
                        visited = false;
                    }
                }
                if (visited){
                    cout << y.adj[i].x->areaIndex << ":" << y.adj[i].x->name << endl;
                }
                else{
                    cout << y.adj[i].x->areaIndex << ":" << y.adj[i].x->name << " ";
                }
                //Push the adjacent vertex onto the queue
                breadthQueue.push(*y.adj[i].x);
            }
        }
    }
    cout << endl;
}
void Map::dijkstra(string startbuilding, string endbuilding){
    // tmp for starting and ending building
    vertex A;
    A.name = "NULL";
    vertex B;
    B.name = "NULL";

    vertex *finalbuilding;      for (int i = 0; i < vertices.size(); i++){
        if(startbuilding == vertices[i].name){
            A = vertices[i];
        }

        if(endbuilding == vertices[i].name && endbuilding != startbuilding){
            B = vertices[i];
        }
    }

    if(A.name == "NULL" || B.name == "NULL"){
        cout << "One or more buildings doesn't exist or the start and end building are the same" << endl;
        return;
    }

    if(A.areaIndex == -1){
        cout << "Areas have not been initialized" << endl;
        return;
    }
    else if(A.areaIndex != B.areaIndex){
        cout << "The two buildings are in different Areas" << endl;
        return;
    }

    vertex *startingbuilding = NULL;
    vertex tmp;

    int minDistance = 0;

    for(int j = 0; j < vertices.size(); j++){
        vertices[j].visited = false;
        vertices[j].previous = NULL;
        vertices[j].distance = 0;
    }
    A.visited = false;
    B.visited = false;

    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == startbuilding){
            vertices[i].visited = true;
            vertices[i].previous = NULL;
            startingbuilding = &vertices[i];
            break;
        }
    }

    startingbuilding->visited = true;
    startingbuilding->distance = 0;
    startingbuilding->previous = NULL;

    int minIndex = -1;
    int minAdjIndex = -1;

    int distance;

    vector <vertex*> solved;
    solved.push_back(startingbuilding);

    while(B.visited == false){
        minDistance = INT_MAX;

        for(int k = 0; k < solved.size(); k++){
            for(int a = 0; a < solved[k]->adj.size(); a++){
                if(solved[k]->adj[a].x->visited == false){
                    distance = solved[k]->distance+solved[k]->adj[a].weight;

                    if(minDistance == INT_MAX){
                        minDistance = distance;
                        minIndex = k;
                        minAdjIndex = a;
                    }
                    else if(minDistance > distance){
                        minDistance = distance;
                        minIndex = k;
                        minAdjIndex = a;
                    }
                }
            }
        }

        solved[minIndex]->adj[minAdjIndex].x->distance = minDistance;
        solved[minIndex]->adj[minAdjIndex].x->visited = true;
        solved[minIndex]->adj[minAdjIndex].x->previous = solved[minIndex];
        finalbuilding = solved[minIndex]->adj[minAdjIndex].x;
        if(solved[minIndex]->adj[minAdjIndex].x->name == B.name)
            B.visited = true;
        solved.push_back(solved[minIndex]->adj[minAdjIndex].x);
    }
    vector<vertex*> finalway;

    cout << minDistance << ", ";

    while (finalbuilding != NULL){
        finalway.push_back(finalbuilding);
        finalbuilding = finalbuilding->previous;
    }

    for (int j = finalway.size()-1; j >= 0; j--){
        if(j != 0)
            cout << finalway[j]->name << ", ";
        else
            cout << finalway[j]->name << endl;
    }

    return;
}
void Map::findAreas(string startbuilding){
    vertex startingbuilding;
    bool foundbuilding = false;


    for (int j = 0; j < vertices.size(); j++){
        if(vertices[j].areaIndex == -1)
            vertices[j].visited = false;
    }

    for (int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == startbuilding){
            foundbuilding = true;
            vertices[i].visited = true;
            vertices[i].areaIndex = areaIndexIndex;
            startingbuilding = vertices[i];
            break;
        }
    }

    if (!foundbuilding){
        cout << "The building does not exist" << endl;
        return;
    }


    startingbuilding.visited = true;

    queue <vertex> districtQueue;


    districtQueue.push(startingbuilding);

    while (!districtQueue.empty()){

        vertex y = districtQueue.front();
        districtQueue.pop();

        for(int a = 0; a < y.adj.size(); a++){
            if(y.adj[a].x->visited == false){

                y.adj[a].x->visited = true;
                y.adj[a].x->areaIndex = areaIndexIndex;

                districtQueue.push(*y.adj[a].x);
            }
        }
    }

    for(int i = 0; i < vertices.size(); i++){

        if(vertices[i].visited == false){
            areaIndexIndex++;
            findAreas(vertices[i].name);
        }
    }
}
void Map::deleteEdge(string startbuilding, string endbuilding){
    vertex *startingbuilding = NULL;
    vertex *endingbuilding = NULL;

    bool foundStart = false;
    bool foundEnd = false;

    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == startbuilding){
            startingbuilding = &vertices[i];
            foundStart = true;
        }

        if(vertices[i].name == endbuilding && startbuilding != endbuilding){
            endingbuilding = &vertices[i];
            foundEnd = true;
        }

    }
    //buildings not found
    if(!foundEnd || !foundStart){
        cout << "Same buildings or one of our buildings doesn't exist" << endl;
    }

    if(startingbuilding->areaIndex == -1){
        cout << "Areas have not been initialized" << endl;
    }
    else if(startingbuilding->areaIndex != endingbuilding->areaIndex && (startingbuilding->erasedIndex != -10 && endingbuilding->erasedIndex != -10)){
        cout << "The two buildings have different Areas" << endl;
    }

    //Boolean is good to use here because we need to store if the vertices are adjacent
    bool adjacentVertices = false;

    //Looping through all the adjacent vertices for starting building and if end building is found, erase it
    for(int i = startingbuilding->adj.size()-1; i >= 0; i--){
        if(startingbuilding->adj[i].x->name == endbuilding){
            startingbuilding->adj.erase(startingbuilding->adj.begin()+i);
            adjacentVertices = true;
            break;
        }
    }

    //If the vertices are not adjacent
    if(!adjacentVertices){
        cout << "The vertices are not adjacent" << endl;
        return;
    }

    //Looping through all the adjacent vertices to ending building and deleting starting building
    for (int i = endingbuilding->adj.size()-1; i >= 0; i--){
        if(endingbuilding->adj[i].x->name == startbuilding){
            endingbuilding->adj.erase(endingbuilding->adj.begin()+i);
            break;
        }
    }
    //Refinding  all the Areas for our Map
    areaIndexIndex = 1;
    for(int i = 0; i < vertices.size(); i++)
        vertices[i].areaIndex = -1;
    
    findAreas(startbuilding);
}
void Map::deleteVertex(string building){
    vertex *x = NULL;   //Vertex to store the building to be deleted
    bool foundbuilding = false;
    //Loop through the vertices and find the vertex
    for (int i = 0; i < vertices.size(); i++){
        if (vertices[i].name == building){
            x = &vertices[i];
            foundbuilding = true;
            vertices[i].erasedIndex = -10;
        }
    }

    if(!foundbuilding){
        cout << "Building doesn't exist" << endl;
    }
    if(x->areaIndex == -1){
        cout << "Areas have not been initialized" << endl;
    }
    //Deleting all of the adj vertexes to which is being deleted
    x->adj.erase(x->adj.begin(), x->adj.end());
    //Deleting any edges that are connected to the vertex if there is
    for (int i = 0; i < vertices.size(); i ++){
        for (int k = 0; k < vertices[i].adj.size(); k++){
            if (vertices[i].adj[k].x->name == building){
                deleteEdge(vertices[i].name, vertices[i].adj[k].x->name);
            }
        }
    }
    for (int i = 0; i < vertices.size(); i++){
        if (vertices[i].name == building){
            vertices[i].name = "";
            vertices[i].erasedIndex = -10;
            vertices[i].distance = 0;
        }
    }
}
void Map::displayEdges(){
    //looping through out all vertices and through all adjacent vertices as well
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name != ""){
            if(vertices[i].areaIndex == -1){
                cout << "Areas have not been initialized" << endl;
                return;
            }
            cout<<vertices[i].areaIndex << ":" << vertices[i].name<<"-->";
            for(int j = 0; j < vertices[i].adj.size(); j++){
                cout<<vertices[i].adj[j].x->name;
                if(j != vertices[i].adj.size()-1)
                    cout << "***";
            }
            cout<<endl;
        }
    }
}
