/*****************************************************************************
Title: tree components
Author: Aviv Illoz
Description: tree components API
******************************************************************************/

#include <iostream> // cout
#include <boost/filesystem.hpp> // filesystem

#include "tree_components.hpp" // api

/*****************************************************************************/

namespace ilrd
{

BaseFile::BaseFile(const std::string& name_)
	: m_name(name_)
{}

BaseFile::~BaseFile()
{}

std::string BaseFile::GetName() const
{
	return boost::filesystem::path(m_name).filename().string();
}

Directory::Directory(const std::string& name_)
	: BaseFile(name_)
{
	boost::filesystem::path p(name_);
	boost::filesystem::directory_iterator iter(p), end;
	for (; iter != end; ++iter)
	{
		std::string name = iter->path().string();
		if (boost::filesystem::is_directory(iter->path()))
		{
			m_entries.push_back(boost::shared_ptr<BaseFile>(new Directory(name)));
		}
		else
		{
			m_entries.push_back(boost::shared_ptr<BaseFile>(new File(name)));
		}
	}
}

Directory::~Directory()
{}

void Directory::Print() const
{
	static std::size_t indent = 0; 

    std::cout << "\033[1;33m";
	std::cout << GetName() << std::endl;

	indent += 1;
	for (std::size_t i = 0; i < m_entries.size(); ++i)
	{
		std::cout << "\033[1;34m";
		for (std::size_t j = 0; j < indent; ++j)
		{
            std::cout << "|____";
		}
		m_entries[i]->Print();
	}
	indent -= 1;
}

File::File(const std::string& name_)
	: BaseFile(name_)
{}

File::~File()
{}

void File::Print() const
{		
    std::cout << "\033[1;32m";
	std::cout << GetName() << std::endl;
}

}

/*****************************************************************************/
