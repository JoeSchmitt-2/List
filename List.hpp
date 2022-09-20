#include "List.h"                                                                                                                                                                                                                                                                                                                                                                                                                                          List.hpp                                                                                            0000600 0266275 0000453 00000021132 14012074670 012462  0                                                                                                    ustar   jschmitt                        CS-Grads                                                                                                                                                                                                               #include "List.h"
using namespace cop4530;
/*
        Joseph Schmitt
        COP4530
*/
// default zero parameter constructor
template<typename T>
List<T>::List()
{
    init();
}
// destructor
template<typename T>
List<T>::~List<T>()
{
    clear();
    delete head;
    delete tail;
}
// copy constructor
template <typename T>
List<T>::List(const List<T> &rhs)
{
    init();
    for( auto & x : rhs)
        push_back(x);
}
// copy assignment operator
template <typename T>
const List<T> &List<T>::operator=(const List<T> &rhs)
{
    List<T> copy = rhs;
    std::swap( *this, copy);
    return *this;
}
// move constructor
template<typename T>
List<T>::List(List<T> &&rhs)
        : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
{
    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}
// num elements with value of val
template<typename T>
List<T>::List(int num, const T &val)
{
    init();
    for(int i = 0; i < num; i++)
        push_back(val);
}
// constructs with elements [start, end)
template<typename T>
List<T>::List(List<T>::const_iterator start, List<T>::const_iterator end)
{
    init();
    while(start != end)
    {
        push_back(start.current->data);
        ++start;
    }
}
// move assignment operator
template<typename T>
List<T> &List<T>::operator=(List<T> &&rhs)
{
    std::swap( theSize, rhs.theSize );
    std::swap( head, rhs.head );
    std::swap(tail, rhs.tail );
    return *this;
}
// initialization
template<typename T>
void List<T>::init()
{
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}
// iterator to first element
template<typename T>
typename List<T>::iterator List<T>::begin()
{
    return { head->next };
}

template<typename T>
typename List<T>::const_iterator List<T>::begin() const
{
    return { head->next };
}
// end marker iterator
template<typename T>
typename List<T>::iterator List<T>::end()
{
    return { tail };
}

template<typename T>
typename List<T>::const_iterator List<T>::end() const
{
    return { tail };
}



// number of elements
template<typename T>
int List<T>::size() const
{
    return theSize;
}
// check if list is empty
template<typename T>
bool List<T>::empty() const
{
    return size() == 0;
}
// delete all elements
template<typename T>
void List<T>::clear()
{
    while( !empty() )
        pop_front();
}
//Look over this one*******************
// reverse the order of the elements
template<typename T>
void List<T>::reverse()
{
    if(!empty())
    {
        auto current_ptr = head;
        while(current_ptr != nullptr)
        {
            std::swap(current_ptr->next, current_ptr->prev);
            current_ptr = current_ptr->prev;
        }
    }
    std::swap(head, tail);
}
// reference to the first element
template<typename T>
T &List<T>::front()
{
    return *begin();
}

template<typename T>
const T &List<T>::front() const
{
    return *begin();
}
// reference to the last element
template<typename T>
T &List<T>::back()
{
    return *--end();
}

template<typename T>
const T &List<T>::back() const
{
    return *--end();
}
// insert to the beginning
template<typename T>
void List<T>::push_front(const T &val)
{
    insert( begin(), val);
}
// move version of insert
template<typename T>
void List<T>::push_front(T &&val)
{
    insert( begin(), std::move( val ));
}
// insert to the end
template<typename T>
void List<T>::push_back(const T &val)
{
    insert( end(), val);
}
// move version of insert
template<typename T>
void List<T>::push_back(T &&val)
{
    insert( end(), std::move( val ));
}
// delete first element
template<typename T>
void List<T>::pop_front()
{
    erase( begin() );
}
// delete last element
template<typename T>
void List<T>::pop_back()
{
    erase( --end() );
}

template<typename T>
void List<T>::remove(const T &val)
{
    for(List<T>::iterator itr = begin(); itr != end(); ++itr)
    {
        if(itr.current->data == val)
            erase(itr);
    }
}

template<typename T>
void List<T>::print(std::ostream &os, char ofc) const
{
    for(List<T>::const_iterator itr = begin(); itr != end(); ++itr)
    {
        os << itr.current->data << ofc;
    }
}
//insert val ahead of itr
template<typename T>
typename List<T>::iterator List<T>::insert(List::iterator itr, const T &val)
{
    Node *p = itr.current;
    theSize++;
    return { p->prev = p->prev->next = new Node{ val, p->prev, p } };
}
// move version of insert
template<typename T>
typename List<T>::iterator List<T>::insert(List::iterator itr, T &&val)
{
    Node *p = itr.current;
    theSize++;
    return { p->prev = p->prev->next
                            = new Node { std::move( val ), p->prev, p } };
}
// erase one element
template<typename T>
typename List<T>::iterator List<T>::erase(List<T>::iterator itr)
{
    Node *p = itr.current;
    iterator retVal{ p->next };
    p->prev->next = p->next;
    p->next->prev = p->prev;
    theSize--;

    return retVal;
}
// erase [start, end)
template<typename T>
typename List<T>::iterator List<T>::erase(List<T>::iterator start, List<T>::iterator end)
{
    for( iterator itr = start; itr != end; )
        itr = erase( itr );

    return end;
}

//****************************************
//const_iterator start

//default zero parameter constructor
template<typename T>
List<T>::const_iterator::const_iterator() : current{nullptr}
{ }
//operator*() to return element
template<typename T>
const T &List<T>::const_iterator::operator*() const
{
    return retrieve();
}

//operator->() to return pointer to element
template<typename T>
const T *List<T>::const_iterator::operator->() const
{
    return operator*();
}

template<typename T>
typename List<T>::const_iterator &List<T>::const_iterator::operator++()
{
    current = current->next;
    return *this;
}

template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)
{
    List<T>::const_iterator old = *this;
    ++(*this);
}

template<typename T>
typename List<T>::const_iterator &List<T>::const_iterator::operator--()
{
    current = current->prev;
    return *this;
}

template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int)
{
    List<T>::const_iterator old = *this;
    --(*this);
}

template<typename T>
bool List<T>::const_iterator::operator==(const List::const_iterator &rhs) const
{
    return current == rhs.current;
}

template<typename T>
bool List<T>::const_iterator::operator!=(const List::const_iterator &rhs) const
{
    return !( *this == rhs );
}
// retrieve the element refers to
template<typename T>
T &List<T>::const_iterator::retrieve() const
{
    return current->data;
}
// protected constructor
template<typename T>
List<T>::const_iterator::const_iterator(List::Node *p)  : current{ p }
{ }
//****************************************
//iterator start

template<typename T>
List<T>::iterator::iterator()
{ }
// return pointer to element
template<typename T>
T &List<T>::iterator::operator*()
{
    return List<T>::const_iterator::retrieve();
}

template<typename T>
const T &List<T>::iterator::operator*() const
{
    return List<T>::const_iterator::operator*();
}
// return pointer to element
template<typename T>
T *List<T>::iterator::operator->()
{
    return List<T>::iterator::retrieve();
}
// return pointer to content element
template<typename T>
const T *List<T>::iterator::operator->() const {
    return List<T>::iterator::operator->();
}
// increment/decrement operators
template<typename T>
typename List<T>::iterator &List<T>::iterator::operator++()
{
    this->current = this->current->next;
    return *this;
}

template<typename T>
typename List<T>::iterator List<T>::iterator::operator++(int)
{
    List<T>::iterator old = *this;
    ++( *this );
    return old;
}

template<typename T>
typename List<T>::iterator &List<T>::iterator::operator--()
{
    this->current = this->current->prev;
    return *this;
}

template<typename T>
typename List<T>::iterator List<T>::iterator::operator--(int)
{
    List<T>::iterator old = *this;
    --( *this );
    return old;
}

template<typename T>
List<T>::iterator::iterator(List::Node *p) : const_iterator{ p }
{ }

//************************
//Overloading comparison operators
template<typename T>
bool operator==(const List<T> &lhs, const List<T> &rhs)
{
    if(lhs.size() == rhs.size())
    {
        for(auto & itr: lhs)
        {
            for(auto & itr2: rhs)
            {
                if(itr != itr2)
                    return false;
            }
        }
        return true;
    }
    else return false;
}

template<typename T>
bool operator!=(const List<T> &lhs, const List<T> &rhs)
{
    return (!(lhs == rhs));
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const List<T> &l)
{
    l.print(os);
    return os;
}
