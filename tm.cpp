/*This program uses an input file with a strict syntax of inputs -
  Note: The states of machine are named as q0,q1,q2.....starting from q0.
  Syntax of input file:
  -	Number of states
  - Start state name(usually 'q0' without quotes)
  -	Number of final states 
  - Space separated final state names
  -	Transition rule 1
  - Transition rule 2
  -	...
  -	...
  
  
  
  - $
  -	Input string 
  Note: The syntax of a transition rule has 5 parts -
  		initial-state input-character new-character-to-be-replaced new-state direction
	      1				2					3						4		5					
		Here, 1 and 4 are states like q0,q1,q5,etc.
			  2,3 and 5 are individual characters.
			  5 can be either 'l'(left) or 'r'(right)
*/
#include<bits/stdc++.h>
#include<conio.h>
using namespace std;
char arr[1000000];							/*a very long tape, on which all the operations are performed. Here, we start taking input string from middle, 
											  i.e. index 500000. Also, initially it is empty i.e. filled with '0' */
											  
int fans=0;									/*a global variable(required for non-deterministic case).Initially 0,as soon as any 1 computation accepts string, 
											it is set to 1 and gets out of loop.*/  							
											
set<string>final;							/*a set which stores all the final states.*/

map<string,vector<string>>trans;			/*a map that stores the transition table for the given turing machine.
											  1st part of transition rule forms the key of the map. Everyting else after 1st part is stored as a string.
											  Since, from a state, there can be many outward arrows, hence all such strings stored in a vector.*/
					
ofstream fout;								/* global variable for writing in output file*/			  
void print(int l,int p)						/*this function prints the tape from index 499995 to index equal to (length of string+5). Also p is the pointer after every step*/
{	
	cout<<". "<<". "<<". "<<". "<<". ";
	for(int i=499995;i<l+500005;i++)
	cout<<arr[i]<<" ";
	cout<<". "<<". "<<". "<<". "<<". "<<"\t"<<p;
	cout<<endl;
	for(int i=499995;i<l+500005;i++)
	fout<<arr[i]<<" ";
	fout<<". "<<". "<<". "<<". "<<". "<<"\t"<<p;
	fout<<endl;
}
void transition(string s1,int p,int l)		/*this is the main function which traverses the string and sees if it is accepted by turing machine.*/
{
	vector<string>v1;
	int i,dir1,flag1,k,temp;
	char ip=arr[p];
	string s2;
	if(final.find(s1)!=final.end())			/*if the current state belongs to final state, string is accepted by turing machine.*/
	{
		fans=1;
	}
	else
	{
		v1=trans[s1];						/*the corresponding vector of strings is taken and traversed and all possibilities are traversed.*/
		for(i=0;i<v1.size() && fans==0;i++)
		{
			if(v1[i][1]==ip)				/*if input character matches the transition rule variable, procced to the next state, updae the tape and move correctly.*/
			{
				temp=arr[p];
				arr[p]=v1[i][3];
				if(v1[i][8]=='r')
				{
					dir1=p+1;		
				}
				else
				dir1=p-1;;					/*here we get new direction(left/right) for the tape*/
				k=6;
				while(v1[i][k]!=' ')
				k++;
				s2=v1[i].substr(5,k-5);		/*here next state is obtained*/
				print(l,dir1);				/*tape printed with updated pointer*/
				transition(s2,dir1,l);		/*proceeded to next state in correct direction*/
				arr[p]=temp;				/*changes are undone to go in next recursive call*/
			}
		}	
	}
}
int main()
{
	memset(arr,'0',sizeof(arr));            /*the tape intialized to '0', i.e. made blank()*/
	int p=500000,i,n,ans=1,n1;
	string s1,s2,str,start,curr;
	fout.open("op1.txt");
	ifstream fin;							/*ifstream object for file-handling*/
	fin.open("ip1.txt");					/*opening the file to read*/
	fin>>n;									/*reading number of states*/
	fin>>start;								/*reading start state*/	
	curr=start;			
	fin>>n1;								/*reading number of final states*/
	for(i=0;i<n1;i++)						/*storing all final states in set 'final'*/	
	{
		fin>>str;
		final.insert(str);
	}
	do{										/*filling the global map trans, which keeps all transition rules mapped with initial
										      state as the key. All rules with the same key stores as vector of strings(mapped to that key).*/ 				
		fin>>s1;
		if(s1!="$")
		{
			getline(fin, s2); 
			trans[s1].push_back(s2);		/*Inserting string in map with vector of strings as second parameter.*/
		}
	}while(s1!="$");
	fin>>str;								/*reading input string*/
	int l=str.length();
	cout<<"No. of states: "<<n<<endl;		/*printing details on console*/
	cout<<"Start stateL: "<<curr<<endl;
	cout<<"Final states: ";
	for(auto itr = final.begin(); itr!= final.end(); ++itr) 
    { 
        cout<<*itr<<" "; 
    } 
	cout<<endl<<"Input string: "<<str<<endl;
	for(i=0;i<l;i++)				/*inputting tape with the input string, starting from middle, i.e. index 500000*/
	arr[p++]=str[i];
	cout<<"Tape initialy: "<<endl;
	cout<<"Char"<<"  "<<"Position"<<endl;
	fout<<"Tape initialy: "<<endl;
	fout<<"Char"<<"  "<<"Position"<<endl;
	p=500000;
	for(i=0;i<l;i++)
	{
		cout<<" "<<arr[p]<<"      "<<p<<endl;
		fout<<" "<<arr[p]<<"      "<<p<<endl;
		p++;
	}
	cout<<"Tape"<<endl;
	fout<<"Tape"<<endl;
	print(l,500000);
	transition(start,500000,l);				/*calling function to check if string is accepted*/
	if(fans==0){
		cout<<"String not accepted by Turing machine."<<endl;
		fout<<"String not accepted by Turing machine."<<endl;
	}
	else
	{
		cout<<"String accepted by Turing machine."<<endl;
		fout<<"String accepted by Turing machine."<<endl;	
	}
	fin.close();
	fout.close();
	return 0;	
}












