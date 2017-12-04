#ifndef INTERCONECTIONS_H
#define INTERCONECTIONS_H

#include "ophidian/design/Design.h"
#include "experiments/metric.h"

using namespace ophidian;

namespace interconnection_estimate
{
class Pin;

class Net
{
    std::string m_name;
    std::vector<Pin*> m_pins;
public:
    Net(std::string &name);
    std::string name();
    void reserve(std::size_t size);
    void add_pin(Pin * pin);
    const std::vector<Pin*> & pins() const;
};

class Pin
{
    std::string m_name;
    std::unique_ptr<Net> m_net_ptr;
public:
    Pin(std::string name, Net * net);
};

class PinPlacement : public Pin
{
    util::LocationDbu m_position;
public:
    PinPlacement(std::string name, Net * net);
    void set_position(const util::LocationDbu &position);
    const util::LocationDbu & pin_position();
};

void interconnection_estimate_sequential_ood(ophidian::design::Design &design, Metric &metric);
void interconnection_estimate_parallel_ood(ophidian::design::Design &design, Metric &metric);

void interconnection_estimate_sequential_dod(ophidian::design::Design &design, Metric &metric);
void interconnection_estimate_parallel_dod(ophidian::design::Design &design, Metric &metric);


} // namespace


#endif // INTERCONECTIONS_H
