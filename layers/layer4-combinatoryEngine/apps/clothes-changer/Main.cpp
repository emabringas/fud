/*
 * File:   Main.cpp
 * Author: bettiol
 *
 * Created on 23 de noviembre de 2010, 13:42
 */
//forward declaration
//class ClothesApplicationClientImp;
//class ClothesApplicationServerImp;
#include "clothes_application_client_imp.h"
#include "clothes_application_server_imp.h"

#include <cstdlib>
//#include <recabs/recabs.h>
#include <recabs/serializable_recursive_functor.h>
#include <recabs/recursion_manager.h>
#include <recabs/deserializer_functor.h>
#include <recabs/prototype_rp.h>

#include <recabs/l4_server_app.h>
#include <recabs/prototype_rm.h>

using namespace std;

/*
 *
 */
int main(int argc, char** argv)
{



    //ClothesApplicationClientImp* a = new ClothesApplicationClientImp();
    ClothesApplicationClientImp a;
    //ClothesApplicationServerImp b;
    ClothesApplicationServerImp* server = new ClothesApplicationServerImp();
    const recabs::DeserializerFunctor& client = a;
    //recabs::L4ServerApp& server = b;


    recabs::RecursionManager* _manager = new recabs::PrototypeRM(*server, client);

    _manager->start();
    std::list<ResultClothe> _best_combinations;
    _best_combinations = server->get_top_5_clothes();
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
    std::cout << "TERMINE" << std::endl;
    return 0;
}