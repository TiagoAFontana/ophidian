#ifndef ophidian_EXPERIMENT_H
#define ophidian_EXPERIMENT_H

#include "ophidian/circuit/Verilog2Netlist.h"
#include "ophidian/circuit/Netlist.h"
#include "ophidian/parser/Def.h"
#include "ophidian/parser/Lef.h"
#include "ophidian/parser/VerilogParser.h"
#include "ophidian/placement/Def2Placement.h"
#include "ophidian/placement/Lef2Library.h"
#include "ophidian/placement/Library.h"
#include "ophidian/standard_cell/StandardCells.h"

//using namespace ophidian;

//struct Experiment
//{
//    std::string circuit_name;
//    std::unique_ptr<parsing::def> def;
//    std::unique_ptr<parsing::lef> lef;
//    std::unique_ptr<parsing::verilog> verilog;
//    std::unique_ptr<standard_cell::standard_cells> m_std_cells;
//    std::unique_ptr<netlist::netlist> m_netlist;
//    std::unique_ptr<placement::library> m_placement_lib;
//    std::unique_ptr<placement::placement> m_placement;

//    Experiment(std::string circuit_name) : circuit_name(circuit_name){
//        def.reset(new parsing::def("./benchmarks/"+circuit_name+"/"+circuit_name+".def"));
//        lef.reset(new parsing::lef("./benchmarks/"+circuit_name+"/"+circuit_name+".lef"));
//        verilog.reset(new parsing::verilog("./benchmarks/"+circuit_name+"/"+circuit_name+".v"));

//        m_std_cells.reset(new standard_cell::standard_cells());
//        m_netlist.reset(new netlist::netlist(m_std_cells.get()));
//        netlist::verilog2netlist(*verilog, *m_netlist);
//        m_placement_lib.reset(new placement::library(m_std_cells.get()));
//        m_placement.reset(new placement::placement(m_netlist.get(), m_placement_lib.get()));
//        placement::def2placement(*def, *m_placement);
//        placement::lef2library(*lef, *m_placement_lib);
//    }
//};

#include <iostream>
#include "ophidian/design/DesignBuilder.h"
#include "ophidian/design/Design.h"

class Experiment
{
private:
    /* Here will be the instance stored. */
    static Experiment* instance;

    /* Private constructor to prevent instancing. */
    Experiment(){
    };
    std::string circuit_name;
    std::string output_file;
public:
    /* Static access method. */
    static Experiment& getInstance(){
        if (instance == 0)
        {
            instance = new Experiment();
        }

        return *(instance);
    };

    std::string getCircuit_name() const;
    void setCircuit_name(const std::string &value);
    std::string getOutput_file() const;
    void setOutput_file(const std::string &value);
};


class ExperimentFixtureICCAD2015
{
public:
    ExperimentFixtureICCAD2015();

    ophidian::design::Design * design_;
private:
    std::unique_ptr<ophidian::design::DesignBuilder> mDesignBuilder;
};

class ExperimentFixtureICCAD2017
{
public:
    ExperimentFixtureICCAD2017();

    ophidian::design::Design * design_;
private:
    std::unique_ptr<ophidian::design::DesignBuilder> mDesignBuilder;
};

#endif //ophidian_EXPERIMENT_H
