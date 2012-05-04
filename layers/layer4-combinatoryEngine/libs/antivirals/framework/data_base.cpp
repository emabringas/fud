/**
 * \file  data_base.cpp
 * \brief implementation of DataBase class.
 *
 * ASO: Antiviral Sequence Optimizer
 * <http://aso.googlecode.com/>
 * Copyright (C) 2010 Velez Ezequiel, Peralta Andres, FuDePAN
 *
 * This file is part of the ASO project.
 *
 * Contents:       CPP file for ASO providing class DataBase.
 *
 * System:         ASO
 * Language:       C++
 *
 * Author:         Velez Ezequiel, Peralta Andres
 * E-Mail:
 *
 * ASO is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ASO is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ASO.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <fxp.h>
#include "data_base.h"

using namespace std;

void DataBase::load_file(const char* file_name)
{
    FXParserLOVMethod<ResisBasedAntiviral, ResisBasedAntiviral&, Parameters2<size_t, const string&> > resistanceParser("resistance", &ResisBasedAntiviral::add_resistance);
    resistanceParser.parameters.set_param0("pos");
    resistanceParser.parameters.set_param1("aminos");

    FXParserLOVMethod<ResisBasedAntiviral, ResisBasedAntiviral&, Parameters2<const string&, const string&> > addendumParser("addendum", &ResisBasedAntiviral::add_attribute);
    addendumParser.parameters.set_param0("attrib");
    addendumParser.parameters.set_param1("value");

    FXParserNonDef<ResisBasedAntiviral, Constructor4<ResisBasedAntiviral, string, size_t, AvType, AvClass> > antiviralParser("antiviral");
    antiviralParser.constructor.set_param0("id");//nombre
    antiviralParser.constructor.set_param1("num");//id
    antiviralParser.constructor.set_param2("type");//tipo
    antiviralParser.constructor.set_param3("class");//clase

    add_lov_child(antiviralParser, resistanceParser);
    add_lov_child(antiviralParser, addendumParser);

    FXPRootParserNonDef<Antivirals> antiviralsParser("antivirals", antiviralParser);
    cout << "-- Data base loaded." << endl;

    parse_xml(file_name, antivirals, antiviralsParser, Warn, Warn);

}

void DataBase::get_antivirals(AntiviralSet& antiviral_set)
{
    for (Antivirals::iterator it = antivirals.begin(); it != antivirals.end(); ++it)
    {
        antiviral_set.add_antiviral(*it);
    }
}

void DataBase::print_database()
{
    Antivirals::iterator it = validated_antivirals.begin();
    while (it != validated_antivirals.end())
    {
        it->print_antiviral();
        ++it;
    }
}

void DataBase::copy_antivirals()
{
    CAutonomousIterator<Antivirals> it(antivirals);
    while (!it.end())
    {
        insert_into(validated_antivirals, *it);
        ++it;
    }
}

void DataBase::ignore_antivirals(const Names& names)
{
    std::string name;

    CAutonomousIterator<Names> it(names);
    while (!it.end())
    {
        Antivirals::iterator it2 = validated_antivirals.begin();

        while (it2 != validated_antivirals.end())
        {
            it2->get_attrib("name", name);
            if (name == *it)
            {
                it2 = validated_antivirals.erase(it2);
            }
            ++it2;
        }
        ++it;
    }
}




