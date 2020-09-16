#ifndef _KISMET_DESIGN_TABLE_MANAGER_H_
#define _KISMET_DESIGN_TABLE_MANAGER_H_
#include "core/kismet_prerequisites.h"

namespace Kismet
{
	class DesignTableManager
	{
	public:
		DesignTableManager() {};
		~DesignTableManager() {};

		void initialize();
		void clear();

		void initializeDesignTable(std::ifstream* fstream, std::map<String, unsigned short>* col_map, std::map<String, std::vector<String>>* row_map);

		String getStringByName(const String& name, const String& table_name, const String& col_name);
		int getIntByName(const String& name, const String& table_name, const String& col_name);
		int getLongByName(const String& name, const String& table_name, const String& col_name);
		float getFloatByName(const String& name, const String& table_name, const String& col_name);
		bool getBoolByName(const String& name, const String& table_name, const String& col_name);
		

		static void splitString(const String& str, std::vector<String>& res, const String &sep);
		static String trim(String& str);

	private:

		std::ifstream m_object_fstream;
		std::map<String, unsigned short> m_object_col_map;
		std::map<String, std::vector<String>> m_object_row_map;

		std::ifstream m_level_fstream;
		std::map<String, unsigned short> m_level_col_map;
		std::map<String, std::vector<String>> m_level_row_map;
	};

}

#endif // !_KISMET_DESIGN_TABLE_MANAGER_H_
