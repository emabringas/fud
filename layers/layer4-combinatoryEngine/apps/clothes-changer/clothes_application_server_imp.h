/**
 *  @file:      clothes_application_server_imp.h
 *  @details    Header file for ClothesApplicationServerImp.\n
 *              System: CombEng \n
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

//=================================
// include guard
#ifndef _CLOTHES_APPLICATION_SERVER_IMP_H
#define _CLOTHES_APPLICATION_SERVER_IMP_H

//=================================
// included dependencies
#include "../../server/l5_application_server.h"
#include "clothes_node.h"
#include <set>
#include <list>


class ResultClothe
{
private:
    float _score;
    std::list<Clothe> _clothes;

public:
    ResultClothe()
        : _score(0)
    {}

    ResultClothe(float score, std::list<Clothe> clothes)
        : _score(score), _clothes(clothes)
    {}

    inline float get_score()
    {
        return _score;
    }

    inline void set_score(const float& value)
    {
        _score = value;
    }

    inline std::list<Clothe> get_clothes()
    {
        return _clothes;
    }

    inline void set_clothes(const std::list<Clothe>& clothes)
    {
        _clothes = clothes;
    }

    void print_clothes()
    {
        std::list<Clothe>::iterator it;
        for (it = _clothes.begin(); it != _clothes.end(); ++it)
        {
            (*it).print_obj();
        }
    }
};

/**
 * Class implementing the interface L5ApplicationServer.
 * Responsabilities:
 *  - Obtain the entire set of elements.
 *  - Obtain the root node. That is, the node containing any clothe.
 *  - Start running this node.
 */
using namespace comb_eng;
class ClothesApplicationServerImp : public comb_eng::L5ApplicationServer<Clothe>
{

private:
    // nodo inicial de la aplicacion
    ClothesNode* _root_node;

    // lista de las mejores 5 combinaciones
    std::list<ResultClothe> _top_5_dressed;

    // hay que ver la utilidad de esto
    void manage_top_dressed(const float& score, const std::list<Clothe>& get_dressed);


public:
    /**
     * Constructor method.
     */
    ClothesApplicationServerImp();

    /**
     * Destroyer method.
     */
    ~ClothesApplicationServerImp();

    /**
     * For implementation. From L4ServerApp (recabs)
     */
    virtual void get_initial_packet(recabs::Packet& pkt) const;

    virtual void receive_result(const recabs::Packet& pkt);

    /**
     * For implementation. From L5ApplicationServer (comb_eng)
     */
    comb_eng::L4Node<Clothe>* get_initial_node();

    /**
     * For implementation. From L5ApplicationServer (comb_eng)
     */
    std::list<Clothe> get_initial_set();

    inline std::list<ResultClothe> get_top_5_clothes() const
    {
        return _top_5_dressed;
    }
};
#endif  /* _CLOTHES_APPLICATION_SERVER_IMP_H */