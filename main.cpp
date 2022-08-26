#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "node.h"
#include <iostream>
#include <fstream>

// Storing the nodes on the heap
Node* nodes[1024];

/* 
   nodes_data.txt is the place where we will store, for each node of the environment (from 0 to 1023), the last prefix that was used in generating an UUID
   Placing data in this file will help us in case the system breaks down so we won't lose already generated UUID's (each UUID can only be given out at most ONCE!)
*/

// Initializing all the system nodes
void initialize_nodes()
{
    // In the file, we will find pairs of (id, prefix). The first time the program will start, all the prefixes will be 0.
    std::ifstream fin("nodes_data.txt");
    unsigned short id;
    unsigned long long prefix;
    // Inserting each node in our environment
    while (fin >> id >> prefix)
        nodes[id] = new Node(id, prefix);
    fin.close();
}

// Deallocating memory and storing the nodes data
void destroy_nodes()
{
    // In case the program ends or an error occurs, we will store data in nodes_data.txt and deallocate the memory used by the nodes in the program execution
    std::ofstream fout("nodes_data.txt");
    for (unsigned short id = 0; id < 1024; id++)
    {
        fout << id << ' ' << nodes[id]->prefix_getter() << '\n';
        delete nodes[id];
    }
    fout.close();
}

// When a caller requests a new id, the node it connects to calls its internal get_id function to get a new, globally unique id
unsigned long long caller_request_id(Node* connect_node)
{
    return connect_node->get_id();
}

//------------------------------------------------------------------------ SOME TESTS HERE ----------------------------------------------------------------------//
/* 
   The maximum value an UUID can have is 18,446,744,073,709,551,024.
   Let's suppose the node A receives 100,000 requests per second.
   This means that the node A will run out of UUIDs after approximately 184,467,440,737,095 seconds with our generation algorithm!
   Knowing that a year has 31,536,000 seconds, the node A will run out of UUIDs after 5,849,424 years! So we're safe :)
*/

// Emulate sending no_of_requests for the connect_node per 1 second!
void requests_per_second_for_a_node(unsigned no_of_requests, unsigned short connect_node)
{
    while (true)
    {
        nodes[connect_node]->increase_prefix_by(no_of_requests - 1); // get_id() will also increment the prefix, so increasing the prefix by no_of_requests - 1
        unsigned long long caller_uuid = caller_request_id(nodes[connect_node]); // requesting an unique id from the selected node
        std::cout << "Node " << connect_node << " reached UUID " << caller_uuid << "!\n";
        Sleep(1000); // waiting for 1s between requests
    }
}

// Assuring that the system works correctly by connecting a big number of callers (requesting ids) to random nodes
void callers_connecting_to_random_nodes(unsigned no_of_callers)
{
    for (unsigned caller = 0; caller < no_of_callers; caller++)
    {
        unsigned short connect_node = rand() % 1024; // generating a random node for the caller to connect to
        unsigned long long caller_uuid = caller_request_id(nodes[connect_node]); // requesting an unique id from the generated node
        std::cout << "Node " << connect_node << " generated UUID " << caller_uuid << " for a caller!\n";
        Sleep(100); // waiting for 100 milliseconds between callers' requests to visualise them better
    }
}

// Assuring that the system works correctly by connecting a big number of callers (requesting ids) to a single node
void callers_connecting_to_a_single_node(unsigned no_of_callers, unsigned short connect_node)
{
    for (unsigned caller = 0; caller < no_of_callers; caller++)
    {
        unsigned long long caller_uuid = caller_request_id(nodes[connect_node]); // requesting an unique id from the connect_node
        std::cout << "Node " << connect_node << " generated UUID " << caller_uuid << " for a caller!\n";
    }
}

int main()
{
    try {
        initialize_nodes();
        // callers_connecting_to_a_single_node(100000, 928);
        // callers_connecting_to_random_nodes(100000);
        // requests_per_second_for_a_node(100000, 592);
        destroy_nodes();
        return 0;
    }
    catch (...) // In case the program finishes abnormally, we have to deallocate used memory and store data persistently
    {
        destroy_nodes();
        return 1;
    }
}