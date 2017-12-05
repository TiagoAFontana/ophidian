#include "catch.hpp"
#include <iostream>
#include "experiments/experiment.h"
#include "experiments/metric.h"
#include "ChipBoundaries.h"

// PAPI_L1_DCM /*Level 1 data cache misses */
// PAPI_L1_ICM /*Level 1 instruction cache misses */
// PAPI_L2_DCM /*Level 2 data cache misses */
// PAPI_L2_ICM /*Level 2 instruction cache misses */
// PAPI_L3_DCM /*Level 3 data cache misses */
// PAPI_L3_ICM /*Level 3 instruction cache misses */
// PAPI_L1_TCM /*Level 1 total cache misses */
// PAPI_L2_TCM /*Level 2 total cache misses */
// PAPI_L3_TCM /*Level 3 total cache misses */


//Chip Boundaries

using namespace ophidian;
using namespace ophidian::experiments;
using namespace ophidian::experiments::chip_boundaries;

// ***********************************************************
//  Object-Oriented Design
// ***********************************************************
//  -- sequential
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Chip Boundaries sequential OOD runtime", "[problem1][OOD][sequential][runtime]")
{
    std::cout << "Test Chip Boundaries sequential OOD runtime" << std::endl;
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());
    chip_boundaries::chip_boundaries_sequential_ood(*design_, *runtime);
    runtime->print_result();
    runtime->print_file_result(Experiment::getInstance().getOutput_file());
}

// ***********************************************************
//  Object-Oriented Design
// ***********************************************************
//  -- sequential
//      -- cache miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Chip Boundaries sequential OOD cache misses", "[problem1][OOD][sequential][miss]")
{
    std::cout << "Test Chip Boundaries sequential OOD cache misses" << std::endl;
    int PAPI_events[] = {PAPI_L1_TCM, PAPI_L2_TCM, PAPI_L3_TCM};//Please change this according with your cpu architecture.
    std::unique_ptr<Miss> miss = std::unique_ptr<Miss>(new Miss(PAPI_events, 3));
    chip_boundaries::chip_boundaries_sequential_ood(*design_, *miss);
    miss->print_result();
    miss->print_file_result(Experiment::getInstance().getOutput_file());
}

// ***********************************************************
//  Object-Oriented Design
// ***********************************************************
//  -- parallel
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Chip Boundaries parallel OOD runtime", "[problem1][OOD][parallel][runtime]")
{
    std::cout << "Test Chip Boundaries parallel OOD runtime" << std::endl;
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());
    chip_boundaries::chip_boundaries_parallel_ood(*design_, *runtime);
    runtime->print_result();
    runtime->print_file_result(Experiment::getInstance().getOutput_file());
}

// ***********************************************************
//  Object-Oriented Design
// ***********************************************************
//  -- parallel
//      -- cache miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Chip Boundaries parallel OOD cache misses", "[problem1][OOD][parallel][miss]")
{
    std::cout << "Test Chip Boundaries parallel OOD cache misses" << std::endl;
    int PAPI_events[] = {PAPI_L1_TCM, PAPI_L2_TCM, PAPI_L3_TCM};//Please change this according with your cpu architecture.
    std::unique_ptr<Miss> miss = std::unique_ptr<Miss>(new Miss(PAPI_events, 3));
    chip_boundaries::chip_boundaries_parallel_ood(*design_, *miss);
    miss->print_result();
    miss->print_file_result(Experiment::getInstance().getOutput_file());
}
//________________________________________________________________________________________________________________________________

// ***********************************************************
//  Data-Oriented Design
// ***********************************************************
//    -- sequential
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Chip Boundaries sequential DOD runtime", "[problem1][DOD][sequential][runtime]")
{
    std::cout << "Test Chip Boundaries sequential DOD runtime" << std::endl;
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());
    chip_boundaries::chip_boundaries_sequential_dod(*design_, *runtime);
    runtime->print_result();
    runtime->print_file_result(Experiment::getInstance().getOutput_file());
}

// ***********************************************************
//  Data-Oriented Design
// ***********************************************************
//    -- sequential
//      -- cache miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Chip Boundaries sequential DOD cache misses", "[problem1][DOD][sequential][miss]")
{
    std::cout << "Test Chip Boundaries sequential DOD cache misses" << std::endl;
    int PAPI_events[] = {PAPI_L1_TCM, PAPI_L2_TCM, PAPI_L3_TCM};
    std::unique_ptr<Miss> miss = std::unique_ptr<Miss>(new Miss(PAPI_events, 3));
    chip_boundaries::chip_boundaries_sequential_dod(*design_, *miss);
    miss->print_result();
    miss->print_file_result(Experiment::getInstance().getOutput_file());
}

// ***********************************************************
//  Data-Oriented Design
// ***********************************************************
//    -- parallel
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Chip Boundaries parallel DOD runtime", "[problem1][DOD][parallel][runtime]")
{
    std::cout << "Test Chip Boundaries parallel DOD runtime" << std::endl;
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());
    chip_boundaries::chip_boundaries_parallel_dod(*design_, *runtime);
    runtime->print_result();
    runtime->print_file_result(Experiment::getInstance().getOutput_file());
}

// ***********************************************************
//  Data-Oriented Design
// ***********************************************************
//    -- parallel
//      -- cache miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Chip Boundaries parallel DOD cache misses", "[problem1][DOD][parallel][miss]")
{
    std::cout << "Test Chip Boundaries parallel DOD cache misses" << std::endl;
    int PAPI_events[] = {PAPI_L1_TCM, PAPI_L2_TCM, PAPI_L3_TCM};//Please change this according with your cpu architecture.
    std::unique_ptr<Miss> miss = std::unique_ptr<Miss>(new Miss(PAPI_events, 3));
    chip_boundaries::chip_boundaries_parallel_dod(*design_, *miss);
    miss->print_result();
    miss->print_file_result(Experiment::getInstance().getOutput_file());
}
