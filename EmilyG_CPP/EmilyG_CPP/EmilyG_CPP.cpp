#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include "pathFinding.h"
using namespace std;

//struct to represent an edge between two nodes in the graph
struct Edge 
{
    int from;
    int to;
};

//function to display the graph in a simple text format
void displayGraph(const map<int, set<int>>& adjacencyList) 
{
    cout << "\nGraph Representation (Adjacency List):\n";
    for (const auto& node : adjacencyList) {
        cout << node.first << " -> ";
        for (const auto& neighbor : node.second) {
            cout << neighbor << " ";  //print each connected node
        }
        cout << endl;
    }
}

//function to add an edge to the adjacency list and store it in the edges vector
void addEdge(int from, int to, map<int, set<int>>& adjacencyList, vector<Edge>& edges) 
{
    adjacencyList[from].insert(to);
    adjacencyList[to].insert(from);
    edges.push_back({ from, to });
}

//function to update the CSV file with the current edges in the graph
void updateCSV(const vector<Edge>& edges) 
{
    ofstream file("graph_data.csv");  //open the CSV file
    if (!file.is_open()) 
    {
        cerr << "Could not open the file for writing!" << endl;
        return;
    }

    //write the CSV header
    file << "from,to\n";

    //write each edge
    for (const auto& edge : edges) 
    {
        file << edge.from << "," << edge.to << "\n";
    }

    file.close();
}

int main() 
{
    pathFinding pf;

    //open the CSV file for reading
    ifstream file("graph_data.csv");
    if (!file.is_open()) 
    {
        cerr << "Could not open the file!" << endl;
        return 1;
    }

    string line;
    vector<Edge> edges;
    map<int, set<int>> adjacencyList;

    //skip the header line
    getline(file, line);

    //read the CSV line by line
    while (std::getline(file, line)) 
    {
        stringstream ss(line);
        string from, to;
        
        getline(ss, from, ',');
        getline(ss, to, ',');

        int fromNode = stoi(from);
        int toNode = stoi(to);

        //add the edge to the adjacency list and the edges vector
        addEdge(fromNode, toNode, adjacencyList, edges);
    }

    file.close();

    //print the current edges
    cout << "Current Edges loaded:\n";
    for (const auto& edge : edges) 
    {
        cout << edge.from << " -> " << edge.to << endl;
    }

    //display the adjacency list
    displayGraph(adjacencyList);

    char mainChoice;
    do {
        //ask the user what they want to do
        cout << "\nWhat would you like to do?\n";
        cout << "1. Find a path between two nodes\n";
        cout << "2. Add a new edge\n";
        cout << "Enter your choice (1 or 2): ";
        cin >> mainChoice;

        if (mainChoice == '1') 
        {
            int start, goal;
            cout << "Enter the start node: ";
            cin >> start;
            cout << "Enter the goal node: ";
            cin >> goal;

            //find the path between start and goal nodes
            set<int> path = pf.findPath(adjacencyList, start, goal);

            if (path.empty()) 
            {
                cout << "No path found between " << start << " and " << goal << ".\n";
            }
            else 
            {
                cout << "Path found: ";
                for (int node : path) 
                {
                    cout << node << " ";
                }
                cout << endl;
            }
        }
        else if (mainChoice == '2') 
        {
            //allow user to input new edges
            char edgeChoice;
            do {
                int from, to;
                cout << "\nEnter a new edge (from to): ";
                cin >> from >> to; //input needs to be 2 ints separated by a space
                addEdge(from, to, adjacencyList, edges);  //add the new edge to the graph

                cout << "Edge added: " << from << " -> " << to << endl;
                displayGraph(adjacencyList);  //display the updated graph

                //ask the user if they want to add another edge
                cout << "Do you want to add another edge? (y/n): ";
                cin >> edgeChoice;
            } while (edgeChoice == 'y' || edgeChoice == 'Y');  //continue adding edges if the user chooses 'y'

            //update the CSV file
            updateCSV(edges);

            cout << "Graph data saved to 'graph_data.csv'." << endl;
        }
        else {
            cout << "Invalid choice! Please enter 1 or 2." << endl;
        }

        cout << "Do you want to perform another operation? (y/n): ";
        cin >> mainChoice;

    } while (mainChoice == 'y' || mainChoice == 'Y');

    return 0;
}
