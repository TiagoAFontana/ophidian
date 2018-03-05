#include "property_test.h"
#include <catch.hpp>

#include <ophidian/entity_system/PropertyGrouped.h>
#include <ophidian/entity_system/Association.h>
#include <ophidian/entity_system/Aggregation.h>
#include <ophidian/entity_system/Composition.h>

#include "string"

using namespace ophidian::entity_system;


TEST_CASE("Property Grouped: null property", "[entity_system][Property][PropertyGrouped]")
{
    PropertyGrouped<MyEntity, MyEntity, MyDummyProperty> prop;
    REQUIRE( prop.empty() );
    REQUIRE( prop.size() == 0 );
}


TEST_CASE("Property Grouped: constructor before creating entities", "[entity_system][Property][PropertyGrouped]")
{
    EntitySystem<MyEntity> sys;
    PropertyGrouped<MyEntity, MyEntity, MyDummyProperty> prop(sys);
    REQUIRE( prop.size() == 0 );
    sys.add();
    REQUIRE( prop.size() == 1 );
}

TEST_CASE("Property Grouped: constructor after creating entities", "[entity_system][Property][PropertyGrouped]")
{
    EntitySystem<MyEntity> sys;
    sys.add();
    PropertyGrouped<MyEntity, MyEntity, MyDummyProperty> prop(sys);
    REQUIRE( prop.size() == 1 );
}

TEST_CASE("Property Grouped: assignment operator", "[entity_system][Property][PropertyGrouped]")
{
    EntitySystem<MyEntity> sys;
    PropertyGrouped<MyEntity, MyEntity, MyDummyProperty> prop;
    // ...
    prop = PropertyGrouped<MyEntity, MyEntity, MyDummyProperty>(sys);
    sys.add();
    REQUIRE( prop.size() == 1 );
}


TEST_CASE("Property Grouped: lazy assignment operator", "[entity_system][Property][PropertyGrouped]")
{
    EntitySystem<MyEntity> sys;
    PropertyGrouped<MyEntity, MyEntity, MyDummyProperty> prop;
    sys.add();
    prop = PropertyGrouped<MyEntity, MyEntity, MyDummyProperty>(sys);
    REQUIRE( prop.size() == 1 );
}

TEST_CASE("Property Grouped: move constructor", "[entity_system][Property][PropertyGrouped]")
{
    EntitySystem<MyEntity> sys;
    PropertyGrouped<MyEntity, MyEntity, MyDummyProperty> prop = PropertyGrouped<MyEntity, MyEntity, MyDummyProperty>(sys);
    REQUIRE( prop.size() == 0 );
    sys.add();
    REQUIRE( prop.size() == 1 );
}

TEST_CASE("Property Grouped: move constructor after creating entities", "[entity_system][Property][PropertyGrouped]")
{
    EntitySystem<MyEntity> sys;
    sys.add();
    PropertyGrouped<MyEntity, MyEntity, MyDummyProperty> prop = PropertyGrouped<MyEntity, MyEntity, MyDummyProperty>(sys);
    REQUIRE( prop.size() == 1 );
}

class Net : public EntityBase
{
public:
    using EntityBase::EntityBase;
};

class Pin : public EntityBase
{
public:
    using EntityBase::EntityBase;
};

TEST_CASE("Property Grouped: subscript operator", "[entity_system][Property][PropertyGrouped]")
{
    EntitySystem<Net> netlist;
    auto n1 = netlist.add();
    auto n2 = netlist.add();
    auto n3 = netlist.add();

    EntitySystem<Pin> pins;
    auto p1 = pins.add();
    auto p2 = pins.add();
    auto p3 = pins.add();
    auto p4 = pins.add();
    auto p5 = pins.add();
    auto p6 = pins.add();

    PropertyGrouped<Net, Pin, std::string> prop(pins);
    prop[p1] = "p1_n1";
    prop[p2] = "p2_n2";
    prop[p3] = "p3_n1";
    prop[p4] = "p4_n3";
    prop[p5] = "p5_n2";
    prop[p6] = "p6_n1";

    Aggregation<Net, Pin> aggregation(netlist, pins);
    aggregation.addAssociation(n1, p1);
    aggregation.addAssociation(n1, p3);
    aggregation.addAssociation(n1, p6);
    aggregation.addAssociation(n2, p2);
    aggregation.addAssociation(n2, p5);
    aggregation.addAssociation(n3, p4);

    prop.group(netlist, aggregation);

    REQUIRE( prop[p1].compare("p1_n1") == 0 );
    REQUIRE( prop[p2].compare("p2_n2") == 0 );
    REQUIRE( prop[p3].compare("p3_n1") == 0 );
}

//TEST_CASE("Property Grouped: const subscript operator", "[entity_system][Property][PropertyGrouped]")
//{
//    EntitySystem<MyEntity> sys;
//    auto entity = sys.add();
//    PropertyGrouped<MyEntity, MyEntity, int> prop(sys);
//    prop[entity] = 3;

//    auto funct = [entity](const PropertyGrouped<MyEntity, MyEntity, int> & prop){
//                     auto element = prop[entity];
////        auto& element = prop[entity]; -> doesn't compile!!
//                     element = 0;
//                 };
//    funct(prop);
//    REQUIRE( prop[entity] == 3 );
//}

//TEST_CASE("Property Grouped: subscript operator (3 elements)", "[entity_system][Property][PropertyGrouped]")
//{
//    EntitySystem<MyEntity> sys;
//    auto en1 = sys.add();
//    auto en2 = sys.add();
//    auto en3 = sys.add();

//    PropertyGrouped<MyEntity, MyEntity, int> prop(sys);
//    prop[en1] = 0;
//    prop[en2] = 1;
//    prop[en3] = 2;

//    REQUIRE( prop[en1] == 0 );
//    REQUIRE( prop[en2] == 1 );
//    REQUIRE( prop[en3] == 2 );

//    prop[en2] = 4;

//    REQUIRE( prop[en1] == 0 );
//    REQUIRE( prop[en2] == 4 );
//    REQUIRE( prop[en3] == 2 );
//}


//TEST_CASE("Property Grouped: reserve, capacity & shrink", "[entity_system][Property][PropertyGrouped]")
//{
//    EntitySystem<MyEntity> sys;
//    auto en1 = sys.add();
//    auto en2 = sys.add();
//    auto en3 = sys.add();

//    PropertyGrouped<MyEntity, MyEntity, int> prop(sys);
//    prop.reserve(42);
//    REQUIRE( prop.capacity() == 42 );
//    prop.shrinkToFit();
//    REQUIRE( prop.capacity() == 3 );

//}

//TEST_CASE("Property Grouped: property capacity", "[entity_system][Property][PropertyGrouped]")
//{
//    EntitySystem<MyEntity> sys;
//    sys.reserve(42);
//    PropertyGrouped<MyEntity, MyEntity, int> prop(sys);
//    sys.add();
//    sys.add();
//    REQUIRE( prop.capacity() == 42 );
//    sys.shrinkToFit();
//    REQUIRE( prop.capacity() == 2 );

//}

//TEST_CASE("Property Grouped: accessing property after erasing entity", "[entity_system][Property][PropertyGrouped]")
//{
//    EntitySystem<MyEntity> sys;
//    auto en1 = sys.add();
//    auto en2 = sys.add();

//    PropertyGrouped<MyEntity, MyEntity, int> prop(sys);
//    prop[en1] = 1;
//    prop[en2] = 2;

//    REQUIRE(prop[en1] == 1);
//    REQUIRE(prop[en2] == 2);

//    sys.erase(en1);

//    auto en3 = sys.add();

//    prop[en3] = 3;

//    REQUIRE(prop[en2] == 2);
//    REQUIRE(prop[en3] == 3);

//    sys.erase(en2);

//    REQUIRE(prop[en3] == 3);
//}
