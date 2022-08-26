#include "node.h"

// "Initializing" a node's attributes
Node::Node(unsigned short _node_id, unsigned long long _prefix)
{
	node_id = _node_id;
	prefix = _prefix;
}

// This increases the prefix by how_many_times
void Node::increase_prefix_by(unsigned how_many_times)
{
	prefix += how_many_times;
}

// This will help us when writing data to nodes_data.txt
unsigned long long Node::prefix_getter()
{
	return prefix;
}
/*
   ------------------------------------------------------- THE ASSIGNMENT'S MAIN TASK -----------------------------------------------------------------
   We know that 64-bit positive values (in our case, the generated UUIDs) can be represented from 0 to 18,446,744,073,709,551,615.
   A node will generate an UUID for a caller using the node's own ID and the node's "prefix".
   The prefix is a value that starts from 1 and go up to 18,446,744,073,709,55 and will serve as a component for the UUID
   The desired UUID can have up to 20 digits. The idea is to reserve the first 1 to 16 digits for the prefix and the last 4 digits for the node ID.
   So, the UUID value will be created by concatenating the prefix and the node's ID!
   Examples:
   1. node_id = 8, prefix = 2456 --> UUID = 24560008
   2. node_id = 1003, prefix = 67 --> UUID = 671003
   3. node_id = 945, prefix = 6103983 --> UUID = 61039830945
   -----------------------------------------------------------------------------------------------------------------------------------------------------
*/
unsigned long long Node::get_id() // the function doesn't take parameters as we are working with data members of the current Node object
{
	prefix++; // incrementing the prefix
	return prefix * 10000 + node_id; // returning the created UUID (concatenating the prefix and the node's ID)
}
