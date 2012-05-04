/**
 *  @file:      main_client.h
 *  @details    Main implementation in the client-side.
 *              System: CombEng\n
 *              Language: C++\n
 *
 *  @author     Favio Bettiol
 *  @email      favio.bettiol AT gmail.com
 *
 *  @author     Diego Diaz
 *  @email      diazdiego86 AT gmail.com
 *
 *  @date       August 2010
 *  @version    0.1
 *
 * This file is part of CombEng
 *
 * CombEng : Combinatory Engine, an FuD's abstraction layer for problems that
 * require to combine elements. Also, this layer provides ranking and prune
 * features for these combinations.
 * <http://fud.googlecode.com/>
 *
 * Copyright (C) 2010 - Favio Bettiol and Diego Diaz
 *
 * CombEng is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CombEng is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with CombEng .  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <recabs/recabs.h>
#include "rnaffe_application_client.h"
#include <getopt_pp.h>
#include <memory>
#include <time.h>

/*************** Global variables for client ***********/
AntiviralSet all_antivirals;    // Contains all available antivirals.
/********** End Global variables for client ************/

using namespace GetOpt;

int main(int argc, char** argv)
{
    size_t      port(31337);
    std::string address("127.0.0.1");

    GetOpt_pp ops(argc, argv);
    ops >> Option('a', "address", address) >> Option('p', "port", port) ;

    DataBase DB(argv[1]);
    DB.get_antivirals(all_antivirals);

    IFold* global_fold = RNABackendsFactory::Instance()->_direct_folders.new_class("rnafold");
    RnaFFEApplicationClient RNA_client (global_fold);

    set_default_matrix(matrix);

    recabs::L4ClientApp aux;
    recabs::DistributeAlwaysAllPolicy dp;
    recabs::DistributableRecursiveProcessor* rp = recabs::create_recursion_processor(aux, RNA_client, dp);

    rp->run(address, port);

    return 0;
}
