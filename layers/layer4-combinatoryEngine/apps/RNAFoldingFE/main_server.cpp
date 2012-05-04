/**
 *  @file:      main_server.h
 *  @details    Main implementation in the server-side.
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
#include <rnafolding/rnafolding.h>
#include "rna_exception.h"
#include "rnaffe_application_server.h"
#include <getopt_pp.h>
#include <memory>
#include <time.h>
#include <signal.h>

#define TOTAL_OF_PARAMS 3

/*************** Global variables for server ***********/
AntiviralSet all_antivirals;    // Contains all available antivirals.
static char* filename;
/************ End Global variables for server **********/


/**
 * this method defines the actions to take when Ctrl+C is pressed.
 */
static void end(int)
{
    printf("\n\n Closing the file containing the results \n");
    printf("\n Goodbye world :) \n");
}

static void install_sigaction(void)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = end;
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
}

void help_file(const char* help_file)
{
    std::string help;
    std::ifstream infile(help_file);

    if (infile)
    {
        while (getline(infile, help))
        {
            std::cout << help << std::endl;
        }
    }
    else
        throw "File not found";
    infile.close();
}

int main(int argc, char** argv)
{
    time_t inicio, fin;
    inicio = time(NULL);

    if (to_string(argv[1]) == "--help")   // we have to copy the rna_help file in the executable's path
    {
        help_file("rnaffe.help");
    }
    else
    {
        try
        {
            if (argc < TOTAL_OF_PARAMS) throw WrongUse("Incorrect Parameters. Try rnaffe --help");

            install_sigaction();

            DataBase DB(argv[2]);
            DB.get_antivirals(all_antivirals);

            filename = argv[3];
            IFold* global_fold = RNABackendsFactory::Instance()->_direct_folders.new_class("rnafold");

            RnaFFEApplicationServer server(argv[1], argv[3], global_fold);

            recabs::RecursionManager* rm = recabs::create_recursion_manager(server);

            rm->start();

            fin = time(NULL);
            std::cout << "\n Done!" << std::endl;
            std::cout << "\n Execution time: " << difftime(fin,inicio)/60 << " minutes" << std::endl;
            return 0;
        }
        catch (const WrongUse& exc)
        {
            std::cerr << exc.what() << std::endl;
        }
    }
}
