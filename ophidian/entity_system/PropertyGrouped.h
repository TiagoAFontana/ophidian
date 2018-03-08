#ifndef PROPERTYGROUPED_H
#define PROPERTYGROUPED_H

#include "Property.h"
#include "Association.h"

namespace ophidian
{
namespace entity_system
{

template <class WholeEntity_, class Entity_, class Value_>
class PropertyGrouped :
    public Property<Entity_, Value_>
{
public:
    using Parent = typename EntitySystem <Entity_>::NotifierType::ObserverBase;
    using Value = Value_;
    using Entity = Entity_;
    using Whole = WholeEntity_;
    using ContainerType = std::vector <Value>;
    using size_type = typename ContainerType::size_type;
    using Iterator = typename ContainerType::iterator;
    using IteratorPair = std::pair<Iterator, Iterator>;

    PropertyGrouped(const EntitySystem<Whole> & whole, const Property<Entity, Value> & propParts, const Association<Whole, Entity> & a) :
        Property<Entity, Value>(propParts), propertyRange(whole)
    {
        mPropertiesGroup.reserve(propParts.size());
        mId2Index.reserve(propParts.size());

        for(auto w: whole)
        {
            Iterator begin = mPropertiesGroup.end();
            auto parts = a.parts(w);
            for(auto p : parts)
            {
                mId2Index[Parent::notifier()->id(p)] = mPropertiesGroup.size();
                mPropertiesGroup.push_back(Property<Entity_, Value_>::mProperties[Parent::notifier()->id(p)]);
            }
            Iterator end = mPropertiesGroup.end();
            propertyRange[w] = std::make_pair(begin, end);
        }
    }

    ~PropertyGrouped() override{

    }

    virtual typename ContainerType::reference operator[](const Entity & entity){
        return mPropertiesGroup[mId2Index[Parent::notifier()->id(entity)]];
    }

    virtual typename ContainerType::const_reference operator[](const Entity & entity) const {
        return mPropertiesGroup[mId2Index[Parent::notifier()->id(entity)]];
    }


    virtual typename ContainerType::iterator begin()
    {
        return mPropertiesGroup.begin();
    }

    virtual typename ContainerType::iterator end()
    {
        return mPropertiesGroup.end();
    }

    virtual typename ContainerType::const_iterator begin() const
    {
        return mPropertiesGroup.begin();
    }

    virtual typename ContainerType::const_iterator end() const
    {
        return mPropertiesGroup.end();
    }

    typename ContainerType::iterator begin(Whole w)
    {
        return propertyRange[w].first;
    }

    typename ContainerType::iterator end(Whole w)
    {
        return propertyRange[w].second;
    }

    template <typename Whole, typename Entity>
    void group (EntitySystem<Whole> & e, Association<Whole, Entity> & a){
        mPropertiesGroup.clear();
        mPropertiesGroup.reserve(Property<Entity_, Value_>::mProperties.size());
        mId2Index.reserve(Property<Entity_, Value_>::mProperties.size());

        for(auto whole: e)
        {
            auto parts = a.parts(whole);
            for(auto p : parts)
            {
                mId2Index[Parent::notifier()->id(p)] = mPropertiesGroup.size();
                mPropertiesGroup.push_back(Property<Entity_, Value_>::mProperties[Parent::notifier()->id(p)]);
            }
        }
    }

private:
    ContainerType mPropertiesGroup;
    std::vector <size_type> mId2Index;
    Property<Whole, IteratorPair> propertyRange;
};


} // namespace entity_system
} // namespace ophidian
#endif // PROPERTYGROUPED_H
