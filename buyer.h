#ifndef BUYER_H
#define BUYER_H

#include <stdio.h>
#include <stdlib.h>
#include "shopkeeper.h"

// typedef struct SLL{
//     struct Orders order;
//     struct SLL *next;
// }node;

// node * create_node(struct Orders order){
//     node * n;
//     n=(node *)malloc(sizeof(node));
//     n->order=order;
//     n->next=NULL;
//     return n;
// }
// node * create_head1(){
//     node *n;
//     n=(node *)malloc(sizeof(node));
//     n->next=NULL;
//     return n;
// }

// void InsertAtEnd1(node *n,struct Orders order){
//    node *newnode;
//    int val=0;
//    newnode =create_node(order);
//    node* temp=n;
//    while(temp->next!=NULL){
//         temp=temp->next;
//    }
//    temp->next=newnode;
// }

//extern variables
// extern node *orders;

// Buyer operations
void makeOrder(float gst,int bid);
int addBuyer(char *bname);
int checkBuyer(int bid);
void addtocart(int itemid,int sid,int bid,int quantityTaken);
void viewcart(int bid);
#endif