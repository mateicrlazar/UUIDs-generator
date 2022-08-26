# UUIDs-generator

Hello!
I tried to extend the assignment and make the final solution a little more comprehensive than just implementing the get_id function :)
So the idea was to design the nodes system as a class that contains some data members which are relevant to our challenge.

- The node.h file contains the Node class definition which models the "template" that helps us define each one of the 1024 system nodes;
- The node.cpp file contains the implementantions of the class methods (this is where the get_id implementation is found)
- The main.cpp file contains details such as creating the nodes environment, functions that emulate callers requesting the desire UUIDs and a suite of tests that show how all the elements work intertwined.
I provided complete details about each element in the program inside the files!

Discussion

1. Please describe your solution to get_id and why it is correct i.e. guaranteed globally unique.
- So we know that a caller will connect to one of the nodes and ask it for a globally unique id. When a caller requests a new id, the node it connects to calls its internal get_id function to get a new, globally unique id. Also, there are a fixed number of nodes in the system, up to 1024. Each node has a numeric id, 0 <= id <= 1023. Each node knows its id at startup and that id never changes for the node. Let's take a node N and assume that the caller C connects to the node and requests a UUID. In the way I modeled the nodes, we know that A contains 2 pieces of data that will be relevant for generating the UUID: node_id - the numeric id we talked about earlier, the unique identifier that each node knows at startup; prefix - this will be a value that will help us build the UUID. The generated UUIDs have to be 64-bit positive values. They can be represented internally from 0 to 18,446,744,073,709,551,615. This means that an UUID can have up to 20 digits. The idea is to reserve the first 1 to 16 digits for the prefix (it can start from 1 and go all the way up to 18,446,744,073,709,55) and the last 4 digits for the node_id. So, the UUID value will be created by concatenating the prefix and the node_id!
- Some examples:
a. 
b.
