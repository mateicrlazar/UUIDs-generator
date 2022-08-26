#pragma once

// Creating a simple template which designs a node environment
class Node
{
private:
	unsigned short node_id; // The node's own unique id (a value from 0 to 1023)
	unsigned long long prefix; // The node's prefix is a simple counter that is incremented every time a caller requests an UUID
public:
	// Helper functions
	Node(unsigned short _node_if, unsigned long long _prefix); // The constructor will be called each time a node is created/initialized
	void increase_prefix_by(unsigned how_many_times); // This function will help us emulate 100 000 requests per second for a node
	unsigned long long prefix_getter(); // This function will help us access the prefix in order to store it in a text file for persistent storage
	
	// get_id implementation
	unsigned long long get_id(); // The prototype of the function that needs to be implemented for this challenge!
};
