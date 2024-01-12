#ifndef SHOPKEEPER_H
#define SHOPKEEPER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Orders{
    char *buyername;
    int itemId;
    int quantityTaken;
    int totalPrice;
    int sId;
    struct tm *orderDate;
}; // Orders structure

struct Item{
    int itemId;
    int price;
    int QOH;
    char* itemName;
    int sId;
};
struct shopkeeper{
    int sid;
    char *skname;
};

typedef struct SLL1{
    struct shopkeeper sk;
    struct SLL1 *next;
}node1;




// extern variables
extern int numOfOrders;
extern node1 *sklist;

//functions
void viewOrders(int sId);
void viewItems(int sId);
void addItem(int sId);
void removeItem(int itemId,int sId);
void updateItem(int itemId,int sId);
int addShopkeeper(char *skname);
int checkShopkeeper(int sid);
node1 * create_node1(struct shopkeeper newsk);
node1 * create_head();
void InsertAtEnd(node1 *n,struct shopkeeper sk);
#endif  // SHOPKEEPER_H