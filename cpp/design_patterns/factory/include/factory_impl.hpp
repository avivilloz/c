/*****************************************************************************
Title: factory_impl - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: factory_impl
******************************************************************************/

#include "factory.hpp"

/*****************************************************************************/

template
<typename ProductType, typename Key, typename Params, typename CreateFunc>
Factory<ProductType, Key, Params, CreateFunc>::Factory()
    : m_creator()
{}

template
<typename ProductType, typename Key, typename Params, typename CreateFunc>
ProductType Factory<ProductType, Key, Params, CreateFunc>::
Create(const Key key_, Params params_) const
{
    typename std::map<Key, CreateFunc>::const_iterator it;
    it = m_creator.find(key_);

    if (m_creator.end() == it)
    {
        throw std::invalid_argument("error: invalid key");
    }

    return it->second(params_); 
}

template
<typename ProductType, typename Key, typename Params, typename CreateFunc>
void Factory<ProductType, Key, Params, CreateFunc>::
Add(const Key type, CreateFunc creator)
{
    m_creator.insert(std::make_pair(type, creator));
}

/*****************************************************************************/
