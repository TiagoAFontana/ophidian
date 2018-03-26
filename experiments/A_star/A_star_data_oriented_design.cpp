#include "A_star_data_oriented_design.h"
#include "A_star.h"
#include <ophidian/interconnection/Flute.h>
#include <ophidian/interconnection/SteinerTree.h>
#include <ophidian/entity_system/PropertyGrouped.h>
#include <lemon/grid_graph.h>
#include <iterator>
#include <iostream>
namespace ophidian
{
namespace experiments
{
namespace a_star
{

//=================================================================================================
//============================================== DOD ==============================================
//=================================================================================================
void A_star_data_oriented_design_sequential(design::Design &design, Metric &metric)
{

    using Net = ophidian::circuit::Net;
    using Pin = ophidian::circuit::Pin;
    using Point = ophidian::geometry::Point;
    using Flute = ophidian::interconnection::Flute;
    using SteinerTree = ophidian::interconnection::SteinerTree;
    using Node = lemon::GridGraph::Node;
    ophidian::entity_system::Property<Pin, Point > pinPosition( design.netlist().makeProperty<Point>(Pin()) );

#pragma omp parallel for
    for(auto net_it = design.netlist().begin(Net()); net_it < design.netlist().end(Net()); ++net_it)
    {
        auto net = *net_it;
        for(auto pin : design.netlist().pins(net))
        {
            if(design.netlist().cell(pin) == ophidian::circuit::Cell())
            {
                //Pad
                auto padInput = design.netlist().input(pin);
                auto padOutput = design.netlist().output(pin);
                auto location = (padInput == ophidian::circuit::Input()) ? design.placement().outputPadLocation(padOutput) : design.placement().inputPadLocation(padInput);
                pinPosition[pin] = location.toPoint();
            }
            else {
                //Cell Pin
                pinPosition[pin] = design.placementMapping().location(pin).toPoint();
            }
        }
    }

    const entity_system::EntitySystem <Net> & nets = design.netlist().getNets();
    const entity_system::Association<Net, Pin> & netPins = design.netlist().getNetPins();

    ophidian::entity_system::PropertyGrouped<Net, Pin, Point> propGrouped(nets, pinPosition, netPins);

    metric.start();

    //construindo o grafo de circuito
    ophidian::util::LocationDbu m_chip_Origin = design.floorplan().chipOrigin();
    ophidian::util::LocationDbu m_chip_UpperRightCorner = design.floorplan().chipUpperRightCorner();
    ophidian::util::LocationDbu siteUpperRightCorner = design.floorplan().siteUpperRightCorner(*design.floorplan().sitesRange().begin());

    int gcell_width = static_cast<int>(std::max(siteUpperRightCorner.x(), siteUpperRightCorner.y())) * 9;
    int cols = static_cast<int>((m_chip_UpperRightCorner.x() - m_chip_Origin.x()) / gcell_width) +1;
    int rows = static_cast<int>((m_chip_UpperRightCorner.y() - m_chip_Origin.y()) / gcell_width) +1;

    int capacity = std::numeric_limits<int>::max();
    A_star astar(cols, rows, capacity);
//    lemon::GridGraph graph = astar.getGraph();

    Flute & flute = Flute::instance();


    int count = nets.size() * NET_PERCENTAGE;
//    std::cout<< "# nets = " << count << std::endl;
    auto begin = nets.begin();
    auto end = nets.begin();
    std::advance(end, count);


    //construindo a steiner de cada net

//    for(auto net_it = nets.begin(); net_it < nets.end(); ++net_it)
    for(auto net_it = begin; net_it != end; ++net_it)
    {
        std::vector<Node> path;
        std::unique_ptr<SteinerTree> tree = flute.create<Point>(propGrouped.begin(*net_it), propGrouped.end(*net_it));

        //executando A* para cada segmento da net
        auto segments = tree->segments();
        for(auto segIterator = segments.first; segIterator != segments.second; ++segIterator)
        {
            Point u = tree->position(tree->u(*segIterator));
            Point v = tree->position(tree->v(*segIterator));
            auto point_u = std::make_pair(static_cast<int>(u.x()/gcell_width), static_cast<int>(u.y()/gcell_width));
            auto point_v = std::make_pair(static_cast<int>(v.x()/gcell_width), static_cast<int>(v.y()/gcell_width));

            path.clear();
            astar.search(point_u, point_v, path);
//            astar.updateGraph(path);]
        }
    }
    metric.end();
}

void A_star_data_oriented_design_parallel(design::Design &design, Metric &metric)
{

    using Net = ophidian::circuit::Net;
    using Pin = ophidian::circuit::Pin;
    using Point = ophidian::geometry::Point;
    using Flute = ophidian::interconnection::Flute;
    using SteinerTree = ophidian::interconnection::SteinerTree;
    using Node = lemon::GridGraph::Node;
    ophidian::entity_system::Property<Pin, Point > pinPosition( design.netlist().makeProperty<Point>(Pin()) );

#pragma omp parallel for
    for(auto net_it = design.netlist().begin(Net()); net_it < design.netlist().end(Net()); ++net_it)
    {
        auto net = *net_it;
        for(auto pin : design.netlist().pins(net))
        {
            if(design.netlist().cell(pin) == ophidian::circuit::Cell())
            {
                //Pad
                auto padInput = design.netlist().input(pin);
                auto padOutput = design.netlist().output(pin);
                auto location = (padInput == ophidian::circuit::Input()) ? design.placement().outputPadLocation(padOutput) : design.placement().inputPadLocation(padInput);
                pinPosition[pin] = location.toPoint();
            }
            else {
                //Cell Pin
                pinPosition[pin] = design.placementMapping().location(pin).toPoint();
            }
        }
    }

    const entity_system::EntitySystem <Net> & nets = design.netlist().getNets();
    const entity_system::Association<Net, Pin> & netPins = design.netlist().getNetPins();

    ophidian::entity_system::PropertyGrouped<Net, Pin, Point> propGrouped(nets, pinPosition, netPins);

    metric.start();
    //construindo o grafo de circuito
    ophidian::util::LocationDbu m_chip_Origin = design.floorplan().chipOrigin();
    ophidian::util::LocationDbu m_chip_UpperRightCorner = design.floorplan().chipUpperRightCorner();
    ophidian::util::LocationDbu siteUpperRightCorner = design.floorplan().siteUpperRightCorner(*design.floorplan().sitesRange().begin());

    int gcell_width = static_cast<int>(std::max(siteUpperRightCorner.x(), siteUpperRightCorner.y())) * 9;
    int cols = static_cast<int>((m_chip_UpperRightCorner.x() - m_chip_Origin.x()) / gcell_width) +1;
    int rows = static_cast<int>((m_chip_UpperRightCorner.y() - m_chip_Origin.y()) / gcell_width) +1;

    int capacity = std::numeric_limits<int>::max();
    A_star astar(cols, rows, capacity);
    lemon::GridGraph graph = astar.getGraph();

    Flute & flute = Flute::instance();


    int count = nets.size() * NET_PERCENTAGE;
//    std::cout<< "# nets = " << count << std::endl;
    auto begin = nets.begin();
    auto end = nets.begin();
    std::advance(end, count);


    //construindo a steiner de cada net
#pragma omp parallel for
//    for(auto net_it = nets.begin(); net_it < nets.end(); ++net_it)
    for(auto net_it = begin; net_it < end; ++net_it)
    {
        std::vector<Node> path;
        std::unique_ptr<SteinerTree> tree = flute.create<Point>(propGrouped.begin(*net_it), propGrouped.end(*net_it));

        //executando A* para cada segmento da net
        auto segments = tree->segments();
        for(auto segIterator = segments.first; segIterator != segments.second; ++segIterator)
        {
            Point u = tree->position(tree->u(*segIterator));
            Point v = tree->position(tree->v(*segIterator));
            auto point_u = std::make_pair(static_cast<int>(u.x()/gcell_width), static_cast<int>(u.y()/gcell_width));
            auto point_v = std::make_pair(static_cast<int>(v.x()/gcell_width), static_cast<int>(v.y()/gcell_width));

            path.clear();
            astar.search(point_u, point_v, path);
//            astar.updateGraph(path);
        }
    }
    metric.end();
}

} // namespace a_star
} // namespace experiments
} // namespace ophidian
