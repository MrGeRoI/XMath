#pragma once

#include "defines.hpp"

namespace xmath
{
	template<typename T>
	class graph
	{
	public:
		class traversal;
		struct node;

		using path = std::list<graph::node*>;
		using link = std::pair<node*,node*>;
		
	protected:
		std::vector<node*> _nodes;

	public:
		struct node
		{
			friend class graph;
			friend class traversal;

		protected:
			std::vector<node*> _links;
			T _data;
		
		public:
			node() { }

			node(T data) : _data(data) { }

			node(const node& other) : _data(other._data)
			{
				for(node* nd : other._links)
					_links.push_back(nd);
			}

			node& operator=(T data) { _data = data; return *this; }
			node& operator=(const node& other) { _data = n._data; return *this; }
			
			~node() { }
		}

		class traversal : std::iterator<input_iterator_tag, T>
		{
			friend class graph;

		protected:
			node* _node;
			std::vector<node*>::iterator _iterator;

			traversal(node* n) : _node(n) { }
		public:
			traversal() : _node(nullptr) { }

			traversal(const traversal& other) : _node(other._node) { }

			T get_data() const { return _data; }

			void set_data(T data) { _node->_data = data; }

			void link_to(node* to)
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

			const std::vector<node*>& neighbours() const { return _node->_links; }
			std::vector<node*>& neighbours() { return _node->_links; }

			const T& operator *() const { return _node->_data; }
			T& operator *() { return _node->_data; }
		};

		void add(node* new_node)
		{
			_nodes.push_back(new_node);
		}

		node* push(T data)
		{
			node* new_node = new node(data);

			add(new_node);

			return new_node;
		}

		const std::vector<node*>& nodes() const { return _nodes; }
		const std::vector<link>& links() const { return _links; }
		
		std::vector<node*>& nodes() { return _nodes; }
		std::vector<link>& links() { return _links; }
	};

}