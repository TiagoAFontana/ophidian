#ifndef GRID_GRAPH_OOD_H
#define GRID_GRAPH_OOD_H
#include <vector>
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
    Node(){
        m_edges.reserve(4);
    }

    void set_edge(Node *target, int capacity);
    std::vector<Edge> & edges() const;

    int x() const;
    int y() const;
    void setPosition(int x, int y);
    void printEdges();

private:
    std::vector<Edge> m_edges;
    int m_x;
    int m_y;
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
    void setCapacity(int capacity);

private:
    Node * m_source;
    Node * m_target;
    int m_capacity;
};

class Grid_graph_OOD
{
public:
    Grid_graph_OOD(int cols, int rows, int edgeCapacity);

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
