#include "catch.hpp"
#include <iostream>
#include "experiments/experiment.h"
#include "experiments/metric.h"
#include "ChipBoundaries.h"

//Chip Boundaries
//TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test all circuits runtime DOD Problem 1", "[problem][1]")
//{
//    std::cout << "problem 1" << std::endl;

//    Experiment &exp = Experiment::getInstance();
//    std::cout << "circuit " << exp.getCircuit_name() << std::endl;
//    std::cout << "filename " << exp.getOutput_file() << std::endl;

//    std::cout << "numero de celulas " << design_->netlist().size(ophidian::circuit::Cell()) << std::endl;
//}

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
    int PAPI_events[] = {PAPI_L1_ICM, PAPI_L1_DCM};//Please change this according with your cpu architecture.
    std::unique_ptr<Miss> miss = std::unique_ptr<Miss>(new Miss(PAPI_events, 2));
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
//TEST_CASE_METHOD(ExperimentFixtureICCAD2015,

// ***********************************************************
//  Object-Oriented Design
// ***********************************************************
//  -- parallel
//      -- cache miss
// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureICCAD2015,



// ***********************************************************
//  Data-Oriented Design
// ***********************************************************
//    -- sequential
//      -- runtime
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Chip Boundaries sequential DOD runtime", "[problem1][DOD][sequential][runtime]")
{
    std::cout << "Test Chip Boundaries sequential DOD runtime" << std::endl;
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());
    chip_boundaries::chip_boundaries_sequential_dod(*design_, *runtime);
    runtime->print_result();
    runtime->print_file_result(Experiment::getInstance().getOutput_file());
}
//  Data-Oriented Design
//    -- sequential
//      -- cache miss
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test Chip Boundaries sequential DOD cache misses", "[problem1][DOD][sequential][miss]")
{
    std::cout << "Test Chip Boundaries sequential DOD cache misses" << std::endl;
    int PAPI_events[] = {PAPI_L1_ICM, PAPI_L1_DCM};//Please change this according with your cpu architecture.
    std::unique_ptr<Miss> miss = std::unique_ptr<Miss>(new Miss(PAPI_events, 2));
    chip_boundaries::chip_boundaries_sequential_dod(*design_, *miss);
    miss->print_result();
    miss->print_file_result(Experiment::getInstance().getOutput_file());
}
// -----------------------------------------------------------
//  Data-Oriented Design
//  -- parallel
//      -- runtime

//  Data-Oriented Design
//  -- parallel
//      -- cache miss
// ***********************************************************
