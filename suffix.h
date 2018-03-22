typedef struct node
{
	struct node *next[26];
	vector<int> positions;
	string str;
}Suffixtree;
Suffixtree *initialize(vector<int> &position)
{
	Suffixtree *tree = new Suffixtree;
	tree->positions = position;
	for(int i=0;i<26;i++)
		tree->next[i] = NULL;
	tree->str = "$";
	return tree;

}
Suffixtree *initialize(int pos)
{
	Suffixtree *tree = new Suffixtree;
	tree->positions.push_back(pos);
	for(int i=0;i<26;i++)
		tree->next[i] = NULL;
	tree->str = "$";
	return tree;

}

Suffixtree *buildtree(Suffixtree * t , string s,int pos)
{
	Suffixtree *tmp = t;
	int j=0;
	while(j<s.size()&&s[j]!='$'&&tmp->next[s[j]-'a']!=NULL)
	{
		tmp->next[s[j]-'a']->positions.push_back(pos);
		tmp = tmp->next[s[j]-'a'];
		j++;
		//cout<<j<<" j "<<s<<"  "<<tmp->positions.size()<<endl;
	}
	if(j<s.size()&&s[j]!='$'&&(tmp->str.size()==1||tmp->str[0]!=s[j]))
	{
		Suffixtree *newnode = initialize(tmp->positions);
		if(newnode->positions.size()==0)
			newnode->positions.push_back(pos);
		else if(newnode->positions.back()!=pos)
			newnode->positions.push_back(pos);
		if(j+1<s.size())
		newnode->str  = s.substr(j+1,s.size());
		if(j<s.size()&&s[j]!='$')
		tmp->next[s[j]-'a'] = newnode;
		//cout<<" first if "<<s<<"  "<<tmp->positions.size()<<endl;
	}
	else
	{
		int k=0;
		Suffixtree *prev = tmp;
		while(k<prev->str.size()&&j<s.size()&&prev->str[k]==s[j])
		{
			//cout<<s<<" "<<s[j];
			if(s[j]=='$'||prev->str[k]=='$')
				break;
			Suffixtree *newnode = initialize(tmp->positions);
			tmp->next[s[j]-'a'] = newnode;
			tmp = tmp->next[s[j]-'a'];
			k++;
			j++;
		}
		if(k<prev->str.size())
		{
			Suffixtree *newnode = initialize(tmp->positions);
			newnode->positions.pop_back();
			if(k<prev->str.size()&&prev->str[k]!='$')
			tmp->next[prev->str[k]-'a'] = newnode;
			k++;
			if(k<prev->str.size()&&prev->str[k]!='$')
				newnode->str = prev->str.substr(k,prev->str.size());

		}
		prev->str ="$";
		if(j<s.size())
		{
			Suffixtree *newnode = initialize(pos);
			if(j<s.size()&&s[j]!='$')
			tmp->next[s[j]-'a'] = newnode;
			//tmp = tmp->next[s[j]-'a'];
			j++;
			if(j<s.size()&&s[j]!='$')
				newnode->str = s.substr(j,s.size());
		}

	}
	return t;
}
void traverse(Suffixtree *tree,int j)
{
	if(tree==NULL)
		return;
	
	for(int i=0;i<26;i++)
	{
		traverse(tree->next[i],i);
	}
	printf("%c ",j+'a');
	//cout<<tree->str<<" "<<tree->positions.size()<<endl;
	
}
Suffixtree* findquerystring(Suffixtree *tree, string query)
{
	int j =0;
	Suffixtree *ref = NULL;
	int min = 12345678;
	while(j<query.size()&&tree->next[query[j]-'a']!=NULL)
	{
		tree = tree->next[query[j]-'a'];
		if(tree->positions.size()<min)
		{
			min = tree->positions.size();
			ref = tree;
		}
		//cout<<query[j];
		j++;
	}
	for(int i=0;i<tree->str.size();i++)
	{
		if(j<query.size()&&tree->str[i]==query[j])
			j++;
		else
			break;
	}
	if(j==query.size())
		return ref;
	else
		return NULL;

}
pair<int,Suffixtree *> findmaxlengthquery(Suffixtree *tree , string query )
{
	int j =0;
	Suffixtree *ref = NULL;
	int min = 12345678;
	while(j<query.size()&&tree->next[query[j]-'a']!=NULL)
	{
		tree = tree->next[query[j]-'a'];
		if(tree->positions.size()<min)
		{
			min = tree->positions.size();
			ref = tree;
		}
		///cout<<query[j];
		j++;
	}
	for(int i=0;i<tree->str.size();i++)
	{
		if(j<query.size()&&tree->str[i]==query[j])
			j++;
		else
			break;
	}
	return make_pair(j,ref);
}
