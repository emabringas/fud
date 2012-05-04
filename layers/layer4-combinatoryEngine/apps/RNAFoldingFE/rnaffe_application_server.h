/*
 * Created on March 14, 2011, 6:48 PM
 *
 *  @file:      rnaffe_application_server.h
 *  @details    Header file for RnaFFEApplicationServer class.\n
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

#ifndef RNAFFE_APPLICATION_SERVER_H
#define RNAFFE_APPLICATION_SERVER_H

#include <sstream>
#include <fstream>
#include "rnaffe_node.h"


using namespace comb_eng;
class RnaFFEApplicationServer: public comb_eng::L5ApplicationServer<ResisBasedAntiviral>
{

private:
    RnaFFENode* _root_node;
    std::ofstream output_file;

public:
    /**
    *  Construtor method.
    *  @param seq: Path file containing the initial sequence.
    *  @param db: Path file containing all availables antivirals.
    *  @param res_file: Path file where results will be stored.
    *  @param fold: Pointer to a fold type. It will be used to get the folding free energy.
    */
    RnaFFEApplicationServer(const char* seq, const char* res_file, const IFold* fold);

    /**
    *  Destrutor method.
    */
    ~RnaFFEApplicationServer();

    /**
    *  Method to get a packet representing the application root node.
    *  @param pkt: Here should be stored the root-node serialization.
    */
    void get_initial_packet(recabs::Packet& pkt) const;

    /**
    *  Describes what should be do when a result arrives to the server.
    *  @param pkt: It represents the result. It has to be deserialized.
    */
    void receive_result(const recabs::Packet& pkt);

};
#endif  /* RNAFFE_APPLICATION_SERVER_H */

