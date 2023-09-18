#pragma once

#include "graph.hpp"

namespace xmath
{
	template<typename _Data,typename _Weight>
	typename graph<_Data,_Weight>::path find_path(typename graph<_Data,_Weight>::node* from,typename graph<_Data,_Weight>::node* to)
	{
		typename graph<_Data,_Weight>::path graph_path;
	
		return graph_path;
	};

	template<typename _Data,typename _Weight>
	typename graph<_Data,_Weight>::path a_star(
		std::function<_Weight(typename graph<_Data,_Weight>::node*,typename graph<_Data,_Weight>::node*)> cost,
		typename graph<_Data,_Weight>::node* from,
		typename graph<_Data,_Weight>::node* to
		)
	{
		return find_path(from,to);
	};

	template<typename _Data,typename _Weight>
	typename graph<_Data,_Weight>::path a_star(
		_Weight(*cost)(typename graph<_Data,_Weight>::node*,typename graph<_Data,_Weight>::node*),
		typename graph<_Data,_Weight>::node* from,
		typename graph<_Data,_Weight>::node* to
		)
	{
		return find_path(from,to);
	};

	template<typename _Data,typename _Weight>
	std::map<typename graph<_Data,_Weight>::node*, bool> dfs(
		typename graph<_Data,_Weight>::node* start,
		std::function<void(typename graph<_Data,_Weight>::node*)>
		)
	{
		std::stack<typename graph<_Data,_Weight>::node*> stack;
		
		stack.push(start);

		std::map<typename graph<_Data,_Weight>::node*, bool> mark;

		mark[start] = true;

		while(!stack.empty())
		{
			typename graph<_Data,_Weight>::node* node = stack.pop();
			
			for(typename graph<_Data,_Weight>::node* nde : graph)

			for u in graph[v]
				if !mark[u]
					func(u)
					mark[u] = true
					push!(stack,u)
				end
			end
		}

		return mark
	};

}