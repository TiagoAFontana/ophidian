#ifndef KMEANSDATAORIENTEDDESIGN_H
#define KMEANSDATAORIENTEDDESIGN_H

#include <omp.h>
#include <random>

#include "ophidian/entity_system/EntitySystem.h"
#include "ophidian/entity_system/Property.h"
#include "ophidian/geometry/Models.h"
#include "ophidian/entity_system/Aggregation.h"
#include "experiments/metric.h"

namespace ophidian
{
namespace experiments
{
namespace register_clustering
{

class Cluster : public entity_system::EntityBase
{
public:
    using entity_system::EntityBase::EntityBase;
};
class KmeansDataOrientedDesign
{

private:
    std::default_random_engine m_generator;
    std::uniform_real_distribution<double> m_distribution_x;
    std::uniform_real_distribution<double> m_distribution_y;

    using rtree_node = std::pair<geometry::Point, const Cluster*>;
    using rtree = boost::geometry::index::rtree<rtree_node, boost::geometry::index::rstar<16> >;


public:
    using cluster_center = geometry::Point;
    KmeansDataOrientedDesign(geometry::Point chipOrigin, geometry::Point chipBondary, unsigned k = 50);
    KmeansDataOrientedDesign(const std::vector<geometry::Point> &centers);

    entity_system::EntitySystem<Cluster> clusters_;
    entity_system::Property<Cluster, geometry::Point> clusterCenters_;
    entity_system::Property<Cluster, std::vector<geometry::Point *> > clusterElements_;

    void cluster_registers_with_rtree(std::vector<geometry::Point> &flip_flops, ophidian::experiments::Metric &metric, unsigned iterations = 10);
    void cluster_registers_with_rtree_parallel(std::vector<geometry::Point> &flip_flops, ophidian::experiments::Metric &metric, unsigned iterations = 10);
};


#if 0
class KmeansDataOrientedDesign
{

private:
    std::default_random_engine m_generator;
    std::uniform_real_distribution<double> m_distribution_x;
    std::uniform_real_distribution<double> m_distribution_y;

    using rtree_node = std::pair<geometry::Point, Cluster>;
    using rtree = boost::geometry::index::rtree<rtree_node, boost::geometry::index::rstar<16> >;


public:
    using cluster_center = std::pair<geometry::Point, Cluster>;
    KmeansDataOrientedDesign(geometry::Point chipOrigin, geometry::Point chipBondary, unsigned k = 50);
    KmeansDataOrientedDesign(const std::vector<geometry::Point> &centers);

    entity_system::EntitySystem<Cluster> clusters_;
    entity_system::Property<Cluster, cluster_center> clusterCenters_;
    entity_system::Property<Cluster, std::vector<geometry::Point> > clusterElements_;

    void cluster_registers_with_rtree(const std::vector<geometry::Point> & flip_flops, ophidian::experiments::Metric &metric, unsigned iterations = 10);
    void cluster_registers_with_rtree_parallel(const std::vector<geometry::Point> & flip_flops, ophidian::experiments::Metric &metric, unsigned iterations = 10);
//    void cluster_registers(const std::vector<geometry::Point> & flip_flops, unsigned iterations = 10);
//    void cluster_registers_parallel(const std::vector<geometry::Point> & flip_flops, unsigned iterations = 10);
};
#endif

} // namespace register_clustering
} // namespace experiments
} // namespace ophidian

#endif // KMEANSDATAORIENTEDDESIGN_H
