#include<bits/stdc++.h>
using namespace std;
#include "suffix.h"
#include "removewords.h"
#include "preprocess.h"
#include "solution.h"
#include "fetchsentence.h"
int main()
{
	vector<string> title,story,tale;
	preprocess(title,story,tale);
	cout<<title.size()<<" "<<story.size();
	vector<Suffixtree *> Suffixvector;
	solve(title,story,Suffixvector);
	string query = "lay";
	cout<<"enter string for query 1"<<endl;
	cin>>query;
	string sentence;
	for(int i=0;i<Suffixvector.size();i++)
	{
	Suffixtree *ans = findquerystring(Suffixvector[0],query);
		if(ans!=NULL)
		{
			sentence = fetchsentence(title[i],story[i],ans->positions,query,ans->positions.size());
			if(sentence!=" ")
			cout<<" title - "<<sentence<<endl;
		} 
	 }
	 string query2 = "helloworld";
	 cout<<"enter string for query 2"<<endl;
	 cin>>query2;
	 for(int i=0;i<Suffixvector.size();i++)
	{
		pair<int,Suffixtree *> maxlen = make_pair(-1,(Suffixtree *)NULL);
		string tmp = query2;
		for(int j=1;j<query2.size();j++)
		{
			pair<int,Suffixtree *> max_tmp = findmaxlengthquery(Suffixvector[i],tmp);
			if(max_tmp.first>maxlen.first)
				maxlen = max_tmp;
			if(maxlen.first>=query2.size()-j)
				break;
		}
		if(maxlen.first!=-1&&maxlen.second!=NULL)
		{
			string sent = fetch(title[i],story[i],maxlen.second->positions[0]);
			cout<<sent<<endl;
		}
	}
	vector<string> query3;
	cout<<"Number of words in the third query"<<endl;
	int n;
	cin>>n;
	while(n-->0)
	{
		string k;
		cin>>k;
		query3.push_back(k);
	}
	int max_count =0,count=0,z=0;
	vector< pair<int,string> > document;
	for(int j=0;j<Suffixvector.size();j++)
	{
		max_count =0,count=0,z=0;
		for(int i=0;i<query3.size();i++)
			{
				Suffixtree *ans = findquerystring(Suffixvector[0],query3[i]);
				if(ans!=NULL)
				{
					count++;
				}
				else if(ans==NULL)
				{
					if(count==i)
						z++;
					if(count<i-2)
						z = 0;
					if(count<i)
						z--;

				}
			}
			document.push_back(make_pair(count+z,title[j]));
	}
	sort(document.begin(),document.end(),comp);
	for(int i=0;i<document.size();i++)
		cout<<document[i].second<<endl;
}