/*
 *  @file:      rnaffe_application_client.cpp
 *  @details    Implementation file for RnaFFEApplicationClient class.\n
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

#include "rnaffe_application_client.h"

RnaFFEApplicationClient::RnaFFEApplicationClient(const IFold* g_fold)
    : L5ApplicationClient(), fold(g_fold)
{
    states = new StatesFSM();
    states->load_map();
}

RnaFFEApplicationClient::~RnaFFEApplicationClient()
{}

void RnaFFEApplicationClient::deserialize(const recabs::Packet& pkt, recabs::SerializableRecursiveFunctor** rf) const
{
    bistream bis(pkt);

    std::list<float> fe_list;
    PseudoNucSequence sequence;
    Therapy antivirals_applied;
    std::list <size_t> antivirals_availables;
    std::string comb_policy_name;

    bis >> fe_list >> sequence >> antivirals_availables >> antivirals_applied >> comb_policy_name;

    RnaFFENode* node = new RnaFFENode(fe_list, sequence, antivirals_applied, antivirals_availables, fold);

    // Sets to this node the FSM state and the combination policy.
    node -> set_state (states->get_state(comb_policy_name));

    CombinationPolicy<ResisBasedAntiviral>* aux = (node->get_state())->get_comb_policy()->clone (node);
    RnaFFEPrunePolicy* prune = new RnaFFEPrunePolicy("Prune Antiviral");
    node->set_combination_policy(aux);
    node->set_prune_policy(prune);

    *rf = node;
}

