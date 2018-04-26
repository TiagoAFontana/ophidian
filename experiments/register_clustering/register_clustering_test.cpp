#include <catch.hpp>
#include <iostream>
#include "experiments/experiment.h"
#include "experiments/metric.h"
#include "kmeans_data_oriented_design.h"
#include "kmeans_object_oriented_design.h"

// PAPI_L1_DCM /*Level 1 data cache misses */
// PAPI_L1_ICM /*Level 1 instruction cache misses */
// PAPI_L2_DCM /*Level 2 data cache misses */
// PAPI_L2_ICM /*Level 2 instruction cache misses */
// PAPI_L3_DCM /*Level 3 data cache misses */
// PAPI_L3_ICM /*Level 3 instruction cache misses */
// PAPI_L1_TCM /*Level 1 total cache misses */
// PAPI_L2_TCM /*Level 2 total cache misses */
// PAPI_L3_TCM /*Level 3 total cache misses */

//Register Clustering (kmeans)

using namespace ophidian;
using namespace ophidian::experiments;
using namespace ophidian::experiments::register_clustering;

#define ITERATIONS 30


//// ***********************************************************
////  Object-Oriented Design
//// ***********************************************************
////  -- sequential
////      -- runtime
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) sequential OOD runtime", "[problem3][OOD][sequential][runtime][e0]")
//{
//    std::cout << "Test Register Clustering (kmeans) sequential OOD runtime" << std::endl;
//    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());

//    using ff = ophidian::experiments::register_clustering::FlipFlop;
//    register_clustering::KmeansObjectOrientedDesign<ff> kmeansOOD (design_->floorplan().chipOrigin().toPoint(), design_->floorplan().chipUpperRightCorner().toPoint(), (int)(flip_flop_positions.size()/50) );

////    using unique_ptr = std::unique_ptr<ophidian::experiments::register_clustering::FlipFlop>;
//    std::vector< ff > flip_flops;

//    flip_flops.reserve(flip_flop_positions.size());

//    for(auto p : flip_flop_positions)
//    {

//        flip_flops.push_back( ff(p) );
//    }

//    kmeansOOD.cluster_registers_with_rtree(flip_flops, *runtime, 10);
//    for (int i = 0; i < ITERATIONS; ++i)
//    {
//        kmeansOOD.cluster_registers_with_rtree(flip_flops, *runtime, 10);

//        runtime->print_result();
//        runtime->print_file_result(Experiment::getInstance().getOutput_file());
//    }
//}

//// ***********************************************************
////  Object-Oriented Design
//// ***********************************************************
////  -- sequential
////      -- miss
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) sequential OOD cache misses", "[problem3][OOD][sequential][miss][e0]")
//{
//    std::cout << "Test Register Clustering (kmeans) sequential OOD cache misses" << std::endl;
//    int PAPI_events[] = {
//        PAPI_L1_DCM,
//        PAPI_L1_ICM,
//        PAPI_L1_TCM,

//        PAPI_L2_DCM,
//        PAPI_L2_ICM,
//        PAPI_L2_TCM,

//        PAPI_L3_TCM
//    };//Please change this according with your cpu architecture.
//    std::unique_ptr<Miss> miss = std::unique_ptr<Miss>(new Miss(PAPI_events, 7));

//    using ff = ophidian::experiments::register_clustering::FlipFlop;
//    register_clustering::KmeansObjectOrientedDesign<ff> kmeansOOD (design_->floorplan().chipOrigin().toPoint(), design_->floorplan().chipUpperRightCorner().toPoint(), (int)(flip_flop_positions.size()/50) );

//    std::vector< ff > flip_flops;
//    flip_flops.reserve(flip_flop_positions.size());

//    for(auto p : flip_flop_positions)
//    {
//        flip_flops.push_back(ff(p));
//    }

//    kmeansOOD.cluster_registers_with_rtree(flip_flops, *miss, 10);
//    for (int i = 0; i < ITERATIONS; ++i)
//    {

//        kmeansOOD.cluster_registers_with_rtree(flip_flops, *miss, 10);

//        miss->print_result();
//        miss->print_file_result(Experiment::getInstance().getOutput_file());

//    }
//}

//// ***********************************************************
////  Object-Oriented Design
//// ***********************************************************
////  -- parallel
////      -- runtime
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) parallel OOD runtime", "[problem3][OOD][parallel][runtime][e0]")
//{
//    std::cout << "Test Register Clustering (kmeans) parallel OOD runtime" << std::endl;
//    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());

//    using ff = ophidian::experiments::register_clustering::FlipFlop;
//    register_clustering::KmeansObjectOrientedDesign<ff> kmeansOOD (design_->floorplan().chipOrigin().toPoint(), design_->floorplan().chipUpperRightCorner().toPoint(), (int)(flip_flop_positions.size()/50) );

//    std::vector< ff > flip_flops;
//    flip_flops.reserve(flip_flop_positions.size());
//    for(auto p : flip_flop_positions)
//    {
//        flip_flops.push_back(ff(p));
//    }

//    kmeansOOD.cluster_registers_with_rtree_paralel(flip_flops, *runtime, 10);
//    for (int i = 0; i < ITERATIONS; ++i)
//    {
//        kmeansOOD.cluster_registers_with_rtree_paralel(flip_flops, *runtime, 10);

//        runtime->print_result();
//        runtime->print_file_result(Experiment::getInstance().getOutput_file());
//    }
//}

//// ***********************************************************
////  Object-Oriented Design
//// ***********************************************************
////  -- parallel
////      -- miss
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) parallel OOD cache misses", "[problem3][OOD][parallel][miss][e0]")
//{
//    std::cout << "Test Register Clustering (kmeans) parallel OOD cache misses" << std::endl;
//    int PAPI_events[] = {
//        PAPI_L1_DCM,
//        PAPI_L1_ICM,
//        PAPI_L1_TCM,

//        PAPI_L2_DCM,
//        PAPI_L2_ICM,
//        PAPI_L2_TCM,

//        PAPI_L3_TCM
//    };//Please change this according with your cpu architecture.
//    std::unique_ptr<Miss> miss = std::unique_ptr<Miss>(new Miss(PAPI_events, 7));

//    using ff = ophidian::experiments::register_clustering::FlipFlop;
//    register_clustering::KmeansObjectOrientedDesign<ff> kmeansOOD (design_->floorplan().chipOrigin().toPoint(), design_->floorplan().chipUpperRightCorner().toPoint(), (int)(flip_flop_positions.size()/50) );

//    std::vector< ff > flip_flops;
//    flip_flops.reserve(flip_flop_positions.size());
//    for(auto p : flip_flop_positions)
//    {
//        flip_flops.push_back(ff(p));
//    }

//    kmeansOOD.cluster_registers_with_rtree_paralel(flip_flops, *miss, 10);
//    for (int i = 0; i < ITERATIONS; ++i)
//    {
//        kmeansOOD.cluster_registers_with_rtree_paralel(flip_flops, *miss, 10);
//        miss->print_result();
//        miss->print_file_result(Experiment::getInstance().getOutput_file());
//    }

//}

// ***********************************************************
//  Object-Oriented Design
// ***********************************************************
//  -- sequential
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) sequential OOD runtime", "[problem3][OOD][sequential][runtime][e0]")
{
    std::cout << "Test Register Clustering (kmeans) sequential OOD runtime" << std::endl;
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());


    register_clustering::KmeansObjectOrientedDesign kmeansOOD (design_->floorplan().chipOrigin().toPoint(), design_->floorplan().chipUpperRightCorner().toPoint(), (int)(flip_flop_positions.size()/50) );

    std::vector< register_clustering::FlipFlop > flip_flops;

    flip_flops.reserve(flip_flop_positions.size());

    for(auto p : flip_flop_positions)
    {

        flip_flops.push_back( register_clustering::FlipFlop(p) );
    }

    kmeansOOD.cluster_registers_with_rtree(flip_flops, *runtime, 10);
    for (int i = 0; i < ITERATIONS; ++i)
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
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) sequential OOD cache misses", "[problem3][OOD][sequential][miss][e0]")
{
    std::cout << "Test Register Clustering (kmeans) sequential OOD cache misses" << std::endl;
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

    std::vector< register_clustering::FlipFlop > flip_flops;
    flip_flops.reserve(flip_flop_positions.size());

    for(auto p : flip_flop_positions)
    {
        flip_flops.push_back(register_clustering::FlipFlop(p));
    }

    kmeansOOD.cluster_registers_with_rtree(flip_flops, *miss, 10);
    for (int i = 0; i < ITERATIONS; ++i)
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
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) parallel OOD runtime", "[problem3][OOD][parallel][runtime][e0]")
{
    std::cout << "Test Register Clustering (kmeans) parallel OOD runtime" << std::endl;
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());

    register_clustering::KmeansObjectOrientedDesign kmeansOOD (design_->floorplan().chipOrigin().toPoint(), design_->floorplan().chipUpperRightCorner().toPoint(), (int)(flip_flop_positions.size()/50) );

    std::vector< register_clustering::FlipFlop > flip_flops;
    flip_flops.reserve(flip_flop_positions.size());
    for(auto p : flip_flop_positions)
    {
        flip_flops.push_back(register_clustering::FlipFlop(p));
    }

    kmeansOOD.cluster_registers_with_rtree_paralel(flip_flops, *runtime, 10);
    for (int i = 0; i < ITERATIONS; ++i)
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
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) parallel OOD cache misses", "[problem3][OOD][parallel][miss][e0]")
{
    std::cout << "Test Register Clustering (kmeans) parallel OOD cache misses" << std::endl;
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

    std::vector< register_clustering::FlipFlop > flip_flops;
    flip_flops.reserve(flip_flop_positions.size());
    for(auto p : flip_flop_positions)
    {
        flip_flops.push_back(register_clustering::FlipFlop(p));
    }

    kmeansOOD.cluster_registers_with_rtree_paralel(flip_flops, *miss, 10);
    for (int i = 0; i < ITERATIONS; ++i)
    {
        kmeansOOD.cluster_registers_with_rtree_paralel(flip_flops, *miss, 10);
        miss->print_result();
        miss->print_file_result(Experiment::getInstance().getOutput_file());
    }

}


//________________________________________________________________________________________________________________________________


// ***********************************************************
//  Data-Oriented Design
// ***********************************************************
//  -- sequential
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) sequential DOD runtime", "[problem3][DOD][sequential][runtime][e0]")
{
    std::cout << "Test Register Clustering (kmeans) sequential DOD runtime" << std::endl;
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());

    register_clustering::KmeansDataOrientedDesign kmeansDOD (design_->floorplan().chipOrigin().toPoint(), design_->floorplan().chipUpperRightCorner().toPoint(), (int)(flip_flop_positions.size()/50) );

    kmeansDOD.cluster_registers_with_rtree(flip_flop_positions, *runtime, 10);
    for (int i = 0; i < ITERATIONS; ++i)
    {
        kmeansDOD.cluster_registers_with_rtree(flip_flop_positions, *runtime, 10);

        runtime->print_result();
        runtime->print_file_result(Experiment::getInstance().getOutput_file());
    }
}

// ***********************************************************
//  Data-Oriented Design
// ***********************************************************
//  -- sequential
//      -- miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) sequential DOD cache misses", "[problem3][DOD][sequential][miss][e0]")
{
    std::cout << "Test Register Clustering (kmeans) sequential DOD cache misses" << std::endl;
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

    register_clustering::KmeansDataOrientedDesign kmeansDOD (design_->floorplan().chipOrigin().toPoint(), design_->floorplan().chipUpperRightCorner().toPoint(), (int)(flip_flop_positions.size()/50) );

    kmeansDOD.cluster_registers_with_rtree(flip_flop_positions, *miss, 10);
    for (int i = 0; i < ITERATIONS; ++i)
    {

        kmeansDOD.cluster_registers_with_rtree(flip_flop_positions, *miss, 10);

        miss->print_result();
        miss->print_file_result(Experiment::getInstance().getOutput_file());

    }
}

// ***********************************************************
//  Data-Oriented Design
// ***********************************************************
//  -- parallel
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) parallel DOD runtime", "[problem3][DOD][parallel][runtime][e0]")
{
    std::cout << "Test Register Clustering (kmeans) parallel DOD runtime" << std::endl;
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());

    register_clustering::KmeansDataOrientedDesign kmeansDOD (design_->floorplan().chipOrigin().toPoint(), design_->floorplan().chipUpperRightCorner().toPoint(), (int)(flip_flop_positions.size()/50) );

    kmeansDOD.cluster_registers_with_rtree_parallel(flip_flop_positions, *runtime, 10);
    for (int i = 0; i < ITERATIONS; ++i)
    {
        kmeansDOD.cluster_registers_with_rtree_parallel(flip_flop_positions, *runtime, 10);

        runtime->print_result();
        runtime->print_file_result(Experiment::getInstance().getOutput_file());
    }
}

// ***********************************************************
//  Data-Oriented Design
// ***********************************************************
//  -- parallel
//      -- miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) parallel DOD cache misses", "[problem3][DOD][parallel][miss][e0]")
{
    std::cout << "Test Register Clustering (kmeans) parallel DOD cache misses" << std::endl;
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

    register_clustering::KmeansDataOrientedDesign kmeansDOD (design_->floorplan().chipOrigin().toPoint(), design_->floorplan().chipUpperRightCorner().toPoint(), (int)(flip_flop_positions.size()/50) );

    kmeansDOD.cluster_registers_with_rtree_parallel(flip_flop_positions, *miss, 10);
    for (int i = 0; i < ITERATIONS; ++i)
    {
        kmeansDOD.cluster_registers_with_rtree_parallel(flip_flop_positions, *miss, 10);

        miss->print_result();
        miss->print_file_result(Experiment::getInstance().getOutput_file());
    }
}
