#include "kmeans_data_oriented_design.h"
#include <boost/geometry/index/rtree.hpp>
namespace ophidian
{
namespace experiments
{
namespace register_clustering
{
KmeansDataOrientedDesign::KmeansDataOrientedDesign(geometry::Point chipOrigin, geometry::Point chipBondary, unsigned k) :
    clusterCenters_(clusters_), 
    clusterElements_(clusters_), 
    m_distribution_x(chipOrigin.x(),chipBondary.x()), 
    m_distribution_y(chipOrigin.y(),chipBondary.y())
{
    clusters_.reserve(k);
    for (int i = 0; i < k; ++i)
    {
        auto cluster = clusters_.add();
        clusterCenters_[cluster] = geometry::Point(m_distribution_x(m_generator), m_distribution_y(m_generator));
    }
}

KmeansDataOrientedDesign::KmeansDataOrientedDesign(const std::vector<geometry::Point> &centers) :
    clusterCenters_(clusters_), clusterElements_(clusters_)
{
    for(auto p : centers)
    {
        auto cluster = clusters_.add();
        clusterCenters_[cluster] = p;
    }

}

void KmeansDataOrientedDesign::cluster_registers_with_rtree(const std::vector<geometry::Point> &flip_flops, Metric &metric, unsigned iterations)
{
    metric.start();
    for (int i = 0; i < iterations; ++i)
    {
        rtree clusters_rtree;

//        for (auto & cluster : clusters_)
        for(auto cluster_it = clusters_.begin(); cluster_it != clusters_.end(); ++cluster_it)
        {
            const Cluster & cluster = *cluster_it;
            clusters_rtree.insert(rtree_node(clusterCenters_[cluster], &cluster));
            clusterElements_[cluster].clear();
        }

        std::vector<rtree_node> closest_nodes;
        for(auto flip_flop_it = flip_flops.begin(); flip_flop_it != flip_flops.end(); ++flip_flop_it)
        {
            auto flip_flop = *flip_flop_it;
            closest_nodes.clear();
            clusters_rtree.query(boost::geometry::index::nearest(flip_flop, 1), std::back_inserter(closest_nodes));
            auto closest_cluster = *closest_nodes.front().second;
            clusterElements_[closest_cluster].push_back(flip_flop);
        }

        for(auto cluster_it = clusters_.begin(); cluster_it != clusters_.end(); ++cluster_it)
        {
            auto cluster = *cluster_it;
            if(clusterElements_[cluster].size() != 0)
            {
                double x_c = 0, y_c = 0;
                for(auto p : clusterElements_[cluster])
                {
                    x_c += p.x();
                    y_c += p.y();
                }
                x_c = x_c / (double)clusterElements_[cluster].size();
                y_c = y_c / (double)clusterElements_[cluster].size();
                clusterCenters_[cluster] = geometry::Point(x_c, y_c);
            }
        }
    }
    metric.end();
}

void KmeansDataOrientedDesign::cluster_registers_with_rtree_parallel(const std::vector<geometry::Point> &flip_flops, Metric &metric, unsigned iterations)
{
    metric.start();
    for (int i = 0; i < iterations; ++i)
    {
        rtree clusters_rtree;
//        for (auto & cluster : clusters_)
        for(auto cluster_it = clusters_.begin(); cluster_it != clusters_.end(); ++cluster_it)
        {
            const Cluster & cluster = *cluster_it;
            clusters_rtree.insert(rtree_node(clusterCenters_[cluster], &cluster));
            clusterElements_[cluster].clear();
        }

        std::vector<Cluster> flip_flop_to_cluster;
        flip_flop_to_cluster.resize(flip_flops.size());
#pragma omp parallel for
        for (unsigned flip_flop_index = 0; flip_flop_index < flip_flops.size(); ++flip_flop_index)
        {
            auto flip_flop = flip_flops.at(flip_flop_index);
            std::vector<rtree_node> closest_nodes;
            clusters_rtree.query(boost::geometry::index::nearest(flip_flop, 1), std::back_inserter(closest_nodes));
            auto closest_cluster = *closest_nodes.front().second;
            flip_flop_to_cluster.at(flip_flop_index) = closest_cluster;
        }

        for(unsigned flip_flop_index = 0; flip_flop_index < flip_flops.size(); ++flip_flop_index)
        {
            auto flip_flop = flip_flops.at(flip_flop_index);
            auto cluster = flip_flop_to_cluster.at(flip_flop_index);
            clusterElements_[cluster].push_back(flip_flop);
        }

#pragma omp parallel for
        for (auto cluster = clusters_.begin(); cluster < clusters_.end(); ++cluster)
        {
            if(clusterElements_[*cluster].size() != 0)
            {
                double x_c = 0, y_c = 0;
                for(auto p : clusterElements_[*cluster])
                {
                    x_c += p.x();
                    y_c += p.y();
                }
                x_c = x_c / (double)clusterElements_[*cluster].size();
                y_c = y_c / (double)clusterElements_[*cluster].size();
                clusterCenters_[*cluster] = geometry::Point(x_c, y_c);
            }
        }
    }
    metric.end();
}



#if 0
KmeansDataOrientedDesign::KmeansDataOrientedDesign(geometry::Point chipOrigin, geometry::Point chipBondary, unsigned k) :
    clusterCenters_(clusters_), clusterElements_(clusters_), m_distribution_x(chipOrigin.x(),chipBondary.x()), m_distribution_y(chipOrigin.y(),chipBondary.y())
{
    clusters_.reserve(k);
    for (int i = 0; i < k; ++i)
    {
        auto cluster = clusters_.add();
        clusterCenters_[cluster].first = geometry::Point(m_distribution_x(m_generator), m_distribution_y(m_generator));
        clusterCenters_[cluster].second = cluster;
    }
}

KmeansDataOrientedDesign::KmeansDataOrientedDesign(const std::vector<geometry::Point> &centers) :
    clusterCenters_(clusters_), clusterElements_(clusters_)
{
    for(auto p : centers)
    {
        auto cluster = clusters_.add();
        clusterCenters_[cluster].first = p;
        clusterCenters_[cluster].second = cluster;
    }

}

void KmeansDataOrientedDesign::cluster_registers_with_rtree(const std::vector<geometry::Point> &flip_flops, ophidian::experiments::Metric &metric, unsigned iterations)
{
    metric.start();
    for (int i = 0; i < iterations; ++i)
    {
        rtree clusters_rtree;

//        std::cout<< "Inicializando RTre"<<std::endl;
//        metric.start();
        for (auto & cluster : clusters_)
        {
            clusters_rtree.insert(rtree_node(clusterCenters_[cluster].first, cluster));
            clusterElements_[cluster].clear();
        }

//        metric.end();
//        metric.print_result();
//        std::cout<< "encontrando cluster"<<std::endl;
//        metric.start();

//        for (auto & flip_flop : flip_flops)
        std::vector<rtree_node> closest_nodes;
        for(auto flip_flop_it = flip_flops.begin(); flip_flop_it != flip_flops.end(); ++flip_flop_it)
        {
            auto flip_flop = *flip_flop_it;
            closest_nodes.clear();
            clusters_rtree.query(boost::geometry::index::nearest(flip_flop, 1), std::back_inserter(closest_nodes));
            auto closest_cluster = closest_nodes.front().second;
            clusterElements_[closest_cluster].push_back(flip_flop);
        }

//        metric.end();
//        metric.print_result();
//        std::cout<< "Atualizando centro do cluster "<<std::endl;
//        metric.start();

//        for (auto & cluster : clusters_)
        for(auto cluster_it = clusters_.begin(); cluster_it != clusters_.end(); ++cluster_it)
        {
            auto cluster = *cluster_it;
            if(clusterElements_[cluster].size() != 0)
            {
                double x_c = 0, y_c = 0;
                for(auto p : clusterElements_[cluster])
                {
                    x_c += p.x();
                    y_c += p.y();
                }
                x_c = x_c / (double)clusterElements_[cluster].size();
                y_c = y_c / (double)clusterElements_[cluster].size();
                clusterCenters_[cluster].first = geometry::Point(x_c, y_c);
            }
        }
//        metric.end();
//        metric.print_result();
    }
    metric.end();
}

void KmeansDataOrientedDesign::cluster_registers_with_rtree_parallel(const std::vector<geometry::Point> &flip_flops, ophidian::experiments::Metric &metric, unsigned iterations)
{
    metric.start();
    for (int i = 0; i < iterations; ++i)
    {
        rtree clusters_rtree;
        for (auto & cluster : clusters_)
        {
            clusters_rtree.insert(rtree_node(clusterCenters_[cluster].first, cluster));
            clusterElements_[cluster].clear();
        }

        std::vector<Cluster> flip_flop_to_cluster;
        flip_flop_to_cluster.resize(flip_flops.size());
#pragma omp parallel for
        for (unsigned flip_flop_index = 0; flip_flop_index < flip_flops.size(); ++flip_flop_index)
        {
            auto flip_flop = flip_flops.at(flip_flop_index);
            std::vector<rtree_node> closest_nodes;
            clusters_rtree.query(boost::geometry::index::nearest(flip_flop, 1), std::back_inserter(closest_nodes));
            auto closest_cluster = closest_nodes.front().second;
            flip_flop_to_cluster.at(flip_flop_index) = closest_cluster;
        }

        for(unsigned flip_flop_index = 0; flip_flop_index < flip_flops.size(); ++flip_flop_index)
        {
            auto flip_flop = flip_flops.at(flip_flop_index);
            auto cluster = flip_flop_to_cluster.at(flip_flop_index);
            clusterElements_[cluster].push_back(flip_flop);
        }

#pragma omp parallel for
        for (auto cluster = clusters_.begin(); cluster < clusters_.end(); ++cluster)
        {
            if(clusterElements_[*cluster].size() != 0)
            {
                double x_c = 0, y_c = 0;
                for(auto p : clusterElements_[*cluster])
                {
                    x_c += p.x();
                    y_c += p.y();
                }
                x_c = x_c / (double)clusterElements_[*cluster].size();
                y_c = y_c / (double)clusterElements_[*cluster].size();
                clusterCenters_[*cluster].first = geometry::Point(x_c, y_c);
            }
        }
    }
    metric.end();
}
#endif

} // namespace register_clustering
} // namespace experiments
} // namespace ophidian
