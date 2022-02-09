#include "ksmedia.h"

void KDTree::range_search_helper(Node *current, Node *node1, Node *node2, int level)
{
    int current_level = level % k;
    int low = min(node1->value[current_level], node2->value[current_level]);
    int high = max(node1->value[current_level], node2->value[current_level]);
    if(isInRange(current, node1, node2)){
        for(int i=0;i<k;i++){
            cout<< current->value[i]<< " ";
        }
        cout<< endl;
    }
    if(current->value[current_level] >= low and current->value[current_level] <= high){
        if(current->right != NULL)
            range_search_helper(current->right, node1, node2, level+1);
        if(current->left != NULL)
            range_search_helper(current->left, node1, node2, level+1);
    }
    else if(current->value[current_level] < low){
        if(current->right != NULL)
            range_search_helper(current->right, node1, node2, level+1);
    }
    if(current->value[current_level] > high){
        if(current->left != NULL)
            range_search_helper(current->left, node1, node2, level+1);
    }
}