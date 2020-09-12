#include<bits/stdc++.h>

using namespace std;

int main()
{
	vector<string> productions;
	char ch='Z';
	int str_index=3;
	int n;
	cout<<"Enter number of productions:";
	cin>>n;
	productions.resize(n);
	cout<<"Certain conditions for entering:\n1.Nonterminals are single Capital alphabet and terminals are single lowercase alphabet\n2.No space in defining production\n";
	cout<<"\nEnter each production on a new line without space(E->E+T|T):\n";
	for(int i=0;i<n;i++)
	{
		cin>>productions[i]; 
	}
	for(int i=0;i<n;i++)
	{
		cout<<"\nLooking into :"<<productions[i]<<"\n";
		char nt=productions[i][0];
		int index=str_index;
		vector<string>p1;
		string s="";
		for(;productions[i][index]!='\0';index++)
		{
			if(productions[i][index]=='|')
			{
				p1.push_back(s);
				s="";
			}
			else
			{	s+=productions[i][index];
			}
			
		}
		p1.push_back(s);
		int c=0;
		vector<string> st;
		vector<string> lr;
		for(int j=0;j<p1.size();j++)
		{
			if(p1[j][0]==nt)
			{
				c++;
				lr.push_back(p1[j]);
			}
			else
				st.push_back(p1[j]);
		}
		if(c==0)
		{
			cout<<"No left recursion in the production "<<productions[i]<<"\n";
		}
		else if(c==p1.size())
		{
			cout<<"The production can't terminate.Illegalproduction!!\n";
		}
		else
		{
			cout<<"Left recursion found!!\n";
			string up_s="";
			string new_prod="";
			cout<<"The production will be replaced as follows:\n";
			cout<<nt<<"->"<<st[0]<<ch;
			up_s+=string(1,nt)+"->"+st[0]+string(1,ch);
			if(st.size()>1)
			{
				for(int k=1;k<st.size();k++)
				{
					cout<<"|"<<st[k]<<ch;
					up_s+="|"+st[k]+string(1,ch);
				}
			}
			productions[i]=up_s;
			cout<<"\n";
			cout<<ch<<"->"<<lr[0].substr(1,lr[0].length()-1)<<ch;
			new_prod=string(1,ch)+"->"+lr[0].substr(1,lr[0].length()-1)+string(1,ch);
			if(lr.size()>1)
			{
				for(int k=1;k<lr.size();k++)
				{	
					cout<<"|"<<lr[k].substr(1,lr[0].length()-1);
					cout<<ch;
					new_prod+="|"+lr[k].substr(1,lr[0].length()-1)+string(1,ch);
				}
			}
			ch--;
			cout<<"|e\n";
			new_prod+="|e";
			productions.push_back(new_prod);
		}
	}
	cout<<"\nUpdated Productions:\n";
	for(int i=0;i<productions.size();i++)
	{
		cout<<productions[i]<<"\n";
	}
	return 0;
}

	