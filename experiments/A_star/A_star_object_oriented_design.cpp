#include "A_star_object_oriented_design.h"
#include "A_star.h"
#include <ophidian/interconnection/Flute.h>
#include <ophidian/interconnection/SteinerTree.h>
#include <ophidian/entity_system/PropertyGrouped.h>
#include <lemon/grid_graph.h>
#include <iterator>
#include "Grid_graph_OOD.h"
namespace ophidian
{
namespace experiments
{
namespace a_star
{


Net::Net(std::string &name) : m_name(name)
{
}

std::string Net::name(){
    return m_name;
}
void Net::reserve(std::size_t size){
    m_pins.reserve(size);
    pinPositions.reserve(size);
}
void Net::add_pin(Pin * pin){
    m_pins.push_back(pin);
}

void Net::add_pinPosition(ophidian::geometry::Point position)
{
    pinPositions.push_back(position);
}
const std::vector<Pin*> & Net::pins() const {
    return m_pins;
}

std::vector<ophidian::geometry::Point> Net::get_pinPositions()
{
    return pinPositions;
}


Pin::Pin(std::string name, Net * net) : m_name(name){
    m_net_ptr.reset(net);
}

PinPlacement::PinPlacement(std::string name, Net * net) : Pin(name, net){
}
void PinPlacement::set_position(const geometry::Point &position){
    m_position = position;
}
const geometry::Point &PinPlacement::pin_position(){
    return m_position;
}



#define NET_PERCENTAGE 0.1

//=================================================================================================
//========================================= OOD GRAPH OOD =========================================
//=================================================================================================
void A_star_object_oriented_design_sequential_graphOOD(design::Design &design, Metric &metric)
{
    using Point = ophidian::geometry::Point;
    using Flute = ophidian::interconnection::Flute;
    using SteinerTree = ophidian::interconnection::SteinerTree;
    using Node = ophidian::experiments::a_star::Node;

    std::vector<Net> m_nets;
    m_nets.reserve(design.netlist().size(ophidian::circuit::Net()));
    for(auto net_it = design.netlist().begin(ophidian::circuit::Net()); net_it != design.netlist().end(ophidian::circuit::Net()); ++net_it)
    {
        auto net = *net_it;
        std::string net_name = design.netlist().name(net);
        Net net_object(net_name);
        m_nets.push_back(net_object);

        for(auto pin : design.netlist().pins(net))
        {
            std::string pin_name = design.netlist().name(pin);
            int a = 0;
            if(design.netlist().cell(pin) == ophidian::circuit::Cell())
            {
                //Pad
                PinPlacement * pin_object = new PinPlacement(pin_name, &net_object);
                auto padInput = design.netlist().input(pin);
                auto padOutput = design.netlist().output(pin);

                auto location = (padInput == ophidian::circuit::Input()) ? design.placement().outputPadLocation(padOutput) : design.placement().inputPadLocation(padInput);

                pin_object->set_position(location.toPoint());
                m_nets.back().add_pin(pin_object);
                net_object.add_pinPosition(location.toPoint());
            }
            else {
                //Cell Pin
                PinPlacement * pin_object = new PinPlacement(pin_name, &net_object);
                pin_object->set_position(design.placementMapping().location(pin).toPoint());
                m_nets.back().add_pin(pin_object);
                net_object.add_pinPosition(design.placementMapping().location(pin).toPoint());
            }
        }
    }


    //construindo o grafo de circuito
    ophidian::util::LocationDbu m_chip_Origin = design.floorplan().chipOrigin();
    ophidian::util::LocationDbu m_chip_UpperRightCorner = design.floorplan().chipUpperRightCorner();
    ophidian::util::LocationDbu siteUpperRightCorner = design.floorplan().siteUpperRightCorner(*design.floorplan().sitesRange().begin());

    int gcell_width = static_cast<int>(std::max(siteUpperRightCorner.x(), siteUpperRightCorner.y())) * 9;
    int cols = static_cast<int>((m_chip_UpperRightCorner.x() - m_chip_Origin.x()) / gcell_width) +1;
    int rows = static_cast<int>((m_chip_UpperRightCorner.y() - m_chip_Origin.y()) / gcell_width) +1;

    int capacity = std::numeric_limits<int>::max();
    A_star_OOD astar(cols, rows, capacity);
//    lemon::GridGraph graph = astar.getGraph();

    Flute & flute = Flute::instance();
    std::vector<Node*> path;


    int count = m_nets.size() * NET_PERCENTAGE;

    auto begin = m_nets.begin();
    auto end = m_nets.begin();
    std::advance(end, count);

    metric.start();

    std::vector<Point> pin_positions;
    for(auto net_it = begin; net_it != end; ++net_it)
    {
        auto net = *net_it;
        auto pins = net.pins();
        pin_positions.clear();
        pin_positions.reserve(pins.size());
        for(auto pin : pins)
            pin_positions.push_back(static_cast<PinPlacement*>(pin)->pin_position());

        std::unique_ptr<SteinerTree> tree = flute.create<Point>(pin_positions.begin(), pin_positions.end());
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


void A_star_object_oriented_design_parallel_graphOOD(design::Design &design, Metric &metric)
{
    using Point = ophidian::geometry::Point;
    using Flute = ophidian::interconnection::Flute;
    using SteinerTree = ophidian::interconnection::SteinerTree;
    using Node = ophidian::experiments::a_star::Node;

    std::vector<Net> m_nets;
    m_nets.reserve(design.netlist().size(ophidian::circuit::Net()));
    for(auto net_it = design.netlist().begin(ophidian::circuit::Net()); net_it != design.netlist().end(ophidian::circuit::Net()); ++net_it)
    {
        auto net = *net_it;
        std::string net_name = design.netlist().name(net);
        Net net_object(net_name);
        m_nets.push_back(net_object);

        for(auto pin : design.netlist().pins(net))
        {
            std::string pin_name = design.netlist().name(pin);
            int a = 0;
            if(design.netlist().cell(pin) == ophidian::circuit::Cell())
            {
                //Pad
                PinPlacement * pin_object = new PinPlacement(pin_name, &net_object);
                auto padInput = design.netlist().input(pin);
                auto padOutput = design.netlist().output(pin);

                auto location = (padInput == ophidian::circuit::Input()) ? design.placement().outputPadLocation(padOutput) : design.placement().inputPadLocation(padInput);

                pin_object->set_position(location.toPoint());
                m_nets.back().add_pin(pin_object);
                net_object.add_pinPosition(location.toPoint());
            }
            else {
                //Cell Pin
                PinPlacement * pin_object = new PinPlacement(pin_name, &net_object);
                pin_object->set_position(design.placementMapping().location(pin).toPoint());
                m_nets.back().add_pin(pin_object);
                net_object.add_pinPosition(design.placementMapping().location(pin).toPoint());
            }
        }
    }


    //construindo o grafo de circuito
    ophidian::util::LocationDbu m_chip_Origin = design.floorplan().chipOrigin();
    ophidian::util::LocationDbu m_chip_UpperRightCorner = design.floorplan().chipUpperRightCorner();
    ophidian::util::LocationDbu siteUpperRightCorner = design.floorplan().siteUpperRightCorner(*design.floorplan().sitesRange().begin());

    int gcell_width = static_cast<int>(std::max(siteUpperRightCorner.x(), siteUpperRightCorner.y())) * 9;
    int cols = static_cast<int>((m_chip_UpperRightCorner.x() - m_chip_Origin.x()) / gcell_width) +1;
    int rows = static_cast<int>((m_chip_UpperRightCorner.y() - m_chip_Origin.y()) / gcell_width) +1;

    int capacity = std::numeric_limits<int>::max();
    A_star_OOD astar(cols, rows, capacity);
//    lemon::GridGraph graph = astar.getGraph();

    Flute & flute = Flute::instance();
    std::vector<Node*> path;


    int count = m_nets.size() * NET_PERCENTAGE;

    auto begin = m_nets.begin();
    auto end = m_nets.begin();
    std::advance(end, count);

    metric.start();

    std::vector<Point> pin_positions;
    for(auto net_it = begin; net_it != end; ++net_it)
    {
        auto net = *net_it;
        auto pins = net.pins();
        pin_positions.clear();
        pin_positions.reserve(pins.size());
        for(auto pin : pins)
            pin_positions.push_back(static_cast<PinPlacement*>(pin)->pin_position());

        std::unique_ptr<SteinerTree> tree = flute.create<Point>(pin_positions.begin(), pin_positions.end());
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


//=================================================================================================
//=========================================== OOD LEMON ===========================================
//=================================================================================================
void A_star_object_oriented_design_sequential_lemon(design::Design &design, Metric &metric)
{
    using Point = ophidian::geometry::Point;
    using Flute = ophidian::interconnection::Flute;
    using SteinerTree = ophidian::interconnection::SteinerTree;
    using Node = lemon::GridGraph::Node;

    std::vector<Net> m_nets;
    m_nets.reserve(design.netlist().size(ophidian::circuit::Net()));
    for(auto net_it = design.netlist().begin(ophidian::circuit::Net()); net_it != design.netlist().end(ophidian::circuit::Net()); ++net_it)
    {
        auto net = *net_it;
        std::string net_name = design.netlist().name(net);
        Net net_object(net_name);
        m_nets.push_back(net_object);

        for(auto pin : design.netlist().pins(net))
        {
            std::string pin_name = design.netlist().name(pin);
            int a = 0;
            if(design.netlist().cell(pin) == ophidian::circuit::Cell())
            {
                //Pad
                PinPlacement * pin_object = new PinPlacement(pin_name, &net_object);
                auto padInput = design.netlist().input(pin);
                auto padOutput = design.netlist().output(pin);

                auto location = (padInput == ophidian::circuit::Input()) ? design.placement().outputPadLocation(padOutput) : design.placement().inputPadLocation(padInput);

                pin_object->set_position(location.toPoint());
                m_nets.back().add_pin(pin_object);
                net_object.add_pinPosition(location.toPoint());
            }
            else {
                //Cell Pin
                PinPlacement * pin_object = new PinPlacement(pin_name, &net_object);
                pin_object->set_position(design.placementMapping().location(pin).toPoint());
                m_nets.back().add_pin(pin_object);
                net_object.add_pinPosition(design.placementMapping().location(pin).toPoint());
            }
        }
    }


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
    std::vector<Node> path;


    int count = m_nets.size() * NET_PERCENTAGE;

    auto begin = m_nets.begin();
    auto end = m_nets.begin();
    std::advance(end, count);

    metric.start();

    std::vector<Point> pin_positions;
    for(auto net_it = begin; net_it != end; ++net_it)
    {
        auto net = *net_it;
        auto pins = net.pins();
        pin_positions.clear();
        pin_positions.reserve(pins.size());
        for(auto pin : pins)
            pin_positions.push_back(static_cast<PinPlacement*>(pin)->pin_position());

        std::unique_ptr<SteinerTree> tree = flute.create<Point>(pin_positions.begin(), pin_positions.end());
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


void A_star_object_oriented_design_parallel_lemon(design::Design &design, Metric &metric)
{
    using Point = ophidian::geometry::Point;
    using Flute = ophidian::interconnection::Flute;
    using SteinerTree = ophidian::interconnection::SteinerTree;
    using Node = lemon::GridGraph::Node;

    std::vector<Net> m_nets;
    m_nets.reserve(design.netlist().size(ophidian::circuit::Net()));
    for(auto net_it = design.netlist().begin(ophidian::circuit::Net()); net_it != design.netlist().end(ophidian::circuit::Net()); ++net_it)
    {
        auto net = *net_it;
        std::string net_name = design.netlist().name(net);
        Net net_object(net_name);
        m_nets.push_back(net_object);

        for(auto pin : design.netlist().pins(net))
        {
            std::string pin_name = design.netlist().name(pin);
            int a = 0;
            if(design.netlist().cell(pin) == ophidian::circuit::Cell())
            {
                //Pad
                PinPlacement * pin_object = new PinPlacement(pin_name, &net_object);
                auto padInput = design.netlist().input(pin);
                auto padOutput = design.netlist().output(pin);

                auto location = (padInput == ophidian::circuit::Input()) ? design.placement().outputPadLocation(padOutput) : design.placement().inputPadLocation(padInput);

                pin_object->set_position(location.toPoint());
                m_nets.back().add_pin(pin_object);
                net_object.add_pinPosition(location.toPoint());
            }
            else {
                //Cell Pin
                PinPlacement * pin_object = new PinPlacement(pin_name, &net_object);
                pin_object->set_position(design.placementMapping().location(pin).toPoint());
                m_nets.back().add_pin(pin_object);
                net_object.add_pinPosition(design.placementMapping().location(pin).toPoint());
            }
        }
    }


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
    std::vector<Node> path;


    int count = m_nets.size() * NET_PERCENTAGE;

    auto begin = m_nets.begin();
    auto end = m_nets.begin();
    std::advance(end, count);

    metric.start();

    std::vector<Point> pin_positions;
    for(auto net_it = begin; net_it != end; ++net_it)
    {
        auto net = *net_it;
        auto pins = net.pins();
        pin_positions.clear();
        pin_positions.reserve(pins.size());
        for(auto pin : pins)
            pin_positions.push_back(static_cast<PinPlacement*>(pin)->pin_position());

        std::unique_ptr<SteinerTree> tree = flute.create<Point>(pin_positions.begin(), pin_positions.end());
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
