#ifndef A_STAR_H
#define A_STAR_H

#include <lemon/grid_graph.h>

namespace ophidian
{
namespace experiments
{
namespace a_star
{


class A_star
{
public:
    A_star(int cols, int rows, int capacity);

    int search(std::pair<int, int> start, std::pair<int, int> goal, std::vector<lemon::GridGraph::Node> &path);

    lemon::GridGraph & getGraph(){
        return graph;
    }
    void updateGraph(std::vector<lemon::GridGraph::Node> &path);
    void insertBlock(std::vector<std::pair<int, int> > &blocks);
private:
    int heuristic_cost_estimate(std::pair<int, int> start, std::pair<int, int> goal);



    lemon::GridGraph graph;
    lemon::GridGraph::EdgeMap<int> edgeCapacity;
};

} // namespace a_star
} // namespace experiments
} // namespace ophidian
#endif // A_STAR_H
