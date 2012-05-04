/*
 * Created on March 14, 2011, 9:24 AM
 *
 *  @file:      states.h
 *  @details    Header file defining some abstract classes to implement a "FSM".\n
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

#ifndef STATE_H
#define STATE_H

#include <map>
#include <string>
#include <combeng/combeng.h>


typedef     ComposedCombinationPolicyParallel<ResisBasedAntiviral>* ParallelCombination;
typedef     ListCombinationPolicy<ResisBasedAntiviral>* ListCombination;
typedef     NewtonianCombinationPolicy<ResisBasedAntiviral>* NewtonianCombination;

// Global variable containig all antivirals
extern AntiviralSet all_antivirals;

template <class T>
class State
{
protected:
    comb_eng::CombinationPolicy<T>* comb_pol;
    std::list<ResisBasedAntiviral> ref_set_NRTI;
    std::list<ResisBasedAntiviral> ref_set_NNRTI;
    std::list<ResisBasedAntiviral> ref_set_PI;

public:

    /**
    *  Construtor method.
    */
    State()
    {
        all_antivirals.split_antivirals_by_type(ref_set_NRTI, ref_set_NNRTI, ref_set_PI);
    }

    /**
    *  Construtor method.
    *  @param pol: Combination policy to initialize the state.
    */
    State(comb_eng::CombinationPolicy<T>* pol)
        : comb_pol(pol)
    {}

    /**
    *  Destructor method.
    */
    virtual ~State()
    {
        delete(comb_pol);
    }

    /**
    *  Returns a new FSM state to continue the execution.
    *  @param pol_failed: Combination policy that cannot be executed. Is used to get the next combination policy.
    */
    virtual State<ResisBasedAntiviral>* next_state(std::string pol_failed)
    {
        pol_failed = pol_failed ; //borrar esto
        return (new State(NULL));
    }

    /**
    *  Returns the combination policy attached to the state.
    */
    comb_eng::CombinationPolicy<T>* get_comb_policy()
    {
        return comb_pol;
    }

    /**
    *  Prints the name of the combination policy attached to the state.
    */
    void print()
    {
        std::cout << comb_pol->get_name() << std::endl;
    }

    /**
    *  Returns the name of the combination policy attached to the state.
    */
    std::string get_name()
    {
        return comb_pol->get_name();
    }
};


// The following struct contain all FSM states.
struct States
{
    //public member variables.
    State<ResisBasedAntiviral>* nrtix2_nnrti;
    State<ResisBasedAntiviral>* nrti_nnrtix2;
    State<ResisBasedAntiviral>* nrtix2_pi ;
    State<ResisBasedAntiviral>* nnrtix2_pi ;
    State<ResisBasedAntiviral>* nrti_nnrti_pi;
    State<ResisBasedAntiviral>* nrti_pix2 ;
    State<ResisBasedAntiviral>* nrtix2 ;
    State<ResisBasedAntiviral>* nnrtix2 ;
    State<ResisBasedAntiviral>* nnrti_pi;
    State<ResisBasedAntiviral>* nrti_nnrti;
    State<ResisBasedAntiviral>* pix2 ;
    State<ResisBasedAntiviral>* nrti_pi;
    State<ResisBasedAntiviral>* nnrti;
    State<ResisBasedAntiviral>* nrti ;
    State<ResisBasedAntiviral>* pi ;

    /**
    *  Construtor method.
    */
    States() {}

    /**
    *  Construtor method.
    */
    virtual ~States() {}

    /**
    *  Returns a state using the combination policy name.
    *  @param state_name: String representing the name of the combination policy.
    */
    State<ResisBasedAntiviral>*  get_state(const std::string& state_name) const
    {
        return (states_map.find(state_name))->second;
    }

    /**
    *  Maps each state with its name.
    */
    void load_map()
    {
        states_map["NNRTI"] = nnrti;
        states_map["PI"] = pi;
        states_map["NRTI"] = nrti;
        states_map["composed_NRTI_PI"] = nrti_pi;
        states_map["PIx2"] = pix2;
        states_map["composed_NRTI_NNRTI"] = nrti_nnrti;
        states_map["composed_NNRTI_PI"]= nnrti_pi;
        states_map["NNRTIx2"] = nnrtix2;
        states_map["NRTIx2"] = nrtix2;
        states_map["composed_NRTI_PIx2"] = nrti_pix2;
        states_map["composed_NRTI_PI_NNRTI"] = nrti_nnrti_pi;
        states_map["composed_NNRTIx2_PI"] = nnrtix2_pi;
        states_map["composed_NRTI_NNRTIx2"] = nrti_nnrtix2;
        states_map["composed_NRTIx2_PI"] = pix2;
        states_map["composed_NRTIx2_NNRTI"] = nrtix2_nnrti;
    }

private:
    std::map <std::string, State<ResisBasedAntiviral>* > states_map;

};

#endif
