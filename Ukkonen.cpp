#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
class suffix_tree
{
private:
	class node {
	public:
 			node * parent;
 			node * suffixLink;
 			int edge_start;
 			int edge_end;
 			int parent_depth;
 			std::unordered_map<char, node *> children;
 	public:
 			node():
 			parent(NULL),suffixLink(NULL),edge_start(0),edge_end(0),parent_depth(0)
 			{
   				children = std::unordered_map<char, node *>();
 			}
  			bool edge__(int position)
  			{
   					return parent_depth <= position && position < depth();
 			}

			int edge_len()
			{
   				return edge_end - edge_start;
 			}

  			int depth()
  			{
   				return parent_depth + edge_len();
			}

 			void link(node * son, int start, int end, const std::string &s)
 			{
   				children[s[start]] = son;
   				son->parent = this;
   				son->parent_depth = this->depth();
   				son->edge_start = start;
   				son->edge_end = end;
			}

 			bool is_leaf()
 			{
   				return children.size() == 0;
 			}

	};
	private:
		std::vector<node> child_nodes;
 		node * head, * req_suffix;
 		int current_node;
 		std::string s;
 		int length;
	public:
	suffix_tree()
	{

 	}

 	suffix_tree(const std::string &str):
 	 length(str.length()),s(str)
 	 {
   		build();
	 }
private:
 		node * create_node()
 		{
   		child_nodes[current_node] = node();
   		return &child_nodes[current_node++];
 		}


 		node * go_down(node * c, int j, int i) 
 		{
   			int k = j + c->depth();
   			if (i - j + 1 > 0)
   			{
    			while (!c->edge__(i - j))
    			{
       				c = c->children[s[k]];
      				k += c->edge_len();
     			}
   			}
   			return c;
 		}

 		void suffix_links(node * current)
 		{
   			if (req_suffix != NULL)
   			{
     			req_suffix->suffixLink = current;
   			}
   			req_suffix = NULL;
 		}
 
		bool check(node *c,const std::string &instr)
		{
			static int index=0;
			if(c==NULL)
				return false;
			for(int i = c->edge_start;i<c->edge_end&&index<instr.size();i++)
			{
				if(s[i]==instr[index])
					index++;
				else
					break;
			}
			if(index==instr.size())
				return true;
			std::cout<<index<<" "<<instr.size()<<std::endl;
			std::cout<<c->edge_start<<"  "<<c->edge_end<<std::endl;
			std::cout<<instr[index]<<std::endl;
			if(c->children.find(instr[index])!=c->children.end())
			{
				index++;
				return check(c->children[instr[index]],instr);
			}
			return false;
		
		}
 		void build() 
 		{
  		 if (child_nodes.size() < 2*length + 10)
  		 {
     		child_nodes.resize(2*length + 10);
  		 }
   		current_node = 0;
   		head = create_node();
   		node * c = create_node();
   		req_suffix = NULL;
   		head->link(c, 0, length, s);
   		bool walk_down = true;

  		 for (int i=0, j=1; i<length-1; ++i)
  		 {
     		char temp_char = s[i+1];
     		while (j <= i + 1)
     		{
       			if (walk_down)
       			{
         		if (c->suffixLink == NULL && c->parent != NULL) c = c->parent;
         			c = (c->suffixLink == NULL ? head : c->suffixLink);
         			c = go_down(c, j, i);
       			}

       			walk_down = true;
      			int m = i - j + 1; 
       			if (m == c->depth())
       			{
                 suffix_links(c);
         		 if (c->children.count(temp_char) > 0)
         		 {
           			c = c->children[temp_char];
           			walk_down = false;
           			break;
         		 }
         		else
         		{
           		node * leaf = create_node();
           		c->link(leaf, i+1, length, s);
         		}
       			}
       		else{
         		int temp = c->edge_start + m - c->parent_depth;
         		if (s[temp] == temp_char) // rule 1 or 3
         		{ 
           		suffix_links(c);
           		if (!c->is_leaf() || j != c->edge_start - c->parent_depth)
           		{
             // rule 3
            	 walk_down = false;
             	break;
           		}
         		}
         else
         {
           node * split = create_node();
           c->parent->link(split, c->edge_start, temp, s);
           split->link(c, temp, c->edge_end, s);
           split->link(create_node(), i+1, length, s);

           suffix_links(split);

           if (split->depth() == 1)
           {
             split->suffixLink = head;
           }
           else
           {
             req_suffix = split;
           }

           c = split;
         }
        }
       	j++;
     	}
   	}
   
 }
public:
 void check(const std::string str)
 {
 	if(check(head,str))
 		std::cout<<"found";
 	else
 		std::cout<<"not found";
 }
};

int main(){
 /* std::ifstream in("AesopTales.txt");
 	std::stringstream buffer;
    buffer << in.rdbuf();
	std::string Tales(buffer.str());
*/
 std::string s ="helloworld";
 suffix_tree t(s+"$");
 //cout<<Tales;
 t.check("owor");
 return 0;
}