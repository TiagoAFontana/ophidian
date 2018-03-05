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
//        using Property = Property<Entity_, Value_>;
    using Value = Value_;
    using Entity = Entity_;
    using Whole = WholeEntity_;
    using ContainerType = std::vector <Value>;
    using size_type = typename ContainerType::size_type;

    PropertyGrouped(const EntitySystem <Entity_> & system, Value defaultValue = Value()) :
        Property<Entity, Value>(system, defaultValue)
    {
        mPropertiesGroup.reserve(system.capacity());
        mPropertiesGroup.resize(system.size());
        mPropertiesGroup.assign(mPropertiesGroup.size(), defaultValue);
        mId2Index.reserve(system.capacity());
        for (int i = 0; i < system.size(); ++i)
        {
            mId2Index.push_back(i);
        }
        grouped = false;
    }

    PropertyGrouped(){

    }

    ~PropertyGrouped() override{

    }

    virtual typename ContainerType::reference operator[](const Entity & entity){
        if(grouped)
        {
            return mPropertiesGroup[mId2Index[Parent::notifier()->id(entity)]];
        }
        else {
            return Property<Entity_, Value_>::mProperties[Parent::notifier()->id(entity)];
        }
    }

    virtual typename ContainerType::const_reference operator[](const Entity & entity) const {
        if(grouped)
        {
            return mPropertiesGroup[mId2Index[Parent::notifier()->id(entity)]];
        }
        else {
            return Property<Entity_, Value_>::mProperties[Parent::notifier()->id(entity)];
        }
    }

    template <typename Whole, typename Entity>
    void group (EntitySystem<Whole> & e, Association<Whole, Entity> & a){
        mPropertiesGroup.clear();
        mPropertiesGroup.reserve(Property<Entity_, Value_>::mProperties.size());
//        mId2Index.clear();
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
        grouped = true;
    }

private:
    ContainerType mPropertiesGroup;
    std::vector <size_type> mId2Index;
    bool grouped;
};


} // namespace entity_system
} // namespace ophidian
#endif // PROPERTYGROUPED_H
