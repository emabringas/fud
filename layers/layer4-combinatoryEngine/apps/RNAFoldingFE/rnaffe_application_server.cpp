/*
 * Created on March 14, 2011, 9:27 AM
 *
 *  @file:      rnaffe_application_server.cpp
 *  @details    Implementation file for RnaFFEApplicationServer class.\n
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

#include "rnaffe_application_server.h"

RnaFFEApplicationServer::RnaFFEApplicationServer(const char* seq, const char* results_file, const IFold* fold)
    : L5ApplicationServer<ResisBasedAntiviral>(),_root_node(NULL), output_file(NULL)
{
    // Obtaining the PseudoNucSequence from the file
    PseudoNucSequence sequence;
    load_sequence(seq, sequence);

    std::list <size_t> id_list;
    all_antivirals.to_id_list (id_list);

    // Root node creation.
    _root_node = new RnaFFENode(sequence, id_list, fold);
    output_file.open(results_file);
}

RnaFFEApplicationServer::~RnaFFEApplicationServer()
{
    delete _root_node;
    output_file.close();
}

void RnaFFEApplicationServer::get_initial_packet(recabs::Packet& pkt) const
{
    this->_root_node->serialize(pkt);
}

void RnaFFEApplicationServer::receive_result(const recabs::Packet& pkt)
{
    bistream bis(pkt);
    PseudoNucSequence nuc_seq;
    std::list <float> fe_list;
    Therapy therapy;

    bis >> fe_list >> nuc_seq >> therapy;

    //writing results (received from clients) into the file.
    std::list<float>::iterator fe_it = fe_list.begin();
    output_file <<  fe_list.size();
    while (fe_it != fe_list.end())
    {
        output_file <<"  "  << *fe_it ;
        ++fe_it;
    }
    output_file << "\n";

    /******** BORRAR ESTOOOOOOOOOO ***/
    std::cout << " ======================= RESULT RECEIVED =======================" << std::endl;
    std::cout << "THERAPY: ";
    Therapy::iterator it = therapy.begin();
    std::list<size_t>::iterator itt;
    it=therapy.begin();
    while (it != therapy.end())
    {
        std::cout << " |";
        itt= (*it).begin();
        while (itt != (*it).end())
        {
            std::cout << (*itt) << "|";
            ++itt;
        }
        std::cout << " <>";
        ++it;
    }
    std::cout <<std::endl;

    std::cout << "FEs LIST: ";
    std::list <float>::iterator lista_fe_it = fe_list.begin();
    std::cout << " |";
    while (lista_fe_it != fe_list.end())
    {
        std::cout << (*lista_fe_it) << "|";
        ++lista_fe_it;
    }
    std::cout <<std::endl;

    std::cout << "MUTATION: ";
    std::cout << nuc_seq.getString().substr(0,40) << " .... ";
    std::cout << std::endl <<  std::endl;

    /******** FIN BORRAR ESTOOOOOOOOOO ***/
}

