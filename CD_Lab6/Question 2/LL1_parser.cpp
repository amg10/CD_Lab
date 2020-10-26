#include<bits/stdc++.h>

using namespace std;

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
vector<state> dfa;
vector<string> terminals;
vector<vector<string>> parsing_tb;

typedef long long ll;
typedef long double ld;
typedef double db; 
typedef string str; 
 
typedef pair<int,int> pi;
typedef pair<ll,ll> pl; 
typedef pair<db,db> pd; 
typedef pair<str, str> ps;
 
typedef vector< int>  vi; 
typedef vector<ll> vl; 
typedef vector<db> vd; 
typedef vector<str> vs; 
typedef vector<pi> vpi;
typedef vector<pl> vpl; 
typedef vector<pd> vpd; 
typedef  set <  pair < pair< string , vector <  string  > >, pair <  vector< string >  , int > > > spv;
#define mp make_pair
#define F first
#define S second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end() 
#define rsz resize
#define ins insert 
#define ft front() 
#define bk back()
#define pf push_front 
#define pb push_back
#define eb emplace_back 
#define lb lower_bound 
#define ub upper_bound 
 
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define trav(a,x) for (auto& a: x)

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define trav(a,x) for (auto& a: x)
 
const int Mod = 1e9 + 7; // 998244353;
const int MX = 2e5+5; 
const ll inf = 1e18; 
const ld PI = acos((ld)-1);
const int xd[4] = {1,0,-1,0}, yd[4] = {0,1,0,-1}; 
template<class T> void remDup(vector<T>& v) { 
    sort(all(v)); v.erase(unique(all(v)),end(v)); }
 
// INPUT
template<class A> void re(complex<A>& c);
template<class A, class B> void re(pair<A,B>& p);
template<class A> void re(vector<A>& v);
template<class A, size_t SZ> void re(array<A,SZ>& a);
 
template<class T> void re(T& x) { cin >> x; }
void re(db& d) { str t; re(t); d = stod(t); }
void re(ld& d) { str t; re(t); d = stold(t); }
template<class H, class... T> void re(H& h, T&... t) { re(h); re(t...); }
 
template<class A> void re(complex<A>& c) { A a,b; re(a,b); c = {a,b}; }
template<class A, class B> void re(pair<A,B>& p) { re(p.f,p.s); }
template<class A> void re(vector<A>& x) { trav(a,x) re(a); }
template<class A, size_t SZ> void re(array<A,SZ>& x) { trav(a,x) re(a); }

string remove_space(string s)
{
    string changed = "";
    for(int i =0;i<s.length();i++)
        if(s[i] != ' ')
            changed+=s[i];
    return changed;
}
string change(char x) 
{ 
    string s(1, x); 
    return s;    
} 
map< string , vector< string  >  >  grammar;
vector<pair<string, vector<string>> > productions;
map <  pair<string, vector<string>> , int  > prod_number;
map< string , vector< string  > > first;
vector< string > w;
int idcnt = 0;
map < spv ,  int  > m;
int cnt = 2;
set < pair< int, string > > graph[1001];
vector <  set <  pair < pair< string , vector <  string  > >, pair <  vector< string >  , int > > > > nodes;  
set < string >  all_char;
vector  <  vector < vector < string  > > > action;
vector  <  vector < vector < string  > > > got;
vector< string > terminal;
vector< string > nonterminal;

void getProductions()
{
    for(auto g : grammar)
    {
        vector<string> temp;
        for(auto s : g.S)
        {
            if(s == "|")
            {
                productions.pb({g.F, temp});
                temp.clear();
            }
            else{
                temp.pb(s);
            }
        }
        productions.pb({g.F, temp});
    }
}

vector<string> split(const string& str, const string& delim){
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do{
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

void remove_left_grammar( string s)
{
    if(grammar.find(s) != grammar.end())
    {
        int ch = 1;
        vector< string > x;
        vector< string > y;
        
        string temp = s + "'";
            
         for(string str1 : grammar[s])
         {
                
                if(str1 == "|")
                {
                    if(ch == 2)
                    {
                        x.pb(temp);
                        x.pb("|");
                            
                    }
                    else
                    {
                        y.pb(temp);
                        y.pb(str1);
                    }
                    ch = 1;
                }
                else if(ch == 2)
                {
                    x.pb(str1); 
                }
                else if(ch == 1 && str1 == s)
                {
                    ch = 2;
                }
                else
                {
                    y.pb(str1);
                    ch = 0;
                }
         }

         if(x.size() == 0)
            return;
         if(x[x.size()-1] != "|")
            x.pb("|");
         if(y.size()  < 1)
         {
            cout<<"\nLEFT recursion found without a terminal character \n";
            return;
         }
         if(y[y.size()-1] == "|")
            y.erase(y.begin() + y.size()-1);
         else
            y.pb(temp);
         grammar[s].clear();        
         grammar[s].assign(all(y));
         x.pb("e");
         grammar[temp].assign(all(x));
    }
}
int make_grammar(string s)
{
    vector< string > v = split(s, " ");
    
    vector< string>  temp;
    if(v.size()  < 2)
    {
        cout<<"Incomplete Grammer\n";
        return  0;
    }
    FOR(i, 2,v.size())
    {
        temp.pb(v[i]);
    }
    grammar[v[0]].assign(all(temp));
    remove_left_grammar(v[0]);
    return 1;
}
void print_all_grammar()
{
    cout<<"\nPrinting Complete Grammer: \n";
    for(auto itr : grammar)
    {
        cout<<itr.F<<"  -----> ";
        for(string s : itr.S)
            cout<<s<<" ";
        cout<<"\n";
    }
    cout<<"\n";
}

vector< vector< string > > break_string( vector< string > x)
{
    vector< vector< string  > > temp;
    vector<string> x1;
    for(string s1 : x)
    {
        if(s1 == "|")
        {
            temp.pb(x1);
            x1.clear();
        }
        else
            x1.pb(s1);
    }
    temp.pb(x1);
    return temp;
}
vector<string >  find_first( vector< string  > x , string sym, bool check_wh)
{
    if(first.find(sym) != first.end())
        return first[sym];
    
    auto  temp = break_string(x);
    vector< string > ans;

    for(auto z : temp)
    {
        int pt = 0;
        while(pt < z.size())
        {
            bool ch = 0;
            if(grammar.find(z[pt]) != grammar.end())
            {
                vector<  string  >  x1 = find_first( grammar[z[pt]] , z[pt], check_wh);
                for(string q : x1)
                    if(q == "e")
                        ch = 1;
                    else
                        ans.pb(q);
                if(!ch)
                    break;
                pt++;
            }
            else
            {
                ans.pb(z[pt]);
                break;
            }
        }
    }
    if(check_wh)
    first[sym].assign(all(ans));
    return ans;
}

void psp(int l)
{
    for(int i =0;i<l;i++)
        cout<<" ";
}


vector<pair<int, int>> findProdnums(string nt){
    vector<pair<int, int>> res;
    for(int i = 0;i<productions.size();i++){
        if(productions[i].F == nt){
            res.pb({i, 0});
        }
    }
    return res;
}
void find_closure(spv &temp)
{
    int prev  = 0;
    while(1)
    {
        prev = temp.size();
        for(auto itr : temp)
        {
            if(itr.S.S < itr.F.S.size())
            {
                for(auto g: productions)
                {
                    if(g.F == itr.F.S[itr.S.S])
                    {
                        vector <  string  > first;
                        first.assign(itr.F.S.begin() + itr.S.S+1, itr.F.S.end());
                        first.insert(first.end(), itr.S.F.begin(), itr.S.F.end());
                        temp.insert( { {g.F, g.S} , {find_first(first, "kabkcabc", 0), 0}});
                    }
                }
            }
        }
        if(prev == temp.size())
            break;

    }
}

void makeDFA()
{   
    for(auto it1 :  nodes)
    {
        for(auto non_ter : all_char)
        {
            spv temp; 
            for(auto itr2 : it1)
            {
                if(itr2.S.S < itr2.F.S.size())
                {
                    if(itr2.F.S[itr2.S.S] == non_ter)
                    {
                        temp.insert({ {itr2.F.F, itr2.F.S }, {itr2.S.F, itr2.S.S+1}});
                    }
                }
            }
            if(temp.size() == 0)
                continue;
            find_closure(temp);
            if(m[temp] == 0)
            {
                nodes.pb(temp);
                m[temp] = cnt;
                cnt++;
            }
            graph[m[it1]].insert( { m[temp],  non_ter });
        
        }
    }
}

int find_terminal(string x)
{
    for(int i =0;i<terminal.size();i++)
        if(terminal[i] == x)
            return i;
    return -1;
}
int find_nonterminal(string x)
{
    for(int i =0;i<nonterminal.size();i++)
        if(nonterminal[i] == x)
            return i;
    return -1;

}
void psg(int cnt)
{
    for(int i =0;i<cnt;i++)
        cout<<"-";
}
void print_parse_table()
{

    int sum = terminal.size() + nonterminal.size();
	cout<<"Table:\n\n";
    cout<<"|"; psp(2);
    cout<<"State ";
    psp(4);
    for(string i  : terminal)
    {
        cout<<"|";
        psp(2);
        cout<<i<<" ";
        psp(7- i.size());
    }
    cout<<"|";
    for(string i  : nonterminal)
    {
        cout<<"|";
        psp(2);
        cout<<i<<" ";
        psp(7- i.size());
    }
    cout<<"|";
    
    cout<<"\n";
    for(int i =0;i< nodes.size();i++)
    {
        cout<<"|";
        psp(3);
        cout<<i+1<<" ";
        if(i > 8) psp(6);
        else  psp(7);
        for(int j =0;j<action[i].size();j++)
        {
            cout<<"|";
            psp(2);
            cnt = 8;
            for(string k : action[i][j])
            {
                string temp =k;
                if(k == "r1")
                    temp ="Accept";
                cout<<temp<<"  ";
                cnt-= (temp.length() +2);
            }
            psp(cnt);
        }
        cout<<"|";
        for(int j =0;j<got[i].size();j++)
        {
            cout<<"|";
            psp(2);
            cnt = 8;
            for(string k : got[i][j])
            {
                string temp = k;
                cout<<temp<<"  ";
                cnt-= (temp.length() +2);
            }
            psp(cnt);
        }
        cout<<"|\n";
    }
    cout<<"\n\n";
}

void make_table()
{
    map <  int ,  pair < vector < string > ,  int > > reduce_map;

    for(int  z = 0; z < productions.size(); z++)
    {
        prod_number[productions[z]] = z+1; 
    }
    for(int i = 0; i<nodes.size();i++)
    {

        for(auto j : nodes[i])
        {
            if(j.S.S == j.F.S.size() || j.F.S[0] == "e")
            {
                reduce_map[i+1].F.insert(reduce_map[i+1].F.begin(), all(j.S.F));
                reduce_map[i+1].S =  prod_number[{j.F.F, j.F.S}];
            }
        }
    }

    for(string c : all_char)
    {
        if(grammar.find(c) != grammar.end())
            nonterminal.pb(c);
        else
            terminal.pb(c);
    }
    terminal.pb("$");
    action.resize(cnt);
    got.resize(cnt);
    for(int i =0;i<cnt;i++)
    {
        action[i].resize(terminal.size());
        got[i].resize(nonterminal.size());
    }

    for(int i =0;i <cnt;i++)
    {

        if(reduce_map.find(i+1) != reduce_map.end())
        {
            for(auto z : reduce_map[i+1].F)
            {
                string x = "r" + to_string(reduce_map[i+1].S);
                action[i][find_terminal(z)].pb(x);
            }
        }
        
        else
        {
            for(auto x : graph[i+1])
            {
                if(find_terminal(x.S) != -1)
                action[i][find_terminal(x.S)].pb(to_string(x.F));
                else
                got[i][find_nonterminal(x.S)].pb(to_string(x.F));
            }
        }          
    }
}

void transform_to_structured()
{
	dfa.resize(nodes.size()+1);
	for(auto node_itr : nodes)
	{
		int i=m[node_itr];
		state st_new;
		for(auto svp_itr : node_itr)
		{
			
			item it_new;
			it_new.lhs=svp_itr.F.F;
			it_new.rhs=svp_itr.F.S;
			
			it_new.look_a=svp_itr.S.F;
			it_new.point_loc=svp_itr.S.S;
			st_new.con.push_back(it_new);
		}
		st_new.transition.resize(dfa.size());
		for(auto x : graph[i])
		{
			st_new.transition[x.F]=x.S;
		}
		dfa[i]=st_new;
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
	for(int i=1;i<dfa.size();i++)
	{
		cout<<"State "<<i<<"\n";
		for(int j=0;j<dfa[i].con.size();j++)
		{
			print_item(i,j);
		}
		cout<<"\nTransitions for state "<<i<<":\n";
		for(int k=1;k<dfa[i].transition.size();k++)
		{
			if(dfa[i].transition[k].size()>0)
			{
				cout<<"To State "<<k<<" on encountering "<<dfa[i].transition[k]<<"\n";
			}
		}
		cout<<"\n";
	}
	
}

/***Printing table***/
void print_table()
{
	cout<<"\nTable:\n";
	cout<<"State\t|";
	for(int i=0;i<terminal.size();i++)
	{
		cout<<terminal[i]<<"\t|";
	}
	for(int i=0;i<nonterminal.size();i++)
	{
		cout<<nonterminal[i]<<"\t|";
	}
	cout<<"\n";
	for(int i=1;i<parsing_tb.size();i++)
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
    string s;
	cout<<"Enter Productions:(Ctr+D to end):\n";
    while( cin>>s)
    {
        string input1;
        getline(cin, input1);
        s = s+input1;
        if(!make_grammar(s))
            break;
    }
    print_all_grammar();
    productions.pb({"S''", {"S"}});
    getProductions();
    spv temp;
    grammar["S''"].pb("S");
    temp.insert({{"S''", {"S"}}, {{"$"},0}});
    find_closure(temp);
    m[temp] = 1;
    nodes.pb(temp);
    for(auto x : productions)
    {
        all_char.insert(x.F);
        for(auto y : x.S)
            all_char.insert(y);
    }
    if(all_char.find("e") != all_char.end())
    all_char.erase(all_char.find("e"));
    int prev  = 0;
    while(1)
    {
        prev = nodes.size();
        makeDFA();
        if(prev  == nodes.size())
            break;
    }
    makeDFA();
	transform_to_structured();
	print_dfa();
    make_table();
    print_parse_table();
}