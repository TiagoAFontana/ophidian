#ifndef KMEANSOBJECTORIENTEDDESIGN_H
#define KMEANSOBJECTORIENTEDDESIGN_H

#include <random>

#include "ophidian/geometry/Models.h"
#include "experiments/metric.h"

namespace ophidian
{
namespace experiments
{
namespace register_clustering
{

class ClusterOOD;

class FlipFlop
{
private:
    geometry::Point position_;
    ClusterOOD * clusterBest_;

    std::string name_ = "DFF_X80";
    volatile long long cap;
    volatile long long cap2;
    geometry::Point size_;
    int net_;
public:
    FlipFlop(geometry::Point & p) : position_(p) {
        cap = 5;
        cap2 = cap * 2;
    }

    geometry::Point position() const;
    void setPosition(const geometry::Point &position);
    ClusterOOD *clusterBest() const;
    void setClusterBest(ClusterOOD *clusterBest);
};

class ClusterOOD
{
private:
    geometry::Point center_;
    std::vector<FlipFlop> elements_;
public:
    ClusterOOD(const geometry::Point &center);

    std::vector<FlipFlop> elements() const;
    void elements(const std::vector<FlipFlop> &elements);
    geometry::Point center() const;
    void center(const geometry::Point &center);

    void insertElement(const FlipFlop &element);
    void clear();
    int size();
};


class KmeansObjectOrientedDesign
{
private:
    std::default_random_engine m_generator;
    std::uniform_real_distribution<double> m_distribution_x;
    std::uniform_real_distribution<double> m_distribution_y;


    using rtree_node = std::pair<geometry::Point, ClusterOOD*>;
    using rtree = boost::geometry::index::rtree<rtree_node, boost::geometry::index::rstar<16> >;
public:
    std::vector<ClusterOOD> clusters_;

    KmeansObjectOrientedDesign(geometry::Point chipOrigin, geometry::Point chipBondary, unsigned k = 50);
    KmeansObjectOrientedDesign(const std::vector<geometry::Point> &centers);

    void cluster_registers_with_rtree(std::vector<FlipFlop> &flip_flops, ophidian::experiments::Metric &metric, unsigned iterations = 10);
    void cluster_registers_with_rtree_paralel(std::vector<FlipFlop> & flip_flops, ophidian::experiments::Metric &metric, unsigned iterations = 10);
//    void cluster_registers(std::vector<FlipFlop> &flip_flops, unsigned iterations = 10);
//    void cluster_registers_paralel(std::vector<FlipFlop> &flip_flops, unsigned iterations = 10);
};


} // namespace register_clustering
} // namespace experiments
} // namespace ophidian
#endif // KMEANSOBJECTORIENTEDDESIGN_H
