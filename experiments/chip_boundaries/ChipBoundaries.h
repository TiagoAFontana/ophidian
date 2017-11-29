#ifndef CHIPBOUNDARIES_H
#define CHIPBOUNDARIES_H



#include "ophidian/floorplan/Floorplan.h"
#include "ophidian/floorplan/LefDef2Floorplan.h"
#include "ophidian/design/Design.h"
#include "experiments/metric.h"


using namespace ophidian;

namespace chip_boundaries
{
class Pin
{
public:
    Pin(){
    }
};

class StdCell
{
public:
    StdCell(){
    }
};

class Cell
{
    std::string m_name;
    StdCell * m_standard_cell;
    std::vector<Pin*> m_pins;
public:
    Cell(const std::string & name, std::size_t pins_size) : m_name(name){
        m_pins.reserve(pins_size);
    }
};

class PlacementCell : public Cell
{
    using point = geometry::Point;
    using polygon = geometry::Polygon;
    using multipolygon = geometry::MultiPolygon;

    multipolygon m_geometry;
    point m_position;
    bool m_fixed;
public:
    PlacementCell(const std::string & name, const bool fixed, std::size_t pins_size);
    void set_geometry(multipolygon geometry);
    void set_position(const point & position);
    const point & get_position();
};

void chip_boundaries_sequential_ood(ophidian::design::Design &design, Metric &metric);
void chip_boundaries_parallel_ood(design::Design &design, Metric &metric);

void chip_boundaries_sequential_dod(ophidian::design::Design &design, Metric &metric);
void chip_boundaries_parallell_dod(ophidian::design::Design &design, Metric &metric);

} // namespace chip_boundaries

#endif // CHIPBOUNDARIES_H
