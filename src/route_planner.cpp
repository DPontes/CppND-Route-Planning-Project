#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    start_node = &model.FindClosestNode(start_x, start_y);
    end_node = &model.FindClosestNode(end_x, end_y);
}

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
    return node->distance(*end_node);
}

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    // populate current_node.neighbors vector using FindNeighbors() method
    current_node->FindNeighbors();

    for (auto *neighbor : current_node->neighbors) {
        if(neighbor->visited) continue; // do not update the neighbor if already visited
        neighbor->parent  = current_node;
        neighbor->h_value = CalculateHValue(neighbor);
        neighbor->g_value  = current_node->g_value +
                            current_node->distance(*neighbor);
        neighbor->visited  = true;
        open_list.emplace_back(neighbor);
    }
    return;
}

RouteModel::Node *RoutePlanner::NextNode() {
    // using a lambda function
    std::sort(open_list.begin(), open_list.end(), [](const auto& list_1,
                                                     const auto& list_2) {
        return  (list_1->h_value + list_1->g_value) <
                (list_2->h_value + list_2->g_value);
    });

    RouteModel::Node *pNode = open_list.front();

    open_list.erase(open_list.begin());

    return pNode;
}

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;
    RouteModel::Node *node = current_node;

    while (node->parent != nullptr) {
            path_found.insert(path_found.begin(),*(node));
            distance += node->distance(*node->parent);
            node = node->parent;
        }

    path_found.insert(path_found.begin(), *(node));

    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters

    return path_found;

}

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;
    open_list.push_back(start_node);
    start_node->visited = true;

    while(open_list.size() > 0 && current_node != end_node) {
        current_node = NextNode();
        if(current_node->distance(*end_node) == 0) {
            m_Model.path = ConstructFinalPath(current_node);
            break;
        } else {
            AddNeighbors(current_node);
        }
    }
    return;
}
