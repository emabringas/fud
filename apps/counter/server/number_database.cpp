#include "number_database.h"

using namespace fud;

NumberDatabase::NumberDatabase(fud_uint up_to) :
    _goal(up_to),
    _n(0)
{
}

fud_uint NumberDatabase::current_number() const
{
    return _n;
}

void NumberDatabase::update(fud_uint new_number)
{
    _n = new_number;
}

bool NumberDatabase::finished_counting() const
{
    return _n >= _goal;
}
