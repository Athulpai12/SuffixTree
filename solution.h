void solve(vector<string> &title, vector<string> &story,vector<Suffixtree *> &Suffixvector)
{
	vector<int> position;
	int k=0;
	vector< pair<string,int> > words;
	for(int i=0;i<story.size();i++)
	{
		Suffixtree *tree = initialize(position);
		//Suffixvector.push_back(tree);
		 words = removewords(story[i]);
		/*while(i==0&&k<words.size())
		{
			cout<<words[k].first<<"  "<<words[k].second<<endl;
			k++;
		}*/
		for(int j=0;j<words.size();j++)
		{
			for(int k=0;k<words[j].first.size();k++)
			{
				string ret_tmp = words[j].first.substr(k,words[j].first.size());
				ret_tmp+="$";
				//cout<<ret_tmp<<endl;
				tree = buildtree(tree,ret_tmp,words[j].second+k);
				//traverse(tree,0);
				//cout<<endl<<endl<<endl;
			}
		}
		Suffixvector.push_back(tree);
		
		//cout<<words.size()<<endl;
	}
	//cout<<Suffixvector.size();
}
bool check(int pos, int size, string &story , string &query)
{
	int k=0;
	for(int j=pos;j<size&&k<query.size();j++)
	{
		if(story[j]!=query[k])
			break;
		k++;
	}
	if(k==query.size())
		return false;
	else
		return true;
}
bool comp(pair<int, string> p1, pair<int, string> p2)
{
	return p1.first < p2.first;
}