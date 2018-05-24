/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  rmschmie@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -a4das
 *    -is2kang
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
// include whatever classes you want
class Weighted_graph {
	private:
		//  your implementation here
		//  you can add both private member variables and private member functions
    
        int numEdges; //Number of edges in graoh
        int numVertices; //Number of verticies in graph
        double **edgeMatrix; //Adjaceny matrix holding edge weights
        int **neighbourMatrix; //Holds neighbours of each matrix
        int *heap; //MinHeap array
        double **shortSolver; //ShortestDistance solver matrix
        int iback; //Next open index in minHeap
        int iend; //Indicatr of end of minHeap
        int numEntries; //Keep track of #entries in minHeap
    
		static const double INF;
        void insertHeap(int vertexNum);
        int popHeap();
        void resizeHeap();
	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int n) const;
		int edge_count() const;
		double adjacent( int m, int n) const;
		double distance( int m, int n);
    
		void insert( int m, int n, double w);

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};


const double Weighted_graph::INF = std::numeric_limits<double>::infinity();
//Weighted_Graph//

//Constructor
Weighted_graph::Weighted_graph(int n):
numEdges(0),numVertices(n),edgeMatrix(nullptr),neighbourMatrix(nullptr),heap(nullptr),shortSolver(nullptr),iback(1),iend(n+1),numEntries(0)
{
    if(n<=0)
        n=1;
    edgeMatrix = new double *[numVertices];
    neighbourMatrix = new int*[numVertices];
    heap = new int[numVertices+1];
    shortSolver = new double*[numVertices];
    
    for(int i = 0; i<numVertices;i++){
        edgeMatrix[i] = new double[numVertices];
        neighbourMatrix[i] = new int[numVertices];
        shortSolver[i] = new double[2];
        
        heap[i+1] = 0;
        
        shortSolver[i][0] = INF;
        shortSolver[i][1] = 0;
        
        for(int j = 0; j<numVertices;j++){
            if(i == j){
                edgeMatrix[i][j] = 0;
            }
            else{
                edgeMatrix[i][j] = INF;
            }
            neighbourMatrix[i][j] = -1;
        }
    }
   
}

//Deconstructor
Weighted_graph::~Weighted_graph(){
    delete []edgeMatrix;
    delete []neighbourMatrix;
    delete []shortSolver;
    delete []heap;
}
//Accessors
int Weighted_graph::degree(int n) const{
    return (int)edgeMatrix[n][n];
}
int Weighted_graph::edge_count() const{
    return numEdges;
}
double Weighted_graph::adjacent(int m,int n) const{
    if(m>numVertices-1 || n>numVertices-1 || m<0 || n<0)
        throw illegal_argument();
    else if(m==n)
        return 0;
    else
        return edgeMatrix[m][n];
}

//Mutators
void Weighted_graph::insert(int m, int n, double w){
    if(w==INF || w<=0 || m==n || m>numVertices-1 || n>numVertices-1 || m<0 || n<0)
        throw illegal_argument();
    else if(edgeMatrix[m][n] != INF){
        //Update edge in edge matrix
        edgeMatrix[m][n] = w;
        edgeMatrix[n][m] = w;
    }
    else{
        //Add edge to edge matrix
        edgeMatrix[m][n] = w;
        edgeMatrix[n][m] = w;
        
        //Update Neighbour matrix
        neighbourMatrix[m][(int)edgeMatrix[m][m]] = n;
        neighbourMatrix[n][(int)edgeMatrix[n][n]] = m;
        
        
        //Incremenet degree cell holder
        edgeMatrix[m][m]++;
        edgeMatrix[n][n]++;
        
        numEdges++;
    }
}
double Weighted_graph::distance(int m, int n){
    if(m>numVertices-1 || n>numVertices-1 || m<0 || n<0)
        throw illegal_argument();
    
    int currentVert = m;
    double currentDistance = 0;
    bool firstIteration = false;
    if(numEntries == 0)
        firstIteration = true;
    
    //Push root vertex onto heap
    insertHeap(m);
    shortSolver[m][0] = 0;
    
    //Iterate until heap is empty
    while(numEntries != 0 || firstIteration){
        firstIteration = false;
        int i = 0;
        currentVert = popHeap();
        //Iterate through all adjacent vertices of current vertex and add all shortest edge lengths
        while(neighbourMatrix[currentVert][i]!=-1){
            //Add adjacent vertices to heap and shortestDistance matrix and check if shortest distance must be updated
            if(shortSolver[neighbourMatrix[currentVert][i]][1] != 1 && edgeMatrix[neighbourMatrix[currentVert][i]][currentVert] + currentDistance < shortSolver[neighbourMatrix[currentVert][i]][0]){
                shortSolver[neighbourMatrix[currentVert][i]][0] = edgeMatrix[neighbourMatrix[currentVert][i]][currentVert] + currentDistance;
                insertHeap(neighbourMatrix[currentVert][i]);
            }
            i++;
        }
       //If no adjacency was found to m, then it is disconnected
        if(firstIteration)
            return INF;
        
         //Move along shortest path and update distance travelled
    
         //If it has already been visited, pop again
        if(shortSolver[currentVert][1] == 1){
            while(shortSolver[currentVert][1]==1){
                currentVert = popHeap();
            }
        }
       
        currentDistance = shortSolver[currentVert][0];
    }
    double shortestDist = shortSolver[n][0];
    
    //Reset shortest Distance solver and heap
    for(int i = 0; i < numVertices; i++){
        heap[i] = 0;
        shortSolver[i][0] = INF;
        shortSolver[i][1] = 0;
    }
    iback = 1;
    numEntries = 0;
    return shortestDist;
}

//Min_heap Functions//

void Weighted_graph::insertHeap(int vertexNum){
    int i = iback;
    //Insert in next available spot oin minHeap
    int tempVert;
    heap[i] = vertexNum;
        //Perculate up insertion until it is no longer less than its parent
        while(i != 1 && shortSolver[heap[i]][0] < shortSolver[heap[i/2]][0]){
            heap[i] = vertexNum;
            tempVert = heap[i];
            
            heap[i] = heap[i/2];
            heap[i/2] = tempVert;
            
            i/=2;
        }
    iback++;
    numEntries++;
    
    //Check if resize of minHeap is necessary
    if(iback == iend)
        resizeHeap();
}


int Weighted_graph::popHeap(){
    int poppedVert = heap[1];
    numEntries--;
    
    //Move last entry into popped space
    heap[1] = heap[iback-1];
    heap[iback-1] = 0;
    int i = 1;
    
    int tempVert;
    
    //Perculate vertex down until it is no longer greater than
    while(i>=numEntries && shortSolver[heap[i]][0] > shortSolver[heap[2*i]][0] && shortSolver[heap[i]][0] > shortSolver[heap[2*i + 1]][0])
    {
        if(shortSolver[heap[2*i]][0] < shortSolver[heap[2*i+1]][0]){
            tempVert = heap[i];
            
            heap[i] = heap[2*i];
            heap[2*i] = tempVert;
        }
        else{
            tempVert = heap[i];
            heap[i] = heap[2*i+1];
            
            heap[2*i+1] = tempVert;
        }
    }
    iback --;
    return poppedVert;
}

//Double minHeap size
void Weighted_graph::resizeHeap(){
    int *newHeap = new int[2*numEntries];
    for(int i=1;i<=numEntries;i++)
        newHeap[i] = heap[i];
    
    iend = 2*numEntries + 1;
    heap = newHeap;
    delete []newHeap;
};
//void Min_heap::update(int vertexNum, double distance)


// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
