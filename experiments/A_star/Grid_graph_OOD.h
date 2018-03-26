#ifndef GRID_GRAPH_OOD_H
#define GRID_GRAPH_OOD_H
#include <vector>
#include <limits>
namespace ophidian
{
namespace experiments
{
namespace a_star
{
class Edge;

class Node
{
public:
    Node(): m_closedSet(false), m_gScore(std::numeric_limits<int>::max()), m_fScore(std::numeric_limits<int>::max()){
        m_edges.reserve(4);
    }

    bool operator ==(Node & node) const {
        return (m_x == node.x()) && (m_y == node.y());
    }

    bool operator !=(Node & node) const {
        return (m_x != node.x()) || (m_y != node.y());
    }

    std::vector<Edge> edges() const;
    void set_edge(Node *target, int capacity);

    int x() const;
    int y() const;
    void position(int x, int y);
    void printEdges();

    bool closedSet() const;
    void closedSet(bool value);

    Node *cameFrom() const;
    void cameFrom(Node *value);

    int GScore() const;
    void GScore(int value);

    int FScore() const;
    void FScore(int value);


private:
    std::vector<Edge> m_edges;
    int m_x;
    int m_y;

    //A_star_variables
    bool m_closedSet;
    Node * m_cameFrom;
    int m_gScore;
    int m_fScore;
};

class Edge
{
public:
    Edge(Node * source, Node * target, int capacity) :
        m_source(source), m_target(target), m_capacity(capacity)
    {
    }

    Node *source() const;
    Node *target() const;
    int capacity() const;
    void capacity(int capacity);

private:
    Node * m_source;
    Node * m_target;
    int m_capacity;
};

class Grid_graph_OOD
{
public:
    Grid_graph_OOD(int cols, int rows, int edgeCapacity);

    Node * operator()(int i, int j){
        return &m_nodes[i][j];
    }

    void print();
private:
    int m_cols;
    int m_rows;
    std::vector< std::vector<Node> > m_nodes;
};


} // namespace a_star
} // namespace experiments
} // namespace ophidian
#endif // GRID_GRAPH_OOD_H
