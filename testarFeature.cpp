#include <stack>
#include <iostream>


using namespace std;

typedef struct SwitchLabelStacks{
	string endLabel;
	string nextLabel;
	string varLabel;
} SwitchLabels;



void showstack(stack <SwitchLabels> s) 
{ 
    while (!s.empty()) 
    { 
        cout << '\t' << s.top().endLabel; 
        s.pop(); 
    } 
    cout << '\n'; 
} 


int main(){
    stack<SwitchLabels> pilha;

    SwitchLabels topo;
    topo.endLabel = "1";
    pilha.push(topo);
    topo.endLabel = "2";
    pilha.push(topo);
    topo.endLabel = "3";
    pilha.push(topo);

    topo = pilha.top();

    showstack(pilha);
    pilha.top().endLabel = "5";
    showstack(pilha);

}