/*
 * Created on March 14, 2011, 9:24 AM
 *
 *  @file:      rnaffe_node.h
 *  @details    Header file for RnaFFENode class.\n
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

#ifndef RNAFFE_NODE_H
#define RNAFFE_NODE_H

#include<combeng/combeng.h>
#include<antivirals/antivirals.h>
#include<rnafolding/rnafolding.h>
#include<biopp/biopp.h>
#include "rnaffe_prune_policy.h"
#include "states_imp.h"

typedef     std::list<std::list<size_t> > Therapy;
typedef     ComposedCombinationPolicyParallel<ResisBasedAntiviral>* ParallelCombination;
typedef     ListCombinationPolicy<ResisBasedAntiviral>* ListCombination;

class RnaFFENode : public comb_eng::L4Node<ResisBasedAntiviral>
{
public:

    /**
    *  Construtor method.
    *  @param seq: String representing the virus DNA.
    *  @param initial_avs: List of antivirals that can be used by the node..
    *  @param avs_applied: List of applied antivirals so far. It represents the therapy.
    *  @param fe_list: List containig the folding free energy for each therapy step.
    *  @param fold: Fold type used to get the folding free energy.
    */
    RnaFFENode(const std::list<float>& fe_list, const PseudoNucSequence& seq, const Therapy& avs_applied,
               const std::list<size_t>&  initialAvs, const IFold* fold);

    /**
    *  Construtor method.
    *  @param sequence: String representing the virus DNA.
    *  @param to_apply: List of antiviral ids that have to be removed from the list of available antiviral ids.
    *  @param father: The RnaFFENode father, used to get information like: combination policy, prune policy, available antivirals...
    */
    RnaFFENode(const PseudoNucSequence& sequence, const std::list<size_t>& to_apply, RnaFFENode* father);

    /**
    *  Construtor method.
    *  @param seq: String representing the virus DNA.
    *  @param initial_avs: List of antivirals that can be used by the node..
    *  @param father: The RnaFFENode father, used to get information like: combination policy, prune policy, fold...
    */
    RnaFFENode(const PseudoNucSequence& seq, const std::list<size_t>& initial_avs, const IFold* fold);

    /**
    *  Destructor method.
    */
    ~RnaFFENode() {}

    /**
    *  Returns true if the node is a leaf. Otherwise, returns false.
    */
    bool is_leaf();

    /**
    *  Serializes the node and returns a data stream containing the serialization.
    *  @param pkt: Result parameter to return the data stram.
    */
    void serialize(recabs::Packet& pkt);

    /**
    *  Returns a list containing all available antivirals to be combined.
    *  @param avs_to_combine: Result parameter to return the list of available antivirals.
    */
    void get_objects_to_combine(std::list<ResisBasedAntiviral>& avs_to_combine);

    /**
    *  Computes and returns a float representing the folding free energy for the current node.
    */
    float score();

    /**
    * Returns true if the node should be used as result.
    */
    bool use_as_result();

    /**
    * Sets a new FSM state for the node.
    *  @param state: The new FSM state for the node.
    */
    void set_state (State<ResisBasedAntiviral>* state)
    {
        _state = state;
    }

    /**
    * Returns the node FSM state
    */
    State<ResisBasedAntiviral>* get_state ()
    {
        return (_state);
    }


private:
    const PseudoNucSequence _sequence;
    Therapy _therapy;
    std::list <float> _Fe_list;
    std::list <size_t> _availables_avs;
    State<ResisBasedAntiviral>* _state;
    const IFold* _fold_type;



protected:
    typedef std::list<ResisBasedAntiviral>::iterator AvsList_it;
    typedef std::list<PseudoNucSequence>::iterator MutantsSeq_it;

    /**
    *  From a combination, it creates the successor states for the current node.
    *  @param combination: Combination of antivirals used to get ths successor states.
    *  @param children: Result parameter to return the successor states.
    */
    void new_children(const std::list<ResisBasedAntiviral>& combination, std::list<comb_eng::L4Node<ResisBasedAntiviral>*>& children);

    /**
    *  Returns a data stram representing a result.
    */
    recabs::Packet get_result();

    /**
    *  If the combination policy cannot be applied, it returns another one to continue the ejecution.
    *  @param failed_comb_policy: Name of the failed combination policy.
    */
    comb_eng::CombinationPolicy<ResisBasedAntiviral>* get_combination_if_failure(const std::string& failed_comb_policy);
};
#endif  /* RNAFFE_NODE_H */

