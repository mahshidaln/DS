#ifndef huffmantree_H
#define huffmantree_H

#include <iostream>
#include <vector>
#include "Tnode.h"
#include "Bst.h"
#include "datastruct.h"
#include "vector"
using namespace std;


class huffmantree{
public:
    datastruct listA[256];
    vector<datastruct> listB;
    int Csize;
    datastruct listC[256];
    Bst *CBst;

    huffmantree(){
        CBst = new Bst();
    }

    void countTheChars(){
        ifstream pf("my.bin", ios::binary);
        for(int zero=0; zero<256; zero++)
            listA[zero].countof = 0;
        char ch;
        while(pf.get(ch)){
            int index = (int) ch;
            if(index>=0){
                listA[index].countof++;
                listA[index].c = ch;
            }
        }
        pf.close();
    }

    void insertToB(datastruct ds, int i){
        while(ds.countof > listB[i].countof && i>=0){
            listB[i+1] = listB[i];
            i--;
        }
        listB[i+1] = ds;
    }

    void insertionSort(){

        for(int j=1; j<listB.size(); j++){
            insertToB(listB[j], j-1);
        }
    }

    void updatepoint(){
         for(int j=0; j<listB.size(); j++){
            listB[j].point = new Tnode();
            listB[j].point->sdata = listB[j].c;
            listB[j].point->countofdata= listB[j].countof;
        }
    }

     void configureListB(){
        for(int i=0; i<256; i++){
            if(listA[i].countof>0){
                listB.push_back(listA[i]);
            }
        }
        insertionSort();
        updatepoint();
    }


    void configureListC(){
        Csize = listB.size();
        for(int ind=0; ind<listB.size(); ind++){
            listC[ind] = listB[ind];
        }
    }

    void makeTree(){
        int length = listB.size();
        while(length != 1){
            datastruct newds;
            newds.c = listB[length-1].c + listB[length-2].c;
            newds.countof = listB[length-1].countof + listB[length-2].countof;
            newds.point = new Tnode();
            newds.point->sdata = newds.c;
            newds.point->countofdata = newds.countof;
            newds.point->left = listB[length-1].point;
            newds.point->right = listB[length-2].point;
            length -= 2;
            listB.push_back(newds);
            insertionSort();
            length++;
        }
    }

    void preorderIteration(Tnode *root){
        if(root->code == "" && root->left== NULL){
            root->code = "1";
            listC[0].code = root->code;
            return;
        }
        if(root->left){
            root->left->code = root->code + "0";
            preorderIteration(root->left);
        }
        if(root->right){
            root->right->code = root->code + "1";
            preorderIteration(root->right);
        }
        if(!root->left && !root->right){
            for(int ii=0; ii<Csize; ii++){
                if(root->sdata == listC[ii].c){
                    listC[ii].code = root->code;
                }
            }
             return;
        }
    }

    void makeBstofC(){
        for(int h=0; h < Csize; h++){
            CBst->addToTree(listC[h]);
        }
    }

    string bstSearchen(char wanted){
        int numeral = (int)wanted;
        for(BstNode *r = CBst->root; r;){
            char chickle =  r->data.c[0];
            if(numeral == (int)chickle)
                return r->data.code;
            else
            if(numeral < (int)r->data.c[0])
                r = r->LC;
            else
                r = r->RC;
        }
        return "";
    }
};

#endif
