//#include <catch.hpp>
//#include <iostream>
//#include "experiments/experiment.h"
//#include "experiments/metric.h"
//#include "kmeans_data_oriented_design.h"
//#include "kmeans_object_oriented_design.h"

//#include "FlipFlop.h"

//// PAPI_L1_DCM /*Level 1 data cache misses */
//// PAPI_L1_ICM /*Level 1 instruction cache misses */
//// PAPI_L2_DCM /*Level 2 data cache misses */
//// PAPI_L2_ICM /*Level 2 instruction cache misses */
//// PAPI_L3_DCM /*Level 3 data cache misses */
//// PAPI_L3_ICM /*Level 3 instruction cache misses */
//// PAPI_L1_TCM /*Level 1 total cache misses */
//// PAPI_L2_TCM /*Level 2 total cache misses */
//// PAPI_L3_TCM /*Level 3 total cache misses */

////Register Clustering (kmeans)

//#include "register_clustering_size.h"

//using namespace ophidian;
//using namespace ophidian::experiments;
//using namespace ophidian::experiments::register_clustering;

//#define ITERATIONS 30

//TEST_CASE("Test size of FlipFlop", "[FF]")
//{
//    std::cout << "size of FF: "<< sizeof(ophidian::experiments::register_clustering::FlipFlop) <<std::endl;
//    std::cout << "size of FFExt125: "<< sizeof(ophidian::experiments::register_clustering::FlipFlopExt125) <<std::endl;
//    std::cout << "size of FFExt150: "<< sizeof(ophidian::experiments::register_clustering::FlipFlopExt150) <<std::endl;
//    std::cout << "size of FFExt175: "<< sizeof(ophidian::experiments::register_clustering::FlipFlopExt175) <<std::endl;
//    std::cout << "size of FFExt200: "<< sizeof(ophidian::experiments::register_clustering::FlipFlopExt200) <<std::endl;
//    std::cout << "size of FFExt400: "<< sizeof(ophidian::experiments::register_clustering::FlipFlopExt400) <<std::endl;
//    std::cout << "size of FFExt600: "<< sizeof(ophidian::experiments::register_clustering::FlipFlopExt600) <<std::endl;
//}

//////**********************************************************************************************************************
//////                                      Object-Oriented Design : extra 125%
//////**********************************************************************************************************************
//// ***********************************************************
////  Object-Oriented Design : extra 125%
//// ***********************************************************
////  -- sequential
////      -- runtime
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD runtime e125", "[problem3][OOD][sequential][runtime][e125]")
//{
//    std::cout << "Test Register Clustering (kmeans) sequential OOD runtime e125" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODsequentialRuntime<FlipFlopExt125>(design, ff, ITERATIONS);
//}
//// ***********************************************************
////  Object-Oriented Design : extra 125%
//// ***********************************************************
////  -- sequential
////      -- Miss
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD mis e125", "[problem3][OOD][sequential][miss][e125]")
//{
//    std::cout << "Test Register Clustering (kmeans) size sequential OOD mis e125" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODsequentialMiss<FlipFlopExt125>(design, ff, ITERATIONS);
//}
//// ***********************************************************
////  Object-Oriented Design : extra 125%
//// ***********************************************************
////  -- parallel
////      -- runtime
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD runtime e125", "[problem3][OOD][parallel][runtime][e125]")
//{
//    std::cout << "Test Register Clustering (kmeans) parallel OOD runtime e125" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODparallelRuntime<FlipFlopExt125>(design, ff, ITERATIONS);
//}
//// ***********************************************************
////  Object-Oriented Design : extra 125%
//// ***********************************************************
////  -- parallel
////      -- Miss
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD miss e125", "[problem3][OOD][parallel][miss][e125]")
//{
//    std::cout << "Test Register Clustering (kmeans) size parallel OOD miss e125" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODparallelMiss<FlipFlopExt125>(design, ff, ITERATIONS);
//}
//////**********************************************************************************************************************


//////**********************************************************************************************************************
//////                                      Object-Oriented Design : extra 150%
//////**********************************************************************************************************************
//// ***********************************************************
////  Object-Oriented Design : extra 150%
//// ***********************************************************
////  -- sequential
////      -- runtime
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD runtime e150", "[problem3][OOD][sequential][runtime][e150]")
//{
//    std::cout << "Test Register Clustering (kmeans) sequential OOD runtime e150" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODsequentialRuntime<FlipFlopExt150>(design, ff, ITERATIONS);
//}
//// ***********************************************************
////  Object-Oriented Design : extra 150%
//// ***********************************************************
////  -- sequential
////      -- Miss
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD mis e150", "[problem3][OOD][sequential][miss][e150]")
//{
//    std::cout << "Test Register Clustering (kmeans) size sequential OOD mis e150" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODsequentialMiss<FlipFlopExt150>(design, ff, ITERATIONS);
//}
//// ***********************************************************
////  Object-Oriented Design : extra 150%
//// ***********************************************************
////  -- parallel
////      -- runtime
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD runtime e150", "[problem3][OOD][parallel][runtime][e150]")
//{
//    std::cout << "Test Register Clustering (kmeans) parallel OOD runtime e150" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODparallelRuntime<FlipFlopExt150>(design, ff, ITERATIONS);
//}
//// ***********************************************************
////  Object-Oriented Design : extra 150%
//// ***********************************************************
////  -- parallel
////      -- Miss
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD miss e150", "[problem3][OOD][parallel][miss][e150]")
//{
//    std::cout << "Test Register Clustering (kmeans) size parallel OOD miss e150" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODparallelMiss<FlipFlopExt150>(design, ff, ITERATIONS);
//}
//////**********************************************************************************************************************


//////**********************************************************************************************************************
//////                                      Object-Oriented Design : extra 175%
//////**********************************************************************************************************************
//// ***********************************************************
////  Object-Oriented Design : extra 175%
//// ***********************************************************
////  -- sequential
////      -- runtime
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD runtime e175", "[problem3][OOD][sequential][runtime][e175]")
//{
//    std::cout << "Test Register Clustering (kmeans) sequential OOD runtime e175" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODsequentialRuntime<FlipFlopExt175>(design, ff, ITERATIONS);
//}
//// ***********************************************************
////  Object-Oriented Design : extra 175%
//// ***********************************************************
////  -- sequential
////      -- Miss
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD mis e175", "[problem3][OOD][sequential][miss][e175]")
//{
//    std::cout << "Test Register Clustering (kmeans) size sequential OOD mis e175" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODsequentialMiss<FlipFlopExt175>(design, ff, ITERATIONS);
//}
//// ***********************************************************
////  Object-Oriented Design : extra 175%
//// ***********************************************************
////  -- parallel
////      -- runtime
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD runtime e175", "[problem3][OOD][parallel][runtime][e175]")
//{
//    std::cout << "Test Register Clustering (kmeans) parallel OOD runtime e175" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODparallelRuntime<FlipFlopExt175>(design, ff, ITERATIONS);
//}
//// ***********************************************************
////  Object-Oriented Design : extra 175%
//// ***********************************************************
////  -- parallel
////      -- Miss
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD miss e175", "[problem3][OOD][parallel][miss][e175]")
//{
//    std::cout << "Test Register Clustering (kmeans) size parallel OOD miss e175" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODparallelMiss<FlipFlopExt175>(design, ff, ITERATIONS);
//}
//////**********************************************************************************************************************



//////**********************************************************************************************************************
//////                                      Object-Oriented Design : extra 200%
//////**********************************************************************************************************************
//// ***********************************************************
////  Object-Oriented Design : extra 200%
//// ***********************************************************
////  -- sequential
////      -- runtime
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD runtime e200", "[problem3][OOD][sequential][runtime][e200]")
//{
//    std::cout << "Test Register Clustering (kmeans) sequential OOD runtime e200" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODsequentialRuntime<FlipFlopExt200>(design, ff, ITERATIONS);
//}
//// ***********************************************************
////  Object-Oriented Design : extra 200%
//// ***********************************************************
////  -- sequential
////      -- Miss
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD mis e200", "[problem3][OOD][sequential][miss][e200]")
//{
//    std::cout << "Test Register Clustering (kmeans) size sequential OOD mis e200" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODsequentialMiss<FlipFlopExt200>(design, ff, ITERATIONS);
//}
//// ***********************************************************
////  Object-Oriented Design : extra 200%
//// ***********************************************************
////  -- parallel
////      -- runtime
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD runtime e200", "[problem3][OOD][parallel][runtime][e200]")
//{
//    std::cout << "Test Register Clustering (kmeans) parallel OOD runtime e200" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODparallelRuntime<FlipFlopExt200>(design, ff, ITERATIONS);
//}
//// ***********************************************************
////  Object-Oriented Design : extra 200%
//// ***********************************************************
////  -- parallel
////      -- Miss
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD miss e200", "[problem3][OOD][parallel][miss][e200]")
//{
//    std::cout << "Test Register Clustering (kmeans) size parallel OOD miss e200" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODparallelMiss<FlipFlopExt200>(design, ff, ITERATIONS);
//}
//////**********************************************************************************************************************


//////**********************************************************************************************************************
//////                                      Object-Oriented Design : extra 400%
//////**********************************************************************************************************************
//// ***********************************************************
////  Object-Oriented Design : extra 400%
//// ***********************************************************
////  -- sequential
////      -- runtime
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD runtime e400", "[problem3][OOD][sequential][runtime][e400]")
//{
//    std::cout << "Test Register Clustering (kmeans) sequential OOD runtime e400" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODsequentialRuntime<FlipFlopExt400>(design, ff, ITERATIONS);
//}
//// ***********************************************************
////  Object-Oriented Design : extra 400%
//// ***********************************************************
////  -- sequential
////      -- Miss
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD mis e400", "[problem3][OOD][sequential][miss][e400]")
//{
//    std::cout << "Test Register Clustering (kmeans) size sequential OOD mis e400" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODsequentialMiss<FlipFlopExt400>(design, ff, ITERATIONS);
//}
//// ***********************************************************
////  Object-Oriented Design : extra 400%
//// ***********************************************************
////  -- parallel
////      -- runtime
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD runtime e400", "[problem3][OOD][parallel][runtime][e400]")
//{
//    std::cout << "Test Register Clustering (kmeans) parallel OOD runtime e400" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODparallelRuntime<FlipFlopExt400>(design, ff, ITERATIONS);
//}
//// ***********************************************************
////  Object-Oriented Design : extra 400%
//// ***********************************************************
////  -- parallel
////      -- Miss
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD miss e400", "[problem3][OOD][parallel][miss][e400]")
//{
//    std::cout << "Test Register Clustering (kmeans) size parallel OOD miss e400" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODparallelMiss<FlipFlopExt400>(design, ff, ITERATIONS);
//}
//////**********************************************************************************************************************


//////**********************************************************************************************************************
//////                                      Object-Oriented Design : extra 600%
//////**********************************************************************************************************************
//// ***********************************************************
////  Object-Oriented Design : extra 600%
//// ***********************************************************
////  -- sequential
////      -- runtime
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD runtime e600", "[problem3][OOD][sequential][runtime][e600]")
//{
//    std::cout << "Test Register Clustering (kmeans) sequential OOD runtime e600" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODsequentialRuntime<FlipFlopExt600>(design, ff, ITERATIONS);
//}
//// ***********************************************************
////  Object-Oriented Design : extra 600%
//// ***********************************************************
////  -- sequential
////      -- Miss
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size sequential OOD mis e600", "[problem3][OOD][sequential][miss][e600]")
//{
//    std::cout << "Test Register Clustering (kmeans) size sequential OOD mis e600" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODsequentialMiss<FlipFlopExt600>(design, ff, ITERATIONS);
//}
//// ***********************************************************
////  Object-Oriented Design : extra 600%
//// ***********************************************************
////  -- parallel
////      -- runtime
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD runtime e600", "[problem3][OOD][parallel][runtime][e600]")
//{
//    std::cout << "Test Register Clustering (kmeans) parallel OOD runtime e600" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODparallelRuntime<FlipFlopExt600>(design, ff, ITERATIONS);
//}
//// ***********************************************************
////  Object-Oriented Design : extra 600%
//// ***********************************************************
////  -- parallel
////      -- Miss
//// ***********************************************************
//TEST_CASE_METHOD(ExperimentFixtureKmeansICCAD2015, "Test Register Clustering (kmeans) size parallel OOD miss e600", "[problem3][OOD][parallel][miss][e600]")
//{
//    std::cout << "Test Register Clustering (kmeans) size parallel OOD miss e600" << std::endl;
//    auto * design = this->design_;
//    auto & ff = this->flip_flop_positions;
//    OODparallelMiss<FlipFlopExt600>(design, ff, ITERATIONS);
//}
//////**********************************************************************************************************************
