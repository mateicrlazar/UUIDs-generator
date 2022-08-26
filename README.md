# UUIDs-generator

Hello!
I tried to extend the assignment and make the final solution a little more comprehensive than just implementing the get_id function.
I think that, just by looking at the code, everything will be easier to understand. :)
So the idea was to design the nodes system as a class that contains some data members which are relevant to our challenge:

- The node.h file contains the Node class definition which models the "template" that helps us define each one of the 1024 system nodes;
- The node.cpp file contains the implementantions of the class methods (this is where the get_id implementation is found)
- The main.cpp file contains details such as creating the nodes environment, functions that emulate callers requesting the desire UUIDs and a few tests that show how all the elements work intertwined.
- The nodes_data.txt file is the place where we will maintain persistent storage by saving the data every node uses for generating UUIDs.
- I provided complete details about each element in the files!

Discussion

1. Please describe your solution to get_id and why it is correct i.e. guaranteed globally unique.
- So we know that a caller will connect to one of the nodes and ask it for a globally unique id. When a caller requests a new id, the node it connects to calls its internal get_id function to get a new, globally unique id. Also, there are a fixed number of nodes in the system, up to 1024. Each node has a numeric id, 0 <= id <= 1023. Each node knows its id at startup and that id never changes for the node. In the way I modeled the nodes, we know that each node contains 2 pieces of data that will be relevant for generating the UUID: node_id - the numeric id we talked about earlier, the unique identifier that each node knows at startup; prefix - this will be a value that will help us build the UUID (it will be initialized as 0 first), it will be incremented each time a caller connects to the node and requests and UUID. The generated UUIDs have to be 64-bit positive values. They can be represented internally from 0 to 18,446,744,073,709,551,615. This means that an UUID can have up to 20 digits. The idea is to reserve the first 1 to 16 digits for the prefix (it can start from 1 and go all the way up to 18,446,744,073,709,55) and the last 4 digits for the node_id. So, the UUID value will be created by concatenating the prefix and the node_id. It won't really matter what the caller C represents.
- Example 1: Let's take node 57. By creating it at the first execution of the program: node_id = 57; prefix = 0. An arbitrary caller (which happens to be the first caller that ever connects to the node 57) requests an UUID. The UUID that the node will give is 10057! Immediately after that, another arbitrary caller connects to the node and requests an UUID. The UUID the node will give this time is 20057... So, by taking this pattern, the n-th caller that connected to the node will receive the UUID: n0057, 1 <= n <= 18,446,744,073,709,55.
- An easier example: node_id = 1021, prefix = 5495 --> UUID = 54951021
- And another: node_id = 7, prefix = 93984 --> UUID = 939840007
- The UUIDs are guaranteed globally unique because, in the generation of an UUID, we use 2 values and each one contributes to the UUID uniqueness in its own way: node_id is unique in the context of all the nodes, we know that there will never be 2 or more nodes (in the environment) that have the same id; prefix is unique in the context of a single node. Each time a caller connects to our node and requests an UUID, the prefix will be incremented. So, the prefix value will be different EVERY TIME we will generate an UUID. We could think of prefix as an increasing function from a mathematical point of view. As the number of callers for a node approaches infinity, the prefix will also approach infinity. Of course, if we take node A and node B, they can have the same prefix, but the fact that node A has a different node_id than node B makes the UUID also unique, ∀ A, B ∈ System.

2. Please explain how your solution achieves the desired performance i.e. 100,000 or more requests per second per node.  How did you verify this?
- The maximum value an UUID can have is 18,446,744,073,709,551,023 (the first 16 digits - the prefix, the last 4 digits - the greatest node ID). Let's suppose the node N receives 100,000 requests per second (maximum). This means that the node A will run out of UUIDs after approximately 184,467,440,737,095 seconds with our generation algorithm (we divided the maximum UUID value by the maximum number of requests per second)! Knowing that a year has 31,536,000 seconds, the node A will run out of UUIDs after 5,849,424 years (we divided the number of seconds in which the node A will run out of UUIDs if it's constantly getting 100,000 requests per second by the number of seconds a year has)! That means that, basically and practically, as long as the system will be functioning, it will generate unlimited UUIDs. We assumed that any node will never accept more than 100,000 requests per second, but if it would, the requests should be well-handled in something like a queue of requests.

3. Please enumerate possible failure cases and describe how your solution correctly handles each case. How did you verify the correctness?
- One possible failure case is the one in which the whole system breaks down/the program stops its execution. At each program start, every node in the environment will initialize with data that was saved in the last session of execution in nodes_data.txt (its id and the last prefix that was used in generating an UUID). Every time the program stops its execution (abnormally or with success), we will write the relevant data to nodes_data.txt for each node. In this way, we ensure that we will not generate the same UUID more than once, conserve the uniqueness and persistent storage. Even though some cases of abortion are not handled (e.g. the user closes the program by pressing X in the program window), the idea of storing the nodes data externally is fine.
- Another possible failure case is the on in which a node crashes or stops its process from execution. In the way my little program is implemented, this scenario won't appear, but this could be solved by creating a function that iterates through the nodes_data.txt until it finds where the data of the node that crashed is found and restore its attributes again.

That was it! Thank you for the opportunity and I hope that I didn't go too far in solving this assignment :)
