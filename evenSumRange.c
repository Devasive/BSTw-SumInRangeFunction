#include <stdio.h>
#include <stdlib.h>

/*
 
 Author: Carter Brown
 
 */

/* Creating type BstNode */

typedef struct BstNode {
    long long data;
    int even;
    struct BstNode* left;
    struct BstNode* right;
    struct BstNode* parent;
} BstNode;

/* Function declarations */

BstNode* GetNewNode(long long data);

BstNode* LocateParent(BstNode** root, long long data);

void Insert(BstNode** root, long long data);

int evenSumRange(BstNode** rootPtr, long long min, long long max);

void freeMem(BstNode** rootPtr);

/* Function definitions */

int main(int argc, char* argv[]) {
    long long dataIn, minIn, maxIn;
    int sum;
    BstNode* root;
    FILE *dataFile, *rangeFile;
    root = NULL;
    
    /* Open filename1 */
    dataFile = fopen(argv[1], "r");
    
    if (dataFile == NULL) {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }
    
    /* Open filename2 */
    rangeFile = fopen(argv[2], "r");
    
    if (rangeFile == NULL) {
        perror(argv[2]);
        exit(EXIT_FAILURE);
    }
    
    /* Create Tree */
    while(fscanf(dataFile, "%ld\n", &dataIn) != -1) {
        Insert(&root, dataIn);
    }
    
    /* Report if the sum in the given ranges is even */
    while(fscanf(rangeFile, "%ld %ld", &minIn, &maxIn) != -1) {
        sum = evenSumRange(&root, minIn, maxIn);
        printf("Range [%d, %d]. ", minIn, maxIn);
        if(sum) {
            printf("even sum\n");
        } else {
            printf("odd sum\n");
        }
    }
    
    /* Free memory */
    freeMem(&root);
    
    /* Close files */
    if(fclose(dataFile) != 0) {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
    if(fclose(rangeFile) != 0) {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}

BstNode* GetNewNode(long long data) {
    BstNode* newNode = malloc(sizeof(BstNode));
    if(data%2==0) {
        newNode->even=1;
    }else {
        newNode->even=0;
    }
    newNode->data = data;
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

BstNode* LocateParent(BstNode** rootPtr, long long data) {
    BstNode *parent, *travPtr;
    parent = NULL;
    travPtr = *rootPtr;
    while(travPtr != NULL) {
        parent = travPtr;
        if(data < travPtr->data) {
            travPtr = travPtr->left;
        } else {
            travPtr = travPtr->right;
        }
    }
    return parent;
}

void Insert(BstNode** rootPtr, long long data) {
    BstNode *parent, *newNode;
    newNode = GetNewNode(data);
    parent = LocateParent(rootPtr, data);
    newNode->parent = parent;
    if (parent == NULL) {
        *rootPtr = newNode;
        return;
    } else if (data < (parent->data)) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    return;
}

int evenSumRange(BstNode** rootPtr, long long min, long long max) {
    int xSum, leftSum, rightSum, halfSum;
    BstNode* x = *rootPtr;
    xSum = leftSum = rightSum = 1;
    if (x == NULL) {
        return 1;
    } else {
        if(min<=x->data) {
            leftSum = evenSumRange(&(x->left), min, max);
        }
        if((min<=x->data)&&(x->data<=max)) {
            xSum = x->even;
        }
        if(max>=x->data) {
            rightSum = evenSumRange(&(x->right), min, max);
        }
        if(leftSum == xSum) {
            halfSum = 1;
        } else {
            halfSum = 0;
        }
        if(halfSum == rightSum) {
            return 1;
        } else {
            return 0;
        }
    }
}

void freeMem(BstNode** rootPtr) {
    BstNode* x = *rootPtr;
    if (x != NULL){
        freeMem(&(x->left));
        freeMem(&(x->right));
        free(x);
    }
}
