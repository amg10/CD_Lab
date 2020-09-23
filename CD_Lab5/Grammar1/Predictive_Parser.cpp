#include<bits/stdc++.h>

using namespace std;
vector<string> nt;
map<string,vector<string>> firstsets;
map<string,vector<string>> followsets;
vector<vector<string>> pn;
vector<string> terminals={"id","+","*","(",")","$"};
vector<vector<string>> parsing_table;
vector<string> remaining_input; 
stack<string> pdstack;


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

void add_to_first(string str)
{
	int flag=0;
	string temp="";
	string ntt="";
	vector<string> t;
	for(int i=0;i<str.size();i++)
	{
		temp+=str[i];
		if(str[i+1]==' ')
		{
			if(flag==0)
			{
				ntt=temp;
				temp="";
				flag=1;
			}
			else
			{
				t.push_back(temp);
				temp="";
			}
			i++;
		}
	}
	t.push_back(temp);
	firstsets[ntt]=t;
}

void add_to_follow(string str)
{
	int flag=0;
	string temp="";
	string ntt="";
	vector<string> t;
	for(int i=0;i<str.size();i++)
	{
		temp+=str[i];
		if(str[i+1]==' ')
		{
			if(flag==0)
			{
				ntt=temp;
				temp="";
				flag=1;
			}
			else
			{
				t.push_back(temp);
				temp="";
			}
			i++;
		}
	}
	t.push_back(temp);
	followsets[ntt]=t;
}

void print_production()
{
	cout<<"\n\nProductions are: ";
	for(int i=0;i<nt.size();++i) 
	{
		int j;
		cout<<"\n"<<nt[i]<<"->";
		for(j=0;j<pn[i].size();++j) 
		{
			cout<<pn[i][j];
			if(j!=pn[i].size()-1)
			{
				cout<<"|";
			}
		}
		cout<<"\n";
	}
    cout<<"\n";
}

void print_map(map<string,vector<string>> set)
{
	map<string, vector<string>>::iterator itr; 
	for (itr = set.begin(); itr != set.end(); ++itr) { 
        cout <<itr->first<< '\t';
		vector<string> v=itr->second; 
		for(int q=0;q<v.size();q++)
		{
			cout<<v[q]<<" ";
		}
		cout<<"\n";
    } 
}

void print_parsing_table()
{
	cout<<"\nParsing Table:";
	cout<<"\n";
	cout<<"\t";
	for(int i=0;i<terminals.size();i++)
	{
		cout<<terminals[i]<<"\t";
	}
	cout<<"\n";
	for(int i=0;i<nt.size();i++)
	{
		cout<<nt[i]<<"\t";
		for(int q=0;q<parsing_table[i].size();q++)
		{
			cout<<parsing_table[i][q]<<"\t";
		}
		cout<<"\n";
	}
}

int find_index(string s)
{
	for(int q=0;q<terminals.size();q++)
	{
		string str=terminals[q];
		if(strcmp(s.c_str(),str.c_str())==0)
		{
			return q;
		}
	}
	return -1;
}

void append_to_reamining(string str)
{
	string temp="";
	for(int i=0;i<str.size();i++)
	{
		temp+=str[i];
		if(str[i+1]==' ')
		{
			remaining_input.push_back(temp);
			temp="";
			i++;
		}
	}
	remaining_input.push_back(temp);
	remaining_input.push_back("$");
}

void make_parsing_table()
{
	parsing_table.resize(nt.size());
	for(int i=0;i<nt.size();i++)
		parsing_table[i].resize(terminals.size());
	string epsilon="#";
	for(int i=0;i<nt.size();i++)
	{
		string ntt=nt[i];
		vector<string>first_s;
		vector<string>follow_s;
		for(int j=0;j<pn[i].size();j++)
		{
			string s=pn[i][j];
			string ntt1="";
			for(int q=0;q<s.size();q++)
			{
				ntt1+=s[q];
				if(s[q+1]==' ')
					break;
			}
			if(find_index(ntt1)>=0)
			{
				int ind=find_index(ntt1);
				parsing_table[i][ind]=s;
			}
			else if(strcmp(ntt1.c_str(),"#")==0)
			{
				if(followsets.find(ntt)!=followsets.end())
					follow_s=followsets[ntt];
				for(int q=0;q<follow_s.size();q++)
				{
					int ind=find_index(follow_s[q]);
					parsing_table[i][ind]=s;
				}
			}
			else
			{
				if(firstsets.find(ntt1)!=firstsets.end())
					first_s=firstsets[ntt1];
				for(int q=0;q<first_s.size();q++)
				{
					int ind=find_index(first_s[q]);
					parsing_table[i][ind]=s;
				}
				
			}
		}
	}
	print_parsing_table();
}

void parse()
{
	pdstack.push("$");
	pdstack.push(nt[0]);
	int next_inp=0;
	int flag=0;
	while(pdstack.size()>1)
	{
		//cout<<"Next input index:"<<next_inp<<"\n";
		string inpt=remaining_input[next_inp];
		string ntt=pdstack.top();
		//cout<<"Stack top:"<<ntt<<"\n";
		int ind=find_index(inpt);
		if(ind<0)
		{
			flag=1;
			break;
		}
		if(find_index(ntt)>=0)
		{
			if(strcmp(inpt.c_str(),ntt.c_str())==0)
			{
				cout<<inpt<<"\t\t"<<ntt<<"\t\t\tMatch\n";
				next_inp++;
				pdstack.pop();
			}
			else
			{
				break;
			}
		}
		else
		{
			int a;
			for(a=0;a<nt.size();a++)
			{
				if(strcmp(ntt.c_str(),nt[a].c_str())==0)
				{
					break;
				}
			}
			string prd_used=parsing_table[a][ind];
			if(prd_used.size()<1)
			{
				break;
			}
			else if(strcmp(prd_used.c_str(),"#")==0)
			{
				pdstack.pop();
				cout<<inpt<<"\t\t"<<ntt<<"\t\t\t"<<ntt<<"-> #"<<"\n";
			}
			else
			{
				pdstack.pop();
				vector<string> tempstk;
				string tmk="";
				for(int a=0;a<prd_used.size();a++)
				{
					tmk+=prd_used[a];
					if(prd_used[a+1]==' ')
					{
						tempstk.push_back(tmk);
						tmk="";
						a++;
					}
				}
				tempstk.push_back(tmk);
				for(int a=tempstk.size()-1;a>=0;a--)
				{
					pdstack.push(tempstk[a]);
				}
				cout<<inpt<<"\t\t"<<ntt<<"\t\t\t"<<ntt<<"-> "<<prd_used<<"\n";
			}
		}
	}
	if(next_inp==remaining_input.size()-1 && pdstack.size()<=1)
	{
		cout<<"\nAccepted\n";
	}
	else if(flag==1)
	{
		cout<<"Not Accepted\n";
		cout<<"\nEncountered lexical error\n";
	}
	else
	{
		cout<<"Not Accepted\n";
		cout<<"Some syntax error has occured near word number "<<next_inp+1<<"\n";
	}
}

int main()
{
	fstream f1,f2,f3;
	f1.open("LL1_Grammar.txt",ios::in);
	f2.open("First.txt",ios::in);
	f3.open("Follow.txt",ios::in);
	if(f1.is_open())
	{
		string pr;
		while(getline(f1,pr)){
			add_to_prod(pr);
			//cout<<pr<<"\n";
		}
	}
	if(f2.is_open())
	{
		string str;
		while(getline(f2,str))
		{
			add_to_first(str);
		}
	}
	if(f3.is_open())
	{
		string str;
		while(getline(f3,str))
		{
			add_to_follow(str);
		}
	}
	f1.close();
	f2.close();
	f3.close();
	//print_production();
	make_parsing_table();
	f1.open("Tokenized_text.txt",ios::in);
	if(f1.is_open())
	{
		string str;
		while(getline(f1,str))
		{
			append_to_reamining(str);
		}
	}
	cout<<"\n\nParsing:\nCurrent Input\tCurrent Stacktop\tNext Action\n";
	parse();
	return 0;
}