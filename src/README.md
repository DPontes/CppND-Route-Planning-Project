# Notes on the tasks for this exercise
The base code in the repo is cloned from Udacity's course on C++.

The code developed by me is located in the indicated functions in the `main.cpp` and `route_planner.cpp` files. More details below.

- `main.cpp`
  - TODO 1: Declare floats `start_x`, `start_y`, `end_x` and `end_y` and get user input for these values using std::cin. Pass the user input to the RoutePlanner object.

  This was rather simple and straight forward, therefore no major explanation necessary. There is however no unit test that verifies this implementation.

  **Sugestion**: a separate function that would do this. The advantage is that it would be clearer what the goal here is, as well as it would allow for unit testing. Also, the code implemented doesn't attend to other inputs outside ints [0-100]. Handling values outside of this interval (as well as other random inputs) would be advised.

- `route_planner.cpp`
  - TODO 2: `RoutePlanner::RoutePlanner(Routemodel &model, float start_c, float start_y, float end_x, float_end_y) : m_Model(model)`
            Use the m_Model.FindClosestNode method to find the closest nodes to the starting and ending coordinates.
            Store the nodes you find in the RoutePlanner's start_node and end_node attributes.

  Also rather straight-forward, although knowing to use the `&` for `model` was not immediately apparent.
  This functionality also didn't have a unit test implemented.

  - TODO 3: `float RoutePlanner::CalculateHValue(RouteModel::Node const *node)`
            Implement CalculateHValue method

  Given that there already is a `distance` method in the `Node` object, it was only a matter of calling it for that particular node, giving the pointer to `end_node` as parameter.
  The `distance` method calculates the Euclidean distance between the two coordinates provided.
  Only here was it finally possible to run a unit test that would confirm the 3 TODOs above.

  - TODO 4: `void RoutePlanner::AddNeighbors(RouteModel::Node *current_node)`
            Complete the AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.

  Go over all the current node's neighbors. If the neighbor node has been visited

    `if(neighbor->visited) continue;`

  break this iteration and continue with the next node of the `current_node` `neighbors`.

  The calculation of the `neighbor->g_value` was understood by searching for clarification in the Knowledge forum.

  - TODO 5: `RouteModel::Node *RoutePlanner::NextNode()`
            Complete the NextNode method to sort the open list and return the next node.

  Initially the return value in the lambda function was to come from a separate function, but was decided against given that it would add more complexity, as well as the end result can be considered "cleaner".

  The decision to use the lambda function was again due to suggestion in the Knowledge forum by the mentors. The sorting `std::sort` together with the `<` symbol in the return part of the lambda function returns a `open_list` ordered in ascending `g_value + h_value`. From this, we create a pointer to the `front` of the `open_list` (the lowest value) and remove the same node with the `erase` functionality.

  - TODO 6: `std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node)`
            Complete the ConstructFinalPath method to return the final path found from your A* search.

  This function goes "backwards" through a `while` loop from the `current_node` until the `node` doesn't have a parent - where it's the `start_node`.
  The line:

    path_found.insert(path_found.begin(), *(node));

  **outside** the `while` loop is used to add the `start_node` to the `path_found`, which otherwise doesn't happen inside the `while` loop.

  - TODO 7: `void RoutePlanner::AStarSearch()`
            Write the A* Search algorithm

  This one was a simple construction of the final path by applying the `AddNeighbors` functionality to the `current_node` unless the distance to the `end_node` was zero. If it was, then the `ConstructFinalPath`function is called and applied to `m_Model.path`. The location of this instructions was figured out with the help from questions asked in the Knowledge forum.

