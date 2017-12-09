// Digraph.cpp -- directed graph class
// c. 2017 T. O'Neil


//Dijkstra Implementation Project
//Nikolai Ruhe
//12/10/2017


#include "Digraph.hpp"

//ran into some overflow errors when using infinity in the math library,
//so i just made infinity a slightly lower, but still very large constant
#define INFINITY 99999999

unsigned int Digraph::noVertices()
{
    return numberOfVertices;
}

unsigned int Digraph::noEdges()
{
    return numberOfEdges;
}

void Digraph::resetEdges()
{
    //brute force through the 2D vector and set all the edges between
    //vertices that aren't the same to INFINITY while the rest are 0
    for(int i = 0; i < numberOfVertices; i++){
        for(int j = 0; j < numberOfVertices; j++){
            if(i == j){
                //vertices match
                distMatrix[i][j] = 0;
            } else {
                //vertices don't match 
                distMatrix[i][j] = INFINITY;
            }
        }
    }
}

void Digraph::addEdge(int source, int dest, int wt)
{
    if(source == dest){
        distMatrix[source][dest] = 0;
    } else {
        distMatrix[source][dest] = wt;
        numberOfEdges++;
    }
}

void Digraph::delEdge(int source, int dest)
{
    if(source == dest){
        distMatrix[source][dest] = 0;
    } else {
        distMatrix[source][dest] = INFINITY;
        numberOfEdges--;
    }
}

int Digraph::isEdge(int source, int dest) {
	// Find and return edge between two verticies
	return distMatrix[source][dest];
}

//returns bool indicating if the target can be visited from the node and
//if the target's new path would be shorter than the existing one
bool Digraph::visitable(int target, int currentAddr, int currentBranch, int smallPath)
{
    if(vertex[target]->getStatus() == NOT_VISITED && currentBranch + distMatrix[currentAddr][target] < smallPath){
        return true;
    } else {
        return false;
    }
}

int Digraph::dijkstra(int source, int dest)
{
    //create a vector to hold the shortest destination paths from a target
    std::vector<int> smallestPath(numberOfVertices, INFINITY);
    
    //set its own address to a distance of 0
    smallestPath[source] = 0;
    
    //initialize comparison checkers
    int minimum, minIndex;
    
    //we need to check all but one of the vertices because we don't have a path
    //for the source node
    //we are looking for the shortest path of all vertices
    for(int num = 0; num < numberOfVertices - 1; num++){
        minimum = INFINITY;
        
        //find a vertex with the shortest immediate distance
        for(int i = 0; i < numberOfVertices; i++){
            if(vertex[i]->getStatus() == NOT_VISITED && smallestPath[i] <= minimum){
                minimum = smallestPath[i];
                minIndex = i;
            }
        }
        
        //this is the vertex we will visit and cross off the list
        vertex[minIndex]->setStatus(VISITED);
        
        //check the vertices around this node to see if they can be visited
        //if there is an adjacent node, check to see if its current path
        //is shorter than the new path discovered
        for(int i = 0; i < numberOfVertices; i++){
            if (visitable(i, minIndex, smallestPath[minIndex], smallestPath[i]) == true){    
                //update the shortest path to this vertex
                smallestPath[i] = smallestPath[minIndex] + distMatrix[minIndex][i];
            }
        }
    }
    
    //reset the state of the vertices to Not Visited
    for (int i = 0; i < vertex.size(); i++){
        vertex[i]->setStatus(NOT_VISITED);
    }
    
    //output the distance from the source to the destination
    return smallestPath[dest];
}
