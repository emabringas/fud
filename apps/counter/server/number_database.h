#include <cstdlib>

#include "fud/fud_client.h"

#ifndef NUMBER_DATABASE_H
#define NUMBER_DATABASE_H

class NumberDatabase
{
public:
    NumberDatabase(fud::fud_uint up_to);

    fud::fud_uint current_number() const;

    void update(fud::fud_uint new_number);

    bool finished_counting() const;
private:
    fud::fud_uint _goal;
    fud::fud_uint _n;
};

#endif