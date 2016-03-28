#include "helper.h"

void Helper::printListToFile(const Skiplist& list, const char* filename)
{
	std::ofstream out(filename);
	if (out.is_open())
	{
		out << "/*************************************************/" << "\n";
		SkiplistNode* current = new SkiplistNode;
		current = list.list_header;
		for (int i = 0; i <= list.list_level; i++)
		{
			out << "level" << i << "  :";
			while (current->forward[i] != NULL)
			{
				std::string key((char*)current->forward[i]->slice.getKey());
				std::string value((char*)current->forward[i]->slice.getValue());
				out << key << "-->" << value << "    ";
				current = current->forward[i];
			}
			out << "\n";

		}
		out.close();
		current = NULL;
		//delete[] current;
	}
}