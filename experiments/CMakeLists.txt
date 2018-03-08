################################################################################
# This is the CMakeLists file for the Ophidian library Test binary. 
#
# Its main goals are:
#   - Fetch test files.
#   - Configure Catch test library.
#   - Add test target.
#   - Link test target.
#   - Prepare test input environment.
################################################################################

# Fetch test files recursevely
file(GLOB_RECURSE ophidian_run_experiments_SRC  
    "*.cpp"
    "*.h"
)

find_package(PAPI)

#SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
#SET(BUILD_SHARED_LIBRARIES OFF)
#SET(CMAKE_EXE_LINKER_FLAGS "-static")
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

# Add Catch lib interface
# add_library(Catch INTERFACE)
# target_include_directories(Catch INTERFACE .)

# Add experiments target
add_executable(ophidian_experiments ${ophidian_run_experiments_SRC})

# Link target dependencies
target_link_libraries(ophidian_experiments PUBLIC 
    Catch
    PAPI
    ophidian_circuit_static
    ophidian_design_static
    ophidian_entity_system_static
    ophidian_floorplan_static
    ophidian_geometry_static
    ophidian_interconnection_static
    ophidian_parser_static
    ophidian_placement_static
    ophidian_standard_cell_static
)

set_target_properties(ophidian_experiments PROPERTIES
    LINK_FLAGS "-static -static-libgcc -static-libstdc++ -pthread"
)

# Add namespace directories for lib generation
#add_subdirectory(chip_boundaries)

# Set option build shared libs
#option(BUILD_SHARED_LIBS "on/off -> (build every non statc lib shared)/(build everything static)" OFF)


################################################################################
# Prepare experiments input environment.
################################################################################

message("Creating symlink for test files")
execute_process(
    COMMAND ln -f -s ${PROJECT_SOURCE_DIR}/test/input_files ${PROJECT_BINARY_DIR}/experiments/.
    COMMAND ln -f -s ${PROJECT_SOURCE_DIR}/experiments/run.sh ${PROJECT_BINARY_DIR}/experiments/.
    RESULT_VARIABLE result
)
#execute_process(
#    COMMAND tar -zxvf superblue18.tar.gz
#    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/input_files
#    RESULT_VARIABLE result
#)

#message("Creating symlink FLUTE LUTs")
#execute_process(
#    COMMAND ln -f -s ${PROJECT_SOURCE_DIR}/3rdparty/Flute/PORT9.dat ${PROJECT_BINARY_DIR}/test/.
#    RESULT_VARIABLE result
#)
#execute_process(
#    COMMAND ln -f -s ${PROJECT_SOURCE_DIR}/3rdparty/Flute/POWV9.dat ${PROJECT_BINARY_DIR}/test/.
#    RESULT_VARIABLE result
#)

################################################################################
# Add experiments to ctest
################################################################################

#enable_testing()
#add_test(NAME unit_test COMMAND ophidian_experiments "~[Profiling] ~[superblue18obs]")

