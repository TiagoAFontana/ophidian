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

//template <class FF> class ClusterOOD;

//class FlipFlop
//{
//private:
//    geometry::Point position_;
//    ClusterOOD<FlipFlop> * clusterBest_;

//    std::string name_ = "DFF_X80";
//    volatile long long cap;
//    volatile long long cap2;
//    geometry::Point size_;
//    int net_;
//public:
//    FlipFlop(geometry::Point & p) : position_(p) {
//        cap = 5;
//        cap2 = cap * 2;
//    }

//    virtual ClusterOOD<FlipFlop> *clusterBest() const
//    {
//        return clusterBest_;
//    }

//    virtual void setClusterBest(ClusterOOD<FlipFlop> *clusterBest)
//    {
//        clusterBest_ = clusterBest;
//    }

//    virtual geometry::Point position() const
//    {
//        return position_;
//    }

//    virtual void setPosition(const geometry::Point &position)
//    {
//        position_ = position;
//    }
//};

//template <class FF>
//class ClusterOOD
//{
//private:
//    geometry::Point center_;
//public:
//    std::vector< FF *> elements_;

//    ClusterOOD(const geometry::Point &center) : center_(center){
//    }

//    std::vector< FF *> elements() const {
//        return elements_;
//    }
//    void elements(const std::vector<FF*> &elements){
//        elements_ = elements;
//    }

//    geometry::Point center() const {
//        return center_;
//    }
//    void center(const geometry::Point &center){
//        center_ = center;
//    }

//    void insertElement(FF *element){
//        elements_.push_back(element);
//    }

//    void clear(){
//        elements_.clear();
//    }

//    int size(){
//        return elements_.size();
//    }
//};

//template <class FF>
//class KmeansObjectOrientedDesign
//{
//private:
//    std::default_random_engine m_generator;
//    std::uniform_real_distribution<double> m_distribution_x;
//    std::uniform_real_distribution<double> m_distribution_y;


//public:
//    using rtree_node = std::pair<geometry::Point, ClusterOOD<FF>*>;

//    using rtree = boost::geometry::index::rtree<rtree_node, boost::geometry::index::rstar<16> >;
//    std::vector<ClusterOOD<FF> > clusters_;


//    KmeansObjectOrientedDesign(geometry::Point chipOrigin, geometry::Point chipBondary, unsigned k = 50) :
//        m_distribution_x(chipOrigin.x(),chipBondary.x()), m_distribution_y(chipOrigin.y(),chipBondary.y())
//    {
//        clusters_.reserve(k);
//        for (int i = 0; i < k; ++i)
//        {
//            clusters_.push_back(ClusterOOD<FF>(geometry::Point(m_distribution_x(m_generator), m_distribution_y(m_generator))));
//        }
//    }
//    KmeansObjectOrientedDesign(const std::vector<geometry::Point> &centers)
//    {
//        clusters_.reserve(centers.size());
//        for(auto p : centers)
//        {
//            clusters_.push_back(ClusterOOD<FF>(p));
//        }
//    }

//    void cluster_registers_with_rtree(std::vector< FF > &flip_flops, ophidian::experiments::Metric &metric, unsigned iterations = 10)
//    {
//            #if 0
//        std::cout<<"---- INFO: teste miss----"
//                 <<"\nNumber flipflops: "<< flip_flops.size()
//                 << "\nsize flipflops : " << sizeof(FlipFlop)
//                 <<"\nNumber Cluster: "<< clusters_.size()
//                 << "\nsize Cluster : " << sizeof(ClusterOOD)
//            //             << "\n expected cache misses: " << design.netlist().size(ophidian::circuit::Cell()) * sizeof(ophidian::experiments::chip_boundaries::PlacementCell) / 64
//                 << "\n------" <<std::endl;
//            #endif

//        metric.start();
//        for (int i = 0; i < iterations; ++i)
//        {
//            rtree clusters_rtree;
//            for (ClusterOOD<FF> &cluster : clusters_)
//            {
//                clusters_rtree.insert(rtree_node(cluster.center(), &cluster));
//                cluster.clear();
//            }
//            std::vector<rtree_node> closest_nodes;
//            for(auto flip_flop_it = flip_flops.begin(); flip_flop_it != flip_flops.end(); ++flip_flop_it)
//            {
//                FF & flip_flop = *flip_flop_it;
//                closest_nodes.clear();
//                clusters_rtree.query(boost::geometry::index::nearest(flip_flop.position(), 1), std::back_inserter(closest_nodes));
//                ClusterOOD<FF> *closest_cluster = closest_nodes.front().second;
//                closest_cluster->insertElement(&flip_flop);
//            }
//            for(auto cluster_it = clusters_.begin(); cluster_it != clusters_.end(); ++cluster_it)
//            {
//                auto cluster = *cluster_it;
//                if(cluster.elements().size() != 0)
//                {
//                    double x_c = 0, y_c = 0;
//                    for(FF * p : cluster.elements())
//                    {
//                        x_c += p->position().x();
//                        y_c += p->position().y();
//                    }
//                    x_c = x_c / (double)cluster.elements().size();
//                    y_c = y_c / (double)cluster.elements().size();
//                    cluster.center(geometry::Point(x_c, y_c));
//                }
//            }
//        }
//        metric.end();
//    }

//    void cluster_registers_with_rtree_paralel(std::vector<FF>  &flip_flops, ophidian::experiments::Metric &metric, unsigned iterations = 10)
//    {
//        metric.start();
//        for (int i = 0; i < iterations; ++i)
//        {
//            rtree clusters_rtree;
//            for (ClusterOOD<FF> &cluster : clusters_)
//            {
//                clusters_rtree.insert(rtree_node(cluster.center(), &cluster));
//                cluster.clear();
//            }

//            std::vector<ClusterOOD<FF>*> flip_flop_to_cluster;
//            flip_flop_to_cluster.resize(flip_flops.size());
//            #pragma omp parallel for
//            for (unsigned flip_flop_index = 0; flip_flop_index < flip_flops.size(); ++flip_flop_index)
//            {
//                FF &flip_flop = flip_flops.at(flip_flop_index);
//                std::vector<rtree_node> closest_nodes;
//                clusters_rtree.query(boost::geometry::index::nearest(flip_flop.position(), 1), std::back_inserter(closest_nodes));
//                ClusterOOD<FF> *closest_cluster = closest_nodes.front().second;
//                flip_flop_to_cluster.at(flip_flop_index) = closest_cluster;
//                //            closest_cluster->insertElement(flip_flop);
//            }

//            for(unsigned flip_flop_index = 0; flip_flop_index < flip_flops.size(); ++flip_flop_index)
//            {
//                auto & flip_flop = flip_flops.at(flip_flop_index);
//                ClusterOOD<FF> *cluster = flip_flop_to_cluster.at(flip_flop_index);
//                cluster->insertElement(&flip_flop);
//            }

//            #pragma omp parallel for
//            for (auto cluster = clusters_.begin(); cluster < clusters_.end(); ++cluster)
//            {
//                if(cluster->elements().size() != 0)
//                {
//                    double x_c = 0, y_c = 0;
//                    for(FF * p : cluster->elements())
//                    {
//                        x_c += p->position().x();
//                        y_c += p->position().y();
//                    }
//                    x_c = x_c / (double)cluster->elements().size();
//                    y_c = y_c / (double)cluster->elements().size();
//                    cluster->center(geometry::Point(x_c, y_c));
//                }
//            }
//        }
//        metric.end();
//    }

//};

class ClusterOOD;

class FlipFlop
{
private:
    geometry::Point position_;
    ClusterOOD * clusterBest_;

    std::string name_ = "DFF_X80";
    geometry::Point size_;
    int net_;
public:
    FlipFlop(geometry::Point & p) : position_(p) {
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
    std::vector<FlipFlop *> elements_;
public:
    ClusterOOD(const geometry::Point &center);

    std::vector<FlipFlop *> elements() const;
    void elements(const std::vector<FlipFlop *> &elements);
    geometry::Point center() const;
    void center(const geometry::Point &center);

    void insertElement(FlipFlop *element)
    {
        elements_.push_back(element);
    }

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

    void cluster_registers_with_rtree(std::vector<FlipFlop> &flip_flops,  ophidian::experiments::Metric &metric, unsigned iterations = 10)
    {
        metric.start();
        for (int i = 0; i < iterations; ++i)
        {
            rtree clusters_rtree;
            for (ClusterOOD & cluster : clusters_)
            {
                clusters_rtree.insert(rtree_node(cluster.center(), &cluster));
                cluster.clear();
            }

            std::vector<rtree_node> closest_nodes;
            for (FlipFlop & flip_flop : flip_flops)
            {
                closest_nodes.clear();
                clusters_rtree.query(boost::geometry::index::nearest(flip_flop.position(), 1), std::back_inserter(closest_nodes));
                ClusterOOD * closest_cluster = closest_nodes.front().second;
                closest_cluster->insertElement(&flip_flop);
            }

            for (ClusterOOD & cluster : clusters_)
            {
                if(cluster.elements().size() != 0)
                {
                    double x_c = 0, y_c = 0;
                    for(FlipFlop * p : cluster.elements())
                    {
                        x_c += p->position().x();
                        y_c += p->position().y();
                    }
                    x_c = x_c / (double)cluster.elements().size();
                    y_c = y_c / (double)cluster.elements().size();
                    cluster.center(geometry::Point(x_c, y_c));
                }
            }
        }
        metric.end();
    }

    void cluster_registers_with_rtree_paralel(std::vector<FlipFlop> & flip_flops, ophidian::experiments::Metric &metric, unsigned iterations = 10)
    {
        metric.start();
        for (int i = 0; i < iterations; ++i)
        {
            rtree clusters_rtree;
            for (ClusterOOD & cluster : clusters_)
            {
                clusters_rtree.insert(rtree_node(cluster.center(), &cluster));
                cluster.clear();
            }

            std::vector<ClusterOOD*> flip_flop_to_cluster;
            flip_flop_to_cluster.resize(flip_flops.size());
    #pragma omp parallel for
            for (unsigned flip_flop_index = 0; flip_flop_index < flip_flops.size(); ++flip_flop_index)
            {
                FlipFlop &flip_flop = flip_flops.at(flip_flop_index);
                std::vector<rtree_node> closest_nodes;
                clusters_rtree.query(boost::geometry::index::nearest(flip_flop.position(), 1), std::back_inserter(closest_nodes));
                ClusterOOD * closest_cluster = closest_nodes.front().second;
                flip_flop_to_cluster.at(flip_flop_index) = closest_cluster;
                //            closest_cluster->insertElement(flip_flop);
            }

            for(unsigned flip_flop_index = 0; flip_flop_index < flip_flops.size(); ++flip_flop_index)
            {
                auto flip_flop = flip_flops.at(flip_flop_index);
                ClusterOOD * cluster = flip_flop_to_cluster.at(flip_flop_index);
                cluster->insertElement(&flip_flop);
            }

    #pragma omp parallel for
            for (auto cluster = clusters_.begin(); cluster < clusters_.end(); ++cluster)
            {
                if(cluster->elements().size() != 0)
                {
                    double x_c = 0, y_c = 0;
                    for(FlipFlop * p : cluster->elements())
                    {
                        x_c += p->position().x();
                        y_c += p->position().y();
                    }
                    x_c = x_c / (double)cluster->elements().size();
                    y_c = y_c / (double)cluster->elements().size();
                    cluster->center(geometry::Point(x_c, y_c));
                }
            }
        }
        metric.end();
    }
};


//-------------------------  Class ClusterElement -------------------------
ClusterOOD *FlipFlop::clusterBest() const
{
    return clusterBest_;
}

void FlipFlop::setClusterBest(ClusterOOD *clusterBest)
{
    clusterBest_ = clusterBest;
}

geometry::Point FlipFlop::position() const
{
    return position_;
}

void FlipFlop::setPosition(const geometry::Point &position)
{
    position_ = position;
}




//-------------------------  Class Cluster -------------------------
ophidian::experiments::register_clustering::ClusterOOD::ClusterOOD(const ophidian::geometry::Point &center) : center_(center)
{

}

std::vector<FlipFlop *> ClusterOOD::elements() const
{
    return elements_;
}

void ClusterOOD::elements(const std::vector<FlipFlop *> &clusterElements)
{
    elements_ = clusterElements;
}


geometry::Point ClusterOOD::center() const
{
    return center_;
}

void ClusterOOD::center(const geometry::Point &clusterCenter)
{
    center_ = clusterCenter;
}

//void ClusterOOD::insertElement(const FlipFlop * element)
//{
//    elements_.push_back(element);
//}

void ClusterOOD::clear()
{
    elements_.clear();
}

int ClusterOOD::size()
{
    return elements_.size();
}


//-------------------------  Class KmeansObjectOrientedDesign -------------------------
experiments::register_clustering::KmeansObjectOrientedDesign::KmeansObjectOrientedDesign(geometry::Point chipOrigin, geometry::Point chipBondary, unsigned k) :
    m_distribution_x(chipOrigin.x(),chipBondary.x()), m_distribution_y(chipOrigin.y(),chipBondary.y())
{
    clusters_.reserve(k);
    for (int i = 0; i < k; ++i)
    {
        clusters_.push_back(ophidian::experiments::register_clustering::ClusterOOD(geometry::Point(m_distribution_x(m_generator), m_distribution_y(m_generator))));
    }
}

experiments::register_clustering::KmeansObjectOrientedDesign::KmeansObjectOrientedDesign(const std::vector<geometry::Point> &centers)
{
    clusters_.reserve(centers.size());
    for(auto p : centers)
    {
        clusters_.push_back(ophidian::experiments::register_clustering::ClusterOOD(p));
    }
}



} // namespace register_clustering
} // namespace experiments
} // namespace ophidian


#endif // KMEANSOBJECTORIENTEDDESIGN_H
