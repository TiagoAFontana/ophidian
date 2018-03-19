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

//// ***********************************************************
////  Object-Oriented Design
//// ***********************************************************
////  -- sequential
////      -- runtime
//// ***********************************************************
template<class FF>
void OODsequentialRuntime(ophidian::design::Design * design_,  std::vector<ophidian::geometry::Point> & flip_flop_positions, int iterations)
{
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());

    register_clustering::KmeansObjectOrientedDesign<FF> kmeansOOD (design_->floorplan().chipOrigin().toPoint(), design_->floorplan().chipUpperRightCorner().toPoint(), (int)(flip_flop_positions.size()/50) );

    std::vector< FF > flip_flops;
    flip_flops.reserve(flip_flop_positions.size());
    for(auto p : flip_flop_positions)
    {

        flip_flops.push_back( FF(p) );
    }

    kmeansOOD.cluster_registers_with_rtree(flip_flops, *runtime, 10);
    for (int i = 0; i < iterations; ++i)
    {
        kmeansOOD.cluster_registers_with_rtree(flip_flops, *runtime, 10);
        runtime->print_result();
        runtime->print_file_result(Experiment::getInstance().getOutput_file());
    }
}

//// ***********************************************************
////  Object-Oriented Design
//// ***********************************************************
////  -- sequential
////      -- miss
//// ***********************************************************
template<class FF>
void OODsequentialMiss(ophidian::design::Design * design_,  std::vector<ophidian::geometry::Point> & flip_flop_positions, int iterations)
{
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

    register_clustering::KmeansObjectOrientedDesign<FF> kmeansOOD (design_->floorplan().chipOrigin().toPoint(), design_->floorplan().chipUpperRightCorner().toPoint(), (int)(flip_flop_positions.size()/50) );

    std::vector< FF > flip_flops;
    flip_flops.reserve(flip_flop_positions.size());

    for(auto p : flip_flop_positions)
    {
        flip_flops.push_back(FF(p));
    }

    kmeansOOD.cluster_registers_with_rtree(flip_flops, *miss, 10);
    for (int i = 0; i < iterations; ++i)
    {
        kmeansOOD.cluster_registers_with_rtree(flip_flops, *miss, 10);
        miss->print_result();
        miss->print_file_result(Experiment::getInstance().getOutput_file());
    }
}

//// ***********************************************************
////  Object-Oriented Design
//// ***********************************************************
////  -- parallel
////      -- runtime
//// ***********************************************************
template<class FF>
void OODparallelRuntime(ophidian::design::Design * design_,  std::vector<ophidian::geometry::Point> & flip_flop_positions, int iterations)
{
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());

    register_clustering::KmeansObjectOrientedDesign<FF> kmeansOOD (design_->floorplan().chipOrigin().toPoint(), design_->floorplan().chipUpperRightCorner().toPoint(), (int)(flip_flop_positions.size()/50) );

    std::vector< FF > flip_flops;
    flip_flops.reserve(flip_flop_positions.size());
    for(auto p : flip_flop_positions)
    {
        flip_flops.push_back(FF(p));
    }

    kmeansOOD.cluster_registers_with_rtree_paralel(flip_flops, *runtime, 10);
    for (int i = 0; i < iterations; ++i)
    {
        kmeansOOD.cluster_registers_with_rtree_paralel(flip_flops, *runtime, 10);
        runtime->print_result();
        runtime->print_file_result(Experiment::getInstance().getOutput_file());
    }

}


//// ***********************************************************
////  Object-Oriented Design
//// ***********************************************************
////  -- parallel
////      -- miss
//// ***********************************************************
template<class FF>
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

    register_clustering::KmeansObjectOrientedDesign<FF> kmeansOOD (design_->floorplan().chipOrigin().toPoint(), design_->floorplan().chipUpperRightCorner().toPoint(), (int)(flip_flop_positions.size()/50) );

    std::vector< FF > flip_flops;
    flip_flops.reserve(flip_flop_positions.size());
    for(auto p : flip_flop_positions)
    {
        flip_flops.push_back(FF(p));
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
