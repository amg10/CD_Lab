#include<bits/stdc++.h>

using namespace std;

/*****Required structures*****/
struct item
{
	string lhs;
	vector<string> rhs;
	int point_loc;
	vector<string> look_a;
};

struct state
{
	vector<item> con;
	vector<string> transition;
};

vector<string> nt;
vector<vector<string>> pn;
vector<state> dfa;
vector<string> terminals={"id","=","*","$"};
vector<vector<string>> parsing_tb;

/*****Reading Productions***/
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
	prds.push_back(temp);
	pn.push_back(prds);
}
void read_productions()
{
	fstream f1;
	f1.open("Grammar.txt",ios::in);
	if(f1.is_open())
	{
		string pr;
		while(getline(f1,pr)){
			add_to_prod(pr);
		}
	}
}
/*****Printing Productions***/
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
/***Making states***/
vector<int> get_state_item(string s)
{
	vector<int> temp;
	string t;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]==' ')
		{
			stringstream numb_s(t); 
			int no_s = 0; 
			numb_s >> no_s;
			temp.push_back(no_s);
			t="";
		}
		t+=s[i];
	}
	stringstream numb_s(t); 
	int no_s = 0; 
	numb_s >> no_s;
	temp.push_back(no_s);
	return temp;
}

void add_to_state(string s, int n)
{
	struct item new_item;
	int i;
	string temp;
	for(i=0;i<s.size();i++)
	{
		if(s[i]=='-' && s[i+1]=='>')
		{
			new_item.lhs=temp;
			i=i+2;
			temp="";
			break;
		}
		else
			temp+=s[i];
	}
	vector<string> tt;
	for(;i<s.size();i++)
	{
		if(s[i]==',')
		{
			tt.push_back(temp);
			i++;
			temp="";
			break;
		}
		if(s[i]==' ')
		{
			tt.push_back(temp);
			temp="";
		}
		else
			temp+=s[i];
	}
	new_item.rhs=tt;
	for(;i<s.size();i++)
	{
		if(s[i]==',')
		{
			stringstream numb_s(temp); 
			int pl = 0; 
			numb_s >> pl;
			new_item.point_loc=pl;
			i++;
			temp="";
			break;
		}
		temp+=s[i];
	}
	for(;i<s.size();i++)
	{
		if(s[i]=='|')
		{
			new_item.look_a.push_back(temp);
			i++;
			temp="";
		}
		temp+=s[i];
	}
	new_item.look_a.push_back(temp);
	dfa[n].con.push_back(new_item);
}

void make_states()
{
	fstream f1;
	f1.open("dfa_states.txt",ios::in);
	if(f1.is_open())
	{
		string pr;
		getline(f1,pr);
		stringstream numb_s(pr); 
		int no_s = 0; 
		numb_s >> no_s;
		dfa.resize(no_s);
		while(getline(f1,pr)){
			vector<int>i_no_stt_no=get_state_item(pr);
			for(int i=0;i<i_no_stt_no[1];i++)
			{
				getline(f1,pr);
				add_to_state(pr,i_no_stt_no[0]);
			}
		}
	}
}

/***Making DFA***/
void add_transition()
{
	int strt,en;
	string label;
	fstream f1;
	f1.open("dfa.txt",ios::in);
	for(int i=0;i<dfa.size();i++)
	{
		dfa[i].transition.resize(dfa.size());
	}
	if(f1.is_open())
	{
		string pr;
		while(getline(f1,pr))
		{
			string t="";
			int i=0;
			for(i=0;i<pr.length();i++)
			{
				if(pr[i]==' ')
				{
					strt=stoi(t);
					t="";
					i++;
					break;
				}
				t+=pr[i];
			}
			for(;i<pr.length();i++)
			{
				if(pr[i]==' ')
				{
					en=stoi(t);
					t="";
					i++;
					break;
				}
				t+=pr[i];
			}
			for(;i<pr.length();i++)
			{
				t+=pr[i];
			}
			label=t;
			dfa[strt].transition[en]=label;
			label="";
		}
	}
}

/***Printing dfa made***/
void print_item(int i,int j)
{
	string str;
	item temp=dfa[i].con[j];
	str=temp.lhs+"->";
	for(int k=0;k<temp.rhs.size();k++)
	{
		if(temp.point_loc==k)
		{
			str+=".";
		}
		str+=temp.rhs[k];
	}
	if (temp.point_loc==temp.rhs.size())
		str+=".";
	str+=",";
	for(int k=0;k<temp.look_a.size();k++)
	{
		str+=temp.look_a[k];
		if(k!=temp.look_a.size())
			str+="|";
	}
	str+="\n";
	cout<<str;
}
void print_dfa()
{
	for(int i=0;i<dfa.size();i++)
	{
		cout<<"State "<<i<<"\n";
		for(int j=0;j<dfa[i].con.size();j++)
		{
			print_item(i,j);
		}
		cout<<"\nTransitions for state "<<i<<":\n";
		for(int k=0;k<dfa[i].transition.size();k++)
		{
			if(dfa[i].transition[k].size()>0)
			{
				cout<<"To State "<<k<<" on encountering "<<dfa[i].transition[k]<<"\n";
			}
		}
		cout<<"\n";
	}
	
}

/***Making table ***/
int find_index(string str)
{
	for(int i=0;i<terminals.size();i++)
	{
		if(strcmp(str.c_str(),terminals[i].c_str())==0)
			return i;
	}
	int ind=terminals.size();
	for(int i=0;i<nt.size();i++)
	{
		if(strcmp(str.c_str(),nt[i].c_str())==0)
			return (ind+i);
	}
return -1;	
}

void make_table()
{
	parsing_tb.resize(dfa.size());
	for(int i=0;i<dfa.size();i++)
	{
		parsing_tb[i].resize(nt.size()+terminals.size());
	}
	for(int i=0;i<dfa.size();i++)
	{
		for(int j=0;j<dfa[i].transition.size();j++)
		{
			if(dfa[i].transition[j].size()>0)
			{
				int ind=find_index(dfa[i].transition[j]);
				if(ind<terminals.size() && ind>=0)
					parsing_tb[i][ind]="Shift "+to_string(j);
				else
					parsing_tb[i][ind]=to_string(j);
			}
		}
		for(int j=0;j<dfa[i].con.size();j++)
		{
			if(dfa[i].con[j].point_loc==dfa[i].con[j].rhs.size())
			{
				for(int k=0;k<dfa[i].con[j].look_a.size();k++)
				{
					item temp=dfa[i].con[j];
					int ind=find_index(temp.look_a[k]);
					if(strcmp(temp.lhs.c_str(),nt[0].c_str())==0 && ind>=0)
					{
						parsing_tb[i][ind]="Accept";
					}
					else
					{
						string s="R ("+temp.lhs+"->";
						for(int l=0;l<temp.rhs.size();l++)
						{
							s+=temp.rhs[l];
						}
						s+=")";
						parsing_tb[i][ind]=s;
					}
				}
			}
		}
	}
}

/***Printing table***/
void print_table()
{
	cout<<"\nTable:\n";
	cout<<"State\t|";
	for(int i=0;i<terminals.size();i++)
	{
		cout<<terminals[i]<<"\t|";
	}
	for(int i=0;i<nt.size();i++)
	{
		cout<<nt[i]<<"\t|";
	}
	cout<<"\n";
	for(int i=0;i<parsing_tb.size();i++)
	{
		cout<<i<<"\t|";
		for(int j=0;j<parsing_tb[i].size();j++)
		{
			if(parsing_tb[i][j].size()>5)
				cout<<parsing_tb[i][j]<<"|";
			else
				cout<<parsing_tb[i][j]<<"\t|";
		}
		cout<<"\n";
	}
}

int main()
{
	read_productions();
	print_production();
	make_states();
	add_transition();
	print_dfa();
	make_table();
	print_table();
	return 0;
}