
#include <iostream>
#include "DFA.h"
//#include "NFA.h"
using namespace std;

int main()
{
    struct NFA_State A, B, C, D,E,F;
    struct Transition edge;
    struct DFA_State* a = new DFA_State;
    A.id = 1;
    edge.input_symbol.name = "1";
    edge.next = &B;
    A.transitions.push_back(edge);

    A.id = 1;
    edge.input_symbol.name = "1";
    edge.next = &D;
    A.transitions.push_back(edge);

    A.id = 1;
    edge.input_symbol.name = "1";
    edge.next = &C;
    A.transitions.push_back(edge);


    B.id = 2;
    edge.input_symbol.name = "0";
    edge.next = &C;
    B.transitions.push_back(edge);

    B.id = 2;
    edge.input_symbol.name = "1";
    edge.next = &D;
    B.transitions.push_back(edge);

    B.id = 2;
    edge.input_symbol.name = "e";
    edge.next = &E;
    B.transitions.push_back(edge);

    C.id = 3;


    D.id = 4;
    edge.input_symbol.name = "1";
    edge.next = &C;
    D.transitions.push_back(edge);

    E.id = 5;
    edge.input_symbol.name = "e";
    edge.next = &F;
    E.transitions.push_back(edge);

    F.id = 6;
    edge.input_symbol.name = "0";
    edge.next = &A;
    F.transitions.push_back(edge);

    C.accept_state_flag = true;
/*
    cout << "current state: " << A.id << " input: " << A.transitions[0].input_symbol.name << " new state " << A.transitions[0].next->id << "\n";
    cout << "current state: " << B.id << " input: " << B.transitions[0].input_symbol.name << " new state " << B.transitions[0].next->id << "\n";
    cout << "current state: " << B.id << " input: " << B.transitions[1].input_symbol.name << " new state " << B.transitions[1].next->id << "\n";
    */
    //cout<<"hiiii"<<endl;
    a->id = 1;
    a->subset_ids.insert(1);
    a->subset.insert(&A);

    test(a);


    //get graph
    get_graph();

    return 0;
}
