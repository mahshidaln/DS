#ifndef bst_H
#define bst_H


#include <iostream>
#include "huffmantree.h"
#include "Bstnode.h"
#include "datastruct.h"
using namespace std;


class Bst{
public:
    BstNode *root;
    Bst(){
        root = NULL;
    }

    bool addToTree(datastruct dd){
        BstNode *p = root;
        BstNode *q = 0;
        while(p){
            q = p;
            if(dd.c == p->data.c)
                return false;
            else
            if(dd.c < p->data.c)
                p = p->LC;
            else
                p = p->RC;
        }
        p = new BstNode();
        p->LC = 0;
        p->RC = 0;
        p->data = dd;
        if(!root)
            root = p;
        else
        if(dd.c < q->data.c)
                q->LC = p;
        else
            q->RC = p;

        return true;

    }

};
#endif
