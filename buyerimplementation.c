#include "buyer.h"
#include <stdio.h>
#include <stdlib.h>

int numOfOrders = 0;

void deletefromcart(int buyerIdToDelete,int itemIdToDelete){
    FILE *file = fopen("cart.txt", "r");
    FILE *tempFile = fopen("temp_cart.txt", "w");

    int buyerId, itemId, shopkeeperId, quantityTaken;
    char itemName[100];

    // Read the content and write to the temporary file excluding the item to be deleted
    while (fscanf(file, "%d %d %s %d %d", &buyerId, &itemId, itemName, &shopkeeperId, &quantityTaken) == 5) {
        if (!(buyerId == buyerIdToDelete && itemId == itemIdToDelete)) {
            fprintf(tempFile, "%d %d %s %d %d\n", buyerId, itemId, itemName, shopkeeperId, quantityTaken);
        }
    }

    // Close both files
    fclose(file);
    fclose(tempFile);

    // Remove the original file
    remove("cart.txt");

    // Rename the temporary file to the original file
    rename("temp_cart.txt", "cart.txt");
}

void makeOrder(float gst,int bid){
    FILE *fp,*fp1,*fp2,*tp;
    fp = fopen("cart.txt","r");
    fp1 = fopen("orders.txt","a");
    fp2 = fopen("data.txt","r");
    tp = fopen("temp.txt","w");

    if (fp == NULL || fp1 == NULL || fp2 == NULL || tp == NULL) {
        perror("File opening failed");
        return;
    }
    // Skip the first line in orders file
    char buffer1[100];
    fgets(buffer1,sizeof(buffer1),fp1);

    char buffer2[100];
    fgets(buffer2,sizeof(buffer2),fp2);

    int cartshkId,shkId, id,bId,itemId;
    char name[100];
    int quantityTaken,quantity;
    int price;

    // Find current date
    time_t currentTime;
    struct tm *localTime;
    time(&currentTime);        
    localTime = localtime(&currentTime);


    fprintf(tp,"%s\n","sid itemid name quantity price");
    // Read each record from the input file
    while (fscanf(fp2, "%d %d %s %d %d", &shkId, &id, name, &quantity, &price) == 5 && fscanf(fp, "%*d %d %*s %d %d",&itemId,&cartshkId,&quantityTaken) == 3) {
        if (shkId == cartshkId && id == itemId) {
            fprintf(tp, "%d %d %s %d %d\n", shkId, itemId, name, quantity - quantityTaken, price); // Update this record if it matches cart item
            continue;
        }
        // just write the record to the temporary file if not cart item
        fprintf(tp, "%d %d %s %d %d\n", shkId, id, name, quantity, price);
    }
    fclose(fp2);
    fclose(tp);   
    printf("Done updatiing\n");
    remove("data.txt");
    rename("temp.txt", "data.txt");

    fp2 = fopen("data.txt","r");
    // Move file pointers to beginning
    rewind(fp2);
    rewind(fp);

    fgets(buffer2,sizeof(buffer2),fp2);
    // Order processing
    while (fscanf(fp, "%d %d %s %d %d", &bId, &id, name, &shkId, &quantityTaken) == 5 && fscanf(fp2,"%*d %*d %*s %*d %d",&price) == 1) {
        if (bid == bId) {
            fpos_t originalPosition;
            fgetpos(fp, &originalPosition);
            fclose(fp);// close file beofre deleting
            deletefromcart(bid, id);

            fp = fopen("cart.txt","r");
            // Restore the original file pointer position
            fsetpos(fp, &originalPosition);
            // Adding order to the file
            fprintf(fp1, "%d %s %d %d %f %d %d/%d/%d\n", bid, name,id, quantityTaken,(1+(gst/100))*price*quantityTaken,shkId, localTime->tm_mday,localTime->tm_mon+1,localTime->tm_year+1900);
        }   
    }
    printf("Order placed successfully");
    numOfOrders++;
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
}

int addBuyer(char *bname){
    // create new shopkeeper
    int randomId;
    // seed the random number generator
    srand(time(NULL));

    // Generate a random 3-digit number
    randomId = rand() % 900 + 100;

    FILE *fp = fopen("buyers.txt","a");
    fprintf(fp,"%d %s\n",randomId,bname);
    fclose(fp);

    return randomId;
}


int checkBuyer(int bid){
    FILE *fp = fopen("buyers.txt","r");
    int id;
    char bname[100];
    while(fscanf(fp,"%d %s",&id,bname) == 2){
        if(bid == id){
            return 1;
        }
    }
    return 0;
}


void addtocart(int itemid,int sid,int bid,int quantityTaken){
    FILE *fp = fopen("cart.txt","a");
    FILE *fp1 = fopen("data.txt","r+");

    char buffer[100];
    // Skip the first line
    fgets(buffer,sizeof(buffer),fp1);

    int shkId, id;
    char name[100];
    int itemquantity;
    int price;

    // Read each record from the input file 
    while (fscanf(fp1, "%d %d %s %d %d", &shkId, &id, name, &itemquantity, &price) == 5) {
        if (shkId == sid && id == itemid) {
            // If quanitity is selected more cant be added to cart
            if(quantityTaken > itemquantity){
                printf("Enter less than %d quantity",itemquantity);
            }else{
                fprintf(fp,"%d %d %s %d %d\n",bid,itemid,name,sid,quantityTaken); // add to the cart file
                printf("Added to cart successfully!!\n");
                break;
            }
        }   
    }
    
    fclose(fp);
}

void viewcart(int bid){
    FILE *fp = fopen("cart.txt","r");
    int buyerid,itemid,quantityTaken;
    char itemname[100];
    printf("Itemid name Selected quantity\n");
    while(fscanf(fp,"%d %d %s %*d %d\n",&buyerid,&itemid,itemname,&quantityTaken) == 4){
        if(bid == buyerid){
            printf("%d %s %d\n",itemid,itemname,quantityTaken);
        }
    }
    fclose(fp);
}