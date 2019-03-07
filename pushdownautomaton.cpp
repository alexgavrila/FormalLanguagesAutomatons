//OLD CODE NOT COMMENTED PROPERLY



#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <cstring>
using namespace std;

class transition{
    int s;
    char v;
    char stackA;
    char stackR[10];

public:
    transition(int stare,char val,char sA,char *sR) {
        v=val;
        s=stare;
        stackA=sA;
        strcpy(stackR,sR);
    }
	
    void print(){
        cout << s <<" "<<v ;
    }
    char getTrans(){
        return v;
    }
    char getStackA(){
        return stackA;
    }
    char *getStackR(){
        return stackR;
    }
    int getState(){
        return s;
    }

};



int accept(vector<list<transition *> > &transitions, vector<int> &states,int qc, int current,char *alfa, char *cuvant,vector<char> stack){
    /*
        transitions-a vector with lists of transitions for each state in the DFA graph
        finalStates-a vector with the size equal to the number of states. It's values are 0 if the state is not final and 1 if the state is final
        qc-the index of the current state
        letterIndex-the index of the curent letter
        alfa-the letters the automaton accepts
        word-the word to check
        stack-the stack.....
    */


    int k=0;
    list<transition *>::iterator it;
    if(current<=strlen(cuvant)){
        for(it=transitions[qc].begin();it!=transitions[qc].end();++it){
            //For every transition from the current state the program recursively calls accept() with the new state and index until it gets to the end of the word 
            // '_' is the lambda symbol
            if(cuvant[current]==(*it)->getTrans()&&strchr(alfa,cuvant[current])&&(*it)->getStackA()==stack.back()) {
                char *temp=(*it)->getStackR();
                stack.pop_back();
				if(temp[0]!='_')
                    for(int i=strlen(temp)-1;i>=0;i--){
						stack.push_back(temp[i]);
                    }
                k+=accept(transitions,states,(*it)->getState(),current+1,alfa,cuvant,stack);

            }
            if((*it)->getTrans()=='_'&&(*it)->getStackA()==stack.back()) {
                    stack.pop_back();
                    char *temp=(*it)->getStackR();
                    if(temp[0]!='_')
                    for(int i=strlen(temp)-1;i>=0;i--){
                        stack.push_back(temp[i]);
                    }
                    k+=accept(transitions,states,(*it)->getState(),current,alfa,cuvant,stack); //transition cu lambda

            }
        }
    }
    
    if(states[qc]==1&&current==strlen(cuvant)) {k++;}
    if(stack.size()==0&&current==strlen(cuvant)){k++;}
 
    return k;
}




int main()
{

	
	
	/*
        The input file pushdown.input:
        [Alphabet] [Word]
        [Number of states] [Number of final states]
        [Final states]
        A list of transition using the format
        [Start State Index][End State Index][Transition Letter][Top of the stack][Replace top of the stack with]
	*/
    ifstream f("pushdown.input");
    char alfa[26],cuvant[200];
    int n,nsf;
    f>>alfa>>cuvant;
    cout << "Alphabet:" << alfa;
    cout << "\nWord:" << cuvant;
    f>>n>>nsf;
    int i,j;
    char s,st,repl[10];/*auxiliary chars
                        s-transition letter
						st-top of the stack
						repl-letters to replace top of the stack
					   */
    vector<list< transition *> > transitions(n);
    vector<int> states(n,0);
    vector<char> stack;
    stack.push_back('-');
    for(i=0;i<nsf;i++){
        int a;
        f>>a;
        states[a]=1;
        cout  << a;
    }

	
    while(f>>i>>j>>s>>st>>repl){
        //For a state I create a transition to J with the character S if top of the stack is ST and replace it with repl
        transitions[i].push_back(new transition(j,s,st,repl));

    }
	
	
    cout <<"\nAcceptat:"<<(accept(transitions,states,0,0,alfa,cuvant,stack)?"Da":"Nu");
    

    return 0;
}
