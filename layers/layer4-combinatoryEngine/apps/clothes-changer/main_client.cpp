#include <recabs/recabs.h>
#include "clothes_application_client_imp.h"
#include <getopt_pp.h>
#include <memory>
#include <time.h>

using namespace GetOpt;

int main(int argc, char** argv)
{
    size_t      port(31337);
    std::string address("127.0.0.1");

    GetOpt_pp ops(argc, argv);
    ops >> Option('a', "address", address) >> Option('p', "port", port) ;

    ClothesApplicationClientImp clothes_client;

    recabs::L4ClientApp aux;
    recabs::FixedLeafsDistributablePolicy dp(1000000);
    recabs::DistributableRecursiveProcessor* rp = recabs::create_recursion_processor(aux, clothes_client, dp);
    rp->run(address, port);

    return 0;
}
