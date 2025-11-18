#include <stdio.h>

#define MAX 20

int ids[MAX], qty[MAX], price[MAX], count = 0;
int rack[3][3];

void addProduct() {
    if(count >= MAX) return;
    int id, q, p, i, dup = 0;
    printf("Enter Product ID: ");
    scanf("%d", &id);
    for(i=0;i<count;i++){
        if(ids[i]==id) dup=1;
    }
    if(dup){
        printf("Duplicate ID\n");
        return;
    }
    printf("Enter Quantity: ");
    scanf("%d", &q);
    printf("Enter Price: ");
    scanf("%d", &p);
    if(q<=0 || p<=0){
        printf("Invalid\n");
        return;
    }
    ids[count]=id;
    qty[count]=q;
    price[count]=p;
    count++;
}

void searchProduct() {
    int id, i, f=-1;
    printf("Enter ID: ");
    scanf("%d",&id);
    for(i=0;i<count;i++){
        if(ids[i]==id) f=i;
    }
    if(f==-1) printf("Not Found\n");
    else printf("ID:%d Qty:%d Price:%d\n", ids[f], qty[f], price[f]);
}

void updateQuantity() {
    int id, i, ch, val;
    printf("Enter ID: ");
    scanf("%d", &id);
    int f=-1;
    for(i=0;i<count;i++){
        if(ids[i]==id) f=i;
    }
    if(f==-1){
        printf("Not Found\n");
        return;
    }
    printf("1-Increase  2-Decrease: ");
    scanf("%d",&ch);
    printf("Enter value: ");
    scanf("%d",&val);
    if(ch==1) qty[f]+=val;
    else {
        if(qty[f]-val<0){
            printf("Invalid\n");
            return;
        }
        qty[f]-=val;
    }
}

void generateRackReport() {
    int i,j, max = rack[0][0], min = rack[0][0], r1=0,c1=0, r2=0,c2=0, sum=0;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(rack[i][j]>max){
                max=rack[i][j]; r1=i; c1=j;
            }
            if(rack[i][j]<min){
                min=rack[i][j]; r2=i; c2=j;
            }
            sum += rack[i][j];
        }
    }
    printf("Max:%d at (%d,%d)\n", max, r1, c1);
    printf("Min:%d at (%d,%d)\n", min, r2, c2);
    printf("Total:%d\n", sum);
}

void calcStockValue() {
    int i, maxIdx=0, minIdx=0;
    long total = 0;
    for(i=0;i<count;i++){
        long sv = qty[i] * price[i];
        printf("%d %d %d %ld\n", ids[i], qty[i], price[i], sv);
        if(sv > qty[maxIdx]*price[maxIdx]) maxIdx = i;
        if(sv < qty[minIdx]*price[minIdx]) minIdx = i;
        total += sv;
    }
    printf("Highest: %d\n", ids[maxIdx]);
    printf("Lowest: %d\n", ids[minIdx]);
    printf("Total Value: %ld\n", total);
}

void displayAll() {
    int i;
    for(i=0;i<count;i++)
        printf("%d %d %d %ld\n", ids[i], qty[i], price[i], (long)qty[i]*price[i]);
}

int main() {
    int i,j;
    printf("Enter 3x3 rack values:\n");
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            scanf("%d",&rack[i][j]);
        }
    }
    int ch;
    while(1){
        printf("\n1 Add\n2 Search\n3 Update\n4 RackReport\n5 StockValue\n6 Display\n7 Exit\n");
        scanf("%d",&ch);
        if(ch==1) addProduct();
        else if(ch==2) searchProduct();
        else if(ch==3) updateQuantity();
        else if(ch==4) generateRackReport();
        else if(ch==5) calcStockValue();
        else if(ch==6) displayAll();
        else break;
    }
    return 0;
}
