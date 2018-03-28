#ifndef A_STAR_DATA_ORIENTED_DESIGN_H
#define A_STAR_DATA_ORIENTED_DESIGN_H

#include "ophidian/design/Design.h"
#include "experiments/metric.h"

namespace ophidian
{
namespace experiments
{
namespace a_star
{

void A_star_data_oriented_design_sequential(ophidian::design::Design &design, Metric &metric);

} // namespace a_star
} // namespace experiments
} // namespace ophidian
#endif // A_STAR_DATA_ORIENTED_DESIGN_H
