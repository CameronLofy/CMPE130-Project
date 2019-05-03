//
// Created by camer on 5/3/2019.
//

#ifndef CMPE_130_CONTACT_NODE_H
#define CMPE_130_CONTACT_NODE_H

#include <string>
#include "info_node.h"

using namespace std;
class contact_node{     // Node used to store each name added to hashtable
public:
    info_node *num_node;	// String for phone number
    string name;			// String for name (basically the key)
    contact_node *next;		// Node for chaining

    //initializing the contact_node
    contact_node(string name, string num){
        this->num_node = new info_node(num); //Stores numbers associated to the name.
        this->name = name;
        this->next = nullptr;
    };

#endif //CMPE_130_CONTACT_NODE_H
