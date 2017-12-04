#include "experiment.h"

namespace ophidian
{
namespace experiments
{

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

ExperimentFixtureKmeansICCAD2015::ExperimentFixtureKmeansICCAD2015()
{
    std::string lefFile = "input_files/"+  Experiment::getInstance().getCircuit_name() + "/" + Experiment::getInstance().getCircuit_name() +".lef";
    std::string defFile = "input_files/"+ Experiment::getInstance().getCircuit_name() + "/" + Experiment::getInstance().getCircuit_name() +".def";
    std::string verilogFile = "input_files/"+ Experiment::getInstance().getCircuit_name() + "/" + Experiment::getInstance().getCircuit_name() +".v";

    mDesignBuilder.reset( new ophidian::design::ICCAD2015ContestDesignBuilder(lefFile, defFile, verilogFile));
    design_ = &mDesignBuilder->build();


    std::string ff ("DFF_X80");
    for(auto cell_it = design.netlist().begin(Cell()); cell_it != design.netlist().end(Cell()); ++cell_it)
    {
        auto cell = *cell_it;
        if(ff.compare(design_->netlist().name(cell)) == 0)
        {
            util::LocationDbu cell_position = design_->placement().cellLocation(cell);
            flip_flop_positions.push_back(ophidian::geometry::Point(cell_position.toPoint().x(), cell_position.toPoint().y()));
        }
    }
}

ExperimentFixtureICCAD2017::ExperimentFixtureICCAD2017()
{
    std::string cell_lef = "input_files/ICCAD2017/"+  Experiment::getInstance().getCircuit_name() +"/cells_modified.lef";
    std::string tech_lef = "input_files/ICCAD2017/"+ Experiment::getInstance().getCircuit_name() +"/tech.lef";
    std::string input_def = "input_files/ICCAD2017/"+ Experiment::getInstance().getCircuit_name() +"/placed.def";

    mDesignBuilder.reset( new ophidian::design::ICCAD2017ContestDesignBuilder(cell_lef, tech_lef, input_def));
    design_ =  &mDesignBuilder->build();
}

} // namespace experiments
} // namespace ophidian
