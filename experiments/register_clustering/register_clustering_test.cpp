#include "catch.hpp"
#include <iostream>
#include "experiments/experiment.h"
#include "experiments/metric.h"
#include "kmeans_data_oriented_design.h"

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

// ***********************************************************
//  Object-Oriented Design
// ***********************************************************
//  -- sequential
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Register Clustering (kmeans) sequential OOD runtime", "[problem3][OOD][sequential][runtime]")
{
    std::cout << "Test Register Clustering (kmeans) sequential OOD runtime" << std::endl;
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());

//    interconnection_estimate::interconnection_estimate_sequential_ood(*design_, *runtime);

    runtime->print_result();
    runtime->print_file_result(Experiment::getInstance().getOutput_file());
}

// ***********************************************************
//  Object-Oriented Design
// ***********************************************************
//  -- sequential
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Register Clustering (kmeans) sequential OOD cache misses", "[problem3][OOD][sequential][miss]")
{
    std::cout << "Test Register Clustering (kmeans) sequential OOD cache misses" << std::endl;
    int PAPI_events[] = {PAPI_L1_ICM, PAPI_L1_DCM};//Please change this according with your cpu architecture.
    std::unique_ptr<Miss> miss = std::unique_ptr<Miss>(new Miss(PAPI_events, 2));

//    interconnection_estimate::interconnection_estimate_sequential_ood(*design_, *miss);

    miss->print_result();
    miss->print_file_result(Experiment::getInstance().getOutput_file());
}

// ***********************************************************
//  Object-Oriented Design
// ***********************************************************
//  -- parallel
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Register Clustering (kmeans) parallel OOD runtime", "[problem3][OOD][parallel][runtime]")
{
    std::cout << "Test Register Clustering (kmeans) parallel OOD runtime" << std::endl;
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());

//    interconnection_estimate::interconnection_estimate_parallel_ood(*design_, *runtime);

    runtime->print_result();
    runtime->print_file_result(Experiment::getInstance().getOutput_file());
}

// ***********************************************************
//  Object-Oriented Design
// ***********************************************************
//  -- parallel
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Register Clustering (kmeans) parallel OOD cache misses", "[problem3][OOD][parallel][miss]")
{
    std::cout << "Test Register Clustering (kmeans) parallel OOD cache misses" << std::endl;
    int PAPI_events[] = {PAPI_L1_ICM, PAPI_L1_DCM};//Please change this according with your cpu architecture.
    std::unique_ptr<Miss> miss = std::unique_ptr<Miss>(new Miss(PAPI_events, 2));

//    interconnection_estimate::interconnection_estimate_parallel_ood(*design_, *miss);

    miss->print_result();
    miss->print_file_result(Experiment::getInstance().getOutput_file());
}

//________________________________________________________________________________________________________________________________


// ***********************************************************
//  Data-Oriented Design
// ***********************************************************
//  -- sequential
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Register Clustering (kmeans) sequential DOD runtime", "[problem3][DOD][sequential][runtime]")
{
    std::cout << "Test Register Clustering (kmeans) sequential DOD runtime" << std::endl;
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());

//    interconnection_estimate::interconnection_estimate_sequential_DOD(*design_, *runtime);

    runtime->print_result();
    runtime->print_file_result(Experiment::getInstance().getOutput_file());
}

// ***********************************************************
//  Data-Oriented Design
// ***********************************************************
//  -- sequential
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Register Clustering (kmeans) sequential DOD cache misses", "[problem3][DOD][sequential][miss]")
{
    std::cout << "Test Register Clustering (kmeans) sequential DOD cache misses" << std::endl;
    int PAPI_events[] = {PAPI_L1_ICM, PAPI_L1_DCM};//Please change this according with your cpu architecture.
    std::unique_ptr<Miss> miss = std::unique_ptr<Miss>(new Miss(PAPI_events, 2));

//    interconnection_estimate::interconnection_estimate_sequential_DOD(*design_, *miss);

    miss->print_result();
    miss->print_file_result(Experiment::getInstance().getOutput_file());
}

// ***********************************************************
//  Data-Oriented Design
// ***********************************************************
//  -- parallel
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Register Clustering (kmeans) parallel DOD runtime", "[problem3][DOD][parallel][runtime]")
{
    std::cout << "Test Register Clustering (kmeans) parallel DOD runtime" << std::endl;
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());

//    interconnection_estimate::interconnection_estimate_parallel_DOD(*design_, *runtime);

    runtime->print_result();
    runtime->print_file_result(Experiment::getInstance().getOutput_file());
}

// ***********************************************************
//  Data-Oriented Design
// ***********************************************************
//  -- parallel
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Register Clustering (kmeans) parallel DOD cache misses", "[problem3][DOD][parallel][miss]")
{
    std::cout << "Test Register Clustering (kmeans) parallel DOD cache misses" << std::endl;
    int PAPI_events[] = {PAPI_L1_ICM, PAPI_L1_DCM};//Please change this according with your cpu architecture.
    std::unique_ptr<Miss> miss = std::unique_ptr<Miss>(new Miss(PAPI_events, 2));

//    interconnection_estimate::interconnection_estimate_parallel_DOD(*design_, *miss);

    miss->print_result();
    miss->print_file_result(Experiment::getInstance().getOutput_file());
}
