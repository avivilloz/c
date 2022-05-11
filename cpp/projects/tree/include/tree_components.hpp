/****************************************************************************
Title: Tree Components
Author: Aviv Illoz
Description: File System Parsing
*****************************************************************************/

#ifndef TREE_COMPOENTS_HPP
#define TREE_COMPOENTS_HPP

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace ilrd
{

class BaseFile
{
public:
    BaseFile(const std::string& name_);
    virtual ~BaseFile();
    void virtual Print() const = 0;
protected:
    std::string GetName() const;
private:
    const std::string m_name;
};

class Directory : public BaseFile
{
public:
    Directory(const std::string& name_);
    ~Directory();
    void Print() const;
private:
    std::vector< boost::shared_ptr<BaseFile> > m_entries;
};

class File : public BaseFile
{
public:
    File(const std::string& name_);
    ~File();
    void Print() const;
};

}

#endif /* TREE_COMPOENTS_HPP */
