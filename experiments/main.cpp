#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

Catch::Session session;
Catch::ConfigData configData;
int main( int argc, char* argv[] )
{
//    Catch::Session session; // There must be exactly one instance

    // writing to session.configData() here sets defaults
    // this is the preferred way to set them

    int returnCode = session.applyCommandLine( argc, argv );
    if( returnCode != 0 )   // Indicates a command line error
        return returnCode;

    // writing to session.configData() or session.Config() here
    // overrides command line args
    // only do this if you know you need to

    configData = session.configData();

    int numFailed = session.run();

    // numFailed is clamped to 255 as some unices only use the lower 8 bits.
    // This clamping has already been applied, so just return it here
    // You can also do any post run clean-up here
    return numFailed;
}


#include <iostream>
#include <memory>

//#include "experiment.h"
//#include "metric.h"
//#include "./chip_boundaries/problem_a.h"

//using namespace ophidian;

//Chip Boundaries
TEST_CASE("Test all circuits runtime DOD Problem 1", "[problem][1]")
{
    std::cout << "problem 1" << std::endl;

    std::cout << "circuit " << configData.circuit << std::endl;
    std::cout << "filename " << configData.outputFilenameExperiments << std::endl;

}
