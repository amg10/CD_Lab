#include<bits/stdc++.h>

using namespace std;

vector<string> productions;
map<char,vector<string>> prod;
char ch='Z';
string input="";
int consumed_pt=0;
int cnt=0;

void left_recursion_check(int n);
int fin_min_size(vector<string> v);
bool is_same_alp(vector<string> v, int w);
void left_factoring();
void create_productions_map();
bool parse(char nt);


int main()
{
	int n;
	cout<<"Enter number of productions:";
	cin>>n;
	productions.resize(n);
	cout<<"\nCertain conditions for entering:\n1.Nonterminals are single Capital alphabet and terminals are single lowercase alphabet\n2.No space in defining production\n3.The letter 'e' stands for epsilon.\n";
	cout<<"\nEnter each production on a new line without space(E->E+T|T):\n";
	for(int i=0;i<n;i++)
	{
		cin>>productions[i]; 
	}
	cout<<"Enter the string to be parsed(enter string of terminals only):\n";
	cin>>input;
	input+="$";
	cout<<"\nChecking for immediate left recursion and updating productions...\n";
	left_recursion_check(n);
	cout<<"Left factoring the productions and updating...\n";
	left_factoring();
	create_productions_map();
	if(parse(productions[0][0]))
	{
		if(consumed_pt>=(input.size()-1))
			cout<<"There input code is correct!!\n";
		else
			cout<<"Sorry the input string has errors\n";
	}
	else{
		cout<<"Sorry the input string has errors\n";
	}
	return 0;
}
bool parse(char nt)
{
	cnt++;
	if(cnt>1000)
	{
		cout<<"Exceeds limit of iterations allowed..Possible indirect left recursion!!\n";
		return false;
	}
	vector<string> v=prod[nt];
	if(v.size()==0)
	{
		cout<<"Productions not completely defined!!\n";
		exit(0);
	}
	int prev_index=consumed_pt;
	for(int q=0;q<v.size();q++)
	{
		string s=v[q];
		cout<<"Checking if production "<<s<<" works\n";
		int z;
		for(z=0;z<s.length();z++)
		{
			if(s[z]>='A' && s[z]<='Z')
			{
				cout<<"Encontered non terminal "<<s[z]<<endl;
				if(parse(s[z]))
				{
					prev_index=consumed_pt;
					continue;
				}
				else
					break;
			}
			else if(s[z]=='e')
			{
				cout<<"Encontered epsilon"<<endl;
				continue;
			}
			else
			{
				cout<<"Encontered terminal "<<s[z]<<endl;
				if(input[consumed_pt]==s[z])
				{
					consumed_pt++;
				}
				else
					break;
			}
		}
		if(z==s.length())
			return true;
		else
		{
			cout<<"Encountered mismatch!!Backtracking\n";
			consumed_pt=prev_index;
		}
	}
	return false;
}

void create_productions_map()
{
	for(int i=0;i<productions.size();i++)
	{
		char ch=productions[i][0];
		int index=3;
		string s="";
		for(;productions[i][index]!='\0';index++)
		{
			if(productions[i][index]=='|')
			{
				prod[ch].push_back(s);
				s="";
			}
			else
			{	
				s+=productions[i][index];
			}
			
		}
		prod[ch].push_back(s);
	}
}

void left_factoring()
{
	for(int i=0;i<productions.size();i++)
	{
		char nt=productions[i][0];
		int index=3;
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
	cout<<"\n";
}

void left_recursion_check(int n)
{
	for(int i=0;i<n;i++)
	{
		char nt=productions[i][0];
		int index=3;
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
			continue;
		}
		else if(c==p1.size())
		{
			cout<<"The production can't terminate.Illegalproduction!!\n";
			exit(0);
		}
		else
		{
			string up_s="";
			string new_prod="";
			up_s+=string(1,nt)+"->"+st[0]+string(1,ch);
			if(st.size()>1)
			{
				for(int k=1;k<st.size();k++)
				{
					up_s+="|"+st[k]+string(1,ch);
				}
			}
			productions[i]=up_s;
			new_prod=string(1,ch)+"->"+lr[0].substr(1,lr[0].length()-1)+string(1,ch);
			if(lr.size()>1)
			{
				for(int k=1;k<lr.size();k++)
				{	
					new_prod+="|"+lr[k].substr(1,lr[0].length()-1)+string(1,ch);
				}
			}
			ch--;
			new_prod+="|e";
			productions.push_back(new_prod);
		}
	}
	cout<<"Updated Productions:\n";
	for(int i=0;i<productions.size();i++)
	{
		cout<<productions[i]<<"\n";
	}
	cout<<"\n";
} 

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