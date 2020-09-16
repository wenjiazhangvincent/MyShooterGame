#include "design_table/kismet_design_table_manager.h"

#include "root/kimset_root.h"

namespace Kismet
{

	void DesignTableManager::initialize()
	{
		try
		{
			m_object_fstream.open(Root::k_design_table_directory_path + "object.csv");
			m_level_fstream.open(Root::k_design_table_directory_path + "level.csv");

			initializeDesignTable(&m_object_fstream, &m_object_col_map, &m_object_row_map);
			initializeDesignTable(&m_level_fstream, &m_level_col_map, &m_level_row_map);

			m_object_fstream.close();
			m_level_fstream.close();
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	void DesignTableManager::clear()
	{
	}

	void DesignTableManager::initializeDesignTable(std::ifstream* fstream, std::map<String, unsigned short>* col_map, std::map<String, std::vector<String>>* row_map)
	{
		String line;
		std::vector<String> fields;

		getline(*fstream, line);
		splitString(line, fields, ",");
		int col_count = fields.size();
		if (col_count == 0)
		{
			return;
		}

		for (int index = 0; index < col_count; index++)
		{
			(*col_map)[fields[index]] = index;
		}

		getline(*fstream, line);
		while (!fstream->eof())
		{
			if (line != "" && line[0] != ',' && line[0] != '#')
			{
				splitString(line, fields, ",");
				if (fields.size() == col_count)
				{
					(*row_map)[fields[0]] = fields;
				}
			}

			getline(*fstream, line);
		}
	}

	String DesignTableManager::getStringByName(const String& name, const String& table_name, const String& col_name)
	{
		String res = "";
		try 
		{
			if (name != "" && table_name != "" && col_name != "")
			{
				int col_index = -1;
				if (table_name == "object")		// hack 
				{
					col_index = m_object_col_map[col_name];
					res = m_object_row_map[name][col_index];
				}
				else if (table_name == "level")
				{
					col_index = m_level_col_map[col_name];
					res = m_level_row_map[name][col_index];
				}
			}

			return res;
		}		
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return res;
		}
	}

	int DesignTableManager::getIntByName(const String& name, const String& table_name, const String& col_name)
	{
		return atoi(getStringByName(name, table_name, col_name).c_str());
	}

	int DesignTableManager::getLongByName(const String& name, const String& table_name, const String& col_name)
	{
		return atol(getStringByName(name, table_name, col_name).c_str());
	}

	float DesignTableManager::getFloatByName(const String& name, const String& table_name, const String& col_name)
	{
		return float(atof(getStringByName(name, table_name, col_name).c_str()));
	}

	bool DesignTableManager::getBoolByName(const String& name, const String& table_name, const String& col_name)
	{
		return atoi(getStringByName(name, table_name, col_name).c_str()) != 0;
	}

	void DesignTableManager::splitString(const String& str, std::vector<String>& res, const String &sep)
	{
		res.clear();
		if (str.empty())
		{
			return;
		}

		String tmp;
		String::size_type pos_begin = 0;
		String::size_type comma_pos = 0;

		while (pos_begin != String::npos)
		{
			comma_pos = str.find(sep, pos_begin);
			if (comma_pos != String::npos)
			{
				tmp = str.substr(pos_begin, comma_pos - pos_begin);
				pos_begin = comma_pos + sep.length();
			}
			else
			{
				tmp = str.substr(pos_begin);
				pos_begin = comma_pos;
			}

			res.push_back(tmp);
		}
	}

	String DesignTableManager::trim(String& str)
	{
		str.erase(0, str.find_first_not_of(" \t\r\n"));
		str.erase(str.find_last_not_of(" \t\r\n") + 1);
		return str;
	}
}