/* $Id: distribution_policy.h 567 2011-06-07 20:06:32Z marjobe $ */

/** 
 *  @file:      distribution_policy.h
 *  @details    Header file for Distribution Policies classes.\n
 *              System: RecAbs\n
 *              Language: C++\n
 *  
 *  @author     Mariano Bessone
 *  @email      marjobe AT gmail.com
 *
 *  @author     Emanuel Bringas
 *  @email      emab73 AT gmail.com
 *
 *  @date       June 2011
 *  @version    0.1
 *
 * RecAbs: Recursive Abstraction, an abstraction layer to any recursive
 * process without data dependency for the framework FuD.
 * See <http://fud.googlecode.com/>.
 *
 * Copyright (C) 2010, 2011 - Mariano Bessone & Emanuel Bringas, FuDePAN
 *
 * This file is part of RecAbs project.
 *
 * RecAbs is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RecAbs is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RecAbs.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef DISTRIBUTION_POLICY_H
#define DISTRIBUTION_POLICY_H

#include "common.h"

namespace recabs
{

static const float SUFFICIENT_INDEX = 0.25;
static const float MIDDLE_INDEX     = 0.5;
static const float BEGGAR_INDEX     = 0.75;

struct DistributablePolicy
{
    protected:

        /**
         * Destructor.
         */
        virtual ~DistributablePolicy(){};

    public:
        /**
         * How many functors are sent to the server ?
         * Should be implemented as a way to distribute work. This function should never
         * return more than n_children-1 and less than 0. In other words, should return a
         * integer k, such that: 0 <= k < n_children
         *
         * @param n_children : the number of children in the current step.
         * @param depth      : current depth of the recursion tree.
         * @returns the number of children to redistribute.
         */
        virtual uint how_much_distribute(uint n_children, uint depth) const = 0;
};

class DistributeAlwaysAllPolicy: public DistributablePolicy
{
    /**
     * How many functors are sent to the server ?
     * Always returns "n_children - 1" functors to deliver.
     *
     * @param n_children : the number of children in the current step.
     * @param depth      : current depth of the recursion tree, UNUSED.
     * @returns "n_children - 1" children to redistribute.
     */
    virtual uint how_much_distribute(uint n_children, uint) const;
};

class DistributeRandomPolicy: public DistributablePolicy
{
    /**
     * How many functors are sent to the server ?
     * Returns random(0, n_children - 1) functors to deliver.
     *
     * @param n_children : the number of children in the current step.
     * @param depth      : current depth of the recursion tree, UNUSED.
     * @returns the number of children to redistribute.
     */
    virtual uint how_much_distribute(uint n_children, uint) const;
};

class Sigmoid : public DistributablePolicy
{
    protected:

        /**
         * Constructor.
         *
         * @param leafs : total leafs of the particular application.
         */
        Sigmoid(uint leafs, float request_index = MIDDLE_INDEX);

    private:

        /**
         * How many functors are sent to the server ?
         * Returns the number of functors to distribute by a sigmoid function.
         *
         * @param n_children : the number of children in the current step.
         * @param depth      : current depth of the recursion tree.
         * @returns the number of children to redistribute.
         */
        virtual uint how_much_distribute(uint n_children, uint depth) const;

        /**
         * The number of total estimated leaf of a particular application.
         * Should be carefully seted because it determinates the sigmoid function
         * of a particular problem.
         */
        const uint _leafs;
        /**
         * Index of requests. It means: upper index, more job requests to the server.
         * Could be set by an specific application, the constructor default is 0.5 .
         * The value must be greater than 0 and less than 1.
         */
        const float _request_index;
};

class FixedLeafsDistributablePolicy : public Sigmoid
{
    public:

        /**
         * Constructor.
         *
         * @param leafs : number of final leafs of the current project.
         * @param request_index : index of requests to the server.
         */
        FixedLeafsDistributablePolicy(uint leafs, float request_index = MIDDLE_INDEX);
};

class MovingAverageLeafsDistributablePolicy : public Sigmoid
{
    public:

        /**
         * Constructor.
         *
         * @param request_index : index of requests to the server.
         */
        MovingAverageLeafsDistributablePolicy(float request_index = MIDDLE_INDEX);

    private:

        /* TODO. Provisional average. */
        static const uint AVERAGE = 1000;
};

}

#endif
