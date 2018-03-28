#ifndef A_STAR_OBJECT_ORIENTED_DESIGN_H
#define A_STAR_OBJECT_ORIENTED_DESIGN_H

#include "ophidian/design/Design.h"
#include "experiments/metric.h"

namespace ophidian
{
namespace experiments
{
namespace a_star
{
class Pin;

class Net
{
    std::string m_name;
    std::vector<Pin*> m_pins;
    std::vector<ophidian::geometry::Point> pinPositions;
public:
    Net(std::string &name);
    std::string name();
    void reserve(std::size_t size);
    void add_pin(Pin * pin);
    void add_pinPosition(ophidian::geometry::Point position);
    const std::vector<Pin*> & pins() const;
    std::vector<ophidian::geometry::Point> get_pinPositions();
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
    ophidian::geometry::Point m_position;
public:
    PinPlacement(std::string name, Net * net);
    void set_position(const ophidian::geometry::Point &position);
    const ophidian::geometry::Point & pin_position();
};

void A_star_object_oriented_design_sequential_graphOOD(design::Design &design, Metric &metric);

void A_star_object_oriented_design_sequential_lemon(design::Design &design, Metric &metric);

} // namespace a_star
} // namespace experiments
} // namespace ophidian
#endif // A_STAR_OBJECT_ORIENTED_DESIGN_H
