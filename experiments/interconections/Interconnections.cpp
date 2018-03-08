#include "Interconnections.h"
#include <ophidian/interconnection/HPWL.h>
//#include <ophidian/interconnection/STWL.h>

#include <ophidian/entity_system/PropertyGrouped.h>
#include <ophidian/entity_system/Association.h>
namespace ophidian
{
namespace experiments
{
namespace interconnection_estimate
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

void Net::add_pinPosition(util::LocationDbu position)
{
    pinPositions.push_back(position);
}
const std::vector<Pin*> & Net::pins() const {
    return m_pins;
}

std::vector<util::LocationDbu> Net::get_pinPositions()
{
    return pinPositions;
}


Pin::Pin(std::string name, Net * net) : m_name(name){
    m_net_ptr.reset(net);
}

PinPlacement::PinPlacement(std::string name, Net * net) : Pin(name, net){
}
void PinPlacement::set_position(const util::LocationDbu &position){
    m_position = position;
}
const util::LocationDbu &PinPlacement::pin_position(){
    return m_position;
}

//=================================================================================================
//============================================== OOD ==============================================
//=================================================================================================

void interconnection_estimate_sequential_ood(design::Design &design, Metric &metric)
{
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

                pin_object->set_position(location);
                m_nets.back().add_pin(pin_object);
                net_object.add_pinPosition(location);
            }
            else {
                //Cell Pin
                PinPlacement * pin_object = new PinPlacement(pin_name, &net_object);
                pin_object->set_position(design.placementMapping().location(pin));
                m_nets.back().add_pin(pin_object);
                net_object.add_pinPosition(design.placementMapping().location(pin));
            }
        }
    }

    metric.start();

    std::vector<util::LocationDbu> pin_positions;
    for(auto net_it = m_nets.begin(); net_it != m_nets.end(); ++net_it)
    {
        auto net = *net_it;
        auto pins = net.pins();
        pin_positions.clear();
        pin_positions.reserve(pins.size());
        for(auto pin : pins)
            pin_positions.push_back(static_cast<PinPlacement*>(pin)->pin_position());
        interconnection::hpwl(pin_positions);
    }

    metric.end();
}

void interconnection_estimate_parallel_ood(design::Design &design, Metric &metric)
{
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

                pin_object->set_position(location);
                m_nets.back().add_pin(pin_object);
            }
            else {
                //Cell Pin
                PinPlacement * pin_object = new PinPlacement(pin_name, &net_object);
                pin_object->set_position(design.placementMapping().location(pin));
                m_nets.back().add_pin(pin_object);
            }
        }
    }

    metric.start();

#pragma omp parallel for
    for(auto net_it = m_nets.begin(); net_it < m_nets.end(); ++net_it)
    {
        auto net = *net_it;
        std::vector<util::LocationDbu> pin_positions;
        for(auto pin : net.pins())
            pin_positions.push_back(static_cast<PinPlacement*>(pin)->pin_position());
        interconnection::hpwl(pin_positions);
    }

    metric.end();
}

//=================================================================================================
//============================================== DOD ==============================================
//=================================================================================================

void interconnection_estimate_sequential_dod(design::Design &design, Metric &metric)
{
    using Net = ophidian::circuit::Net;
    using Pin = ophidian::circuit::Pin;

    ophidian::entity_system::Property<Pin, util::LocationDbu > pinPosition( design.netlist().makeProperty<util::LocationDbu>(Pin()) );

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
                pinPosition[pin] = location;
            }
            else {
                //Cell Pin
                pinPosition[pin] = design.placementMapping().location(pin);
            }
        }
    }

    metric.start();

    std::vector<util::LocationDbu> pin_positions;
    for(auto net_it = design.netlist().begin(Net()); net_it != design.netlist().end(Net()); ++net_it)
    {
        auto net = *net_it;
        auto pins = design.netlist().pins(net);
        pin_positions.clear();
        pin_positions.reserve(pins.size());
        for(auto pin : pins)
        {
            pin_positions.push_back(pinPosition[pin]);
        }
        interconnection::hpwl(pin_positions);
    }

    metric.end();
}


void interconnection_estimate_parallel_dod(design::Design &design, Metric &metric)
{
    using Net = ophidian::circuit::Net;
    using Pin = ophidian::circuit::Pin;

    ophidian::entity_system::Property<Pin, util::LocationDbu > pinPosition( design.netlist().makeProperty<util::LocationDbu>(Pin()) );

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
                pinPosition[pin] = location;
            }
            else {
                //Cell Pin
                pinPosition[pin] = design.placementMapping().location(pin);
            }
        }
    }

    metric.start();

#pragma omp parallel for
    for(auto net_it = design.netlist().begin(Net()); net_it < design.netlist().end(Net()); ++net_it)
    {
        auto net = *net_it;
        auto pins = design.netlist().pins(net);
        std::vector<util::LocationDbu> pin_positions;
        pin_positions.reserve(pins.size());
        for(auto pin : pins)
        {
            pin_positions.push_back(pinPosition[pin]);
        }
        interconnection::hpwl(pin_positions);
    }

    metric.end();
}

//=================================================================================================
//========================================== DOD Ordered ==========================================
//=================================================================================================

void interconnection_estimate_sequential_dod_ordered(design::Design &design, Metric &metric)
{
    using Net = ophidian::circuit::Net;
    using Pin = ophidian::circuit::Pin;
    using locationIterator = std::vector<util::LocationDbu>::const_iterator;
    using iteratorPair = std::pair<locationIterator, locationIterator>;

    ophidian::entity_system::Property<Net, iteratorPair > netPinsRange( design.netlist().makeProperty< iteratorPair >(Net()) );

    std::vector<util::LocationDbu> pin_positions;
    pin_positions.reserve(design.netlist().size(Pin()));

    for(auto net_it = design.netlist().begin(Net()); net_it < design.netlist().end(Net()); ++net_it)
    {
        Net net = *net_it;
        locationIterator begin = pin_positions.end();
        for(auto pin : design.netlist().pins(net))
        {
            if(design.netlist().cell(pin) == ophidian::circuit::Cell())
            {
                //Pad
                auto padInput = design.netlist().input(pin);
                auto padOutput = design.netlist().output(pin);
                auto location = (padInput == ophidian::circuit::Input()) ? design.placement().outputPadLocation(padOutput) : design.placement().inputPadLocation(padInput);
                pin_positions.push_back(location);
            }
            else {
                //Cell Pin
                pin_positions.push_back(design.placementMapping().location(pin));
            }
        }
        locationIterator end = pin_positions.end();
        netPinsRange[net] = std::make_pair(begin, end);
    }

    metric.start();

    for(auto net_it = design.netlist().begin(Net()); net_it != design.netlist().end(Net()); ++net_it)
    {
        interconnection::hpwl(netPinsRange[*net_it].first, netPinsRange[*net_it].second);
    }

    metric.end();
}

void interconnection_estimate_parallel_dod_ordered(design::Design &design, Metric &metric)
{
    using Net = ophidian::circuit::Net;
    using Pin = ophidian::circuit::Pin;
    using locationIterator = std::vector<util::LocationDbu>::const_iterator;
    using iteratorPair = std::pair<locationIterator, locationIterator>;

    ophidian::entity_system::Property<Net, iteratorPair > netPinsRange( design.netlist().makeProperty< iteratorPair >(Net()) );

    std::vector<util::LocationDbu> pin_positions;
    pin_positions.reserve(design.netlist().size(Pin()));

    for(auto net_it = design.netlist().begin(Net()); net_it < design.netlist().end(Net()); ++net_it)
    {
        Net net = *net_it;
        locationIterator begin = pin_positions.end();
        for(auto pin : design.netlist().pins(net))
        {
            if(design.netlist().cell(pin) == ophidian::circuit::Cell())
            {
                //Pad
                auto padInput = design.netlist().input(pin);
                auto padOutput = design.netlist().output(pin);
                auto location = (padInput == ophidian::circuit::Input()) ? design.placement().outputPadLocation(padOutput) : design.placement().inputPadLocation(padInput);
                pin_positions.push_back(location);
            }
            else {
                //Cell Pin
                pin_positions.push_back(design.placementMapping().location(pin));
            }
        }
        locationIterator end = pin_positions.end();
        netPinsRange[net] = std::make_pair(begin, end);
    }

    metric.start();
#pragma omp parallel for
    for(auto net_it = design.netlist().begin(Net()); net_it < design.netlist().end(Net()); ++net_it)
    {
        interconnection::hpwl(netPinsRange[*net_it].first, netPinsRange[*net_it].second);
    }

    metric.end();
}

//=================================================================================================
//===================================== DOD Property Ordered ======================================
//=================================================================================================
void interconnection_estimate_sequential_dod_property_ordered(design::Design &design, Metric &metric)
{
    using Net = ophidian::circuit::Net;
    using Pin = ophidian::circuit::Pin;
    using Location = util::LocationDbu;
    ophidian::entity_system::Property<Pin, Location > pinPosition( design.netlist().makeProperty<Location>(Pin()) );

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
                pinPosition[pin] = location;
            }
            else {
                //Cell Pin
                pinPosition[pin] = design.placementMapping().location(pin);
            }
        }
    }

    const entity_system::EntitySystem <Net> & nets = design.netlist().getNets();
    const entity_system::Association<Net, Pin> & netPins = design.netlist().getNetPins();

    ophidian::entity_system::PropertyGrouped<Net, Pin, Location> propGrouped(nets, pinPosition, netPins);

    metric.start();

    for(auto net_it = nets.begin(); net_it != nets.end(); ++net_it)
    {
        interconnection::hpwl(propGrouped.begin(*net_it), propGrouped.end(*net_it));
    }

    metric.end();
}

void interconnection_estimate_parallel_dod_property_ordered(ophidian::design::Design &design, Metric &metric){
    using Net = ophidian::circuit::Net;
    using Pin = ophidian::circuit::Pin;
    using Location = util::LocationDbu;
    ophidian::entity_system::Property<Pin, Location > pinPosition( design.netlist().makeProperty<Location>(Pin()) );

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
                pinPosition[pin] = location;
            }
            else {
                //Cell Pin
                pinPosition[pin] = design.placementMapping().location(pin);
            }
        }
    }

    const entity_system::EntitySystem <Net> & nets = design.netlist().getNets();
    const entity_system::Association<Net, Pin> & netPins = design.netlist().getNetPins();

    ophidian::entity_system::PropertyGrouped<Net, Pin, Location> propGrouped(nets, pinPosition, netPins);

    metric.start();

#pragma omp parallel for
    for(auto net_it = nets.begin(); net_it != nets.end(); ++net_it)
    {
        interconnection::hpwl(propGrouped.begin(*net_it), propGrouped.end(*net_it));
    }

    metric.end();
}

} // namespace interconnection_estimate
} // namespace experiments
} // namespace ophidian
