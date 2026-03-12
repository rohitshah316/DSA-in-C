#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int key;
    struct Node *left;
    struct Node *right;
}Node;

//Create new Node
Node* newNode(int key){
    Node *n=(Node*)malloc(sizeof(Node));

    if(!n){
        fprintf(stderr,"Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    n->key=key;
    n->left=NULL;
    n->right=NULL;

    return n;
}

//attaching key as immediate child
int attach_to_immediate_child(Node *node,int key){
    if(node==NULL) return 0;

    if(key<node->key){
        if(node->left==NULL){
            node->left=newNode(key);
            return 1;
        }else{
            return -1;
        }
    }else if(key>node->key){
        if(node->right==NULL){
            node->right=newNode(key);
            return 2;
        }else{
            return -2;
        }
    }else{
        return -3;
    }
}


//insert
void insert(Node *root,int key){
    Node *current=root;

    while(1){
        int result=attach_to_immediate_child(current,key);

        if(result==1 || result==2){
            return;
        }else if(result==-1){
            current=current->left;
        }else if(result==-2){
            current=current->right;
        }else if(result==-3){
            printf("Duplicate key ignored: %d\n",key);
            return;
        }
    }
}


//inorder 
void inorder(Node *root){
    if(root==NULL) return;

    inorder(root->left);
    printf("%d ",root->key);
    inorder(root->right);
}


int main(){
    int keys[]={50,30,70,20,40,60,80};
    int n=sizeof(keys)/sizeof(keys[0]);

    Node *root=newNode(keys[0]);


    for(int i=1;i<n;i++){
        insert(root,keys[i]);
    }
    printf("Inorder traversal of BST:\n");
    inorder(root);

    return 0;
}