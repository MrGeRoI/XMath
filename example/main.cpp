#include <iostream>

#include "../source/xmath/xmath.hpp"

void LolPrint(xmath::graph<int>::node* nde)
{
	std::cout << nde->get_data() << std::endl;
}

int main(int argc,char* argv[])
{
	std::nullptr_t a;
	
	xmath::graph<int> g;

	xmath::graph<int>::node* node1 = g.push(3);
	xmath::graph<int>::node* node2 = g.push(5);

	node1->link_to(node2);

	const std::vector<xmath::graph<int>::node*>& nodes = g.nodes();
	
	//xmath::dfs(node1,LolPrint);
	
	return 0;
}