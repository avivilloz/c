/****************************************************************************
Title: Tree
Description: File System Parsing
*****************************************************************************/

#ifndef TREE_HPP
#define TREE_HPP

#include "tree_components.hpp"

namespace ilrd
{

class Tree
{
public:
    explicit Tree(const std::string& path_);
    ~Tree();
    void Print() const;
private:
    BaseFile *m_base;
};

}

#endif /* TREE_HPP */
