#include "Interconnections.h"
#include <ophidian/interconnection/HPWL.h>
#include <ophidian/interconnection/STWL.h>

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
}
void Net::add_pin(Pin * pin){
    m_pins.push_back(pin);
}
const std::vector<Pin*> & Net::pins() const {
    return m_pins;
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
            PinPlacement * pin_object = new PinPlacement(pin_name, &net_object);
            pin_object->set_position(design.placementMapping().location(pin));
            m_nets.back().add_pin(pin_object);
        }
    }

    metric.start();
    for(auto net : m_nets)
    {
        std::vector<util::LocationDbu> pin_positions;
        for(auto pin : net.pins())
            pin_positions.push_back(static_cast<PinPlacement*>(pin)->pin_position());
        interconnection::hpwl(pin_positions);
        interconnection::stwl(pin_positions);
    }
    metric.end();
}

void interconnection_estimate_parallel_ood(design::Design &design, Metric &metric)
{
    metric.start();
    metric.end();
}

void interconnection_estimate_sequential_dod(design::Design &design, Metric &metric)
{
    metric.start();
    using Net = ophidian::circuit::Net;
    for(auto net_it = design.netlist().begin(Net()); net_it != design.netlist().end(Net()); ++net_it)
    {
        auto net = *net_it;
        std::vector<util::LocationDbu> pin_positions;
        pin_positions.reserve(design.netlist().pins(net).size());
        for(auto pin : design.netlist().pins(net))
            pin_positions.push_back(design.placementMapping().location(pin));
        interconnection::hpwl(pin_positions);
        interconnection::stwl(pin_positions);
    }
    metric.end();
}

void interconnection_estimate_parallel_dod(design::Design &design, Metric &metric)
{
    metric.start();
    metric.end();
}



} // namespace interconnection_estimate
} // namespace experiments
} // namespace ophidian
