#ifndef COUNTER_H
#define COUNTER_H

#include <list>
#include <fstream>
#include <string>

#include <fud/fud.h>

using namespace fud;

class Counter : public DistributableJobImplementation
{
    public:
        Counter(const char* file_name);

        virtual void        output_results()      const;

        virtual ~Counter(){};
    private:
        virtual void        handle_results (JobUnitID id,InputMessage& input);

        virtual DistributableJobStatus get_status()    const;
        virtual const char*            get_name()      const;

        virtual JobUnit*    produce_next_job_unit(JobUnitSize size);

        class CounterJobUnit : public JobUnit
        {
            public:
                CounterJobUnit(char* message,JobUnitSize size);

            private:
                virtual const char*  method_name_required() const { return "count";}
                virtual ~CounterJobUnit(){};

                virtual const std::string& get_message()    const;

                std::string _message;
        };

        size_t       _total_count;
        std::fstream _file;
};

#endif
