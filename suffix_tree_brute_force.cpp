#include<bits/stdc++.h>
using namespace std;
#define threshhold 195
typedef struct node
{
	struct node *next[256];
	string str;
}Suffixtree;
void check(vector<string> &tales, vector<string> &titles)
{
	if(titles.size()>tales.size())
	{
	//cout<<tales.size()<<" "<<titles.size()<<endl;
	string tmp = titles.back();
	titles.pop_back();
	if(tmp.size()>45&&tmp.size()<threshhold)
	tales[tales.size()-1] = tales[tales.size()-1]+" "+tmp;
	else
		titles.push_back(tmp);
	}
	return;
}
int main()
{
	ifstream in("AesopTales.txt");
	stringstream buffer;
	buffer << in.rdbuf();
	string Tales(buffer.str());
	vector<string> tales;
	vector<string> titles;
	int i=1;
	string tmp(1,Tales[0]);
	for(int i=1;i<Tales.size();i++)
		{
			if(Tales[i]!='\n')
				tmp = tmp+Tales[i];
			else if(i+3<Tales.size()&&Tales[i+1]=='\n'&&Tales[i+2]==' '&&Tales[i+3]=='\n')
			{
				i=i+3;
				if(tmp.size()<=threshhold+5)
					tales[tales.size()-1] = tales[tales.size()-1] + tmp;
				else
				tales.push_back(tmp);
				tmp=" ";
			}
			else if(i+3<Tales.size()&&Tales[i+1]==' '&&Tales[i+2]=='\n'&&Tales[i+3]=='\n')
			{
				i=i+3;
				if(tmp.size()<=threshhold+5)
					tales[tales.size()-1] = tales[tales.size()-1] + tmp;
				else
				tales.push_back(tmp);
				tmp=" ";
			}
			else if((i+2<Tales.size()&&Tales[i+2]=='\n'&&Tales[i+1]=='\n'))
			{
				
				i=i+2;
				if(tmp.size()<=threshhold+5)
					tales[tales.size()-1] = tales[tales.size()-1] + tmp;
				else
				tales.push_back(tmp);
				tmp=" ";
			}
			else if(i+2<Tales.size()&&Tales[i+1]==' '&&Tales[i+2]=='\n')
			{
				i=i+2;
				if(tmp.size()>=threshhold)
					tales.push_back(tmp);
				else
				{	
					check(tales,titles);
					titles.push_back(tmp);
				}
				tmp=" ";
			}
			else if(i+1<Tales.size()&&Tales[i+1]=='\n')
			{
				i=i+1;
				if(tmp.size()>=threshhold)
					tales.push_back(tmp);
				else
				{	
					check(tales,titles);
					titles.push_back(tmp);
				}
				tmp=" ";
			}
			else
			{
				tmp= tmp+" ";
			}	
			
		}
		tales.push_back(tmp);
		cout<<titles.size()<<" "<<tales.size()<<endl;
		for(int i=0;i<titles.size();i++)
		{ 		
			cout<<titles[i]<<endl;
			cout<<tales[i]<<endl;
		}
}

	
