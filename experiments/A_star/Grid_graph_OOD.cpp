#include "Grid_graph_OOD.h"
#include <iostream>
namespace ophidian
{
namespace experiments
{
namespace a_star
{


Grid_graph_OOD::Grid_graph_OOD(int cols, int rows, int edgeCapacity) : m_rows(rows), m_cols(cols)
{
//    std::vector< std::vector<Node> > m_nodes;
    m_nodes.resize(cols);
    for (int i = 0; i < cols; ++i)
    {
        m_nodes[i].resize(rows);
    }

    for (int i = 0; i < cols; ++i)
    {
        for (int j = 0; j < rows; ++j)
        {
            Node node;
            m_nodes[i][j] = node;
            m_nodes[i][j].position(i,j);
        }
    }

    for (int i = 0; i < cols; ++i)
    {
        for (int j = 0; j < rows; ++j)
        {
            //esquerda
            if(i > 0)
                m_nodes[i][j].set_edge(&m_nodes[i-1][j], edgeCapacity);
            //direita
            if(i < cols -1)
                m_nodes[i][j].set_edge(&m_nodes[i+1][j], edgeCapacity);
            //cima
            if(j < rows -1)
                m_nodes[i][j].set_edge(&m_nodes[i][j+1], edgeCapacity);
            //baixo
            if(j > 0)
                m_nodes[i][j].set_edge(&m_nodes[i][j-1], edgeCapacity);
        }
    }
}

void Grid_graph_OOD::print()
{
    for (int i = 0; i < m_cols; ++i)
    {
        for (int j = 0; j < m_rows; ++j)
        {
            m_nodes[i][j].printEdges();
        }
    }
}

Node *Edge::source() const
{
    return m_source;
}

Node *Edge::target() const
{
    return m_target;
}

int Edge::capacity() const
{
    return m_capacity;
}

void Edge::capacity(int capacity)
{
    m_capacity = capacity;
}

void Node::set_edge(Node *target, int capacity)
{
    Edge edge(this, target, capacity);
    m_edges.push_back(edge);
}

int Node::x() const
{
    return m_x;
}

int Node::y() const
{
    return m_y;
}

void Node::position(int x, int y)
{
    m_x = x;
    m_y = y;
}

void Node::printEdges()
{
    for(auto edge : m_edges)
    {
        Node * target = edge.target();
        std::cout << "("<< m_x << ", "<< m_y <<") -> (" << target->x() << ", " << target->y() << ") cap = " << edge.capacity() << std::endl;
    }
}

bool Node::closedSet() const
{
    return m_closedSet;
}

void Node::closedSet(bool value)
{
    m_closedSet = value;
}

Node *Node::cameFrom() const
{
    return m_cameFrom;
}

void Node::cameFrom(Node *value)
{
    m_cameFrom = value;
}

int Node::GScore() const
{
    return m_gScore;
}

void Node::GScore(int value)
{
    m_gScore = value;
}

int Node::FScore() const
{
    return m_fScore;
}

void Node::FScore(int value)
{
    m_fScore = value;
}

std::vector<Edge> Node::edges() const
{
    return m_edges;
}





} // namespace a_star
} // namespace experiments
} // namespace ophidian
