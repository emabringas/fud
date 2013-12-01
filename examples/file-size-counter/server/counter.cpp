#include <fstream>
#include <iostream>
#include <mili/mili.h>
#include "counter.h"

using namespace fud;
using namespace mili;

Counter::Counter(const char* file_name) :
    DistributableJobImplementation(),
    _total_count(0),
    _file()
{
    _file.open(file_name);
}

Counter::CounterJobUnit::CounterJobUnit(char* message,JobUnitSize size) :
    JobUnit(),
    _message()
{
    std::string msg(message,size);
    bostream<> bos;
    bos << msg;
    _message = bos.str();
    set_size(size);
}

const std::string& Counter::CounterJobUnit::get_message() const
{
    return _message;
}

const char* Counter::get_name() const
{
    return "Counter";
}

void Counter::handle_results (JobUnitID /*id*/, InputMessage& input)
{
    size_t count;
    input >> count;
    _total_count += count;
}

void Counter::output_results() const
{
    std::cout << "Final count: " << _total_count << std::endl;
}

DistributableJobStatus Counter::get_status() const
{
    if (_file.eof())
        return FinishedGenerating;
    else
        return ReadyToProduce; // never returns WaitingMoreData, this test is too simple.
}

JobUnit* Counter::produce_next_job_unit(JobUnitSize size)
{
    if ( get_status() != FinishedGenerating)
    {
        char* message = new char[size];
        _file.read (message, size);
        JobUnit* res = new CounterJobUnit(message,_file.gcount());

        return res;

        delete[] message;
    }
    else
        return NULL;
}
