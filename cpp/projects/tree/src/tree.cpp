/*****************************************************************************
Title: tree
Author: Aviv Illoz
Description: tree
******************************************************************************/

#include <boost/filesystem.hpp> // filesystem

#include "tree.hpp" // api

/*****************************************************************************/

namespace ilrd
{

Tree::Tree(const std::string& path_)
{
	boost::filesystem::path p(path_);
	if (boost::filesystem::is_regular_file(p))
	{
		m_base = new File(path_);
	}
	else if (boost::filesystem::is_directory(p))
	{
		m_base = new Directory(path_);
	}
}

Tree::~Tree()
{
	delete m_base;
	m_base = NULL;
}

void Tree::Print() const
{
	m_base->Print();
}

}

/*****************************************************************************/

