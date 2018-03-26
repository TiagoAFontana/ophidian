#include "A_star.h"

namespace ophidian
{
namespace experiments
{
namespace a_star
{
struct LessThan
{
    bool operator()(const std::pair<lemon::GridGraph::Node, int>& a, const std::pair<lemon::GridGraph::Node, int>& b) const
    {
        return a.second > b.second;
    }

    bool operator()(const std::pair<ophidian::experiments::a_star::Node *, int>& a, const std::pair<ophidian::experiments::a_star::Node *, int>& b) const
    {
        return a.second > b.second;
    }
};

int heuristic_cost_estimate(std::pair<int, int> start, std::pair<int, int> goal){
    // Manhattan distance between start and goal
    return std::abs(start.first - goal.first) + std::abs(start.second - goal.second);
}

A_star::A_star(int cols, int rows, int capacity)
    : graph(cols, rows),
    cameFrom(graph),
    edgeCapacity(graph, capacity),
    closedSet(graph, false),
    gScore(graph, std::numeric_limits<int>::max()),
    fScore(graph, std::numeric_limits<int>::max())
{
}


int A_star::search(std::pair<int, int> start, std::pair<int, int> goal, std::vector<lemon::GridGraph::Node> &path)
{
    using Node = lemon::GridGraph::Node;
    std::vector<Node> clearNode;


    Node sourceNode = graph(start.first, start.second);
    Node sinkNode = graph(goal.first, goal.second);

    clearNode.push_back(sourceNode);
    clearNode.push_back(sinkNode);

    // The set of nodes already evaluated
//    lemon::GridGraph::NodeMap<bool> closedSet(graph, false);

    // The set of currently discovered nodes that are not evaluated yet.
    // Initially, only the start node is known.
    // openSet := {start}
    std::priority_queue<std::pair<Node, int>, std::vector<std::pair<Node, int> >, LessThan> openSet;
    openSet.push(std::make_pair( sourceNode, 0));

    // For each node, which node it can most efficiently be reached from.
    // If a node can be reached from many nodes, cameFrom will eventually contain the
    // most efficient previous step.
    // cameFrom := an empty map
//    lemon::GridGraph::NodeMap<Node> cameFrom(graph);

    // For each node, the cost of getting from the start node to that node.
    // gScore := map with default value of Infinity
//    lemon::GridGraph::NodeMap<int> gScore(graph, std::numeric_limits<int>::max());

    // The cost of going from start to start is zero.
    // gScore[start] := 0
    gScore[sourceNode] = 0;

    // For each node, the total cost of getting from the start node to the goal
    // by passing by that node. That value is partly known, partly heuristic.
    // fScore := map with default value of Infinity
//    lemon::GridGraph::NodeMap<int> fScore(graph, std::numeric_limits<int>::max());

    // For the first node, that value is completely heuristic.
    // fScore[start] := heuristic_cost_estimate(start, goal)
    fScore[sourceNode] = heuristic_cost_estimate(start, goal);

    while (!openSet.empty())  //openSet is not empty
    {   // current := the node in openSet having the lowest fScore[] value
        Node current = openSet.top().first;
        clearNode.push_back(current);
        // if current = goal
        //    return reconstruct_path(cameFrom, current)
        if (current == sinkNode)
        {
            path.push_back(current);
            while(current != sourceNode)
            {
                current = cameFrom[current];
                path.push_back(current);
            }

            for(Node n : clearNode)
            {
                closedSet[n] = false;
                gScore[n] = std::numeric_limits<int>::max();
                fScore[n] = std::numeric_limits<int>::max();
            }

            return 0;
        }

        // openSet.Remove(current)
        // closedSet.Add(current)
        openSet.pop();
        if(closedSet[current])
        {
            continue;
        }
        closedSet[current] = true;

        for(auto arc = lemon::GridGraph::OutArcIt(graph, current); arc != lemon::INVALID; ++arc)
        {
            if(edgeCapacity[arc] <= 0)
                continue; // Edge full

            auto neighbor = graph.target(arc);
            clearNode.push_back(neighbor);
            if(closedSet[neighbor])
                continue; // Ignore the neighbor which is already evaluated.

            // The distance from start to a neighbor
            //the "dist_between" function may vary as per the solution requirements.
            int tentative_gScore = gScore[current] + 1;
            if (tentative_gScore >= gScore[neighbor])
                continue; // This is not a better path.

            // This path is the best until now. Record it!
            cameFrom[neighbor] = current;
            gScore[neighbor] = tentative_gScore;
            fScore[neighbor] = gScore[neighbor] + heuristic_cost_estimate(std::make_pair(graph.col(neighbor), graph.row(neighbor)), goal);
            openSet.push(std::make_pair( neighbor, fScore[neighbor]));
        }
    }
    return -1;
}

void A_star::updateGraph(std::vector<lemon::GridGraph::Node> & path)
{
    if(path.size() < 2)
        return;
    for (int i = 0; i < path.size() -1; ++i)
    {
        auto current = path[i];
        auto next = path[i+1];
        for(auto arc = lemon::GridGraph::InArcIt(graph, current); arc != lemon::INVALID; ++arc)
        {
            auto neighbor = graph.source(arc);
            if(neighbor == next)
            {
                edgeCapacity[arc] = edgeCapacity[arc]-1;
            }
        }
    }

}

void A_star::insertBlock(std::vector<std::pair<int, int> > & blocks)
{
    for(auto block : blocks)
    {
        auto node = graph(block.first, block.second);
        for(auto arc = lemon::GridGraph::IncEdgeIt(graph, node); arc != lemon::INVALID; ++arc)
        {
            edgeCapacity[arc] = 0;
        }
    }
}



A_star_OOD::A_star_OOD(int cols, int rows, int capacity) : graph(cols, rows, capacity){

}

int A_star_OOD::search(std::pair<int, int> start, std::pair<int, int> goal, std::vector<Node*> &path)
{
    using Node = ophidian::experiments::a_star::Node;

    std::vector<Node *> clearNodes;
//    graph.clearNodes();

    Node * sourceNode = graph(start.first, start.second);
    Node * sinkNode = graph(goal.first, goal.second);

    // The set of nodes already evaluated
//    lemon::GridGraph::NodeMap<bool> closedSet(graph, false);

    // The set of currently discovered nodes that are not evaluated yet.
    // Initially, only the start node is known.
    // openSet := {start}
    std::priority_queue<std::pair<Node*, int>, std::vector<std::pair<Node*, int> >, LessThan> openSet;
    openSet.push(std::make_pair( sourceNode, 0));

    // For each node, which node it can most efficiently be reached from.
    // If a node can be reached from many nodes, cameFrom will eventually contain the
    // most efficient previous step.
    // cameFrom := an empty map
//    lemon::GridGraph::NodeMap<Node> cameFrom(graph);

    // For each node, the cost of getting from the start node to that node.
    // gScore := map with default value of Infinity
//    lemon::GridGraph::NodeMap<int> gScore(graph, std::numeric_limits<int>::max());

    // The cost of going from start to start is zero.
    // gScore[start] := 0
//    gScore[sourceNode] = 0;
    sourceNode->GScore(0);

    // For each node, the total cost of getting from the start node to the goal
    // by passing by that node. That value is partly known, partly heuristic.
    // fScore := map with default value of Infinity
//    lemon::GridGraph::NodeMap<int> fScore(graph, std::numeric_limits<int>::max());

    // For the first node, that value is completely heuristic.
    // fScore[start] := heuristic_cost_estimate(start, goal)
//    fScore[sourceNode] = heuristic_cost_estimate(start, goal);
    sourceNode->FScore(heuristic_cost_estimate(start, goal));

    if(*sourceNode == *graph(1,61) && *sinkNode == *graph(45,61))
    {
        int cc;
        cc =2;
    }

    clearNodes.push_back(sourceNode);
    clearNodes.push_back(sinkNode);
    while (!openSet.empty())  //openSet is not empty
    {   // current := the node in openSet having the lowest fScore[] value
        Node * current = openSet.top().first;
        // if current = goal
        //    return reconstruct_path(cameFrom, current)
        if (*current == *sinkNode)
        {
            path.push_back(current);
            while(*current != *sourceNode)
            {
                current = current->cameFrom();
                path.push_back(current);;
            }

            for(Node * n : clearNodes)
            {
                n->closedSet(false);
                n->GScore(std::numeric_limits<int>::max());
                n->FScore(std::numeric_limits<int>::max());
                n->clearNeighbors();
                n->clearNeighbors();
            }
            return 0;
        }

        // openSet.Remove(current)
        // closedSet.Add(current)
        openSet.pop();
        if(current->closedSet())
        {
            continue;
        }
        current->closedSet(true);

        clearNodes.push_back(current);

        for(Edge arc : current->edges())
        {
            if(arc.capacity() <= 0)
                continue; // Edge full

            auto * neighbor = arc.target();
            clearNodes.push_back(neighbor);
            if(neighbor->closedSet())
                continue; // Ignore the neighbor which is already evaluated.

            // The distance from start to a neighbor
            //the "dist_between" function may vary as per the solution requirements.
            int tentative_gScore = current->GScore() + 1;
            if (tentative_gScore >= neighbor->GScore())
                continue; // This is not a better path.

            // This path is the best until now. Record it!
            neighbor->cameFrom(current);
            neighbor->GScore(tentative_gScore);
            neighbor->FScore(neighbor->GScore() + heuristic_cost_estimate(std::make_pair(neighbor->x(), neighbor->y()), goal));
            openSet.push(std::make_pair( neighbor, neighbor->FScore()));
            clearNodes.push_back(neighbor);
        }
    }
    return -1;
}



} // namespace a_star
} // namespace experiments
} // namespace ophidian
