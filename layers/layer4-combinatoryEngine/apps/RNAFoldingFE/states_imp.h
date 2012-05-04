/*
 * Created on March 14, 2011, 9:24 AM
 *
 *  @file:      states.h
 *  @details    This file defines the "FSM" states.\n
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
#ifndef STATE_IMP_H
#define STATE_IMP_H

#include "states.h"

static States* states; // FSM states.

//---------------------------------------------------------------------------------------------------------
class NNRTI : public State<ResisBasedAntiviral>
{
public:
    NNRTI ()
        : State<ResisBasedAntiviral> (new ListCombinationPolicy<ResisBasedAntiviral>(NULL , "NNRTI")) {}


    State<ResisBasedAntiviral>* next_state (std::string pol_failed)
    {
        pol_failed = pol_failed ; //borrar esto
        return NULL;
    }

};

//---------------------------------------------------------------------------------------------------------
class PI : public State<ResisBasedAntiviral>
{
public:
    PI ()
        : State<ResisBasedAntiviral> (new ListCombinationPolicy<ResisBasedAntiviral>(NULL , "PI")) {}

    State<ResisBasedAntiviral>* next_state (std::string pol_failed)
    {
        pol_failed = pol_failed ; //borrar esto
        return NULL;
    }

};

//---------------------------------------------------------------------------------------------------------
class NRTI : public State<ResisBasedAntiviral>
{
public:
    NRTI ()
        : State<ResisBasedAntiviral> (new ListCombinationPolicy<ResisBasedAntiviral>(NULL , "NRTI")) {}

    State<ResisBasedAntiviral>* next_state (std::string pol_failed)
    {
        pol_failed = pol_failed ; //borrar esto
        return NULL;
    }

};

//---------------------------------------------------------------------------------------------------------
class NRTI_PI : public State<ResisBasedAntiviral>
{
public:
    NRTI_PI ()
    {
        ListCombination comb_NRTI = new ListCombinationPolicy<ResisBasedAntiviral>(NULL, "NRTI");
        ListCombination comb_PI = new ListCombinationPolicy<ResisBasedAntiviral>(NULL, "PI");

        //creo la politica compuesta y le agreso las simples con sus conj de referencia.
        ParallelCombination combination_pol= new ComposedCombinationPolicyParallel <ResisBasedAntiviral>(NULL, "composed_NRTI_PI");
        combination_pol->add_new_combination_policy(comb_NRTI, ref_set_NRTI, true);
        combination_pol->add_new_combination_policy(comb_PI, ref_set_PI, true);
        comb_pol = combination_pol;
    }

    State<ResisBasedAntiviral>* next_state (std::string pol_failed)
    {
        State<ResisBasedAntiviral>* ret = NULL;

        if (pol_failed == "NRTI")
        {
            ret = states->pi;
        }
        else if (pol_failed == "PI")
        {
            ret = states->nrti;
        }
        return ret;
    }

};

//---------------------------------------------------------------------------------------------------------
class PIx2 : public State<ResisBasedAntiviral>
{
public:
    PIx2 ()
        : State<ResisBasedAntiviral> (new NewtonianCombinationPolicy<ResisBasedAntiviral>(2,2,"PIx2")) {}

    State<ResisBasedAntiviral>* next_state (std::string pol_failed)
    {
        pol_failed = pol_failed ; //borrar esto
        return states->pi;
    }

};

//---------------------------------------------------------------------------------------------------------
class NRTI_NNRTI : public State<ResisBasedAntiviral>
{
public:
    NRTI_NNRTI ()
    {
        ListCombination comb_NRTI = new ListCombinationPolicy<ResisBasedAntiviral>(NULL, "NRTI");
        ListCombination comb_NNRTI = new ListCombinationPolicy<ResisBasedAntiviral>(NULL, "NNRTI");

        //creo la politica compuesta y le agreso las simples con sus conj de referencia.
        ParallelCombination combination_pol= new ComposedCombinationPolicyParallel <ResisBasedAntiviral>(NULL, "composed_NRTI_NNRTI");
        combination_pol->add_new_combination_policy(comb_NRTI, ref_set_NRTI, true);
        combination_pol->add_new_combination_policy(comb_NNRTI, ref_set_NNRTI, true);
        comb_pol = combination_pol;
    }

    State<ResisBasedAntiviral>* next_state (std::string pol_failed)
    {
        State<ResisBasedAntiviral>* ret = NULL;

        if (pol_failed == "NRTI")
        {
            ret = states->nnrti;
        }
        else if (pol_failed == "NNRTI")
        {
            ret = states->nrti;
        }
        return ret;
    }

};

//---------------------------------------------------------------------------------------------------------
class NNRTI_PI: public State<ResisBasedAntiviral>
{
public:
    NNRTI_PI ()
    {
        ListCombination comb_NNRTI = new ListCombinationPolicy<ResisBasedAntiviral>(NULL, "NNRTI");
        ListCombination comb_PI = new ListCombinationPolicy<ResisBasedAntiviral>(NULL, "PI");

        //creo la politica compuesta y le agreso las simples con sus conj de referencia.
        ParallelCombination combination_pol= new ComposedCombinationPolicyParallel <ResisBasedAntiviral>(NULL, "composed_NNRTI_PI");
        combination_pol->add_new_combination_policy(comb_NNRTI, ref_set_NNRTI, true);
        combination_pol->add_new_combination_policy(comb_PI, ref_set_PI, true);
        comb_pol = combination_pol;

    }

    State<ResisBasedAntiviral>* next_state (std::string pol_failed)
    {
        State<ResisBasedAntiviral>* ret = NULL;

        if (pol_failed == "NNRTI")
        {
            ret = states->pi;
        }
        else if (pol_failed == "PI")
        {
            ret = states->nnrti;
        }
        return ret;
    }

};

//---------------------------------------------------------------------------------------------------------
class NNRTIx2 : public State<ResisBasedAntiviral>
{
public:
    NNRTIx2 ()
        : State<ResisBasedAntiviral> (new NewtonianCombinationPolicy<ResisBasedAntiviral>(2,2,"NNRTIx2")) {}

    State<ResisBasedAntiviral>* next_state (std::string pol_failed)
    {
        pol_failed = pol_failed ; //borrar esto
        return states->nnrti;
    }

};

//---------------------------------------------------------------------------------------------------------
class NRTIx2 : public State<ResisBasedAntiviral>
{
public:
    NRTIx2 ()
        : State<ResisBasedAntiviral> (new NewtonianCombinationPolicy<ResisBasedAntiviral>(2,2,"NRTIx2")) {}

    State<ResisBasedAntiviral>* next_state (std::string pol_failed)
    {
        pol_failed = pol_failed ; //borrar esto
        return states->nrti;
    }

};

//---------------------------------------------------------------------------------------------------------
class NRTI_PIx2 : public State<ResisBasedAntiviral>
{
public:
    NRTI_PIx2 ()
    {
        ListCombination comb_NRTI = new ListCombinationPolicy<ResisBasedAntiviral>(NULL, "NRTI");
        NewtonianCombination comb_PI = new NewtonianCombinationPolicy<ResisBasedAntiviral>(2,2,"PI");

        ParallelCombination combination_pol= new ComposedCombinationPolicyParallel <ResisBasedAntiviral>(NULL, "composed_NRTI_PIx2");

        combination_pol->add_new_combination_policy(comb_NRTI, ref_set_NRTI, true);
        combination_pol->add_new_combination_policy(comb_PI, ref_set_PI, true);
        comb_pol = combination_pol;
    }

    State<ResisBasedAntiviral>* next_state (std::string pol_failed)
    {
        State<ResisBasedAntiviral>* ret = NULL;
        if (pol_failed == "NRTI")
        {
            ret = states->pix2;
        }
        else if (pol_failed == "PI")
        {
            ret = states->nrti_pi;
        }
        return ret;
    }

};

//---------------------------------------------------------------------------------------------------------
class NRTI_NNRTI_PI : public State<ResisBasedAntiviral>
{
public:
    NRTI_NNRTI_PI ()
    {
        ListCombination comb_NRTI = new ListCombinationPolicy<ResisBasedAntiviral>(NULL, "NRTI");
        ListCombination comb_NNRTI = new ListCombinationPolicy<ResisBasedAntiviral>(NULL, "NNRTI");
        ListCombination comb_PI = new ListCombinationPolicy<ResisBasedAntiviral>(NULL, "PI");

        ParallelCombination combination_pol= new ComposedCombinationPolicyParallel <ResisBasedAntiviral>(NULL, "composed_NRTI_PI_NNRTI");
        combination_pol->add_new_combination_policy(comb_NRTI, ref_set_NRTI, true);
        combination_pol->add_new_combination_policy(comb_NNRTI, ref_set_NNRTI, true);
        combination_pol->add_new_combination_policy(comb_PI, ref_set_PI, true);
        comb_pol = combination_pol;
    }

    State<ResisBasedAntiviral>* next_state (std::string pol_failed)
    {
        State<ResisBasedAntiviral>* ret = NULL;

        if (pol_failed == "NRTI")
        {
            ret= states->nnrti_pi;
        }
        else if (pol_failed == "PI")
        {
            ret = states->nrti_nnrti;
        }
        else if (pol_failed == "NNRTI")
        {
            ret = states->nrti_pi;
        }
        return ret;
    }

};

//---------------------------------------------------------------------------------------------------------
class NNRTIx2_PI : public State<ResisBasedAntiviral>
{
public:
    NNRTIx2_PI ()
    {
        ListCombination comb_NNRTI = new ListCombinationPolicy<ResisBasedAntiviral>(NULL, "NNRTI");
        NewtonianCombination comb_PI = new NewtonianCombinationPolicy<ResisBasedAntiviral>(2,2,"PI");

        ParallelCombination combination_pol= new ComposedCombinationPolicyParallel <ResisBasedAntiviral>(NULL, "composed_NNRTIx2_PI");
        combination_pol->add_new_combination_policy(comb_NNRTI, ref_set_NNRTI, true);
        combination_pol->add_new_combination_policy(comb_PI, ref_set_PI, true);
        comb_pol = combination_pol;
    }


    State<ResisBasedAntiviral>* next_state (std::string pol_failed)
    {
        State<ResisBasedAntiviral>* ret = NULL;

        if (pol_failed == "PI")
        {
            ret = states->nnrtix2;
        }
        else if (pol_failed == "NNRTI")
        {
            ret = states->nnrti_pi;
        }
        return ret;
    }

};

//---------------------------------------------------------------------------------------------------------
class NRTI_NNRTIx2 : public State<ResisBasedAntiviral>
{
public:
    NRTI_NNRTIx2 ()
    {
        ListCombination comb_NRTI = new ListCombinationPolicy<ResisBasedAntiviral>(NULL, "NRTI");
        NewtonianCombination comb_NNRTI = new NewtonianCombinationPolicy<ResisBasedAntiviral>(2,2,"NNRTI");

        ParallelCombination combination_pol= new ComposedCombinationPolicyParallel <ResisBasedAntiviral>(NULL, "composed_NRTI_NNRTIx2");
        combination_pol->add_new_combination_policy(comb_NRTI, ref_set_NRTI, true);
        combination_pol->add_new_combination_policy(comb_NNRTI, ref_set_NNRTI, true);
        comb_pol = combination_pol;
    }

    State<ResisBasedAntiviral>* next_state (std::string pol_failed)
    {
        State<ResisBasedAntiviral>* ret = NULL;

        if (pol_failed == "NRTI")
        {
            ret = states->nnrtix2_pi;
        }
        else if (pol_failed == "NNRTI")
        {
            ret = states->nrti_nnrti_pi;
        }
        return ret;
    }

};

//---------------------------------------------------------------------------------------------------------
class NRTIx2_PI : public State<ResisBasedAntiviral>
{
public:
    NRTIx2_PI ()
    {
        ListCombination comb_PI = new ListCombinationPolicy<ResisBasedAntiviral>(NULL, "PI");
        NewtonianCombination comb_NRTI = new NewtonianCombinationPolicy<ResisBasedAntiviral>(2,2,"NRTI");

        ParallelCombination combination_pol= new ComposedCombinationPolicyParallel <ResisBasedAntiviral>(NULL, "composed_NRTIx2_PI");
        combination_pol->add_new_combination_policy(comb_NRTI, ref_set_NRTI, true);
        combination_pol->add_new_combination_policy(comb_PI, ref_set_PI, true);
        comb_pol = combination_pol;
    }

    State<ResisBasedAntiviral>* next_state (std::string pol_failed)
    {
        State<ResisBasedAntiviral>* ret = NULL;

        if (pol_failed == "NRTI")
        {
            ret = states->nrti_pix2;
        }
        else if (pol_failed == "PI")
        {
            ret = states->nrtix2;
        }
        return ret;
    }

};

//---------------------------------------------------------------------------------------------------------
class NRTIx2_NNRTI : public State<ResisBasedAntiviral>
{
public:
    NRTIx2_NNRTI ()
    {
        ListCombination comb_NNRTI = new ListCombinationPolicy<ResisBasedAntiviral>(NULL, "NNRTI");
        NewtonianCombination comb_NRTI = new NewtonianCombinationPolicy<ResisBasedAntiviral>(2,2,"NRTI");

        ParallelCombination combination_pol= new ComposedCombinationPolicyParallel <ResisBasedAntiviral>(NULL, "composed_NRTIx2_NNRTI");
        combination_pol->add_new_combination_policy(comb_NNRTI, ref_set_NNRTI, true);
        combination_pol->add_new_combination_policy(comb_NRTI, ref_set_NRTI, true);

        comb_pol = combination_pol;
    }

    State<ResisBasedAntiviral>* next_state (std::string pol_failed)
    {
        State<ResisBasedAntiviral>* ret = NULL;

        pol_failed=pol_failed;
        if (pol_failed == "NRTI")
        {
            ret = states->nrti_nnrtix2;
        }
        else if (pol_failed == "NNRTI")
        {
            ret = states->nrti_pix2;
        }
        return ret;
    }

};

//--------------------------------------------- END OF STATES -----------------------------------------------------


struct StatesFSM : public States
{
    StatesFSM()
    {
        nrtix2_nnrti = new NRTIx2_NNRTI ();
        nrti_nnrtix2 = new NRTI_NNRTIx2 ();
        nrtix2_pi = new NRTIx2_PI ();
        nnrtix2_pi = new NNRTIx2_PI();
        nrti_nnrti_pi = new NRTI_NNRTI_PI();
        nrti_pix2 = new NRTI_PIx2;
        nrtix2 = new NRTIx2();
        nnrtix2 = new NNRTIx2();
        nnrti_pi = new NNRTI_PI();
        nrti_nnrti = new NRTI_NNRTI();
        pix2 = new PIx2() ;
        nrti_pi = new NRTI_PI ();
        nnrti = new NNRTI();
        nrti = new NRTI();
        pi = new PI();
    }
};

#endif
