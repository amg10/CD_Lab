#include<bits/stdc++.h>

using namespace std;

int fin_min_size(vector<string> v)
{
	int mis=INT_MAX;
	for(int p=0;p<v.size();p++)
	{
		if(v[p].length()<mis)
			mis=v[p].length();
	}
	return mis;
}

bool is_same_alp(vector<string> v, int w)
{
	for(int p=1;p<v.size();p++)
	{
		if(v[p][w]!=v[p-1][w])
			return false;
	}
	return true;
}

int main()
{
	vector<string> productions;
	char ch='Z';
	int str_index=3;
	int n;
	cout<<"Enter number of productions:";
	cin>>n;
	cout<<"Certain conditions for entering:\n1.Nonterminals are single Capital alphabet and terminals are single lowercase alphabet\n2.No space in defining production\n";
	cout<<"\nEnter each production on a new line without space(E->E+T|T):\n";
	productions.resize(n);
	for(int i=0;i<n;i++)
	{
		cin>>productions[i]; 
	}
	for(int i=0;i<productions.size();i++)
	{
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
			{	
				s+=productions[i][index];
			}
			
		}
		p1.push_back(s);
		/*****Find similarities***/
		int sameas[p1.size()];
		for(int q=0;q<p1.size();q++)
		{
			sameas[q]=q;
		}
		for(int q=0;q<p1.size()-1;q++)
		{
			for(int z=q+1;z<p1.size();z++)
			{
				if(p1[q][0]==p1[z][0])
				{
					sameas[z]=sameas[q];
				}
			}
		}
		string up_s=string(1,nt)+"->";
		vector<vector<string>> similar;
		similar.resize(p1.size());
		for(int q=0;q<p1.size();q++)
		{
			similar[sameas[q]].push_back(p1[q]);
		}
		/**debug*
		for(int q=0;q<p1.size();q++)
		{
			for(int w=0;w<similar[q].size();w++)
				cout<<similar[q][w]<<"\t";
			cout<<"\n";
		}
		-------*/
		for(int q=0;q<p1.size();q++)
		{
			if(similar[q].size()==1)
			{
				up_s+=similar[q][0];
				up_s+="|";
			}	
			else if (similar[q].size()>1)
			{
				int min_size=fin_min_size(similar[q]);
				int w,flag=0;
				for(w=0;w<min_size;w++)
				{
					if(!is_same_alp(similar[q],w))
						break;
				}
				if(w==min_size)
				{
					flag=1;
				}
				up_s+=similar[q][0].substr(0,w);
				up_s+=string(1,ch);
				up_s+="|";
				string new_prod=string(1,ch)+"->";
				for(int p=0;p<similar[q].size();p++)
				{
					if(similar[q][p].substr(w,similar[q][p].size()-1).size()>0)
						new_prod+=similar[q][p].substr(w,similar[q][p].size()-1)+"|";
				}
				ch--;
				if(flag==1)
				{
					new_prod+="e|";
				}
				new_prod=new_prod.substr(0,new_prod.size()-1);
				productions.push_back(new_prod);
			}
		}
		up_s=up_s.substr(0,up_s.size()-1);
		productions[i]=up_s;
		
	}
	cout<<"\nUpdated Productions:\n";
	for(int i=0;i<productions.size();i++)
	{
		cout<<productions[i]<<"\n";
	}
	return 1;
}