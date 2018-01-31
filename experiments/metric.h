#ifndef ophidian_METRIC_H
#define ophidian_METRIC_H

#include <chrono>
#include <papi.h>
#include <string>
#include <fstream>
#include <string.h>
#include <assert.h>     /* assert */

namespace ophidian
{
namespace experiments
{

class Metric
{
public:
        virtual void start() = 0;
        virtual void end() = 0;
        virtual void print_result() = 0;
        virtual void print_file_result(std::string filename) = 0;
};

class Runtime : public Metric
{
        std::chrono::high_resolution_clock::time_point time_start, time_end;
public:
        void start(){
                time_start = std::chrono::high_resolution_clock::now();
        }

        void end(){
                time_end = std::chrono::high_resolution_clock::now();
        }

        void print_result(){
                auto total_time = time_end - time_start;
//        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(total_time).count()<<" ms"<<std::endl;
                std::cout << std::chrono::duration_cast<std::chrono::microseconds>(total_time).count()<<" us"<<std::endl;
                std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(total_time).count()<<" ns"<<std::endl;
        }

        void print_file_result(std::string filename){
                if(filename == "")
                {
                        std::cout << "Output file name error!!" << std::endl;
                        return;
                }
                std::cout << "Write runtime result on file : " << filename << std::endl;
                auto total_time = time_end - time_start;

                std::fstream ofs;
                ofs.open(filename.c_str(), std::fstream::in | std::fstream::out);
                // If file does not exist, Create new file
                if (!ofs )
                {
                        //no file in directory
                        //creating metric label
                        ofs.open(filename.c_str(), std::ofstream::out | std::ofstream::app);
                        ofs << "runtime unidade\n";
                }
                else {
                        ofs.seekg(0, std::ios_base::end);
                }


                if (ofs.is_open())
                {
//            ofs << std::chrono::duration_cast<std::chrono::milliseconds>(total_time).count() << " ms\n";
                        ofs << std::chrono::duration_cast<std::chrono::microseconds>(total_time).count() << " us\n";
                }
                else {
                        std::cout << "Open file error!!" << std::endl;
                }
                ofs.close();
        }
};

class Miss : public Metric
{
        std::string * PAPI_events_str;
        int * PAPI_events;
        unsigned int events_size;
        std::vector<long long> events;
public:
        Miss(int events[], unsigned int events_size, std::string events_str[]) : events_size(events_size){
                PAPI_events = events;
                PAPI_events_str = events_str;
                assert(PAPI_library_init(PAPI_VER_CURRENT) == PAPI_VER_CURRENT);

        }

        void start(){
                PAPI_reset(*PAPI_events);
                assert(PAPI_start_counters( PAPI_events, events_size ) == PAPI_OK);
        }

        void end(){
                long long counters[events_size];
                assert(PAPI_stop_counters(counters, events_size) == PAPI_OK);
                events = std::vector<long long>(counters, counters + sizeof counters / sizeof counters[0]);
        }

        void print_result(){
                int index = 0;
                for(auto e : events)
                {
                        std::cout << PAPI_events_str[index] << " "<<e<<"\n";
                        index++;
                }
        }

        void print_file_result(std::string filename){
                if(filename == "")
                {
                        std::cout << "Output file name error!!" << std::endl;
                        return;
                }
                std::cout << "Write cache miss result on file : " << filename << std::endl;
                std::fstream ofs;
                ofs.open(filename.c_str(), std::fstream::in | std::fstream::out);
                // If file does not exist, Create new file
                if (!ofs )
                {
                        //no file in directory
                        //creating metric label
                        ofs.open(filename.c_str(), std::ofstream::out | std::ofstream::app);
                        //header for CSV
                        ofs << PAPI_events_str[0];
                        for (int index = 1; index < events_size; ++index)
                        {
                                ofs << " " << PAPI_events_str[index];
                        }
                        ofs << "\n";
                }
                else {
                        ofs.seekg(0, std::ios_base::end);
                }

                if (ofs.is_open())
                {
                        std::vector<long long>::size_type size_events = events.size();
                        for(unsigned i=0; i<size_events-1; i++)
                        {
                                ofs << events[i] <<" ";
                        }
                        ofs << events[size_events-1] <<"\n";
                }
                else {
                        std::cout << "Open file error!!" << std::endl;
                }
                ofs.close();
        }
};

} // namespace experiments
} // namespace ophidian

#endif //ophidian_METRIC_H
