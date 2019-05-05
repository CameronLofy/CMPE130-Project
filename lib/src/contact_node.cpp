//
// Created by camer on 5/4/2019.
//


#include "hashtable.h"
#include "contact_node.h"
#include <string>
#include <iostream>

using namespace std;  //Not sure why this is getting errors
namespace lib{
    static void contact_node::print_all() {
        contact_node *entry = this;
        info_node *info = entry->num_node;
        while(info != nullptr)
        {
            cout<< entry->name << ", "<< info->num << endl;
            info = info->next_num;
        }
    }
}