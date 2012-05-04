/*
 * File:   tables.h
 * Author: diego
 *
 * Created on October 28, 2010, 8:52 PM
 */

#ifndef TABLES_H
#define TABLES_H

#include <vector>

class tables
{
public:
    /*
     * constructor method. Initialization
     */
    tables();

    float remera_pantalon(std::string remera, std::string pantalon);

    float pantalon_zapato(std::string pantalon, std::string zapato);

    float zapato_media(std::string zapato, std::string media);

private:
// tablas para las funciones de scoring
    std::vector < std::vector <int> > _tabla_remera_pantalon;
    std::vector < std::vector <int> > _tabla_pantalon_zapato;
    std::vector < std::vector <int> > _tabla_zapato_media;
};
#endif  /* TABLES_H */