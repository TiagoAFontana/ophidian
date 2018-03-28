#include <catch.hpp>
#include <iostream>
#include "experiments/experiment.h"
#include "experiments/metric.h"
#include "A_star.h"
#include "A_star_data_oriented_design.h"
#include "A_star_object_oriented_design.h"
#include <lemon/grid_graph.h>
#include "Grid_graph_OOD.h"

// PAPI_L1_DCM /*Level 1 data cache misses */
// PAPI_L1_ICM /*Level 1 instruction cache misses */
// PAPI_L2_DCM /*Level 2 data cache misses */
// PAPI_L2_ICM /*Level 2 instruction cache misses */
// PAPI_L3_DCM /*Level 3 data cache misses */
// PAPI_L3_ICM /*Level 3 instruction cache misses */
// PAPI_L1_TCM /*Level 1 total cache misses */
// PAPI_L2_TCM /*Level 2 total cache misses */
// PAPI_L3_TCM /*Level 3 total cache misses */

using namespace ophidian;
using namespace ophidian::experiments;
using namespace ophidian::experiments::a_star;

#define ITERATIONS 30
#define GRAPH_OOD 1

TEST_CASE("Test A*", "[astar]")
{
    std::cout << "Test A* " << std::endl;
    using Node = lemon::GridGraph::Node;
    int cols = 4;
    int rows = 6;
    int capacity = 2;
    A_star astar(cols, rows, capacity);

    //blocs
    std::vector<std::pair<int, int> > blocks;
    blocks.push_back(std::make_pair(1,3));
    blocks.push_back(std::make_pair(2,3));
    blocks.push_back(std::make_pair(0,3));
    astar.insertBlock(blocks);

    std::vector<Node> path;
    int ret = astar.search(std::make_pair(1,4), std::make_pair(2,1), path);
    std::cout << "ret: " << ret << std::endl;
    std::cout << "size path = " << path.size() << std::endl;
    lemon::GridGraph graph = astar.getGraph();
    for(auto node : path)
    {
        std::printf("Nodo : col: %d row: %d \n", graph.col(node), graph.row(node));
    }

    //update graph
    astar.updateGraph(path);
    path.clear();

    std::cout << "GRAPH UPDATE" << ret << std::endl;

    ret = astar.search(std::make_pair(1,4), std::make_pair(2,1), path);
    std::cout << "ret: " << ret << std::endl;
    std::cout << "size path = " << path.size() << std::endl;
    for(auto node : path)
    {
        std::printf("Nodo : col: %d row: %d \n", graph.col(node), graph.row(node));
    }
}





TEST_CASE("Test A* OOD", "[astarOOD]")
{
    std::cout << "Test A* OOD" << std::endl;
    using Node = ophidian::experiments::a_star::Node;
    int cols = 5;
    int rows = 7;
    int capacity = 2;
    A_star_OOD astar(cols, rows, capacity);
    auto graph = astar.graph;
    //blocs
//    std::vector<std::pair<int, int> > blocks;
//    blocks.push_back(std::make_pair(1,3));
//    blocks.push_back(std::make_pair(2,3));
//    blocks.push_back(std::make_pair(0,3));
//    astar.insertBlock(blocks);

    std::vector<Node*> path;
    int ret = astar.search(std::make_pair(1,5), std::make_pair(3,2), path);
    std::cout << "ret: " << ret << std::endl;
    std::cout << "size path = " << path.size() << std::endl;
//    lemon::GridGraph graph = astar.getGraph();
    for(auto node : path)
    {
//        std::printf("Nodo : col: %d row: %d \n", graph.col(node), graph.row(node));
        std::cout << "Nodo : col: "<< node->x() << " row: " << node->y() << std::endl;
    }

    //update graph
//    astar.updateGraph(path);
//    path.clear();

//    std::cout << "GRAPH UPDATE" << ret << std::endl;

//    ret = astar.search(std::make_pair(1,4), std::make_pair(2,1), path);
//    std::cout << "ret: " << ret << std::endl;
//    std::cout << "size path = " << path.size() << std::endl;
//    for(auto node : path)
//    {
//        std::printf("Nodo : col: %d row: %d \n", graph.col(node), graph.row(node));
//    }

}


// ***********************************************************
//  Object-Oriented Design
// ***********************************************************
//  -- sequential
//      -- runtime
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test A* sequential OOD runtime", "[problem4][OOD][sequential][runtime]")
{
    std::cout << "Test A* sequential OOD runtime" << std::endl;
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());

    if(GRAPH_OOD)
    {
        a_star::A_star_object_oriented_design_sequential_graphOOD(*design_, *runtime);
    }
    else {
        a_star::A_star_object_oriented_design_sequential_lemon(*design_, *runtime);
    }
    for (int i = 0; i < ITERATIONS; ++i)
    {
        if(GRAPH_OOD)
        {
            a_star::A_star_object_oriented_design_sequential_graphOOD(*design_, *runtime);
        }
        else {
            a_star::A_star_object_oriented_design_sequential_lemon(*design_, *runtime);
        }
        runtime->print_result();
        runtime->print_file_result(Experiment::getInstance().getOutput_file());
    }
}

// ***********************************************************
//  Object-Oriented Design
// ***********************************************************
//  -- sequential
//      -- cache miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test A* sequential OOD miss", "[problem4][OOD][sequential][miss]")
{
    std::cout << "Test A* sequential OOD miss" << std::endl;
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

    if(GRAPH_OOD)
    {
        a_star::A_star_object_oriented_design_sequential_graphOOD(*design_, *miss);
    }
    else {
        a_star::A_star_object_oriented_design_sequential_lemon(*design_, *miss);
    }
    for (int i = 0; i < ITERATIONS; ++i)
    {
        if(GRAPH_OOD)
        {
            a_star::A_star_object_oriented_design_sequential_graphOOD(*design_, *miss);
        }
        else {
            a_star::A_star_object_oriented_design_sequential_lemon(*design_, *miss);
        }
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
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test A* sequential DOD runtime", "[problem4][DOD][sequential][runtime]")
{
    std::cout << "Test A* sequential DOD runtime" << std::endl;
    std::unique_ptr<Runtime> runtime = std::unique_ptr<Runtime>(new Runtime());

    a_star::A_star_data_oriented_design_sequential(*design_, *runtime);
    for (int i = 0; i < ITERATIONS; ++i)
    {
        a_star::A_star_data_oriented_design_sequential(*design_, *runtime);
        runtime->print_result();
        runtime->print_file_result(Experiment::getInstance().getOutput_file());
    }
}

// ***********************************************************
//  Data-Oriented Design
// ***********************************************************
//  -- sequential
//      -- cache miss
// ***********************************************************
TEST_CASE_METHOD(ExperimentFixtureICCAD2015, "Test A* sequential DOD miss", "[problem4][DOD][sequential][miss]")
{
    std::cout << "Test A* sequential DOD runtime" << std::endl;
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

    a_star::A_star_data_oriented_design_sequential(*design_, *miss);
    for (int i = 0; i < ITERATIONS; ++i)
    {
        a_star::A_star_data_oriented_design_sequential(*design_, *miss);
        miss->print_result();
        miss->print_file_result(Experiment::getInstance().getOutput_file());
    }
}




