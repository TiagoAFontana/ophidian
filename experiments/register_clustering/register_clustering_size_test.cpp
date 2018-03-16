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

#include "register_clustering_size.h"

using namespace ophidian;
using namespace ophidian::experiments;
using namespace ophidian::experiments::register_clustering;

#define ITERATIONS 10

TEST_CASE("Test size of FlipFlop", "[FF]")
{
    std::cout << "size of FF: "<< sizeof(ophidian::experiments::register_clustering::FlipFlopF) <<std::endl;
    std::cout << "size of FF0: " << sizeof(ophidian::experiments::register_clustering::FlipFlopT<0>) <<std::endl;
    std::cout << "size of FF25: " << sizeof(ophidian::experiments::register_clustering::FlipFlopT<3>) <<std::endl;
    std::cout << "size of FF50: " << sizeof(ophidian::experiments::register_clustering::FlipFlopT<6>) <<std::endl;
    std::cout << "size of FF75: " << sizeof(ophidian::experiments::register_clustering::FlipFlopT<9>) <<std::endl;
    std::cout << "size of FF100: "<< sizeof(ophidian::experiments::register_clustering::FlipFlopT<12>) <<std::endl;
    std::cout << "size of FF150: "<< sizeof(ophidian::experiments::register_clustering::FlipFlopT<18>) <<std::endl;
    std::cout << "size of FF200: "<< sizeof(ophidian::experiments::register_clustering::FlipFlopT<24>) <<std::endl;
    std::cout << "size of FF400: "<< sizeof(ophidian::experiments::register_clustering::FlipFlopT<48>) <<std::endl;
    std::cout << "size of FF600<>: "<< sizeof(ophidian::experiments::register_clustering::FlipFlopT<72>) <<std::endl;
    std::cout << "size of FF600 fix: "<< sizeof(ophidian::experiments::register_clustering::FlipFlopF600) <<std::endl;
    std::cout << "size of FFExt fix: "<< sizeof(ophidian::experiments::register_clustering::FlipFlopExt) <<std::endl;


    std::cout << "size of multibox: "<< sizeof(ophidian::geometry::MultiBox) <<std::endl;
    std::cout << "size of Location: "<< sizeof(ophidian::util::LocationDbu) <<std::endl;
    std::cout << "size of bool: "<< sizeof(bool) <<std::endl;
    std::cout << "size of *standard_cell: "<< sizeof(std::unique_ptr<ophidian::standard_cell::StandardCells>) <<std::endl;
    std::cout << "size of string: "<< sizeof("asdasdasdasd") <<std::endl;
    std::cout << "size of *Pin: "<< sizeof(std::unique_ptr<ophidian::circuit::Pin>) <<std::endl;
    std::cout << "size of vector[*Pin]: "<< sizeof(std::vector<std::unique_ptr<ophidian::circuit::Pin>>) <<std::endl;
    std::vector<std::unique_ptr<ophidian::circuit::Pin>> v;
//    v.push_back( std::make_unique<ophidian::circuit::Pin()>( ophidian::circuit::Pin()) );
//    v.push_back( std::make_unique<ophidian::circuit::Pin()>( ophidian::circuit::Pin()) );
//    v.push_back( std::make_unique<ophidian::circuit::Pin()>( ophidian::circuit::Pin()) );
//    v.push_back( std::make_unique<ophidian::circuit::Pin()>( ophidian::circuit::Pin()) );
    std::cout << "size of vector[*Pin] populado: "<< sizeof(v) <<std::endl;
}

// ***********************************************************
//  Object-Oriented Design : extra 0%
// ***********************************************************
//  -- sequential
//      -- Miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD mis e0", "[problem3][OOD][sequential][miss][e0]")
{
    std::cout << "Test Register Clustering (kmeans) sequential OOD miss e0" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODsequentialMiss<0>(design, ff, ITERATIONS);
}
// ***********************************************************
//  Object-Oriented Design : extra 0%
// ***********************************************************
//  -- parallel
//      -- Miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD miss e0", "[problem3][OOD][parallel][miss][e0]")
{
    std::cout << "Test Register Clustering (kmeans) parallel OOD miss e0" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODparallelMiss<0>(design, ff, ITERATIONS);
}


// ***********************************************************
//  Object-Oriented Design : extra 400%
// ***********************************************************
//  -- sequential
//      -- Miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD mis e400", "[problem3][OOD][sequential][miss][e400]")
{
    std::cout << "Test Register Clustering (kmeans) sequential OOD miss e400" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODsequentialMiss<FF400>(design, ff, ITERATIONS);
}
// ***********************************************************
//  Object-Oriented Design : extra 400%
// ***********************************************************
//  -- parallel
//      -- Miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD miss e400", "[problem3][OOD][parallel][miss][e400]")
{
    std::cout << "Test Register Clustering (kmeans) parallel OOD miss e400" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODparallelMiss<FF400>(design, ff, ITERATIONS);
}
// ***********************************************************
//  Object-Oriented Design : extra 600%
// ***********************************************************
//  -- sequential
//      -- Miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD mis e600", "[problem3][OOD][sequential][miss][e600]")
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

    register_clustering::KmeansObjectOrientedDesign kmeansOOD (design_->floorplan().chipOrigin().toPoint(), design_->floorplan().chipUpperRightCorner().toPoint(), (int)(flip_flop_positions.size()/50) );

    using unique_ptr = std::unique_ptr<ophidian::experiments::register_clustering::FlipFlop>;
    using ff = ophidian::experiments::register_clustering::FlipFlopExt;
    std::vector< ff > flip_flops;
    flip_flops.reserve(flip_flop_positions.size());

    for(auto p : flip_flop_positions)
    {
        flip_flops.push_back(ff(p));
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
//  Object-Oriented Design : extra 600%
// ***********************************************************
//  -- parallel
//      -- Miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD miss e600", "[problem3][OOD][parallel][miss][e600]")
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
    using ff = ophidian::experiments::register_clustering::FlipFlopF600;
    std::vector< unique_ptr > flip_flops;
    flip_flops.reserve(flip_flop_positions.size());
    for(auto p : flip_flop_positions)
    {
        flip_flops.push_back(unique_ptr(new ff(p)));
    }

    kmeansOOD.cluster_registers_with_rtree_paralel(flip_flops, *miss, 10);
    for (int i = 0; i < ITERATIONS; ++i)
    {
        kmeansOOD.cluster_registers_with_rtree_paralel(flip_flops, *miss, 10);
        miss->print_result();
        miss->print_file_result(Experiment::getInstance().getOutput_file());
    }
}


// ***********************************************************
//  Object-Oriented Design : extra 25%
// ***********************************************************
//  -- sequential
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD runtime e25", "[problem3][OOD][sequential][runtime][e25]")
{
    std::cout << "Test Register Clustering (kmeans) sequential OOD runtime e25" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODsequentialRuntime<FF25>(design, ff, ITERATIONS);
}
// ***********************************************************
//  Object-Oriented Design : extra 25%
// ***********************************************************
//  -- sequential
//      -- Miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD mis e25", "[problem3][OOD][sequential][miss][e25]")
{
    std::cout << "Test Register Clustering (kmeans) sequential OOD miss e25" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODsequentialMiss<FF25>(design, ff, ITERATIONS);
}
// ***********************************************************
//  Object-Oriented Design : extra 25%
// ***********************************************************
//  -- parallel
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD runtime e25", "[problem3][OOD][parallel][runtime][e25]")
{
    std::cout << "Test Register Clustering (kmeans) parallel OOD runtime e25" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODparallelRuntime<FF25>(design, ff, ITERATIONS);
}
// ***********************************************************
//  Object-Oriented Design : extra 25%
// ***********************************************************
//  -- parallel
//      -- Miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD miss e25", "[problem3][OOD][parallel][miss][e25]")
{
    std::cout << "Test Register Clustering (kmeans) parallel OOD miss e25" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODparallelMiss<FF25>(design, ff, ITERATIONS);
}

// **********************************************************************************************************************
// **********************************************************************************************************************

// ***********************************************************
//  Object-Oriented Design : extra 50%
// ***********************************************************
//  -- sequential
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD runtime e50", "[problem3][OOD][sequential][runtime][e50]")
{
    std::cout << "Test Register Clustering (kmeans) sequential OOD runtime e50" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODsequentialRuntime<FF50>(design, ff, ITERATIONS);
}
// ***********************************************************
//  Object-Oriented Design : extra 50%
// ***********************************************************
//  -- sequential
//      -- Miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD mis e50", "[problem3][OOD][sequential][miss][e50]")
{
    std::cout << "Test Register Clustering (kmeans) sequential OOD miss e50" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODsequentialMiss<FF50>(design, ff, ITERATIONS);
}
// ***********************************************************
//  Object-Oriented Design : extra 50%
// ***********************************************************
//  -- parallel
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD runtime e50", "[problem3][OOD][parallel][runtime][e50]")
{
    std::cout << "Test Register Clustering (kmeans) parallel OOD runtime e50" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODparallelRuntime<FF50>(design, ff, ITERATIONS);
}
// ***********************************************************
//  Object-Oriented Design : extra 50%
// ***********************************************************
//  -- parallel
//      -- Miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD miss e50", "[problem3][OOD][parallel][miss][e50]")
{
    std::cout << "Test Register Clustering (kmeans) parallel OOD miss e50" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODparallelMiss<FF50>(design, ff, ITERATIONS);
}

// **********************************************************************************************************************
// **********************************************************************************************************************

// ***********************************************************
//  Object-Oriented Design : extra 75%
// ***********************************************************
//  -- sequential
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD runtime e75", "[problem3][OOD][sequential][runtime][e75]")
{
    std::cout << "Test Register Clustering (kmeans) sequential OOD runtime e75" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODsequentialRuntime<FF75>(design, ff, ITERATIONS);
}
// ***********************************************************
//  Object-Oriented Design : extra 75%
// ***********************************************************
//  -- sequential
//      -- Miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD mis e75", "[problem3][OOD][sequential][miss][e75]")
{
    std::cout << "Test Register Clustering (kmeans) sequential OOD miss e75" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODsequentialMiss<FF75>(design, ff, ITERATIONS);
}
// ***********************************************************
//  Object-Oriented Design : extra 75%
// ***********************************************************
//  -- parallel
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD runtime e75", "[problem3][OOD][parallel][runtime][e75]")
{
    std::cout << "Test Register Clustering (kmeans) parallel OOD runtime e75" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODparallelRuntime<FF75>(design, ff, ITERATIONS);
}
// ***********************************************************
//  Object-Oriented Design : extra 75%
// ***********************************************************
//  -- parallel
//      -- Miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD miss e75", "[problem3][OOD][parallel][miss][e75]")
{
    std::cout << "Test Register Clustering (kmeans) parallel OOD miss e75" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODparallelMiss<FF75>(design, ff, ITERATIONS);
}

// **********************************************************************************************************************
// **********************************************************************************************************************

// ***********************************************************
//  Object-Oriented Design : extra 100%
// ***********************************************************
//  -- sequential
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD runtime e100", "[problem3][OOD][sequential][runtime][e100]")
{
    std::cout << "Test Register Clustering (kmeans) sequential OOD runtime e100" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODsequentialRuntime<FF100>(design, ff, ITERATIONS);
}
// ***********************************************************
//  Object-Oriented Design : extra 100%
// ***********************************************************
//  -- sequential
//      -- Miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD mis e100", "[problem3][OOD][sequential][miss][e100]")
{
    std::cout << "Test Register Clustering (kmeans) sequential OOD miss e100" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODsequentialMiss<FF100>(design, ff, ITERATIONS);
}
// ***********************************************************
//  Object-Oriented Design : extra 100%
// ***********************************************************
//  -- parallel
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD runtime e100", "[problem3][OOD][parallel][runtime][e100]")
{
    std::cout << "Test Register Clustering (kmeans) parallel OOD runtime e100" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODparallelRuntime<FF100>(design, ff, ITERATIONS);
}
// ***********************************************************
//  Object-Oriented Design : extra 100%
// ***********************************************************
//  -- parallel
//      -- Miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD miss e100", "[problem3][OOD][parallel][miss][e100]")
{
    std::cout << "Test Register Clustering (kmeans) parallel OOD miss e100" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODparallelMiss<FF100>(design, ff, ITERATIONS);
}

// **********************************************************************************************************************
// **********************************************************************************************************************

// ***********************************************************
//  Object-Oriented Design : extra 150%
// ***********************************************************
//  -- sequential
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD runtime e150", "[problem3][OOD][sequential][runtime][e150]")
{
    std::cout << "Test Register Clustering (kmeans) sequential OOD runtime e150" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODsequentialRuntime<FF150>(design, ff, ITERATIONS);
}
// ***********************************************************
//  Object-Oriented Design : extra 150%
// ***********************************************************
//  -- sequential
//      -- Miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD mis e150", "[problem3][OOD][sequential][miss][e150]")
{
    std::cout << "Test Register Clustering (kmeans) sequential OOD miss e150" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODsequentialMiss<FF150>(design, ff, ITERATIONS);
}
// ***********************************************************
//  Object-Oriented Design : extra 150%
// ***********************************************************
//  -- parallel
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD runtime e150", "[problem3][OOD][parallel][runtime][e150]")
{
    std::cout << "Test Register Clustering (kmeans) parallel OOD runtime e150" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODparallelRuntime<FF150>(design, ff, ITERATIONS);
}
// ***********************************************************
//  Object-Oriented Design : extra 150%
// ***********************************************************
//  -- parallel
//      -- Miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD miss e150", "[problem3][OOD][parallel][miss][e150]")
{
    std::cout << "Test Register Clustering (kmeans) parallel OOD miss e150" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODparallelMiss<FF150>(design, ff, ITERATIONS);
}

// **********************************************************************************************************************
// **********************************************************************************************************************

// ***********************************************************
//  Object-Oriented Design : extra 200%
// ***********************************************************
//  -- sequential
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD runtime e200", "[problem3][OOD][sequential][runtime][e200]")
{
    std::cout << "Test Register Clustering (kmeans) sequential OOD runtime e200" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODsequentialRuntime<FF200>(design, ff, ITERATIONS);
}
// ***********************************************************
//  Object-Oriented Design : extra 200%
// ***********************************************************
//  -- sequential
//      -- Miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD mis e200", "[problem3][OOD][sequential][miss][e200]")
{
    std::cout << "Test Register Clustering (kmeans) sequential OOD miss e200" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODsequentialMiss<FF200>(design, ff, ITERATIONS);
}
// ***********************************************************
//  Object-Oriented Design : extra 200%
// ***********************************************************
//  -- parallel
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD runtime e200", "[problem3][OOD][parallel][runtime][e200]")
{
    std::cout << "Test Register Clustering (kmeans) parallel OOD runtime e200" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODparallelRuntime<FF200>(design, ff, ITERATIONS);
}
// ***********************************************************
//  Object-Oriented Design : extra 200%
// ***********************************************************
//  -- parallel
//      -- Miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD miss e200", "[problem3][OOD][parallel][miss][e200]")
{
    std::cout << "Test Register Clustering (kmeans) parallel OOD miss e200" << std::endl;
    auto * design = this->design_;
    auto & ff = this->flip_flop_positions;
    OODparallelMiss<FF200>(design, ff, ITERATIONS);
}
