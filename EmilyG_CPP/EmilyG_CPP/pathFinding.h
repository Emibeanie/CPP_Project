#pragma once
#include <map>
#include <set>
class pathFinding
{
	public:
		pathFinding() {};

		std:: set<int> findPath(std::map<int, std::set<int>> graph, int start, int goal);
		
};

