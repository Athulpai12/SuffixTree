void preprocess(vector<string> &title,vector<string> &story,vector<string> &tale)
{
	ifstream in("AesopTales.txt");
	stringstream buffer;
	buffer << in.rdbuf();
	string Tales(buffer.str());
	int i=1;
	string tmp(1,(char)tolower(Tales[0]));
	for(int i=1;i<Tales.size();i++)
	{
			if(Tales[i]!='\n')
				tmp = tmp+(char)tolower(Tales[i]);
			else if(i+3<Tales.size()&&Tales[i+1]=='\n'&&Tales[i+2]==' '&&Tales[i+3]=='\n')
			{
				i=i+3;
				tale.push_back(tmp);
				tmp=" ";
			}
			else if(i+3<Tales.size()&&Tales[i+1]==' '&&Tales[i+2]=='\n'&&Tales[i+3]=='\n')
			{
				i=i+3;
				tale.push_back(tmp);
				tmp=" ";
			}
			else if((i+2<Tales.size()&&Tales[i+2]=='\n'&&Tales[i+1]=='\n'))
			{
				
				i=i+3;
				tale.push_back(tmp);
				tmp=" ";
			}
			else
			{
				tmp= tmp+"\n";
			}	
	}
	tale.push_back(tmp);
	//cout<<"lines "<<tale.size()<<endl;
	for(int i=0;i<tale.size();i++)
	{
		int j=0;
		string tmp(1,tale[i][j]);
		while(tale[i][++j]!='\n')
			tmp = tmp+tale[i][j];
		title.push_back(tmp);
		story.push_back(tale[i].substr(j+1,tale[i].size()-1
			));
	}
	//cout<<tale[0];
	for(int i=0;i<story.size();i++)
	{
		for(int j=0;j<story[i].size();j++)
			if(story[i][j]=='\n')
				story[i][j] = ' ';
	}
}