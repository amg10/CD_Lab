#include <bits/stdc++.h>

using namespace std;

/***** Required Structures *****/
struct nfa_state
{
	vector<int> a[2],e;
	bool f=0;
};

struct dfa_state
{
	int a[2]={-1,-1};
	bool f=0;
};

/***** Global variables *****/
string orig_re;
vector<nfa_state> nfa;
vector<dfa_state> dfa;
stack<int> actv_states;
int nfa_size,dfa_size;
struct nfa_state new_nfa_st;
struct dfa_state new_dfa_st;

/***** Function Declarations *****/
void clear_up_global();
void stimulate_fa();
string add_concat(string Re);
int priority(char c);
string Re_to_postfixRe(string Re);
void character(int i_);
void union_op();
void concatenation_op();
void closure_op();
void postfixRe_to_nfa(string PRe);
void epsilon_closure(int state,set<int>&si);
set<int> state_change(int c,set<int>&si);
void nfa_to_dfa(set<int>&si,queue<set<int>>&que,int start_state);
void display_dfa();
void display_nfa();

/***** Main function *****/
int main()
{
	while(1){
	clear_up_global();
	string Re,PRe;
	cout<<"\nEnter the Regular Expression: ";
	cin>>Re;
	orig_re=Re;
	Re= add_concat(Re);
	PRe= Re_to_postfixRe(Re);
	postfixRe_to_nfa(PRe);
	
	int final_state=actv_states.top();actv_states.pop();
    int start_state=actv_states.top();actv_states.pop();
    nfa[final_state].f=1;
	
	set<int> si;
	queue<set<int>> que;
	nfa_to_dfa(si,que,start_state);
	
	while(1){
		int opt;
		cout<<"\nInput Regular Expression:"<<orig_re;
		cout<<"\nSelect the option required:";
		cout<<"\n1.Display nfa";
		cout<<"\n2.Display dfa";
		cout<<"\n3.Stimulate";
		cout<<"\n4.Enter other Regular Expression";
		cout<<"\n5.Quit\n";
		cin>>opt;
		if(opt==4)
			break;
		else
		{	switch(opt)
			{
				case 1: display_nfa();
						cout<<"The start state is:"<<start_state<<"\n";
						break;
				case 2: display_dfa();
						cout<<"The start state is: 0\n";
						break;
				case 3: stimulate_fa();
						break;
				default: exit(EXIT_SUCCESS); 
			}
		}
	}
	}
	return 0;
}

/***** Function to initialise global variables *****/
void clear_up_global()
{
	orig_re="";
	nfa.clear();
	dfa.clear();
	while(!actv_states.empty())
	{
		actv_states.pop();
	}
	nfa_size=0;
	dfa_size=0;
}

/***** This function inserts concatination symbol '.' into RE *****/
string add_concat(string Re)
{
	string cre="";
	for(int i=0;i<Re.size();i++)
	{
		cre+=Re[i];
		if(i+1<Re.size())
		{
			if(Re[i]!= '(' && Re[i]!='+' && Re[i+1]!= ')' && Re[i+1]!='+' && Re[i+1]!='*')
			{
				cre+='.';
			}
		}
	}
	return cre;
}


/***** This function coverts RE to postfix expression *****/
string Re_to_postfixRe(string Re)
{
	string pf="";
	stack <char> op;
	for(int i=0;i<Re.size();i++)
	{
		switch(Re[i])
		{
			case '0' :
			case '1' :
				pf+=Re[i];
				break;
			case '(':
				op.push(Re[i]);
				break;
			case ')':
				while(op.top()!='(')
				{
					pf+=op.top();
					op.pop();
				}
				op.pop();
				break;
			default:
				while(!op.empty())
				{
					char c;
					c=op.top();
                    if(priority(c)>=priority(Re[i])){
                        pf+=op.top();
                        op.pop();
                    }
                    else break;
				}
				op.push(Re[i]);
		}
		
	}
	while(!op.empty())
	{
		pf+=op.top();
		op.pop();
	}
	return pf;
}

/***** The function tells the priority of operation *****/
int priority(char c)
{
	switch(c)
	{
		case '*': return 3;
		case '.': return 2;
		case '+' : return 1;
		default: return 0;
	}
}

/***** This function creates nfa from Regular Expression *****/
void postfixRe_to_nfa(string PRe)
{
	for(int i=0;i<PRe.size();i++)
	{
		switch(PRe[i])
		{
			case '0':
			case '1':
				character(PRe[i]-'0');
				break;
			case '*':
				closure_op();
				break;
			case '.':
				concatenation_op();
				break;
			case '+':
				union_op();
		}
	}
}

/***** Function creates character *****/
void character(int i)
{
	nfa.push_back(new_nfa_st);
    nfa.push_back(new_nfa_st);
    nfa[nfa_size].a[i].push_back(nfa_size+1);
    actv_states.push(nfa_size);
    nfa_size++;
    actv_states.push(nfa_size);
    nfa_size++;
}

/***** Function implements Closure Operation(*) *****/ 
void closure_op()
{
	nfa.push_back(new_nfa_st);
    nfa.push_back(new_nfa_st);
    int b = actv_states.top();
    actv_states.pop();
    int a = actv_states.top();
    actv_states.pop();
    nfa[nfa_size].e.push_back(a);
    nfa[nfa_size].e.push_back(nfa_size+1);
    nfa[b].e.push_back(a);
    nfa[b].e.push_back(nfa_size+1);
    actv_states.push(nfa_size);
    nfa_size++;
    actv_states.push(nfa_size);
    nfa_size++;
}

/***** Function implements Concatination Operation *****/
void concatenation_op()
{
	int d = actv_states.top(); actv_states.pop();
    int c = actv_states.top(); actv_states.pop();
    int b = actv_states.top(); actv_states.pop();
    int a = actv_states.top(); actv_states.pop();
    nfa[b].e.push_back(c);
    actv_states.push(a);
    actv_states.push(d);
}

/***** FUnction implemets the Union Operation *****/
void union_op()
{
	nfa.push_back(new_nfa_st);
    nfa.push_back(new_nfa_st);
    int d = actv_states.top(); actv_states.pop();
    int c = actv_states.top(); actv_states.pop();
    int b = actv_states.top(); actv_states.pop();
    int a = actv_states.top(); actv_states.pop();
    nfa[nfa_size].e.push_back(a);
    nfa[nfa_size].e.push_back(c);
    nfa[b].e.push_back(nfa_size+1);
    nfa[d].e.push_back(nfa_size+1);
    actv_states.push(nfa_size);
    nfa_size++;
    actv_states.push(nfa_size);
    nfa_size++;
}

/***** Converts nfa to dfa *****/
void nfa_to_dfa(set<int>&si,queue<set<int> >&que,int start_state){
    map<set<int>, int> mp;
    mp[si]=-1;
    set<int> temp1;
    set<int> temp2;
    int ct=0;
    si.clear();
    si.insert(0);
    epsilon_closure(start_state,si);
    if(mp.count(si)==0){
        mp[si]=ct++;
        que.push(si);
    }
    int p=0;
    bool f1=false;
    while(que.size()!=0){
        dfa.push_back(new_dfa_st);
        si.empty();
        si=que.front();
        f1=false;
        for (set<int>::iterator it=si.begin(); it!=si.end(); ++it){
            if(nfa[*it].f==true)
                f1=true;
        }
        dfa[p].f=f1;
        temp1=state_change(1,si);
        si=temp1;
        for (set<int>::iterator it=si.begin(); it!=si.end(); ++it){
            epsilon_closure(*it,si);
        }
        if(mp.count(si)==0){
            mp[si]=ct++;
            que.push(si);
            dfa[p].a[0]=ct-1;
        }
        else{
            dfa[p].a[0]=mp.find(si)->second;
        }
        temp1.clear();

        si=que.front();
        temp2=state_change(2,si);
        si=temp2;
        for (set<int>::iterator it=si.begin(); it!=si.end(); ++it){
            epsilon_closure(*it,si);
        }
        if(mp.count(si)==0){
            mp[si]=ct++;
            que.push(si);
            dfa[p].a[1]=ct-1;
        }
        else{
            dfa[p].a[1]=mp.find(si)->second;
        }
        temp2.clear();
        que.pop();
        p++;
    }
    for(int i=0;i<p;i++){
        if(dfa[i].a[0]==-1)dfa[i].a[0]=p;
        if(dfa[i].a[1]==-1)dfa[i].a[1]=p;
    }
    dfa.push_back(new_dfa_st);
    dfa[p].a[0]=p;
    dfa[p].a[1]=p;
}

/***** Function to find epsilon closure of the state provided as argument *****/
void epsilon_closure(int state,set<int>&si){
    for(unsigned int i=0;i<nfa[state].e.size();i++){
        if(si.count(nfa[state].e[i])==0){
            si.insert(nfa[state].e[i]);
            epsilon_closure(nfa[state].e[i],si);
        }
    }
}

/***** Replace with states including epsilon closure *****/
set<int> state_change(int c,set<int>&si){
    set<int> temp;
    if(c==1){
        for (std::set<int>::iterator it=si.begin(); it!=si.end(); ++it){
            for(unsigned int j=0;j<nfa[*it].a[0].size();j++){
                temp.insert(nfa[*it].a[0][j]);
            }
        }
    }
    else{
        for (std::set<int>::iterator it=si.begin(); it!=si.end(); ++it){
            for(unsigned int j=0;j<nfa[*it].a[1].size();j++){
                temp.insert(nfa[*it].a[1][j]);
            }
        }
    }
    return temp;
}

/***** Function to display nfa *****/
void display_nfa()
{
    cout<<endl<<endl;
    cout<<"\n------------------------------------------------------------------------\n";
    cout<<"State\t|\t0\t|\t1\t|\teps\t|Accepting State|"<<endl;
    cout<<"------------------------------------------------------------------------\n";
    for(int i=0; i<nfa.size(); i++)
    {
        cout<<i<<"\t|\t";
        for(int j=0; j<nfa[i].a[0].size(); j++)cout<<nfa[i].a[0][j]<<' ';
        cout<<"\t|\t";
        for(int j=0; j<nfa[i].a[1].size(); j++)cout<<nfa[i].a[1][j]<<' ';
        cout<<"\t|\t";
        for(int j=0; j<nfa[i].e.size(); j++)cout<<nfa[i].e[j]<<' ';
        cout<<"\t|\t";
        if(nfa[i].f)cout<<"Yes"; else cout<<"No";
        cout<<"\t|\n";
    }
    cout<<"------------------------------------------------------------------------\n";
}

/**** Function to display dfa *****/
void display_dfa(){
    cout<<endl;
    cout<<"\n---------------------------------------------------------"<<endl;
    cout<<"STATE\t|\t"<<"0"<<"\t|\t"<<"1"<<"\t|"<<"Accepting State"<<"\t|"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
    for(int i=0;i<dfa.size();i++){
        cout<<i<<"\t|\t"<<dfa[i].a[0]<<"\t|\t"<<dfa[i].a[1]<<"\t|\t"<<dfa[i].f<<"\t|"<<endl;
    }
    cout<<"---------------------------------------------------------"<<endl;
}

/***** Function stimulates the Automata *****/
void stimulate_fa()
{
	cout<<"\nEnter the string to be stimulated:";
	string str="";
	cin>>str;
	if(str=="e")
	{
		if(dfa[0].f==1)
			cout<<"\nResult:Accepted\n";
		else
			cout<<"\nResult:Rejected\n";
		return;
	}
	int current_st=0,next_st;
	cout<<"-----------------------------------------"<<endl;
	cout<<"Input\t|Current State\t|Next State\t|\n";
	cout<<"-----------------------------------------"<<endl;
	for(int i=0;i<str.size();i++)
	{
		if((str[i]-'0')==0)
			next_st=dfa[current_st].a[0];
		else if((str[i]-'0')==1)
			next_st=dfa[current_st].a[1];
		else 
			next_st=current_st;
		cout<<str[i]<<"\t|\t"<<current_st<<"\t|\t"<<next_st<<"\t|\n";
		current_st=next_st;
	}
	cout<<"-----------------------------------------"<<endl;
	cout<<"Result:";
	if(dfa[current_st].f==0)
		cout<<"Rejected\n";
	else
		cout<<"Accepted\n";
}