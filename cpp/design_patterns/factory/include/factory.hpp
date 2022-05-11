/*******************************************************************************
Title: Factory - Infinity Labs R&D 
Group: RD91
Description: Factory API
*******************************************************************************/

#ifndef ILRD_RD91_FACTORY_HPP
#define ILRD_RD91_FACTORY_HPP

#include <map>
#include <boost/core/noncopyable.hpp>
#include <stdexcept> // used in factory_impl, std::invalid_argument

namespace ilrd
{

template
<
    typename ProductType, 
    typename Key, 
    typename Params, 
    typename CreateFunc = ProductType (*)(Params)
>
class Factory : private boost::noncopyable
{
public:
    Factory();
    ProductType Create(const Key key_, Params params_) const;
    void Add(const Key type, CreateFunc creator);
private:
    std::map<const Key, CreateFunc> m_creator;
};

#include "factory_impl.hpp"

}

#endif /* ILRD_RD91_FACTORY_HPP */
