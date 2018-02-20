#include "../test/catch.hpp"
#include <iostream>
#include "experiments/experiment.h"
#include "experiments/metric.h"
#include "Interconnections.h"

// PAPI_L1_DCM /*Level 1 data cache misses */
// PAPI_L1_ICM /*Level 1 instruction cache misses */
// PAPI_L2_DCM /*Level 2 data cache misses */
// PAPI_L2_ICM /*Level 2 instruction cache misses */
// PAPI_L3_DCM /*Level 3 data cache misses */
// PAPI_L3_ICM /*Level 3 instruction cache misses */
// PAPI_L1_TCM /*Level 1 total cache misses */
// PAPI_L2_TCM /*Level 2 total cache misses */
// PAPI_L3_TCM /*Level 3 total cache misses */

//interconnection_estimate

#define ITERATIONS 1

using namespace ophidian;
using namespace ophidian::experiments;
using namespace ophidian::experiments::interconnection_estimate;

// ***********************************************************
//  Object-Oriented Design
// ***********************************************************
//  -- sequential
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Interconection sequential OOD runtime", "[problem2][OOD][sequential][runtime]")
{
    std::cout << "Test Interconection sequential OOD runtime" << std::endl;
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());
    interconnection_estimate::interconnection_estimate_sequential_ood(*design_, *runtime);
    runtime->print_result();
    runtime->print_file_result(Experiment::getInstance().getOutput_file());
}

// ***********************************************************
//  Object-Oriented Design
// ***********************************************************
//  -- sequential
//      -- cache miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Interconection sequential OOD cache misses", "[problem2][OOD][sequential][miss]")
{
    std::cout << "Test Interconection sequential OOD cache misses" << std::endl;
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

    for (int i = 0; i < ITERATIONS; ++i)
    {
        interconnection_estimate::interconnection_estimate_sequential_ood(*design_, *miss);
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
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Interconection parallel OOD runtime", "[problem2][OOD][parallel][runtime]")
{
    std::cout << "Test Interconection parallel OOD runtime" << std::endl;
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());
    interconnection_estimate::interconnection_estimate_parallel_ood(*design_, *runtime);
    runtime->print_result();
    runtime->print_file_result(Experiment::getInstance().getOutput_file());
}

// ***********************************************************
//  Object-Oriented Design
// ***********************************************************
//  -- parallel
//      -- cache miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Interconection parallel OOD cache misses", "[problem2][OOD][parallel][miss]")
{
    std::cout << "Test Interconection parallel OOD cache misses" << std::endl;
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
    for (int i = 0; i < ITERATIONS; ++i)
    {
        interconnection_estimate::interconnection_estimate_parallel_ood(*design_, *miss);
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
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Interconection sequential DOD runtime", "[problem2][DOD][sequential][runtime]")
{
    std::cout << "Test Interconection sequential DOD runtime" << std::endl;
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());
    interconnection_estimate::interconnection_estimate_sequential_dod(*design_, *runtime);
    runtime->print_result();
    runtime->print_file_result(Experiment::getInstance().getOutput_file());
}

// ***********************************************************
//  Data-Oriented Design
// ***********************************************************
//  -- sequential
//      -- cache miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Interconection sequential DOD cache misses", "[problem2][DOD][sequential][miss]")
{
    std::cout << "Test Interconection sequential DOD cache misses" << std::endl;
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
    for (int i = 0; i < ITERATIONS; ++i)
    {
        interconnection_estimate::interconnection_estimate_sequential_dod(*design_, *miss);
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
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Interconection parallel DOD runtime", "[problem2][DOD][parallel][runtime]")
{
    std::cout << "Test Interconection parallel DOD runtime" << std::endl;
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());
    interconnection_estimate::interconnection_estimate_parallel_dod(*design_, *runtime);
    runtime->print_result();
    runtime->print_file_result(Experiment::getInstance().getOutput_file());
}

// ***********************************************************
//  Data-Oriented Design
// ***********************************************************
//  -- parallel
//      -- cache miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Interconection parallel DOD cache misses", "[problem2][DOD][parallel][miss]")
{
    std::cout << "Test Interconection parallel DOD cache misses" << std::endl;
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
    for (int i = 0; i < ITERATIONS; ++i)
    {
        interconnection_estimate::interconnection_estimate_parallel_dod(*design_, *miss);
        miss->print_result();
        miss->print_file_result(Experiment::getInstance().getOutput_file());
    }
}
