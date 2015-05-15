#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class command
{
	private:
		string call;
		bool next;
		char sperator;
		char* arg[100];
		vector<string> copy;
	public:
		void set_copy( vector<string> );
		void reset();
		command();
		command(string,char);
		void set_next(bool);
		void set_sperator(char);
		void printc();
		void set_call(string, char);
		char get_sperator();
		string get_call();
		char** get_arr();
		vector<string> get_copy();
};

void command :: set_copy( vector<string> a )
{
	for (unsigned int e=0; e < a.size(); e++ )
	{
		copy.push_back(a.at(e));
	}
}
	
char** command :: get_arr()
{
	return arg;
}

char command :: get_sperator()
{
	return sperator;
}
void command :: reset()
{
	unsigned int keep = 0 ;
	for (unsigned int t=0; t<copy.size(); t++)
	{
		arg[t] = (char*) copy.at(t).c_str() ;
		keep = t;
	}

	if (copy.size() >0)
	{
		arg[keep+1] = NULL;	
	}
	else
	{
		arg[keep] = NULL;
	}
	//call = copy.at(0);	
}

command :: command ()
{
	next = 1;
	//arg[0] = NULL;
}
string command :: get_call()
{
	return call;
}


command :: command (string a, char d)
{
	sperator = d;
	call = a;
	next = 1;
	//arg[0] = NULL;
}

void command :: set_call (string a,char d)
{
	sperator = d;
	call = a;
	next = 1;
	//arg[0] = NULL;
}
void command :: set_next (bool b)
{
	next = b;
}

void command :: set_sperator(char c)
{
	sperator = c;
} 

void command :: printc ()
{
	cout << "call: " << call<<" ";
	//for (int y=0; y<copy.size(); y++)
	//{
	//	cout << copy.at(y)<< " ";
	//}
	
	cout << "symbol:" << sperator << endl;
	//cout << call<<"("<<sperator<<")";
}

vector<string> command :: get_copy()
{
	return copy;
}
