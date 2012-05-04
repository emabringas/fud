/*
 *  @file:      rnaffe_node.cpp
 *  @details    Implementation file for RnaFFENode class.\n
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
#include <combeng/combeng.h>
#include <antivirals/antivirals.h>
#include "rnaffe_node.h"

using namespace comb_eng;

RnaFFENode::RnaFFENode(const PseudoNucSequence& sequence, const std::list<size_t>& avs_to_apply, RnaFFENode * father)
    : L4Node<ResisBasedAntiviral>(father->get_combination_policy(), father->get_prune_policy()), _sequence(sequence), _therapy(), _Fe_list()
{
    // Initializes all availables antivirals
    _availables_avs = father->_availables_avs;
    std::list<size_t>::const_iterator it = avs_to_apply.begin();
    while (it != avs_to_apply.end())
    {
        _availables_avs.remove(*it);
        ++it;
    }

    // Loads the father's therapy and adds to it the combination (as a new therapy step).
    _therapy = father->_therapy;
    _therapy.push_back(avs_to_apply);

    // Loads the father's fold method.
    _fold_type = father->_fold_type;

    // Load the list of FE from its father, and adds the new FE.
    _Fe_list = father->_Fe_list;
    _Fe_list.push_back(this->score()); // here we get the Free Energy of the current node

    // Loads the FSM state and the combination policy from its father
    _state = father->get_state();
    CombinationPolicy<ResisBasedAntiviral>* composed = father->get_combination_policy()->clone(this);
    this->set_combination_policy(composed);

    // Loads the prune policy from its father.
    RnaFFEPrunePolicy* prune = new RnaFFEPrunePolicy("Prune Antiviral");
    this->set_prune_policy(prune);
}


RnaFFENode::RnaFFENode(const std::list<float>& fe_list, const PseudoNucSequence& seq, const Therapy& avs_applied, const std::list<size_t>& initial_avs, const IFold* fold)
    : L4Node<ResisBasedAntiviral>(),_sequence(seq),_therapy(avs_applied),_Fe_list(fe_list),_availables_avs(initial_avs),_fold_type(fold)
{}

RnaFFENode::RnaFFENode(const PseudoNucSequence& seq, const std::list<size_t>& initial_avs, const IFold* fold)
    : L4Node<ResisBasedAntiviral>(), _sequence(seq), _therapy(), _Fe_list(), _availables_avs(initial_avs),_fold_type(fold)
{
    _combination_policy = new ListCombinationPolicy<ResisBasedAntiviral>(NULL, "composed_NRTIx2_NNRTI");
    _Fe_list.push_back(this->score());
}

bool RnaFFENode::is_leaf()
{
    return (_availables_avs.empty());
}

void RnaFFENode::serialize(recabs::Packet& pkt)
{
    bostream bos;
    bos << _Fe_list << _sequence << _availables_avs << _therapy << _combination_policy->get_name();
    pkt = bos.str();
}

void RnaFFENode::get_objects_to_combine(std::list<ResisBasedAntiviral>& avs_to_combine)
{

    AntiviralSelector selector;
    AntiviralSet elems_to_combine;
    AntiviralSet availables_avs;

    all_antivirals.select (_availables_avs, availables_avs);
    selector.select_antivirals(availables_avs, _sequence, elems_to_combine);;

    AVIterator it(elems_to_combine.antivirals);
    while (!it.end())
    {
        insert_into(avs_to_combine, **it);
        ++it;
    }

}

float RnaFFENode::score()
{
    NucSequence nuc_seq;
    _sequence.getNucSequence(nuc_seq);
    SecStructure sec_struct;
    float fe = _fold_type->fold(nuc_seq, sec_struct, false);
    return fe;
}

void RnaFFENode::new_children(const std::list<ResisBasedAntiviral>& combination, std::list<comb_eng::L4Node<ResisBasedAntiviral>*>& children)
{
    AntiviralSet avsSet;
    std::list<size_t> tmp;
    std::list<ResisBasedAntiviral>::const_iterator it_t;
    for (it_t = combination.begin(); it_t != combination.end(); ++it_t)
    {
        size_t id;
        (*it_t).get_attrib("id", id);
        tmp.push_back(id);
        avsSet.add_antiviral(*it_t);
    }

    std::list <PseudoNucSequence> mutations;
    avsSet.get_mutants(_sequence, mutations);

    for (std::list <PseudoNucSequence>::iterator s_it = mutations.begin(); s_it != mutations.end(); ++s_it)
    {
        RnaFFENode* child = new RnaFFENode((*s_it), tmp, this);
        children.push_back(child);
    }
}

bool RnaFFENode::use_as_result()
{
    return false;
}

recabs::Packet RnaFFENode::get_result()
{
    recabs::Packet pkt;
    bostream bos;
    bos << _Fe_list << _sequence << _therapy ;
    pkt = bos.str();

    /************** borrar ****************/
//
//                                        Therapy::iterator it = _therapy.begin();
//                                        std::list<size_t>::iterator itt;
//
//                                        std::cout << "THERAPIA: ";
//                                        it=_therapy.begin();
//                                        while (it != _therapy.end())
//                                        {
//                                            std::cout << " |";
//                                            itt= (*it).begin();
//                                            while (itt != (*it).end())
//                                            {
//                                                std::cout << (*itt) << "|";
//                                                ++itt;
//                                            }
//                                            std::cout << " <>";
//                                           ++it;
//                                        }
//                                        std::cout <<std::endl;
//
//                                        std::cout << "LISTA FEs: ";
//                                        std::list <float>::iterator lista_fe_it = _Fe_list.begin();
//                                        std::cout << " |";
//                                        while (lista_fe_it != _Fe_list.end())
//                                        {
//                                             std::cout << (*lista_fe_it) << "|";
//                                             ++lista_fe_it;
//                                        }
//                                        std::cout <<std::endl;

//                                        std::cout << "MUTACION: ";
//                                        std::cout << _sequence.getString().substr(0,40) << " .... ";
//                                        std::cout << std::endl <<  std::endl;
    /************** fin borrar ****************/
    return pkt;
}

CombinationPolicy<ResisBasedAntiviral>* RnaFFENode::get_combination_if_failure(const std::string& failed_comb_policy)
{
    State<ResisBasedAntiviral>* aux = _state->next_state(failed_comb_policy);
    _state = aux;

    if (_state == NULL)
        return (NULL);

    return (_state->get_comb_policy()->clone (this));
}


