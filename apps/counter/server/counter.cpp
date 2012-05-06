#include <sstream>

#include "counter.h"

size_t Counter::_job_count = 0;

Counter::Counter(NumberDatabase& num_db, size_t my_id) :
    DistributableJobImplementation(),
    _id(my_id),
    _num_db(num_db),
    _last(my_id + 1)
{
    ++_job_count;
}

const char* Counter::get_name() const
{
    std::ostringstream oss;
    oss << "Counter " << _id;
    return oss.str().c_str();
}

void Counter::handle_results(JobUnitID id, InputMessage& input)
{
    fud_uint count;
    input >> count;
    _num_db.update(count);
}

DistributableJobStatus Counter::get_status() const
{
    if (_num_db.finished_counting())
        return FinishedGenerating;
    else if ((_num_db.current_number() % _job_count == _id) && (_last != _num_db.current_number()))
        return ReadyToProduce;
    else
        return WaitingMoreData;
}

JobUnit* Counter::produce_next_job_unit(JobUnitSize size)
{
    if (get_status() == ReadyToProduce)
    {
        StreamingJobUnit* res = new StreamingJobUnit();

        (*res) << _num_db.current_number();
        res->set_size(1);

        _last = _num_db.current_number();

        return res;
    }
    else
        return NULL;
}
