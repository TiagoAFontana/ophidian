#include "ChipBoundaries.h"

using namespace ophidian;

namespace chip_boundaries
{

PlacementCell::PlacementCell(const std::string & name, const bool fixed, std::size_t pins_size) : Cell(name, pins_size), m_fixed(m_fixed){
}
void PlacementCell::set_geometry(multipolygon geometry){
    m_geometry = geometry;
}
void PlacementCell::set_position(const point & position){
    m_position = position;
}
const PlacementCell::point & PlacementCell::get_position(){
    return m_position;
}

//void problem_a_ood(parsing::def * def, parsing::lef * lef, placement::placement & m_placement, Metric &metric){
//    floorplan::floorplan m_floorplan;
//    floorplan::lefdef2floorplan(*lef, *def, m_floorplan);
//    geometry::point<double> m_chip_boundaries = m_floorplan.chip_boundaries();
//    std::vector<PlacementCell> m_cells;
//    m_cells.reserve(m_placement.netlist().cell_system().size());

//    for(auto cell : m_placement.netlist().cell_system())
//    {
//        PlacementCell p_cell(m_placement.netlist().cell_name(cell), m_placement.cell_fixed(cell), m_placement.netlist().cell_pins(cell).size());
//        p_cell.set_geometry(m_placement.cell_geometry(cell));
//        p_cell.set_position(m_placement.cell_position(cell));
//        m_cells.push_back(p_cell);
//    }

//    bool placemente_is_legal = true;
//    metric.start();
//    for(auto cell : m_cells)
//    {
//        auto position = cell.get_position();
//        if(position.x() < 0 || position.y() < 0 || position.x() > m_chip_boundaries.x() || position.y() > m_chip_boundaries.y())
//        {
//            placemente_is_legal = false;
//            break;
//        }
//    }
//    metric.end();
//    metric.print_result();
//}
void chip_boundaries_sequential_ood(design::Design &design, Metric &metric)
{
//    using Cell = ophidian::circuit::Cell();

//    util::LocationDbu m_chip_Origin = design.floorplan().chipOrigin();
//    util::LocationDbu m_chip_UpperRightCorner = design.floorplan().chipUpperRightCorner();

//    std::vector<PlacementCell> m_cells;
//    m_cells.reserve(design.netlist().size(Cell));

//    //for(auto cell : m_placement.netlist().cell_system()){
//    for(auto cell_it = design.netlist().begin(Cell); cell_it != design.netlist().end(Cell); ++cell_it)
//    {
//        auto cell = *cell_it;
////        PlacementCell p_cell(m_placement.netlist().cell_name(cell), m_placement.cell_fixed(cell), m_placement.netlist().cell_pins(cell).size());
//        PlacementCell p_cell(design.netlist().name(cell), design.placement().isFixed(cell), design.netlist().pins(cell).size());
////        p_cell.set_geometry(m_placement.cell_geometry(cell));
//        p_cell.set_geometry(design.placementMapping().geometry(cell));
////        p_cell.set_position(m_placement.cell_position(cell));
//        p_cell.set_position(design.placement().cellLocation(cell).toPoint());
//        m_cells.push_back(p_cell);
//    }

//    bool placemente_is_legal = true;
//    metric.start();
//    for(auto cell : m_cells)
//    {
//        auto position = cell.get_position();
//        if(position.x() < m_chip_Origin.x() || position.y() < m_chip_Origin.y() || position.x() > m_chip_UpperRightCorner.x() || position.y() > m_chip_UpperRightCorner.y())
//        {
//            placemente_is_legal = false;
////            break;
//        }
//    }
//    metric.end();
//    metric.print_result();
}
void chip_boundaries_parallel_ood(design::Design &design, Metric &metric)
{

}


void chip_boundaries_sequential_dod(ophidian::design::Design &design, Metric &metric){
    util::LocationDbu m_chip_Origin = design.floorplan().chipOrigin();
    util::LocationDbu m_chip_UpperRightCorner = design.floorplan().chipUpperRightCorner();
    bool placement_is_legal = true;
    auto range = design.placement().cellLocationRange();
    metric.start();
    for(auto position_it = range.begin(); position_it != range.end(); ++position_it)
    {
        auto position = *position_it;
        if(position.x() < m_chip_Origin.x() || position.y() < m_chip_Origin.y() || position.x() > m_chip_UpperRightCorner.x() || position.y() > m_chip_UpperRightCorner.y())
        {
            placement_is_legal = false;
//            break;
        }
    }
    metric.end();
}

void chip_boundaries_parallel_dod(ophidian::design::Design &design, Metric &metric){
    util::LocationDbu m_chip_Origin = design.floorplan().chipOrigin();
    util::LocationDbu m_chip_UpperRightCorner = design.floorplan().chipUpperRightCorner();
    bool placement_is_legal = true;
    auto range = design.placement().cellLocationRange();
    metric.start();
    //TODO: parallel
    for(auto position_it = range.begin(); position_it != range.end(); ++position_it)
    {
        auto position = *position_it;
        if(position.x() < m_chip_Origin.x() || position.y() < m_chip_Origin.y() || position.x() > m_chip_UpperRightCorner.x() || position.y() > m_chip_UpperRightCorner.y())
        {
            placement_is_legal = false;
//            break;
        }
    }
    metric.end();
}





} // namespace chip_boundaries
