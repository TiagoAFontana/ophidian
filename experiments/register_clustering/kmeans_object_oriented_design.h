#ifndef KMEANSOBJECTORIENTEDDESIGN_H
#define KMEANSOBJECTORIENTEDDESIGN_H

#include <random>

#include "ophidian/geometry/Models.h"
#include "experiments/metric.h"

namespace ophidian
{
namespace experiments
{
namespace register_clustering
{

class ClusterOOD;


class FlipFlop
{
public:
    virtual geometry::Point position() const = 0;
    virtual void setPosition(const geometry::Point &position) = 0;
    virtual ClusterOOD *clusterBest() const = 0;
    virtual void setClusterBest(ClusterOOD *clusterBest) = 0;
};

class FlipFlopExt
{
private:
private:
    geometry::Point position_;
    ClusterOOD * clusterBest_;

    std::string name_ = "DFF_X80";
    volatile long long cap;
    volatile long long cap2;
    geometry::Point size_;
    int net_;

    volatile long double a;
    volatile long double b;
    volatile long double c;
    volatile long double d;
    volatile long double e;
    volatile long double f;
    volatile long double g;
    volatile long double h;
    volatile long double i;
    volatile long double j;
    volatile long double k;
    volatile long double l;
    volatile long double m;
    volatile long double n;
    volatile long double o;
    volatile long double p;
    volatile long double q;
    volatile long double r;
    volatile long double s;
    volatile long double t;
    volatile long double u;
    volatile long double v;
    volatile long double x;
    volatile long double z;
    volatile long double aa;
    volatile long double bb;
    volatile long double cc;
    volatile long double dd;
    volatile long double ee;
    volatile long double ff;
    volatile long double gg;
    volatile long double hh;
    volatile long double ii;
    volatile long double jj;
    volatile double aaa;
public:
    FlipFlopExt(geometry::Point & p) : position_(p) {
        cap = 5;
        cap2 = cap * 2;
        a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, x, z, aa, bb, cc, dd, ee, ff, gg, hh, ii, jj, aaa = 0.5;
    }

    virtual ClusterOOD *clusterBest() const
    {
        return clusterBest_;
    }

    virtual void setClusterBest(ClusterOOD *clusterBest)
    {
        clusterBest_ = clusterBest;
    }

    virtual geometry::Point position() const
    {
        return position_;
    }

    virtual void setPosition(const geometry::Point &position)
    {
        position_ = position;
    }
};

class FlipFlopF : public FlipFlop
{
private:
    geometry::Point position_;
    ClusterOOD * clusterBest_;

    std::string name_ = "DFF_X80";
    volatile long long cap;
    volatile long long cap2;
    geometry::Point size_;
    int net_;
public:
    FlipFlopF(geometry::Point & p) : position_(p) {
        cap = 5;
        cap2 = cap * 2;
    }

    virtual ClusterOOD *clusterBest() const
    {
        return clusterBest_;
    }

    virtual void setClusterBest(ClusterOOD *clusterBest)
    {
        clusterBest_ = clusterBest;
    }

    virtual geometry::Point position() const
    {
        return position_;
    }

    virtual void setPosition(const geometry::Point &position)
    {
        position_ = position;
    }
};

class FlipFlopF600 : public FlipFlop
{
private:
    geometry::Point position_;
    ClusterOOD * clusterBest_;

    std::string name_ = "DFF_X80";
    volatile long double cap;
    volatile long double cap2;


    geometry::Point size_;
    int net_;
public:
    FlipFlopF600(geometry::Point & p) : position_(p) {
        cap = 5;
        cap2 = cap * 2;

//        a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, x, z, aa, bb, cc, dd, ee, ff, gg, hh, ii, jj, aaa = 0.5;
    }

    virtual ClusterOOD *clusterBest() const
    {
        return clusterBest_;
    }

    virtual void setClusterBest(ClusterOOD *clusterBest)
    {
        clusterBest_ = clusterBest;
    }

    virtual geometry::Point position() const
    {
        return position_;
    }

    virtual void setPosition(const geometry::Point &position)
    {
        position_ = position;
    }
};

template<int N>
class FlipFlopT : public FlipFlop
{
private:
    geometry::Point position_;
    ClusterOOD * clusterBest_;

    std::string name_ = "DFF_X80";
    volatile long long cap;
    volatile long long cap2;
    geometry::Point size_;
    int net_;

public:
    volatile std::array<double, N> mem;

    FlipFlopT(geometry::Point & p) : position_(p) {
        cap = 5;
        cap2 = cap * 2;
//        mem.fill(5.0);
    }

    virtual ClusterOOD * clusterBest() const
    {
        return clusterBest_;
    }

    virtual void setClusterBest(ClusterOOD *clusterBest)
    {
        clusterBest_ = clusterBest;
    }

    virtual geometry::Point position() const
    {
        return position_;
    }

    virtual void setPosition(const geometry::Point &position)
    {
        position_ = position;
    }

};

class ClusterOOD
{
private:
    geometry::Point center_;
    std::vector<FlipFlop*> elements_;
public:
    ClusterOOD(const geometry::Point &center);

    std::vector<FlipFlop*> elements() const;
    void elements(const std::vector<FlipFlop*> &elements);
    geometry::Point center() const;
    void center(const geometry::Point &center);

    void insertElement(FlipFlop *element);
    void clear();
    int size();
};

class ClusterOODext
{
private:
    geometry::Point center_;
    std::vector<FlipFlopExt*> elements_;
public:
    ClusterOODext(const geometry::Point &center);

    std::vector<FlipFlopExt*> elements() const;
    void elements(const std::vector<FlipFlopExt*> &elements);
    geometry::Point center() const;
    void center(const geometry::Point &center);

    void insertElement(FlipFlopExt *element);
    void clear();
    int size();
};


class KmeansObjectOrientedDesign
{
private:
    std::default_random_engine m_generator;
    std::uniform_real_distribution<double> m_distribution_x;
    std::uniform_real_distribution<double> m_distribution_y;


    using rtree_node = std::pair<geometry::Point, ClusterOOD*>;
    using rtree_nodeExt = std::pair<geometry::Point, ClusterOODext*>;

    using rtree = boost::geometry::index::rtree<rtree_node, boost::geometry::index::rstar<16> >;
    using rtreeExt = boost::geometry::index::rtree<rtree_nodeExt, boost::geometry::index::rstar<16> >;
public:
    std::vector<ClusterOOD> clusters_;
    std::vector<ClusterOODext> clustersExt_;

    KmeansObjectOrientedDesign(geometry::Point chipOrigin, geometry::Point chipBondary, unsigned k = 50);
    KmeansObjectOrientedDesign(const std::vector<geometry::Point> &centers);

    void cluster_registers_with_rtree(std::vector<FlipFlopExt > &flip_flops, ophidian::experiments::Metric &metric, unsigned iterations = 10);

    void cluster_registers_with_rtree(std::vector<std::unique_ptr<FlipFlop> > &flip_flops, ophidian::experiments::Metric &metric, unsigned iterations = 10);
    void cluster_registers_with_rtree_paralel(std::vector<std::unique_ptr<FlipFlop> > &flip_flops, ophidian::experiments::Metric &metric, unsigned iterations = 10);
//    void cluster_registers(std::vector<FlipFlop> &flip_flops, unsigned iterations = 10);
//    void cluster_registers_paralel(std::vector<FlipFlop> &flip_flops, unsigned iterations = 10);
};


} // namespace register_clustering
} // namespace experiments
} // namespace ophidian
#endif // KMEANSOBJECTORIENTEDDESIGN_H
