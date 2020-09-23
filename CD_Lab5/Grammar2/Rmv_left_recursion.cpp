#include<bits/stdc++.h>

using namespace std;
vector<string> nt;
vector<vector<string>> pn;
vector<int> lr;

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

void add_to_prod(string pr)
{
	int i;
	string ntt="";
	for(i=0;i<pr.size();i++)
	{
		ntt+=pr[i];
		if(pr[i+1]=='-' && pr[i+2]=='>')
		{
			nt.push_back(ntt);
			i=i+3;
			break;
		}
	}
	string temp="";
	vector<string> prds;
	for(;i<pr.size();i++)
	{
		temp+=pr[i];
		if(pr[i+1]=='|' || i==pr.size()-1)
		{
			prds.push_back(temp);
			temp="";
			i++;
		}
	}
	pn.push_back(prds);
}

void check_left_recursion()
{
	int n=nt.size();
	lr.resize(n);
	int i;
	for(i=0;i<n;++i) 
	{
		int k=pn[i].size();
		for(int j=0;j<k;++j) 
		{
			string str=pn[i][j];
			if(nt[i].length()<=str.length()&&nt[i].compare(str.substr(0,nt[i].length()))==0)
				lr[i]=1;
		}
	}	
	for(i=0;i<n;++i) 
	{
		if(lr[i]!=1)
			continue;
		int j;
		nt.push_back(nt[i]+"'");
		vector<string> temp;
		for(j=0;j<pn[i].size();++j) 
		{
			if(nt[i].length()<=pn[i][j].length()&& nt[i].compare(pn[i][j].substr(0,nt[i].length()))==0) 
			{
				string str=pn[i][j].substr(nt[i].length(),pn[i][j].length()-nt[i].length())+" "+nt[i]+"'";
				if(str[0]==' ')
					str.erase(0,1);
				cout<<"Adding to new prod "<<nt[i]<<"' "<<str;
				temp.push_back(str);
				pn[i].erase(pn[i].begin()+j);
				--j;
			}
			else 
			{
				pn[i][j]+=" "+nt[i]+"'";
			}
		}
		temp.push_back("#");
		pn.push_back(temp);
	}
}


int main()
{
	fstream f,f1;
	f.open("Original_grammar.txt",ios::in);
	f1.open("LL1_Grammar.txt",ios::out);
	if(f.is_open())
	{
		string pr;
		while(getline(f,pr)){
			add_to_prod(pr);
		}
		
	}
	check_left_recursion();
	cout<<"\n\nNew productions are: ";
	for(int i=0;i<nt.size();++i) 
	{
		int j;
		string strg="";
		cout<<"\n"<<nt[i]<<"->";
		strg+=nt[i]+"->";
		for(j=0;j<pn[i].size();++j) 
		{
			strg+=pn[i][j];
			cout<<pn[i][j];
			if(j!=pn[i].size()-1)
			{
				cout<<"|";
				strg+="|";
			}
		}
		strg+="\n";
		f1<<strg;
	}
    cout<<"\n";
	f.close();
	f1.close();
	return 0;
}