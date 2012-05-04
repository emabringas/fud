// include guard
#ifndef STATE_SET_H
#define STATE_SET_H

#include <mili/mili.h>
#include <iostream>

template <class Element, typename StateType>
class StateSet
{

private:
    std::vector<StateType>  _vec_state;
    std::vector<Element>    _vec_elem;

public:
    StateSet() {};

    StateSet(const StateSet& other)
    {
        mili::copy_container(other._vec_state, _vec_state);
        mili::copy_container(other._vec_elem, _vec_elem);
    };

    /* Constructor method.
     * @param elements: Vector of elements for the set.
     * @param states: Vector (with the same lenght that 'elements') representing the state of each elemennt in the set.
     */
    template <class container_1, class container_2>
    StateSet(const container_1& elements, const container_2& states)
    {
        mili::copy_container(elements, _vec_elem);
        mili::copy_container(states, _vec_state);
        //assert( _vec_elem.size() == _vec_state.size() );
    }

    /* Constructor method.
     * @param elements: Vector of elements for the set.
     * @param state: With this state, all elements are added in the vector _vec_elem.
     */
    template <class Container>
    StateSet(const Container& elements, StateType state)
    {
        mili::copy_container(elements, _vec_elem);
        for (typename std::vector<Element>::iterator it = _vec_elem.begin(); it != _vec_elem.end(); ++it)
            _vec_state.push_back(state);
    }

    /* Returns if the state of the _vec_state in the position i is the same that the parameter state
     * @param id: Position on the vector.
     * @param state: The state to compare.
     */
    bool has_state(size_t id, StateType state) const
    {
        return _vec_state[id] == state;
    }

    /* Sets the state to an element represented by the id.
     * @param id: Position on the vector.
     * @param state: The new state for the element.
     */
    void set_state(size_t id, StateType state)
    {
        _vec_state[id] = state;
    }

    /* Sets all states to a given state,
     * @param state: The new state for the elements.
     */
    void set_all_state(StateType state)
    {
        for (size_t id = 0; id < _vec_state.size(); id++)
        {
            _vec_state[id] = state;
        }
    }

    /* Change the state of the objects belonging to a list to an specific state.
     * @param list: List of elements in which their states want to be changed.
     * @param state: The new state for the elements.
     */
    void change_states_to(std::list<Element> list, StateType state)
    {
        typename std::list<Element>::iterator it;
        size_t i;
        for (it = list.begin(); it != list.end(); ++it)
        {
            i = 0;
            while ((i < _vec_elem.size()) && !(_vec_elem[i] == (*it)))
                i++;

            if (i < _vec_elem.size())
                _vec_state[i] = state;

        }
    }

    /* Gets the state of an element represented by the id.
     * @param id: Position on the vector.
     */
    StateType get_state(size_t id) const
    {
        return _vec_state[id];
    }

    /*
     * Returns a the amount of elements that have a given state.
     */
    size_t count(StateType state) const
    {
        size_t count = 0;
        for (size_t id = 0; id < _vec_state.size(); id++)
        {
            if (_vec_state[id] == state)
                count++;
        }
        return count;
    }

    /*
     * Returns a container containing those elements that have a given state.
     */
    template <class Container>
    void to_container(Container& res, StateType state)
    {
        res.clear();
        for (size_t i = 0; i < _vec_elem.size(); i++)
        {
            if (_vec_state[i] == state)
                mili::insert_into(res, _vec_elem[i]);
        }
    }

    /*
     * Computes the intersection of two StateSet that have the same size. If they have different size, the result is *this.
     * @param res: Reference to a StateSet where will be stored the intersection..
     * @param other: The StateSet that will be intersected whit this.
     * @param v_true: State equivalent to true value.
     * @param v_false: State equivalent to false value.
     */
    void intersection(StateSet& res, const StateSet& other, StateType v_true, StateType v_false)
    {
        mili::copy_container(_vec_state, res._vec_state);
        mili::copy_container(_vec_elem, res._vec_elem);

        if (_vec_elem.size() == other._vec_elem.size())
        {
            typename StateSet<Element, StateType>::ConstIterator it = other.begin_const();
            while (!it.end())
            {
                if (_vec_state[it.get_id()] == it.get_state() && it.get_state() == v_true)
                    res.set_state(it.get_id(), v_true);
                else
                    res.set_state(it.get_id(), v_false);
                ++it;
            }
        }
    }

    /*
     * Returns true if _vec_elem is empty, otherwise, returns false.
     */
    bool empty() const
    {
        return _vec_elem.empty();
    }

    /*
     * Operator =
     */
    StateSet& operator= (const StateSet& other)
    {
        this->_vec_elem = other._vec_elem;
        this->_vec_state = other._vec_state;

        return (*this);
    }


    /********************************************************************************
     ********************************** ITERATORS ***********************************
     ********************************************************************************/

    struct ConstIteratorBase
    {
        ConstIteratorBase(const StateSet<Element, StateType>& father)
            : id(0), _father(father)
        {
            size = _father._vec_elem.size();
        }

        bool operator == (const ConstIteratorBase& other) const
        {
            return (other.id == id);
        }

        bool operator != (const ConstIteratorBase& other) const
        {
            return !(other == (*this));
        }

        Element get_element() const
        {
            return _father._vec_elem [id];
        }

        StateType get_state() const
        {
            return _father._vec_state[id];
        }

        size_t get_id() const
        {
            return id;
        }

        bool end() const
        {
            return (id == size);
        }

        void restart()
        {
            id = 0;
        }
    protected:

        size_t id;
        size_t size;
        const StateSet<Element, StateType>& _father;
    };

    // Constant Iterator
    struct ConstIterator : public ConstIteratorBase
    {
        ConstIterator(const StateSet<Element, StateType>& father)
            : ConstIteratorBase(father) {}

        ConstIterator& operator ++()
        {
            ++(this->id);
            return (*this);
        }

        void next(StateType state)
        {
            do
            {
                ++(this->id);
            }
            while (this->get_state() != state && (this->id) < (this->size));
        }
    };

    // Constant Iterator
    struct ConstSpecificIterator : public ConstIteratorBase
    {

        ConstSpecificIterator(const StateSet<Element, StateType>& father, StateType state)
            : ConstIteratorBase(father), _state(state) {}

        ConstSpecificIterator& operator++()
        {
            do
            {
                ++(this->id);
            }
            while (!this->end() && (this->get_state() != _state));

            return *this;
        }

    protected:
        StateType _state;

    };

    // Regular Iterator (Not Constant)
    struct Iterator : public ConstIterator
    {

        Iterator(const StateSet<Element, StateType>& father)
            : ConstIterator(father) {}

        void set_element(Element elem)
        {
            this->_father._vec_elem [this->id] = elem;
        }

        void set_state(StateType state)
        {
            this->_father._vec_state[this->id] = state;
        }
    };

    // Regular Iterator (Not Constant)
    struct SpecificIterator : public ConstSpecificIterator
    {

        SpecificIterator(const StateSet<Element, StateType>& father, StateType state)
            : ConstSpecificIterator(father, state) {}

        void set_element(Element elem)
        {
            this->_father._vec_elem [this->id] = elem;
        }

        void set_state(StateType state)
        {
            this->_father._vec_state[this->id] = state;
        }
    };
    /********************************************************************************
     *******************************FIN DE LOS ITERADORES ***************************
     ********************************************************************************/

    /*
     *  Returns an iterator positioned on the first element.
    */
    Iterator begin() const
    {
        Iterator it(*this);
        return it;
    }

    /*
     *  Returns a constant iterator positioned on the first element.
    */
    ConstIterator begin_const() const
    {
        ConstIterator it(*this);
        return it;
    }

    /*
     * Returns an iterator positioned on the first element of a given type.
     * @param state: Type used to initialize the iterator.
    */
    SpecificIterator begin_SpecificIterator(StateType state) const
    {
        SpecificIterator it(*this, state);
        if (!_vec_elem.empty())
        {
            while (it.get_state() != state && ! it.end())
                ++it;
        }
        return it;
    }

    /*
     * Returns a constant iterator positioned on the first element of a given type.
     * @param state: Type used to initialize the iterator.
    */
    ConstSpecificIterator begin_SpecificIterator_const(StateType state) const
    {
        ConstSpecificIterator it(*this, state);
        if (!_vec_elem.empty())
        {
            while (it.get_state() != state && ! it.end())
                ++it;
        }
        return it;
    }

    /*
     * Returns an iterator positioned on the first element that has the template parameter type.
    */
    template <StateType state>
    SpecificIterator begin_SpecificIterator() const
    {
        return begin_SpecificIterator(state);
    }

    /*
     * Returns a constant iterator positioned on the first element that has the template parameter type.
    */
    template <StateType state>
    ConstSpecificIterator begin_SpecificIteratorT_const() const
    {
        return begin_SpecificIterator_const(state);
    }
};

#endif
