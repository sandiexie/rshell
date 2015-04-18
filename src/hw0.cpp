#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include "command.h"

using namespace std;

bool execute ( char*argu[])
{
	int pass = 0;

	if( *argu == NULL )
	{
		return false;
	}

	pid_t pid = fork();

	if (pid == -1)
	{
		perror ("fork");
		exit (1);
		// iperror 
	}

	if (pid == 0)
	{
		pass = execvp (argu[0], argu);

		if( pass < 0)
		{
			perror ("exec");
			exit(1);
		} 
		// in child
	}
	if (pid > 0)
	{
		pid_t wait = waitpid(pid, &pass, 0);
		
		if (wait < 0 )
		{
			perror("wait");
		}

		if (pass > 0)
		{
			return false;
		}
		else 
		{
			return true;
		}
		//in parent
	}
}

int main(int argc, char* argv[])
{
	string input;
	getline(cin,input);

	size_t found =-1;
	found = input.find("#");
	
	if (found != -1)
	{
		input = input.substr(0, found);
	}
	
	char* temp_input = (char*) input.c_str();
	char* token;
	
	vector < vector<command> > syscalls;
	vector <command> inner;

	token = strtok (temp_input,";");

	// sperate command by ;

	command holder;

	if (token!=NULL)
	{
		holder.set_call (token,';');
		inner.push_back(holder);

		syscalls.push_back(inner);
	}
	inner.clear();

	while (token != NULL)
	{	
		token = strtok (NULL, ";");
		
		if (token != NULL)
		{
			holder.set_call(token,';');
			inner.push_back(holder);
			syscalls.push_back (inner);
		}
		inner.clear();
	}
	
	cout << syscalls.size()<<endl;

	cout << "sperate by ; success" <<endl;
	
	// sperate command by &  ==============================================================
	
	if (syscalls.size() > 0)
	{
		
	//	int size = syscalls.size();
		
		command holder1;
		//cout << "3" <<endl;
		
		for (int i = 0; i < syscalls.size(); ++i )
		{
	//		cout << "4" <<endl;
			
			//cout << i << "&" << syscalls.size() ;
			
			string whole1 = syscalls.at(i).at(0).get_call();
			string wholecopy1 = whole1;
			
			size_t found1 = whole1.find("&&");
			string call1;
			
			//cout << found<< endl;
			//cout << std::string::npos;
			
			while ( found1 != string::npos)
			{
				call1 = wholecopy1.substr(0,found1);
				
				holder1.set_call ( call1, '&' );
				syscalls.at(i).push_back(holder1);
				
				whole1 = whole1.substr(found1+2,whole1.size());
				wholecopy1 = whole1;
			
				found1 = whole1.find("&&");			
			}

				if(whole1.length() != 0)
				{
					holder1.set_call (whole1, ';');
					syscalls.at(i).push_back(holder1);
				}

				//cout << "here" << endl;*/ 
		}
		
		
		//cout << "5" <<endl;
		
		for (int u=0; u<syscalls.size(); u++)
		{
			syscalls.at(u).erase(syscalls.at(u).begin());
		}
		cout << "sperate by & success" <<endl;

		// sperate command by ||  ======================================================
		// run throught all commands, sperate them by ||

		command holder2;
		for (int i=0; i < syscalls.size(); ++i)
		{
			int size = syscalls.at(i).size();
			int newsize;
			for (int j=0; j < size; ++j)
			{
				string whole2 = syscalls.at(i).at(j).get_call();
				string wholecopy2 = whole2;

				size_t found2 = whole2.find("||");
				string call2;

				while (found2 != string::npos)
				{
					call2 = wholecopy2.substr(0,found2);
					
					if (call2.length() > 0)
					{
						holder2.set_call (call2, '|');
						syscalls.at(i).push_back(holder2);
					}
					whole2 = whole2.substr(found2+2, whole2.size());
					wholecopy2 = whole2;

					found2 = whole2.find("||");		
				}
				
				if(whole2.length() != 0)
				{
					holder2.set_call (whole2, '&');
					syscalls.at(i).push_back(holder2);
				}

				newsize = syscalls.at(i).size();
			}
			
			
			syscalls.at(i).at(newsize-1).set_call(syscalls.at(i).at(newsize-1).get_call(), ';');	
		
			for (int y =0 ; y < size; y++)
			{
				syscalls.at(i).erase( syscalls.at(i).begin() );
			}
		}

		cout << "seperate by || success" <<endl;
	}


	// print parsing =======================================================================
	
	if (syscalls.size()>0)
	{
		cout << syscalls.at(0).size();

		for(int i=0; i <= syscalls.size()-1; i++)
		{	
			if (syscalls.at(i).size() >0)
			{
				for (int j=0; j<=syscalls.at(i).size()-1; j++)
				{
					syscalls.at(i).at(j).printc();
					cout << "___";
					cout << endl;
					//int y = 0;
					//cout << endl;
				}
			}
			cout <<endl;
		}
	}
	// create char** ======================================================================
	for (int i=0; i<syscalls.size(); i++)
	{
		//char* arr[100];
		for (int j=0; j<syscalls.at(i).size(); j++)
		{
			
			cout << "**" << endl;
			vector<string> tempA;
		
			
			char* whole_cell = (char*) (syscalls.at(i).at(j).get_call()).c_str();
			char* command1;
			
			syscalls.at(i).at(j).printc();

			cout << syscalls.at(i).at(j).get_call();
			cout << whole_cell << endl;		
			
			command1 = strtok(whole_cell, " ");
			if (command1 != NULL)
			{
				tempA.push_back(command1);
			}		
	
			while(command1 != NULL)
			{
				command1 = strtok (NULL, " ");
				if (command1 != NULL)
				{
					tempA.push_back(command1);
				}
			}
				
			//syscalls.at(i).at(j+1).printc();
			//cout << "printed the second value"<<endl;
			//////////////  zhe shi dui de
			
			cout << tempA.size();
			if (tempA.size() > 0)
			{
				char* arr[tempA.size()+1];

				for (int k=0; k<= tempA.size()-1;k++)
				{
					arr[k] = (char* ) tempA.at(k).c_str();
				}
				cout << "!!" << endl;
				arr [tempA.size()] = NULL;
			
			//syscalls.at(i).at(j).reset(arr[0], arr);
				for (int y=0; y<tempA.size(); y++)
				{
					cout << arr[y] << " | " ;

				}
			//syscalls.at(i).at(j+1).printc();	
			///cout << "printed the second value"<<endl;
				
				syscalls.at(i).at(j).reset(arr[0],arr);
				//syscalls.at(i).at(j+1).printc();
				//cout << "printed the second value"<<endl;
				for (int y =0; y<=tempA.size(); y++)
				{
					if ( ( syscalls.at(i).at(j).get_arr()[y])  == NULL )
					{
						cout << "!" << " | ";	
					}
					else
					{
						cout << (syscalls.at(i).at(j).get_arr()[y]) << " | ";
					}
				}

			}
			cout << endl;
						
			//delete whole_cell;
			//delete command1;
			//tempA.clear();
		}	
	}	
	
	// executing ==========================================================================
	
	for (int i=0; i <= syscalls.size()-1; i++)
	{
		for (int j=0; j <= syscalls.at(i).size()-1; j++)
		{
			bool e_or = false;
			bool e_and = true;
		}
	}

	// codes to test whats in char** arr[]================================================
	/*if (syscalls.size() >0)
	{
		
		
		for (int i=0; i <= syscalls.size()-1; i++)
		{
			if (syscalls.at(i).size() > 0)
			{
				for (int j=0; j <= syscalls.at(i).size()-1; j++)
				{
					cout <<"111" << endl;
					for ( int y=0; y < 3; y++ )
					{
						if ( ( syscalls.at(i).at(j).get_arr()[y])  == NULL )
						{
							cout << "!" << " | ";	
						}
						else
						{
							cout << (syscalls.at(i).at(j).get_arr()[y]) << " | ";
						}
					}
					cout << endl;
				}
			}
		}
	}*/
	

}






