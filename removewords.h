vector<pair<string,int> > removewords(string ref)
{
	vector<pair<string,int> > word;
	int j=0;
	while(ref[j]==' ')
		j++;
	int currentpos =j;
	string tmp = " ";
	for(int i=j;i<ref.size();i++)
	{
		if(ref[i]=='"'||ref[i]=='.'||ref[i]==','||ref[i]=='!'||ref[i]=='\''||ref[i]==':'||ref[i]==';'||ref[i]=='-'||ref[i]=='?')
			continue;
		if(ref[i]=='('||ref[i]==')'||ref[i]=='{'||ref[i]=='}')
			continue;
		if(ref[i]==' ')
		{
			word.push_back(make_pair(tmp.substr(1,tmp.size()),currentpos));
			while(i<ref.size()&&ref[i]==' ')
				i++;
			currentpos = i;
			if(i<ref.size()&&ref[i]!=' ')
				i--;

			tmp=" ";
		}
		else
			tmp = tmp+ref[i];
	}
	if(tmp[0]==' '&&tmp.size()>1)
		word.push_back(make_pair(tmp.substr(1,tmp.size()),currentpos));
	return word;
}