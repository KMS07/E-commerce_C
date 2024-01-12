#include "shopkeeper.h"
#include <stdio.h>
#include <time.h>

node1 * create_node1(struct shopkeeper newsk){
    node1 *n;
    n=(node1 *)malloc(sizeof(node1));
    n->sk=newsk;
    n->next=NULL;
    return n;
}
node1 * create_head(){
    node1 *n;
    n=(node1 *)malloc(sizeof(node1));
    n->next=NULL;
    return n;
}

void InsertAtEnd(node1 *n,struct shopkeeper sk){
   node1 *newnode;
   newnode =create_node1(sk);
   node1* temp=n;
   while(temp->next!=NULL){
        temp=temp->next;
   }
   temp->next=newnode;
}



int addShopkeeper(char *skname){
    // create new shopkeeper
    int randomId;
    // seed the random number generator
    srand(time(NULL));

    // Generate a random 3-digit number
    randomId = rand() % 900 + 100;

    //struct shopkeeper newsk = {randomId,skname};

    // Adding this shopkeeper
    // InsertAtEnd(sklist,newsk);

    FILE *fp = fopen("sklist.txt","a");
    fprintf(fp,"%d %s\n",randomId,skname);
    fclose(fp);

    return randomId;
}


int checkShopkeeper(int sid){
    // while(sklist->next!=NULL){
    //     sklist=sklist->next;
    //     if(sklist->sk.sid == sid){
    //         return 1;
    //     }
    // }
    FILE *fp = fopen("sklist.txt","r");
    int id;
    char skname[100];

    while(fscanf(fp,"%d %s",&id,skname) == 2){
        if(sid == id){
            return 1;
        }
    }
    return 0;
}
void viewOrders(int sId){
    
    // for(int i = 0; i < numOfOrders;i++){
    //     struct Orders order = orders[i];
    //     struct tm *orderDate = order.orderDate;
    //     int day = orderDate->tm_mday;
    //     int month = orderDate->tm_mon + 1; 
    //     int year = orderDate->tm_year + 1900;
    //     if(order.sId == sId){
    //         //printf("%s %d %d %d %d/%d/%d",order.buyername,order.itemId,order.quantityTaken,order.totalPrice,day,month,year);
    //     }
    // } 
    FILE *fp = fopen("orders.txt","r");

    char buffer[100];

    // Skip the first line
    fgets(buffer,sizeof(buffer),fp);

    int id;
    char buyername[100];
    int itemId,quantityTaken,totalPrice;
    char orderDate[100];
    
    while (fscanf(fp, "%*d %s %d %d %d %d %s",buyername,&itemId,&quantityTaken,&totalPrice,&id,orderDate) == 6) {
        // Check if the current record matches the parameters to delete
        if (id == sId) {
            printf("%s %d %d %d %s",buyername,itemId,quantityTaken,totalPrice,orderDate);
        }
    }
    fclose(fp);
}
void viewItems(int sId){
    FILE *fp = fopen("data.txt","r");

    char buffer[100];
    // Skip the first line
    fgets(buffer,sizeof(buffer),fp);

    int shkId, id;
    char name[100];
    int quantity;
    int price;

    while (fscanf(fp, "%d %d %s %d %d", &shkId, &id, name, &quantity, &price) == 5) {
        if (shkId == sId) {
            printf("%d %d %s %d %d\n",shkId, id, name, quantity, price);
        }
    }

}
// add item to data.txt
void addItem(int sId){
    FILE *filePointer;
    filePointer = fopen("data.txt", "a");

    if (filePointer == NULL) {
        printf("File opening failed.\n");
        return;
    }

    int randomId;
    srand(time(NULL));

    // Generate a random item id
    randomId = rand() % 900 + 100;

    struct Item newItem;

    printf("Enter item price\n");
    scanf("%d",&newItem.price);

    printf("Enter quantity in hand\n");
    scanf("%d",&newItem.QOH);

    printf("Enter item name\n");
    scanf("%s",newItem.itemName);

    fprintf(filePointer, "%d %d %s %d %d\n", sId, randomId,
            newItem.itemName, newItem.QOH, newItem.price);
    fclose(filePointer);

    printf("Item added successfully");
}

void removeItem(int itemId,int sId){
    // Find the item id and shopkeeper id
    FILE *fp,*tp;
    fp = fopen("data.txt","r");
    tp = fopen("temp.txt","w");

    if (fp == NULL || tp == NULL) {
        printf("File opening failed.\n");
        return ;
    }
    char buffer[100];

    // Skip the first line
    fgets(buffer,sizeof(buffer),fp);

    int shkId, id;
    char name[100];
    int quantity;
    int price;

    fprintf(tp,"%s\n","sid itemid name quantity price");
    // Read each record from the input file
    while (fscanf(fp, "%d %d %s %d %d", &shkId, &id, name, &quantity, &price) == 5) {
        // Check if the current record matches the parameters to delete
        if (shkId == sId && id == itemId) {
            continue; // Skip this record if it matches the parameters to delete
        }
        // Write the record to the temporary file if it doesn't match the parameters
        fprintf(tp, "%d %d %s %d %.2f\n", shkId, id, name, quantity, price);
    }

    fclose(fp);  // Close the input file
    fclose(tp);   // Close the temporary file

    remove("data.txt");       // Remove the original file
    rename("temp.txt", "data.txt"); // Rename the temporary file to the original file name
    printf("Item removed successfully\n");
}

void updateItem(int itemId,int sId){
    // Find the item id and shopkeeper id
    FILE *fp,*tp;
    fp = fopen("data.txt","r");
    tp = fopen("temp.txt","w");

    if (fp == NULL || tp == NULL) {
        printf("File opening failed.\n");
        return ;
    }
    struct Item updatedItem;

    printf("Enter updated item price\n");
    scanf("%d",&updatedItem.price);

    printf("Enter updated quantity in hand\n");
    scanf("%d",&updatedItem.QOH);

    printf("Enter updated item name\n");
    scanf("%s",updatedItem.itemName);
    char buffer[100];

    // Skip the first line
    fgets(buffer,sizeof(buffer),fp);

    int shkId, id;
    char name[100];
    int quantity;
    int price;

    fprintf(tp,"%s\n","sid itemid name quantity price");
    // Read each record from the input file
    while (fscanf(fp, "%d %d %s %d %d", &shkId, &id, name, &quantity, &price) == 5) {
        // Check if the current record matches the parameters to update
        if (shkId == sId && id == itemId) {
            fprintf(tp, "%d %d %s %d %d\n", updatedItem.sId, updatedItem.itemId, updatedItem.itemName, updatedItem.QOH, updatedItem.price); // Update this record if it matches the parameters to update
        }
        // Write the record to the temporary file if it doesn't match the parameters
        fprintf(tp, "%d %d %s %d %d\n", shkId, id, name, quantity, price);
    }
    fclose(fp);  // Close the input file
    fclose(tp);   // Close the temporary file

    remove("data.txt");       // Remove the original file
    rename("temp.txt", "data.txt"); // Rename the temporary file to the original file name
    printf("Item updated successfully\n");
}

