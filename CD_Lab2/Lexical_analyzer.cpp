#include<bits/stdc++.h>

using namespace std;

/*** Global variable ***/
bool invalid_num=false;

/*** Functions ***/

/*** Function tells if character is a digit ***/
bool is_digit(char ch)
{
	if(ch>='0'&&ch<='9')
		return true;
	else
		return false;
}

/*** Function tells if character is a letter ***/
bool is_letter(char ch)
{
	if((ch>='a'&& ch<='z')||(ch>='A'&& ch<='Z'))
		return true;
	else 
		return false;
}

/*** Function tells if string is a valid id ***/
bool is_valid_id(string str)
{
	int i;
	if(is_letter(str[0]))
	{
		for(i=1;i<str.length();i++)
		{	
			if(is_letter(str[i])||is_digit(str[i]))
				continue;
			else 
				break;
		}
		if(i<str.length())
			return false;
	}
	else
		return false;
	return true;
}

/*** Function tells if string is a valid number ***/
bool is_valid_num(string str)
{
	int gotdecimal=0,gotexponen=0,gotsign=0;
	if(is_digit(str[0]))
	{
		for(int i=0;i<str.length();i++)
		{
			if(str[i]=='.')
			{
				if(gotdecimal==1)
				{
					invalid_num=true;
					return false;
				}
				gotdecimal=1;
			}
			else if(str[i]=='E')
			{
				if(gotexponen==1)
				{
					invalid_num=true;
					return false;
				}
				gotexponen=1;
			}
			else if(str[i]=='+'||str[i]=='-')
			{
				if(gotsign==1)
				{
					invalid_num=true;
					return false;
				}
				gotsign=1;
			}
		}
		return true;
	}
	else
		return false;
}

/*** Function that finds and prints the tokens ***/
void get_tokens(string in_code)
{
	string temp="";
	vector<string> tokens;
	int flag=0;
	for(int i=0;i<in_code.length();i++)
	{
		temp+=in_code[i];
		if(temp.compare(" ")==0)
		{
			temp="";
			continue;
		}
		if(temp=="if" ||temp=="else" ||temp=="then")
		{
			if(in_code[i+1]==' ')
			{
				tokens.push_back("("+temp+","+temp+")");
				temp="";
				i++;
			}
		}
		else if(temp==">"||temp=="<"||temp=="=")
		{
			if(temp==">" && in_code[i+1]=='=')
			{	temp+=in_code[i+1];
				i++;
			}
			else if(temp=="<" && ((in_code[i+1]=='=')||(in_code[i+1]=='>')))
			{	
				temp+=in_code[i+1];
				i++;
			}	
			if(is_letter(in_code[i+1]) || is_digit(in_code[i+1]) || in_code[i+1]==' ')
			{
				tokens.push_back("(relop,"+temp+")");
				temp="";
			}
			else
				flag=1;
		}
		else if(is_valid_id(temp))
		{
			if(!is_letter(in_code[i+1]) && !is_digit(in_code[i+1]))
			{
				tokens.push_back("(id,"+temp+")");
				temp="";
			}
			else
				continue;
		}
		else if(is_valid_num(temp))
		{
			if(temp[temp.size()-1]=='.' || temp[temp.size()-1]=='E' || temp[temp.size()-1]=='+' ||temp[temp.size()-1]=='-')
			{
				if(temp[temp.size()-1]=='E' && (in_code[i+1]=='+' ||in_code[i+1]=='-'))
					flag=0;
				else if(!is_digit(in_code[i+1]))
					flag=1;
			}
			
			else if(in_code[i+1]==' ')
			{
				tokens.push_back("(number,"+temp+")");
				temp="";
			}
			else
				continue;
		}
		else
		{
			if(invalid_num==true)
			{
				flag=1;
				invalid_num=false;
			}
			else
			{
				while(!is_digit(in_code[i])|| !is_letter(in_code[i]))
				{
					i++;
					temp+=in_code[i];
				}
				tokens.push_back("(unidentified,"+temp+")");
				temp="";
			}
		}
		if(flag==1)
		{
			while(in_code[i]!=' ')
			{
				i++;
				temp+=in_code[i];
			}
			tokens.push_back("(unidentified,"+temp+")");
			temp="";
			flag=0;
		}
	}
	
	cout<<"\nThe tokens are as follows:\n";
	for(int i=0;i<tokens.size();i++)
	{
		cout<<tokens[i]<<endl;
	}
}

/*** Main function ***/
int main()
{
	string input_str="";
	cout<<"Input Code:";
	getline(cin, input_str); 
	input_str=input_str+' ';
	get_tokens(input_str);
	return 0;
}

