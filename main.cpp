#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <queue>
#include <stack>
#include <limits.h>
#include "Map.h"

using namespace std;

int main()
{
    ifstream in_file;    // variable used later to open file
    string stringLine;     // variable in order for storing line by line from the text file
    string * buildings;     // Dynamic array in order for storing each building
    int ** buildingDistanceValues;    //Dynamic two dimension array in order for storing distances or weight between buildings


    int numberOfLines = -1;  // variable so it stores the number of lines in our file

    Map M;    // create an instance of the Map class

    in_file.open("Map.txt");    //Open the file to read our text

    if(in_file.fail()){
        cout << "File did not open." << endl;
        return -1;
    }
    else{
        //While not at end of the file, get each line and increment the line counter
        while(in_file.good()){
            getline(in_file, stringLine);
            numberOfLines++;
        }

        // seting up both dynamic arrays
        buildings = new string [numberOfLines-1];
        buildingDistanceValues = new int *[numberOfLines-1]; //Initialize first dimension of two dimension array
        //setting up second dimension of twoD array
        for(int i = 0; i < numberOfLines-1; i++)
            buildingDistanceValues[i] = new int[numberOfLines-1];

        // clearing the file and resetting to beginning of file to read in data
        in_file.clear();
        in_file.seekg(0, ios::beg);

        // To get the first line of our file
        getline(in_file, stringLine);

        // Find all of the commas in the first line
        int comma1 = stringLine.find(',');
        int comma2 = stringLine.find(',', comma1+1);

        for(int i = 0; i < numberOfLines-1; i++)
        {
            //Loop through just the first line adding in all buildings to the buildings array
            buildings[i] = stringLine.substr(comma1+1, comma2-comma1-1);
            comma1 = comma2;
            comma2 = stringLine.find(',', comma2+1);
        }
        //Create variable line length to get the last building name in the file without getting the extra \r sequence
        //int lineLength = stringLine.substr(comma1+1).length();
        //buildings[numberOfLines-2] = stringLine.substr(comma1+1, lineLength-1);

        int index = 0;  //Variable to keep track of all of the lines traversed in the file

        while(in_file.good()){
            //Get line in file
            getline(in_file, stringLine);

            int comma3 = stringLine.find(',');
            int comma4 = stringLine.find(',', comma3+1);

            //Loop through the remaining lines and add all numerical values to the 2d array
            //Update the comma values for each numerical value
            for(int i = 0; i < numberOfLines-1; i++){
                buildingDistanceValues[index][i] = atoi(stringLine.substr(comma3+1, comma4-comma3-1).c_str());
                comma3 = comma4;
                comma4 = stringLine.find(',', comma4+1);
            }
            index++;
            if(index == numberOfLines-1)
                break;
        }
    }
    in_file.close();
    // Adding all Buildings to our Map as vertices
    for(int w = 0; w < numberOfLines-1; w++){
        M.addVertex(buildings[w]);
    }
    //Loop through the 2d array and add all edges on the Map between vertices
    for(int i = 0; i < numberOfLines-1; i++){
        for(int j = 0; j < numberOfLines-1; j++){
            // Just to make sure that distance value is bigger than 0
            if(buildingDistanceValues[i][j] > 0){
                M.addEdge(buildings[i], buildings[j], buildingDistanceValues[i][j]);
                // Just in case if there is an edge was created already then set corresponding value as -10 so that two edges wont created for same vertices
                buildingDistanceValues[j][i] = -10;
            }
        }
    }
    cout << "This program is containing numbers of building in our beautful campus and a group of ways connecting to these buildings." << endl;
    cout << "If all of the buildings we have in the text file are connected by the ways they" << endl <<  "will be in the same Area, therefore, after deleting some buildings" << endl << "and the ways to Areas could change." << endl;
    cout << "We can delete buildings and also ways" << endl << "and print out buildings by some good tools around our Map through algorithms." << endl << endl;

LOOP:while(1 == 1){
    // Printing our main menu the different options
    cout << "||=======||= Main Menu ==||======||" << endl;
    cout << "1. Show All Buildings" << endl;
    cout << "2. Print Buildings" << endl;
    cout << "3. Compute Areas" << endl;
    cout << "4. Find Shortest Way" << endl;
    cout << "5. Find Shortest Distance" << endl;
    cout << "6. Delete Direction " << endl;
    cout << "7. Delete Building" << endl;
    cout << "8. Quit" << endl;

    // get what user chooses and called it "choice"
    string choice = "";
    getline(cin, choice);
    if(choice == "1"){
        M.displayEdges();
    }
    else if(choice == "2"){
        cout << "1. Breadth First Traversal" << endl;
        cout << "2. Depth First Traversal" << endl;
        string building1;
        choice = "";
        getline(cin, choice);
        if (choice == "1"){
            cout << "What building are you at?" << endl;
            getline(cin, building1);
            choice = "";
            M.breadthFirstTraversal(building1);
        }
        else if (choice == "2"){
            cout << "What building are you at?" << endl;
            getline(cin, building1);
            choice = "";
            M.depthFirstTraversal(building1);
        }
/*        else if (choice == "3"){
            cout << "What building are you at?" << endl;
            getline(cin, building1);
            choice = "";
            M.depthFirstTraversalRecursive(building1);
        }
*/
    }
    else if(choice == "3"){
        choice = "";
        M.findAreas(buildings[0]);
        cout << "Number is showing in front of all buildings when" << endl << "Printing them out is the Area it is in." << endl;
    }
    else if(choice == "4"){
        // Two variables in order to keep tracking of each building
        string building1;
        string building2;
        // Finding shortest way between two building by breadth-first
        cout << "What building are you at?" << endl;
        getline(cin, building1);
        cout << "Where do you want to walk to?" << endl;
        getline(cin, building2);
        choice = ""; // To Reset choice value everytime
        M.breadthFirstSearch(building1, building2);
    }
    else if(choice == "5"){
        // Finding the shortest distance between 2 buildings by Dijkstra  algorithm
        string building1;
        string building2;
        cout << "What building are you at?" << endl;
        getline(cin, building1);
        cout << "Where do you want to walk to?" << endl;
        getline(cin, building2);
        M.dijkstra(building1, building2);
    }

    else if(choice == "6"){
        // Deleting the edge between 2 vertices
        string building1;
        string building2;
        cout << "Enter a starting building:" << endl;
        getline(cin, building1);
        cout << "Enter an adjacent building:" << endl;
        getline(cin, building2);
        choice = "";

        M.deleteEdge(building1, building2);
    }
    else if(choice == "7"){
        // Deleting a vertex from our Map
        string building1;
        cout << "Enter a starting building:" << endl;
        getline(cin, building1);
        choice = "";
        M.deleteVertex(building1);
    }

    else if (choice == "8"){
        // once user Quiting wish him/her best luck
        cout << "Have a good day ,Goodbye!" << endl;
        return 0;
    }

    else{
        //when user puts an invalid thing
        cout << "What you chose is invalid input, Please restart from Main Menu" << endl;
        goto LOOP;
    }

}
    return 0;
}
