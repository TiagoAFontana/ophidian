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

TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test circuit runtime DOD Problem 1", "[problem][1][DOD][sequential][runtime]")
{
    std::cout << "Test circuit runtime DOD Problem 1" << std::endl;
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());
    chip_boundaries::chip_boundaries_sequential_dod(*design_, *runtime);
    runtime->print_result();
    runtime->print_file_result(Experiment::getInstance().getOutput_file());
}
