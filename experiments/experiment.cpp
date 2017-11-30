#include "experiment.h"

/* Null, because instance will be initialized on demand. */
Experiment* Experiment::instance = 0;

std::string Experiment::getOutput_file() const
{
    return output_file;
}

void Experiment::setOutput_file(const std::string &value)
{
    output_file = value;
}

std::string Experiment::getCircuit_name() const
{
    return circuit_name;
}

void Experiment::setCircuit_name(const std::string &value)
{
    circuit_name = value;
}

ExperimentFixtureICCAD2015::ExperimentFixtureICCAD2015()
{
    std::string lefFile = "input_files/"+  Experiment::getInstance().getCircuit_name() + "/" + Experiment::getInstance().getCircuit_name() +".lef";
    std::string defFile = "input_files/"+ Experiment::getInstance().getCircuit_name() + "/" + Experiment::getInstance().getCircuit_name() +".def";
    std::string verilogFile = "input_files/"+ Experiment::getInstance().getCircuit_name() + "/" + Experiment::getInstance().getCircuit_name() +".v";

    mDesignBuilder.reset( new ophidian::design::ICCAD2015ContestDesignBuilder(lefFile, defFile, verilogFile));
    design_ = &mDesignBuilder->build();
}

ExperimentFixtureICCAD2017::ExperimentFixtureICCAD2017()
{
    std::string cell_lef = "input_files/ICCAD2017/"+  Experiment::getInstance().getCircuit_name() +"/cells_modified.lef";
    std::string tech_lef = "input_files/ICCAD2017/"+ Experiment::getInstance().getCircuit_name() +"/tech.lef";
    std::string input_def = "input_files/ICCAD2017/"+ Experiment::getInstance().getCircuit_name() +"/placed.def";

    mDesignBuilder.reset( new ophidian::design::ICCAD2017ContestDesignBuilder(cell_lef, tech_lef, input_def));
    design_ =  &mDesignBuilder->build();
}
