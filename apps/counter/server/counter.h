#ifndef COUNTER_H
#define COUNTER_H

#include <string>

#include "fud.h"

#include "number_database.h"

using namespace fud;
class Counter : public DistributableJobImplementation
{
public:
    Counter(NumberDatabase& num_db, size_t my_id);

    virtual ~Counter() {};
private:
    virtual void        handle_results(JobUnitID id, InputMessage& input);

    virtual DistributableJobStatus get_status()    const;
    virtual const char*            get_name()      const;

    virtual JobUnit*    produce_next_job_unit(JobUnitSize size);

    static size_t   _job_count;

    size_t          _id;
    NumberDatabase& _num_db;

    size_t          _last;
};

#endif
