#include "experiment.h"

/* Null, because instance will be initialized on demand. */
Experiment* Experiment::instance = 0;
//std::unique_ptr<Experiment> instance (nullptr);

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

    ophidian::design::ICCAD2015ContestDesignBuilder ICCAD2015DesignBuilder(lefFile, defFile, verilogFile);
    design_ = &ICCAD2015DesignBuilder.build();

    int a = 0;
    a++;
}

ExperimentFixtureICCAD2017::ExperimentFixtureICCAD2017()
{
    std::string cell_lef = "input_files/ICCAD2017/"+  Experiment::getInstance().getCircuit_name() +"/cells_modified.lef";
    std::string tech_lef = "input_files/ICCAD2017/"+ Experiment::getInstance().getCircuit_name() +"/tech.lef";
    std::string input_def = "input_files/ICCAD2017/"+ Experiment::getInstance().getCircuit_name() +"/placed.def";

    ophidian::design::ICCAD2017ContestDesignBuilder ICCAD2017DesignBuilder(cell_lef, tech_lef, input_def);
    design_ = &ICCAD2017DesignBuilder.build();
}
