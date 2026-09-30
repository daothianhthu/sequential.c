#include<stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct Node{
    int data;
    struct Node*left;
    struct Node*right;
}Node;
int Comparisons =0;
Node*createNode(int value){
    Node* newNode = malloc(sizeof(Node));
    newNode->data=value;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}
Node* insert(Node* root, int value){
    if(root==NULL){
        return createNode(value);
    }
    Comparisons++;
    if(value<root->data){
        root->left= insert(root->left,value);
    }
    else 
        root->right =insert(root->right,value);
    
    return root;

}
int isDuplicate(int data[], int size, int value)
{
    for (int i = 0; i < size; i++)
    {
        if (data[i] == value)
        {
            return 1;
        }
    }

    return 0;
}
int sequentialSearch(int data[], int size,int key,int*Comparisons ){
*Comparisons=0;
for(int i=0;i<size; i++){
    (*Comparisons)++;
    if(data[i]==key)
    return 1;

}
return 0;
}
int bstSearch(Node* root, int key, int *Comparisons)
{
    *Comparisons = 0;

    Node* current = root;

    while(current != NULL)
    {
        (*Comparisons)++;

        if(key == current->data)
        {
            return 1;
        }
        else if(key < current->data)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    return 0;
}
void freeTree(Node* root)
{
    if(root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);

    free(root);
}
int main()
{

    int data[100];
    int count = 0;

    srand(time(NULL));

    while (count < 100)
    {
        int value = rand() % 1001;

        if (isDuplicate(data, count, value) == 0)
        {
            data[count] = value;
            count++;
        }
    }

    printf("Generated 100 numbers:\n");

    for (int i = 0; i < 100; i++)
    {
        printf("%d ", data[i]);
    }

    printf("\n\n");

    Node* root = NULL;

    for (int i = 0; i < 100; i++)
    {
        root = insert(root, data[i]);
    }

    printf("BST construction comparisons: %d\n",Comparisons);

    printf("\n");


    int search[50];

    for (int i = 0; i < 50; i++)
    {
        search[i] = rand() % 1001;
    }

    printf("Search Keys:\n");

    for (int i = 0; i < 50; i++)
    {
        printf("%d ", search[i]);
    }

    printf("\n\n");

    int sequentialTotal = 0;
    int bstTotal = 0;

    for (int i = 0; i < 50; i++)
    {
        int sequentialComparisons;
        int bstComparisons;

        int sequentialResult =
            sequentialSearch(
                data,
                100,
                search[i],
                &sequentialComparisons
            );

        int bstResult =
            bstSearch(
                root,
                search[i],
                &bstComparisons
            );
        sequentialTotal += sequentialComparisons;
        bstTotal += bstComparisons;


       
        printf("Search Key: %d\n", search[i]);

        if (sequentialResult == 1)
        {
            printf("Sequential Search Result: Found\n");
        }
        else
        {
            printf("Sequential Search Result: Not Found\n");
        }

        printf("Sequential Comparisons: %d\n",
               sequentialComparisons);


        if (bstResult == 1)
        {
            printf("BST Search Result: Found\n");
        }
        else
        {
            printf("BST Search Result: Not Found\n");
        }

        printf("BST Comparisons: %d\n",
               bstComparisons);

        printf("\n");
    }

    double sequentialAverage =
        (double)sequentialTotal / 50;

    double bstAverage =
        (double)bstTotal / 50;

int bstTotalCost =Comparisons + bstTotal;
printf("\nBST Total Cost\n");
printf("Construction + Search comparisons: %d\n",
       bstTotalCost);

    printf("==============================\n");
    printf("Number of searches: 50\n");

    printf("\nSequential Search\n");
    printf("Total comparisons: %d\n",
           sequentialTotal);

    printf("Average comparisons: %.2f\n",
           sequentialAverage);


    printf("\nBST Search\n");
    printf("Total comparisons: %d\n",
           bstTotal);

    printf("Average comparisons: %.2f\n",
           bstAverage);

    printf("==============================\n");

freeTree(root);
    return 0;
}

