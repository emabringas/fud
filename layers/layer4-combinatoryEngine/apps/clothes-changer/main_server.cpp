#include <recabs/recabs.h>
#include "clothes_application_server_imp.h"
#include <getopt_pp.h>
#include <memory>
#include <time.h>


int main()
{
    time_t inicio, fin;
    inicio = time(NULL);


    ClothesApplicationServerImp server;
    recabs::RecursionManager* rm = recabs::create_recursion_manager(server);

    rm->start();

    std::list<ResultClothe> _best_combinations;
    _best_combinations = server.get_top_5_clothes();
    std::list<ResultClothe>::iterator it;
    int i(0);
    for (it = _best_combinations.begin(); it != _best_combinations.end(); ++it)
    {
        i++;
        std::cout << i << "- score: " << (*it).get_score() << " " << std::endl;
        std::cout << "clothes: ";
        (*it).print_clothes();
        std::cout << "\n" << std::endl;
    }


    fin = time(NULL);
    std::cout << "\n Done!" << std::endl;
    std::cout << "\n Execution time: " << difftime(fin,inicio)/60 << " minutes" << std::endl;
    return 0;


}
