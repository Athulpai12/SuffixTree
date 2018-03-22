string fetchsentence(string &title,string &story, vector<int> &position,string &query,int size)
{
	string sentence=" ";
	for(int j=0;j<size;j++)
	{
		int pos = position[j];
		if(check(pos,story.size(),story,query))
			continue;
		pos = pos-1;
		while(pos>=0&&story[pos]!='.')
		{
			sentence = story[pos]+ sentence;
			pos--;
		}
		pos = position[j];
		while(pos<story.size()&&story[pos]!='.')
		{
			sentence = sentence+story[pos];
			pos++;
		}
		sentence = sentence+'\n';
	}
	if(sentence.size()>2)
		sentence = title+'\n' + sentence;
	return sentence;
}
string fetch(string &title, string &story , int position)
{
	string sentence=" ";
		int pos = position;
		pos = pos-1;
		while(pos>=0&&story[pos]!='.')
		{
			sentence = story[pos]+ sentence;
			pos--;
		}
		pos = position;
		while(pos<story.size()&&story[pos]!='.')
		{
			sentence = sentence+story[pos];
			pos++;
		}
		sentence = sentence+'\n';
		sentence ="title -" + title+'\n' + sentence;
	return sentence;
}