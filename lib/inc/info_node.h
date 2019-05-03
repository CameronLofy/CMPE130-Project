//
// Created by camer on 5/3/2019.
//

#ifndef CMPE_130_INFO_NODE_H
#define CMPE_130_INFO_NODE_H

using namespace std;

class info_node{	//Stores numbers associated to a specific name. 
public:
    string num;
    info_node *next_num;
    //Store any additional info here.
    //Second number would require slight modification

    //Linklist to store each number.
    info_node(string num){
        this->num = num;
        this->next_num = nullptr;
    }
};

#endif //CMPE_130_INFO_NODE_H
