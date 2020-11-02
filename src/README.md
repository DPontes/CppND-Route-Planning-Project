# Notes on the tasks for this exercise
The base code in the repo is cloned from Udacity's course on C++.

The code developed by me is below the TODOs along the `main.cpp` and `route_planner.cpp` files. More details below.

- `main.cpp`
  - TODO 1: Declare floats `start_x`, `start_y`, `end_x` and `end_y` and get user input for these values using std::cin. Pass the user input to the RoutePlanner object.

  This was rather simple and straight forward, therefore no major explanation necessary. There is however no unit test that verifies this implementation.
  **Sugestion**: a separate function that would do this. The advantage is that it would be clearer what the goal here is, as well as it would allow for unit testing. Also, the code implemented doesn't attend to other inputs outside ints [0-100]. Handling values outside of this interval (as well as other random inputs) would be advised.

- `route_planner.cpp`
  - TODO 2: Use the m_Model.FindClosestNode method to find the closest nodes to the starting and ending coordinates.
            Store the nodes you find in the RoutePlanner's start_node and end_node attributes.

  Also rather straight-forward, although knowing to use the `&` for `model` was not immediately apparent.
  This functionality also didn't have a unit test implemented.

  - TODO 3: Implement CalculateHValue method

  Given that there already is a `distance` method in the `Node` object, it was only a matter of calling it for that particular node, giving the pointer to `end_node` as parameter.
  The `distance` method calculates the Euclidean distance between the two coordinates provided.
  Only here was it finally possible to run a unit test that would confirm the 3 TODOs above.

  - TODO 4: Complete the AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.

  
