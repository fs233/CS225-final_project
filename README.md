# haomiao4-boda2-jialuoh2-kaifeng3
Final Project

Use the data for the routes and airport to construct the airportgraph, and  can perform BFS search, shortest path algorithms and projecting the shortest path onto the map. The route data set is a data including the information of the existing routes as shown in the routes.txt. And the airport data is the file that include the information about airports as shown in the airports.txt.
We have two groups of small testcases airports_testcase1.txt, routes_testcase1.txt and airports_testcase2.txt, routes_testcase2.txt. To create small test cases select a set of routes from the routes.txt and the airports related from the airports.txt. And perform the algorithms on the new airport graph created by these small test cases. 
To verify our result we draw the graph out and performed the algorithms by hands and find out that they match with the output of our code.
The tests are included in the file we uploaded. airports.txt and routes.txt are the large dataset and airports_testcase1.txt, routes_testcase1.txt and airports_testcase2.txt, routes_testcase2.txt are the small dataset we created.

BFS Traversal
Perform Breadth-First Search on the Airport Graph. Input a start node (airport), returns all the nodes that can be reached from the start node (all the airports that can be reached from the start airport). 
Testing:
make test
./test "BFS Traversal 1" #the first test case for BFS Traversal
./test "BFS Traversal 2" #Another test case of BFS on another test graph

Dijkstra                                                                     Perform Dijkstra's shortest path on the Airport graph. Input the start node and the end node, then returns the shortest path from the start node to the end.                                                               
Testing:
make test
./test  "Shortest Path" #test case for Dijkstra algorithm

To perform all tests
make test
./test 

Drawmap
Given a start and end airport, the function calls dijkstra for shortest routes, then draw all airports and airlines of this route on the world map.
Earth is simplified to a cylinder, routes across north or south poles are different from real world.
Testing:
To change routes of testing, change function parameter in main function of "drawmap.cpp"
make drawmap 
./drawmap // will generate route on "outputmap.png"