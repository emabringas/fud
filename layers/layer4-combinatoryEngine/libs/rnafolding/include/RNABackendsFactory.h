#ifndef _RNABACKENDSFACTORY_H
#define _RNABACKENDSFACTORY_H

#include <string>
#include <mili/mili.h>
#include "IFold.h"
using std::string;

class RNABackendsFactory
{
public:
    
    static RNABackendsFactory* Instance()
    {
        if (!_pInstance)    // NULL
            _pInstance = new RNABackendsFactory;
        return _pInstance;
    }

    template <class DerivedClass>
    static void Register(string name) { Instance()->_direct_folders.register_factory<DerivedClass>(name); }
    
    mili::Factory<string, IFold> _direct_folders;

private:
    RNABackendsFactory(){};
    RNABackendsFactory(const RNABackendsFactory&);
    static RNABackendsFactory* _pInstance;
};
#endif
