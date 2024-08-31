#include "pathFinding.h"
#include <queue>
using namespace std;


//function to find the shortest path between two nodes in a graph
//using Breadth-First Search (BFS) algorithem

set<int> pathFinding::findPath(map<int, set<int>> graph, int start, int goal)
{
    set<int> path;
    bool reached = false;
    queue<int> frontier;
    frontier.push(start);
    map<int, int> cameFrom;
    cameFrom[start] = start;

   
    while (!frontier.empty())
    {
        int currentNode = frontier.front(); //get the current node to explore
        frontier.pop();//remove the current node from the frontier

        //check if the goal node is reached
        if (currentNode == goal)
        {
            reached = true;
            break;
        }

        //explore all neighbors of the current node
        for (int neighbor : graph[currentNode])
        {
            //if the neighbor hasn't been visited yet
            if (cameFrom.find(neighbor) == cameFrom.end())
            {
                frontier.push(neighbor); //add neighbor to the frontier to explore later
                cameFrom[neighbor] = currentNode; //record that we reached neighbor from currentNode
            }
        }
    }

    //if the goal was reached, reconstruct the path
    if (reached)
    {
        vector<int> reversePath;
        reversePath.emplace_back(goal);
        int current = cameFrom[goal];

        //trace back from the goal to the start
        while (current != start)
        {
            reversePath.emplace_back(current);
            current = cameFrom[current];
        }

        reversePath.emplace_back(start);

        //reverse the path to get the correct order
        for (int i = reversePath.size() - 1; i >= 0; i--)
        {
            path.insert(reversePath[i]);
        }
    }
    return path;
}
