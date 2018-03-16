#ifndef REGISTER_CLUSTERING_SIZE_H
#define REGISTER_CLUSTERING_SIZE_H
#include <iostream>
#include "experiments/experiment.h"
#include "experiments/metric.h"
#include "kmeans_data_oriented_design.h"
#include "kmeans_object_oriented_design.h"

namespace ophidian
{
namespace experiments
{
namespace register_clustering
{

enum FFsize{
    FF25 = 3,
    FF50 = 6,
    FF75 = 9,
    FF100 = 12,
    FF150 = 18,
    FF200 = 24,
    FF400 = 48,
    FF600 = 72,
};

// ***********************************************************
//  Object-Oriented Design
// ***********************************************************
//  -- sequential
//      -- runtime
// ***********************************************************
template<int N>
void OODsequentialRuntime(ophidian::design::Design * design_,  std::vector<ophidian::geometry::Point> & flip_flop_positions, int iterations)
{
//    std::cout << "Test Register Clustering (kmeans) sequential OOD runtime" << std::endl;
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());

    register_clustering::KmeansObjectOrientedDesign kmeansOOD (design_->floorplan().chipOrigin().toPoint(), design_->floorplan().chipUpperRightCorner().toPoint(), (int)(flip_flop_positions.size()/50) );

    using unique_ptr = std::unique_ptr<ophidian::experiments::register_clustering::FlipFlop>;
    using ff = ophidian::experiments::register_clustering::FlipFlopT<N>;
    std::vector< unique_ptr > flip_flops;

    flip_flops.reserve(flip_flop_positions.size());

    for(auto p : flip_flop_positions)
    {

        flip_flops.push_back( unique_ptr(new ff(p)) );
    }

    kmeansOOD.cluster_registers_with_rtree(flip_flops, *runtime, 10);
    for (int i = 0; i < iterations; ++i)
    {
        kmeansOOD.cluster_registers_with_rtree(flip_flops, *runtime, 10);
        runtime->print_result();
        runtime->print_file_result(Experiment::getInstance().getOutput_file());
    }
}

// ***********************************************************
//  Object-Oriented Design
// ***********************************************************
//  -- sequential
//      -- miss
// ***********************************************************
template<int N>
void OODsequentialMiss(ophidian::design::Design * design_,  std::vector<ophidian::geometry::Point> & flip_flop_positions, int iterations)
{
//    std::cout << "Test Register Clustering (kmeans) sequential OOD cache misses" << std::endl;
    int PAPI_events[] = {
        PAPI_L1_DCM,
        PAPI_L1_ICM,
        PAPI_L1_TCM,

        PAPI_L2_DCM,
        PAPI_L2_ICM,
        PAPI_L2_TCM,

        PAPI_L3_TCM
    };//Please change this according with your cpu architecture.
    std::unique_ptr<Miss> miss = std::unique_ptr<Miss>(new Miss(PAPI_events, 7));

    register_clustering::KmeansObjectOrientedDesign kmeansOOD (design_->floorplan().chipOrigin().toPoint(), design_->floorplan().chipUpperRightCorner().toPoint(), (int)(flip_flop_positions.size()/50) );

    using unique_ptr = std::unique_ptr<ophidian::experiments::register_clustering::FlipFlop>;
    using ff = ophidian::experiments::register_clustering::FlipFlopT<N>;
    std::vector< unique_ptr > flip_flops;
    flip_flops.reserve(flip_flop_positions.size());

    for(auto p : flip_flop_positions)
    {
        flip_flops.push_back(unique_ptr(new ff(p)));
    }

    kmeansOOD.cluster_registers_with_rtree(flip_flops, *miss, 10);
    for (int i = 0; i < iterations; ++i)
    {
        kmeansOOD.cluster_registers_with_rtree(flip_flops, *miss, 10);
        miss->print_result();
        miss->print_file_result(Experiment::getInstance().getOutput_file());
    }
}

// ***********************************************************
//  Object-Oriented Design
// ***********************************************************
//  -- parallel
//      -- runtime
// ***********************************************************
template<int N>
void OODparallelRuntime(ophidian::design::Design * design_,  std::vector<ophidian::geometry::Point> & flip_flop_positions, int iterations)
{
//    std::cout << "Test Register Clustering (kmeans) parallel OOD runtime" << std::endl;
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());

    register_clustering::KmeansObjectOrientedDesign kmeansOOD (design_->floorplan().chipOrigin().toPoint(), design_->floorplan().chipUpperRightCorner().toPoint(), (int)(flip_flop_positions.size()/50) );

    using unique_ptr = std::unique_ptr<ophidian::experiments::register_clustering::FlipFlop>;
    using ff = ophidian::experiments::register_clustering::FlipFlopT<N>;
    std::vector< unique_ptr > flip_flops;
    flip_flops.reserve(flip_flop_positions.size());
    for(auto p : flip_flop_positions)
    {
        flip_flops.push_back(unique_ptr(new ff(p)));
    }

    kmeansOOD.cluster_registers_with_rtree_paralel(flip_flops, *runtime, 10);
    for (int i = 0; i < iterations; ++i)
    {
        kmeansOOD.cluster_registers_with_rtree_paralel(flip_flops, *runtime, 10);
        runtime->print_result();
        runtime->print_file_result(Experiment::getInstance().getOutput_file());
    }

}


// ***********************************************************
//  Object-Oriented Design
// ***********************************************************
//  -- parallel
//      -- miss
// ***********************************************************
template<int N>
void OODparallelMiss(ophidian::design::Design * design_,  std::vector<ophidian::geometry::Point> & flip_flop_positions, int iterations)
{
//    std::cout << "Test Register Clustering (kmeans) parallel OOD cache misses" << std::endl;
    int PAPI_events[] = {
        PAPI_L1_DCM,
        PAPI_L1_ICM,
        PAPI_L1_TCM,

        PAPI_L2_DCM,
        PAPI_L2_ICM,
        PAPI_L2_TCM,

        PAPI_L3_TCM
    };//Please change this according with your cpu architecture.
    std::unique_ptr<Miss> miss = std::unique_ptr<Miss>(new Miss(PAPI_events, 7));

    register_clustering::KmeansObjectOrientedDesign kmeansOOD (design_->floorplan().chipOrigin().toPoint(), design_->floorplan().chipUpperRightCorner().toPoint(), (int)(flip_flop_positions.size()/50) );

    using unique_ptr = std::unique_ptr<ophidian::experiments::register_clustering::FlipFlop>;
    using ff = ophidian::experiments::register_clustering::FlipFlopT<N>;
    std::vector< unique_ptr > flip_flops;
    flip_flops.reserve(flip_flop_positions.size());
    for(auto p : flip_flop_positions)
    {
        flip_flops.push_back(unique_ptr(new ff(p)));
    }

    kmeansOOD.cluster_registers_with_rtree_paralel(flip_flops, *miss, 10);
    for (int i = 0; i < iterations; ++i)
    {
        kmeansOOD.cluster_registers_with_rtree_paralel(flip_flops, *miss, 10);
        miss->print_result();
        miss->print_file_result(Experiment::getInstance().getOutput_file());
    }

}


} // namespace register_clustering
} // namespace experiments
} // namespace ophidian

#endif // REGISTER_CLUSTERING_SIZE_H
