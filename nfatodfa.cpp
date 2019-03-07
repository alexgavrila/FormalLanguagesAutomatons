//IM NOT GOING TO COMMENT THIS CODE IT'S WAAAAAAAAAAAAAAY TOO OLD
//I SHOULD LEARN TO COMMENT MY CODE BETTER
//LIVE AND LEARN


#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <cstring>
#include <set>
#include <deque>
#include <algorithm>


using namespace std;

class tranzitie{
    set<int> *s;
    char v;
public:
    tranzitie(int stare,char val) {
        v=val;
        s=new set<int>;
        s->insert(stare);
    }
    tranzitie(set<int> *stari,char val){
        v=val;
        s=new set<int>;
        set<int>::iterator it1;
        for(it1=stari->begin();it1!=stari->end();++it1) s->insert(*it1);
    }
    void print(){
        set<int>::iterator it1;
        for(it1=s->begin();it1!=s->end();++it1) cout <<*it1;
        cout <<" "<<v ;
    }
    char getTrans(){
        return v;
    }
    set<int>* getState(){
        return s;
    }

};

int main()
{
    /*
    n=numar de stari
    nsf=numar de stari finale


    */

    ifstream f("nfatodfa.input");
    char alfa[26];
    int n,nsf;
    f>>alfa;
    cout << "Alfabet:" << alfa;
    f>>n>>nsf;
    int i,j;
    char s;//folosit pentru citirea tranzitiilor
    vector<list< tranzitie *> > vect(n);
    vector<int> stari(nsf);


    for(i=0;i<nsf;i++){
        int a;
        f>>a;
        stari[i]=a;
    }

    while(f>>i>>j>>s){
        vect[i].push_back(new tranzitie(j,s));
    }
    for(int i=0;i<n;i++){
        list<tranzitie *>::iterator it;
        for(it=vect[i].begin();it!=vect[i].end();++it){
        }

    }

    /*
        Construire matrice intermediara
        Pentru fiecare stare in care apare nedeterminism se va creea un
        set(multime ordonata), ce va reprezenta o noua stare,
        compus din starile care creeaza nedeterminismul
    */

    vector<list<tranzitie*>* > intermediar(n);
    for(int i=0;i<n;i++){
        intermediar[i]=new list<tranzitie*>;
        for(int j=0;j<strlen(alfa);j++){
            set<int> *t=new set<int>;
            list<tranzitie*>::iterator it;
            for(it=vect[i].begin();it!=vect[i].end();++it){
                if((*it)->getTrans()==alfa[j]) {
                    set<int> timp=*(*it)->getState();
                    set<int>::iterator it1;
                    for(it1=timp.begin();it1!=timp.end();++it1) t->insert(*it1);

                }

            }
            tranzitie *temp=new tranzitie(t,alfa[j]);
            intermediar[i]->push_back(temp);
        }
    }

    /*
        Se adauga intr-o coada cu doua capete toate starile
        din tabelul anterior fara a se tine cont de tranzitii
        Se foloseste coada cu doua capete pentru a putea itera
        prin aceasta si a se determian daca starea curenta exista
        sau nu in coada
    */
    deque<set<int> > q;
    set<int> tempSet;
    tempSet.insert(0);
    q.push_back(tempSet);
    for(int i=0;i<n;i++){
        list<tranzitie*>::iterator it;
        for(it=intermediar[i]->begin();it!=intermediar[i]->end();++it){
            deque<set<int> >::iterator qIt;
            int aux=0;
            for(qIt=q.begin();qIt!=q.end();++qIt) {
                if(*qIt==*(*it)->getState()){
                    aux=1;
                    break;
                }
            }
            if(aux==0&&(*(*it)->getState()).size()!=0) q.push_back(*(*it)->getState());

        }
    }
    /*
        In cazul in care starile compuse vor avea tranzitii spre
        alte stari compuse care nu exista deja in coada acestea vor
        fi calculate si adaugate la randul lor in coada prin BFS

    */

    int ins=0;
    while(ins==0){
        ins=1;
        deque<set<int> >::iterator qIt;
        for(qIt=q.begin();qIt!=q.end();++qIt) {
            set<int>::iterator it1;

            list<tranzitie*>::iterator it;
            for(i=0;i<strlen(alfa);i++){
                    tempSet.clear();
                for(it1=(*qIt).begin();it1!=(*qIt).end();++it1){
                    for(it=intermediar[*it1]->begin();it!=intermediar[*it1]->end();++it){
                        if((*it)->getTrans()==alfa[i]) {
                            tempSet.insert((*it)->getState()->begin(),(*it)->getState()->end());
                        }
                    }

                }
            deque<set<int> >::iterator qIt2;
            int aux=0;
            for(qIt2=q.begin();qIt2!=q.end();++qIt2) {
                if(*qIt2==tempSet){
                    aux=1;
                    break;
                }
            }
            if(aux==0&&tempSet.size()!=0) {q.push_back(tempSet);ins=0;}
            }
        }

    }

    /*
        Se calculeaza si afiseaza toate tranzitiile
        Se poate salva in memorie folosind o mapa formata din
        pair<set<int>,list<tranzitie*> >  sau alvare intr-un fisier
    */


    vector<set<int> > starifin;
    deque<set<int> >::iterator qIt;
    for(qIt=q.begin();qIt!=q.end();++qIt){
        set<int>::iterator it1;
        for(int i=0;i<strlen(alfa);i++){
            tempSet.clear();
            for(it1=(*qIt).begin();it1!=(*qIt).end();++it1){
                list<tranzitie*>::iterator listIt;
                for(listIt=intermediar[*it1]->begin();listIt!=intermediar[*it1]->end();++listIt){
                    if((*listIt)->getTrans()==alfa[i]){
                        tempSet.insert((*listIt)->getState()->begin(),(*listIt)->getState()->end());
                    }
                }

            }
            if(tempSet.size()!=0){
                cout << endl;
                int fin=0;
                set<int>::iterator it2;
                for(it2=(*qIt).begin();it2!=(*qIt).end();++it2) {
                    cout << *it2;
                    if(find(stari.begin(),stari.end(),*it2)!=stari.end()) fin=1;
                }

                //if(fin) cout << "(fin)";
                cout << " ";
                if(fin==1&&find(starifin.begin(),starifin.end(),*qIt)==starifin.end()) starifin.push_back(*qIt);
                for(it2=tempSet.begin();it2!=tempSet.end();++it2) cout << *it2;
                cout << " ";
                cout << alfa[i];

            }

        }
    }

    cout << "\nStari finale: ";
    //cout << starifin.size();
    for(int i=0;i<starifin.size();i++){
        set<int>::iterator it2;
        for(it2=starifin[i].begin();it2!=starifin[i].end();++it2) {
            cout << *it2;
        }
        cout << " ";
    }

    return 0;
}
