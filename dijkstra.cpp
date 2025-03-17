#include <iostream>
#include <cstdlib>
#include <climits>
using namespace std;

/* ----------------------- Struct to create a link list --------------------------------- */
struct node { //used to store edges
    int id;
    char name;
    int weight;
    node* next;
    node(int i, char s, int w, node* p = nullptr)
    {
        id = i;
        name = s;
        weight = w;
        next = p;
    }
};

/* ----------------------- Function to add edges --------------------------------- */
void addAdjacentNodeList(node** aList, int s, int d, char st, int w) // Array of linked lists each holding their adjacent nodes and weight
{

    aList[s] = new node(d, st, w, aList[s]); //Index into node s in the array and add new edge
}

/* ----------------------- Struct to create MIN HEAP --------------------------------- */
struct sd{ //used for min heap
    char n;
    int value;
    int id;
    sd(char c, int i, int d)
    {
        n=c;
        value=i;
        id=d;
    }
    sd()
    {
        n=NULL;
        value=NULL;
        id=NULL;
    }
};

/* ----------------------- Function to MIN HEAPIFY --------------------------------- */
void min_heapify(sd A[], int i, int size)
{
    int left = 2 * i + 1;  // Left child index
    int right = 2 * i + 2; // Right child index
    int smallest = i;

    if (left < size && A[left].value < A[smallest].value) {
        smallest = left;
    }
    if (right < size && A[right].value < A[smallest].value) {
        smallest = right;
    }
    if (smallest != i) {
        swap(A[i], A[smallest]);
        min_heapify(A, smallest, size);
    }
}

/* ----------------------- Function to Build MIN HEAP--------------------------------- */

void build_min_heap(sd A[], int n)
{
    if (n <= 0) 
    {
        return;  // empty or invalid array
    }
    for (int i = (n / 2) - 1; i >= 0; i--)
    {
        min_heapify(A, i, n);
    }
}

/* -----------------------Function to extract min value in the heap --------------------------------- */
sd extract_min(sd A[], int n)
{
    sd min = A[0];
    A[0] = A[n-1];
    n=n-1;
    min_heapify(A, 0, n);
    return min;
}

/* ----------------------- Function to decrease key value --------------------------------- */
void heap_decrease_key(sd A[], int i, int key, char na)
{
    A[i].value = key;
    A[i].n = na;
    while (i > 0 && A[(i - 1) / 2].value > A[i].value)
    {
        swap(A[i], A[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

/* USED TO DECODE
void print(sd arr[], int size)
{
    cout<< "Printing out min heap of nodes list \n";
    
    for(int i=0; i < size; i++)
    {
        cout<< arr[i].id <<"->Id " << arr[i].value <<"->value " <<arr[i].n <<"->char " <<endl;
    }
    cout<<endl;
}
*/

/* ----------------------- Dijkstras Algorithm Function --------------------------------- */
void dijkstra(char names[], node** edges, int source_index, char source_char, int size)
{
    sd distance[size]; //min heap ~ priority queue
    int value = size;
    bool visited[size]; //visited nodes
    int shortest_distance[size]; //final cost values
    
    for(int i =0; i<size; i++) //Initialization all values
    {
        distance[i].n = names[i];
        distance[i].value= INT_MAX;
        distance[i].id= i;
        visited[i]= false;
        shortest_distance[i]= INT_MAX;
    }
    
    
    distance[source_index].value=0;  // Setting source node value to 0 so it will be at the top of the min heap
    shortest_distance[source_index]=0; // Setting distance to itself as zero
    
    build_min_heap(distance, size);  // Rearranging heap to a min heap
    
    //print(distance, value); //Used to DECODE
    
    
    while(value != 0)
    {
        sd current = extract_min(distance, value); // Extracting the smallest value from the heap and set as current node being looked at
        
        //Used to DECODE
        //cout<< "Current char extracted: " <<current.n <<endl;
        
        visited[current.id]=true; // Update vistied array to keep track if the node has already been looked at
        value = value-1; // Update value variable because we just extracted the current node form the min heap
        
        node* adj = edges[current.id]; // Obtain the edges of the current lode from the array of linked list

        /*Used to DECODE
        for(int i = 0; i<size;i++)
        {
            cout<< "index " <<i <<" current visited value: " <<visited[i] << " \n";
        } */
        
        
        int temp; // Create temp variable
        while(adj != nullptr) // Loop while there are still outgoing edges from the node that need to be looked at
        {
            //Used to DECODE
            //cout<< "Adj node  " << adj->name << " Adjacent node weight " <<adj->weight <<" \n";
            
            temp = shortest_distance[current.id] + adj->weight; // Update shortest distance value by adding the edge node weight
            
            //Used to DECODE
            //cout<< "temp value " <<temp <<" \n";
            
            if(temp < shortest_distance[adj->id] && !visited[adj->id]) // See if the temp value is less than current distance value and if the node has not been visited
            {
                shortest_distance[adj->id] = temp; // Change shortest distance to temp
                
                int j = -1;  // Find the correct index of the node in the heap
                for(int i = 0; i < value; i++)
                {
                    if(distance[i].n == adj->name)
                    {
                        j = i;
                        break;
                    }
                }
                
                if(j != -1)
                {
                    distance[j].value = temp;
                    heap_decrease_key(distance, j, temp, adj->name);
                }
            }
            
            adj = adj->next;
        }
        
        build_min_heap(distance, value);
        //print(distance, value); //Used to DECODE
    }
    
     /* -----------------------Printing Results--------------------------------- */
    for(int i = 0; i < size; i++)
    {
        cout << "The shortest distance from " << source_char << " to " << names[i] << " is " << shortest_distance[i] << endl;
    }
    
    cout<<endl;
     
}


int main()
{
    int numofNodes = 6;
    
    char oneD[] = {'U', 'V', 'X', 'W', 'Y', 'Z'};
    
    cout << "\n---------------------Find Shortest Path using Dijkstra-----------------------------\n";
    
    node** adjList = new node * [numofNodes];
    for (int i = 0; i < numofNodes; i++)
        adjList[i] = nullptr;

    addAdjacentNodeList(adjList, 0, 1, oneD[1], 8);
    addAdjacentNodeList(adjList, 0, 2, oneD[2], 3);
    addAdjacentNodeList(adjList, 0, 3, oneD[3], 1);
    
    addAdjacentNodeList(adjList, 1, 0, oneD[0], 8);
    addAdjacentNodeList(adjList, 1, 2, oneD[2], 3);
    addAdjacentNodeList(adjList, 1, 3, oneD[3], 6);
    
    addAdjacentNodeList(adjList, 2, 0, oneD[0], 3);
    addAdjacentNodeList(adjList, 2, 1, oneD[1], 3);
    addAdjacentNodeList(adjList, 2, 3, oneD[3], 9);
    addAdjacentNodeList(adjList, 2, 4, oneD[4], 9);
    
    addAdjacentNodeList(adjList, 3, 0, oneD[0], 1);
    addAdjacentNodeList(adjList, 3, 1, oneD[1], 6);
    addAdjacentNodeList(adjList, 3, 2, oneD[2], 9);
    addAdjacentNodeList(adjList, 3, 4, oneD[4], 8);
    addAdjacentNodeList(adjList, 3, 5, oneD[5], 2);
    
    addAdjacentNodeList(adjList, 4, 2, oneD[2], 9);
    addAdjacentNodeList(adjList, 4, 3, oneD[3], 8);
    addAdjacentNodeList(adjList, 4, 5, oneD[5], 9);
    
    addAdjacentNodeList(adjList, 5, 3, oneD[3], 2);
    addAdjacentNodeList(adjList, 5, 4, oneD[4], 9);
    
    /* ----------- User Input Solution ------------------ */
    //int node;
   // cout<<"Select starting node (0-5): ";
    //cin>> node;
    //dijkstra(oneD, adjList, node, oneD[node], 6);
    
    /* ---------- All solutions ----------------- */
    for(int i=0; i<6; i++)
    {
        dijkstra(oneD, adjList, i, oneD[i], 6);
    }
    return 0;
}


