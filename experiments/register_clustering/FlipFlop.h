#ifndef FLIPFLOP_H
#define FLIPFLOP_H

//namespace ophidian
//{
//namespace experiments
//{
//namespace register_clustering
//{

//class FlipFlopExt125
//{
//private:
//    geometry::Point position_;
//    ClusterOOD<FlipFlopExt125> * clusterBest_;

//    std::string name_ = "DFF_X80";
//    volatile long long cap;
//    volatile long long cap2;
//    geometry::Point size_;
//    int net_;

//    volatile long double a;
//    volatile double aaa;
//    volatile int b;
//public:
//    FlipFlopExt125(geometry::Point & p) : position_(p)
//    {
//        cap = 5;
//        cap2 = cap * 2;
//        b = 5;
//        a, aaa = 0.5;
//    }

//    ClusterOOD<FlipFlopExt125> *clusterBest() const
//    {
//        return clusterBest_;
//    }

//    void setClusterBest(ClusterOOD<FlipFlopExt125> *clusterBest)
//    {
//        clusterBest_ = clusterBest;
//    }

//    geometry::Point position() const
//    {
//        return position_;
//    }

//    void setPosition(const geometry::Point &position)
//    {
//        position_ = position;
//    }
//};

//class FlipFlopExt150
//{
//private:
//    geometry::Point position_;
//    ClusterOOD<FlipFlopExt150> * clusterBest_;

//    std::string name_ = "DFF_X80";
//    volatile long long cap;
//    volatile long long cap2;
//    geometry::Point size_;
//    int net_;

//    volatile long double a, b, c;
//    volatile double aaa;
//    volatile int d;
//public:
//    FlipFlopExt150(geometry::Point & p) : position_(p)
//    {
//        cap = 5;
//        cap2 = cap * 2;
//        d = 5;
//        a, b, c, aaa = 0.5;
//    }

//    ClusterOOD<FlipFlopExt150> *clusterBest() const
//    {
//        return clusterBest_;
//    }

//    void setClusterBest(ClusterOOD<FlipFlopExt150> *clusterBest)
//    {
//        clusterBest_ = clusterBest;
//    }

//    geometry::Point position() const
//    {
//        return position_;
//    }

//    void setPosition(const geometry::Point &position)
//    {
//        position_ = position;
//    }
//};

//class FlipFlopExt175
//{
//private:
//    geometry::Point position_;
//    ClusterOOD<FlipFlopExt175> * clusterBest_;

//    std::string name_ = "DFF_X80";
//    volatile long long cap;
//    volatile long long cap2;
//    geometry::Point size_;
//    int net_;

//    volatile long double a, b, c, d, e;
//    volatile double aaa;

//public:
//    FlipFlopExt175(geometry::Point & p) : position_(p)
//    {
//        cap = 5;
//        cap2 = cap * 2;
//        a, b, c, d, e, aaa = 0.5;
//    }

//    ClusterOOD<FlipFlopExt175> *clusterBest() const
//    {
//        return clusterBest_;
//    }

//    void setClusterBest(ClusterOOD<FlipFlopExt175> *clusterBest)
//    {
//        clusterBest_ = clusterBest;
//    }

//    geometry::Point position() const
//    {
//        return position_;
//    }

//    void setPosition(const geometry::Point &position)
//    {
//        position_ = position;
//    }
//};

//class FlipFlopExt200
//{
//private:
//    geometry::Point position_;
//    ClusterOOD<FlipFlopExt200> * clusterBest_;

//    std::string name_ = "DFF_X80";
//    volatile long long cap;
//    volatile long long cap2;
//    geometry::Point size_;
//    int net_;

//    volatile long double a, b, c, d, e, f;
//    volatile double aaa, bb;
//public:
//    FlipFlopExt200(geometry::Point & p) : position_(p)
//    {
//        cap = 5;
//        cap2 = cap * 2;
//        a, b, c, d, e, f, aaa, bb = 0.5;
//    }

//    ClusterOOD<FlipFlopExt200> *clusterBest() const
//    {
//        return clusterBest_;
//    }

//    void setClusterBest(ClusterOOD<FlipFlopExt200> *clusterBest)
//    {
//        clusterBest_ = clusterBest;
//    }

//    geometry::Point position() const
//    {
//        return position_;
//    }

//    void setPosition(const geometry::Point &position)
//    {
//        position_ = position;
//    }
//};

//class FlipFlopExt400
//{
//private:
//    geometry::Point position_;
//    ClusterOOD<FlipFlopExt400> * clusterBest_;

//    std::string name_ = "DFF_X80";
//    volatile long long cap;
//    volatile long long cap2;
//    geometry::Point size_;
//    int net_;

//    volatile long double a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t;
//public:
//    FlipFlopExt400(geometry::Point & p) : position_(p)
//    {
//        cap = 5;
//        cap2 = cap * 2;
//        a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t = 0.5;
//    }

//    ClusterOOD<FlipFlopExt400> *clusterBest() const
//    {
//        return clusterBest_;
//    }

//    void setClusterBest(ClusterOOD<FlipFlopExt400> *clusterBest)
//    {
//        clusterBest_ = clusterBest;
//    }

//    geometry::Point position() const
//    {
//        return position_;
//    }

//    void setPosition(const geometry::Point &position)
//    {
//        position_ = position;
//    }
//};

//class FlipFlopExt600
//{
//private:
//    geometry::Point position_;
//    ClusterOOD<FlipFlopExt600> * clusterBest_;

//    std::string name_ = "DFF_X80";
//    volatile long long cap;
//    volatile long long cap2;
//    geometry::Point size_;
//    int net_;

//    volatile long double a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, x, z, aa, bb, cc, dd, ee, ff, gg, hh;
//    volatile double aaa;
//public:
//    FlipFlopExt600(geometry::Point & p) : position_(p)
//    {
//        cap = 5;
//        cap2 = cap * 2;
//        a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, x, z, aa, bb, cc, dd, ee, ff, gg, hh, aaa = 0.5;
//    }

//    ClusterOOD<FlipFlopExt600> *clusterBest() const
//    {
//        return clusterBest_;
//    }

//    void setClusterBest(ClusterOOD<FlipFlopExt600> *clusterBest)
//    {
//        clusterBest_ = clusterBest;
//    }

//    geometry::Point position() const
//    {
//        return position_;
//    }

//    void setPosition(const geometry::Point &position)
//    {
//        position_ = position;
//    }
//};

//} // namespace register_clustering
//} // namespace experiments
//} // namespace ophidian

#endif // FLIPFLOP_H
