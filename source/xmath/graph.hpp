#pragma once

#include "defines.hpp"

namespace xmath
{
	template<typename _Node,typename _Link = std::nullptr_t>
	class graph
	{
	public:
		class node;
		class link;
		using path = std::list<graph::node*>;
		
	protected:
		std::vector<node*> _nodes;
		std::vector<link*> _links;

	public:
		class link
		{
			friend class graph;
			friend class node;
		protected:
			node* _from, *_to;
			_Link _weight;
		public:
			link()
			{
				_from = _to = nullptr;
				_weight = ONE(_Link);
			}

			link(_Link weight) : link()
			{
				_weight = weight;
			}

			link(node* from,node* to) : link()
			{
				_from = from;
				_to = to;
			}

			// link(node* from,node* to,_Link weight) : link(from,to) , link(weight) { }

			node* from() const { return _from; }
			node* to() const { return _to; }

			void connect(node* from, node* to)
			{
				from->link_to(to);
			}
		};

		class node
		{
			friend class graph; 
			friend class link;

		protected:
			std::vector<link*> _links;
			_Node _data;

		public:
			node() { }

			node(_Node data)
			{
				_data = data;
			}

			_Node get_data() const { return _data; }

			void set_data(_Node data) { _data = data; }

			link* link_to(node* nde)
			{
				link* lnk = new link(this,nde);

				_links.push_back(lnk);
				
				return lnk;
			}

			link* link_to(node* node,_Link weight)
			{
				link* lnk = link_to(node);
				lnk.set_weight(weight);
				return lnk;
			}

			std::pair<link*,link*> link_both(node* node)
			{
				link* lnk1 = link_to(node);
				link* lnk2 = node->link_to(this);

				return std::pair<link*,link*>(lnk1,lnk2);
			}

			link* get_link_to(node* node) const
			{
				for(link lnk : _links)
					if(lnk->_to == node)
						return lnk;

				return nullptr;
			}

			bool is_linked_to(node* node) const
			{
				return get_link(node) != nullptr;
			}

			void unlink_from(node* node)
			{
				// _links.erase(std::remove(_links.begin(), _links.end(), node), _links.end());
			}

			void unlink_both(node* node)
			{
				unlink_from(node);
				node->unlink_from(this);
			}

			void unlink_all()
			{
				for(link lnk : _links)
					lnk->_to->unlink(this);
				
				_links.clear();
			}

			void unlink_both_all()
			{
				for(link lnk : _links)
					lnk->_to->unlink_both(this);
				
				_links.clear();
			}
		};

		void add(node* new_node)
		{
			_nodes.push_back(new_node);
		}

		node* push(_Node data)
		{
			node* new_node = new node(data);

			add(new_node);

			return new_node;
		}

		const std::vector<node*>& nodes() const { return _nodes; }
		const std::vector<link*>& links() const { return _links; }
		
		std::vector<node*>& nodes() { return _nodes; }
		std::vector<link*>& links() { return _links; }
	};

}