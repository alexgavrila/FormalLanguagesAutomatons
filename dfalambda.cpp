#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <cstring>
using namespace std;

class transition{
    int s;
    char v[2];
public:
    transition(int state,char *val) {
        strcpy(v,val);
        s=state;
    }
    void print(){
        cout << s <<" "<<v ;
    }
    char *getTrans(){
        return v;
    }
    int getState(){
        return s;
    }

};





int accept(vector<list<transition *> > &transitions, vector<int> &finalStates,int qc, int letterIndex,char *alfa, char *word){
    /*
        transitions-a vector with lists of transitions for each state in the DFA graph
        finalStates-a vector with the size equal to the number of states. It's values are 0 if the state is not final and 1 if the state is final
        qc-the index of the current state
        letterIndex-the index of the curent letter
        alfa-the letters the automaton accepts
        word-the word to check
    */

    int k=0;
    list<transition *>::iterator it;
    if(letterIndex<strlen(word))
        //For every transition from the current state the program recursively calls accept() with the new state and index until it gets to the end of the word 
        // '_' is the lambda symbol
        for(it=transitions[qc].begin();it!=transitions[qc].end();++it){
            if(word[letterIndex]==(*it)->getTrans()[0]&&strchr(alfa,word[letterIndex])) 
                k+=accept(transitions,finalStates,(*it)->getState(),letterIndex+1,alfa,word);
            if((*it)->getTrans()[0]=='_') 
                k+=accept(transitions,finalStates,(*it)->getState(),letterIndex,alfa,word);
        }
    else
    if(finalStates[qc]==1) k++;
    return k;
}




int main()
{

    /*
        The input file date:
        [Alphabet] [Word]
        [Number of states] [Number of final states]
        [Final states]
        A list of transition using the format
        [Start State Index][End State Index][Transition Letter]
    */

    ifstream f("dfalambda.input");
    char alfa[26],word[200],s[2];
    int n,nsf,i,j;
    vector<list< transition *> > transitions(n);
    vector<int> finalStates(n,0);


    f>>alfa>>word;
    cout << "Alphabet:" << alfa;
    cout << "\nWord:" << word;
    

    f>>n>>nsf;
    for(i=0;i<nsf;i++){
        int a;
        f>>a;
        finalStates[a]=1;
    }

    while(f>>i>>j>>s){
        transitions[i].push_back(new transition(j,s));
    }

    cout <<"\nAccepted:"<<(accept(transitions,finalStates,0,0,alfa,word)?"Yes":"No");

    return 0;
}
