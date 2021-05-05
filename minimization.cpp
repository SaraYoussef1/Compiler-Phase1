#include <iostream>
#include"minimization.h"
#include <map>

using namespace std;

void table_filling(map<int, DFA_Graph> graph){
    int states_no = graph.size();
    //table to do minimization through
    int table[states_no-1][states_no-1] = {};
    //array where indx+1 represents state id
    //& its value represents whether it is an accepting state or not
    int accepting[states_no+1];

    map<int, DFA_Graph>::iterator itr;
    for(itr = graph.begin(); itr !=  graph.end(); ++itr)
        accepting[itr->first] = itr->second.acceptance_state;
    //states from 0 to states_no-2 -> columns -> column + 1 "state id"
    //states from 1 to states_no-1 -> rows -> row+2 "state id"

    //looping through this table only need to check the lower triangular
    //mark all transition between accepting & notaccepting as invalid transitions
    for(int i=0; i<states_no-1; i++){
        for(int j=0; j<=i; j++){
            if(accepting[i+2]!=accepting[j+1])
                table[i][j] = -1;
        }
    }
    //construct the table
    int flag = 1;
    while(flag){
        flag = 0;
        for(int i=0; i<states_no-1; i++){
            for(int j=0; j<=i; j++){
                if(table[i][j]==0){
                    int id1 = i+2;
                    int id2 = j+1;
                    map<string, int> transition1 = graph[id1].next_state;
                    map<string, int> transition2 = graph[id2].next_state;
                    if(transition1.size()!=transition2.size()){
                        table[i][j] = -1;
                        flag = 1;
                    }
                    else{
                        map<string, int>::iterator itr;
                        for(itr =  transition1.begin(); itr !=  transition1.end(); ++itr){
                            string input_symbol = itr->first;
                            int next_state_id1 = itr -> second;
                            if(transition2.count(input_symbol)==0){
                                table[i][j] = -1;
                                flag = 1;
                                break;
                            }
                            else{
                                int next_state_id2 = transition2[input_symbol];
                                int x = max(next_state_id1, next_state_id2)-2;
                                int y = min(next_state_id1, next_state_id2)-1;
                                if(table[x][y] == -1){
                                    table[i][j] = -1;
                                    flag = 1;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout<<"\n";
    for(int i=1; i<states_no+1; i++)
        cout<<accepting[i]<<" ";
    cout<<"\n";
    for(int i=0; i<states_no-1; i++){
        for(int j=0; j<states_no-1; j++)
            cout<<table[i][j]<<"  ";
        cout<<"\n";
    }
}




