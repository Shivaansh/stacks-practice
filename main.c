#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ArrayStack{
    int size;
    int top;
    int *stack;
};

struct Node{
    int value;
    struct Node *next;
};

void displayStack(struct ArrayStack stackPtr){
    for(int i = stackPtr.size-1; i >= 0; i--){
        if(stackPtr.stack[i] != -1){
            printf("%d\n", stackPtr.stack[i]);
        }
    }
}

//displays LL in reverse
void displayLLStack(struct Node *p) {
    if(p != NULL){
        printf(" Node value: %d\n", p->value);
        displayLLStack(p->next);
    }
}
// HELPERS

// ARRAY IMPLEMENTATION
//Pass ADDRESS of stack
void push(struct ArrayStack *stackPtr, int value){
    if (stackPtr->top == stackPtr->size-1){
        printf("Stack overflow\n");
    }else{
        stackPtr->top++;
        stackPtr->stack[stackPtr->top] = value;
    }
}

//Pass ADDRESS of stack
int pop(struct ArrayStack *stackPtr){
    int val = -1;
    if(stackPtr->top == -1){
        printf("Stack already empty\n");
    }else{
        val = stackPtr->stack[stackPtr->top];
        stackPtr->stack[stackPtr->top] = -1;
        stackPtr->top--;
    }
    return val;
}

//Pass ADDRESS of stack
int peek(struct ArrayStack *stackPtr, int index){
    int val = -1;
    int pos = stackPtr->top - index + 1;
    if(pos >= stackPtr->size || pos < 0){
        printf("INVALID POSITION\n");
    }else{
        val = stackPtr->stack[pos];
    }
    return val;
}

//Pass ADDRESS of stack
int stackTop(struct ArrayStack *stackPtr){
    if(stackPtr->top == -1){
        printf("EMPTY STACK\n");
        return -1;
    }
    return stackPtr->stack[stackPtr->top];
}

//Pass ADDRESS of stack
bool isEmpty(struct ArrayStack *stackPtr){
    if(stackPtr->top == -1) {
        return true;
    }else{
        return false;
    }
}

bool isFull(struct ArrayStack *stackPtr){
    if(stackPtr->top == stackPtr->size-1) {
        return true;
    }else{
        return false;
    }
}

// LINKED LIST IMPLEMENTATION
struct Node* pushInLLStack(struct Node *top, int value){
    struct Node *t = (struct Node*)malloc(sizeof(struct Node));
    t->value = value;
    if(t == NULL){
        printf("Stack overflow\n");
        return top;
    }else{
        if(top){
            t->next = top;
        }else{
            t->next = NULL;
        }
        top = t;
    }
    return top;
}

struct Node* popInLLStack(struct Node *top){
    if(top){
        printf("Deleted value %d\n", top->value);
        struct Node *p = top;
        top = top->next;
        free(p);
    }else{
        printf("Stack is empty\n");
    }
    return top;
}

int peekInLLStack(struct Node *top, int position){
    if(top){
        struct Node *p = top;
        for(int i = 0; p && i<position-1; i++){
            p = p->next;
        }
        if(p){
            return p->value;
        }else{
            printf("Invalid position\n");
            return -1;
        }
    }else{
        printf("Stack is empty\n");
        return -1;
    }
}

int topInLLStack(struct Node *top){
    if(top){
        return top->value;
    }else{
        printf("Stack is empty\n");
        return -1;
    }
}

bool isEmptyLLStack(struct Node *top){
    if(top == NULL) {
        return true;
    }else{
        return false;
    }
}

bool isFullLLStack(struct Node *top){
    struct Node *t = (struct Node*)malloc(sizeof(struct Node));
    if(t == NULL) {
        return true;
    }else{
        free(t);
        return false;
    }
}

bool bracketsBalanced(char *string){
    int i = 0;
    struct Node *stackLL = NULL;
    printf("Displaying stack\n");
    displayLLStack(stackLL);
    while(string[i] != '\0'){
        if(string[i] == '('){
            stackLL = pushInLLStack(stackLL, 1);
            i++;
        }else if(string[i] == ')'){
            if(isEmptyLLStack(stackLL)){
                return false;
            }else{
                stackLL = popInLLStack(stackLL);
                i++;
            }
        }else{
            i++;
        }
    }
    if(isEmptyLLStack(stackLL)){
        return true;
    }else{
        return false;
    }
}

int main() {

    struct ArrayStack st;
    printf("Enter size of ARRAY STACK to be created\n");
    scanf("%d", &st.size);
    st.stack = (int *)malloc(st.size*sizeof(int));
    st.top = -1;
    for(int i = 0; i<st.size; i++){
        st.stack[i] = -1;
    }

    push(&st, 5);
    printf("Stack:\n");
    displayStack(st);
    push(&st, 10);
    printf("Stack:\n");
    displayStack(st);
    push(&st, 7);
    printf("Stack:\n");
    displayStack(st);
    pop(&st);
    printf("Stack:\n");
    displayStack(st);
    printf("Stack peek at position 2: %d\n", peek(&st, 2));
    printf("Stack top: %d\n", stackTop(&st));
    if(isEmpty(&st)){
        printf("Stack is empty\n");
    }else{
        printf("Stack is not empty\n");
    }
    if(isFull(&st)){
        printf("Stack is full\n");
    }else{
        printf("Stack is not full\n");
    }

    printf("LL IMPLEMENTATION\n");
    struct Node *stackLL;
    stackLL = pushInLLStack(stackLL, 5);
    printf("Stack:\n");
    displayLLStack(stackLL);
    stackLL = pushInLLStack(stackLL, 10);
    printf("Stack:\n");
    displayLLStack(stackLL);
    stackLL = pushInLLStack(stackLL, 7);
    printf("Stack:\n");
    displayLLStack(stackLL);
    printf("Stack peek at position 3: %d\n", peekInLLStack(stackLL, 3));
    stackLL = popInLLStack(stackLL);
    printf("Stack:\n");
    displayLLStack(stackLL);
    printf("Stack top: %d\n", topInLLStack(stackLL));
    if(isEmptyLLStack(stackLL)){
        printf("Stack is empty\n");
    }else{
        printf("Stack is not empty\n");
    }
    if(isFullLLStack(stackLL)){
        printf("Stack is full\n");
    }else{
        printf("Stack is not full\n");
    }

    printf("Checking brackets\n");
    //Bracket balance method
    char *s1 ="(a+b)*(c-d)";
    char *s2 ="(a+b))*(c-d)";
    char *s3 ="((a+b)*(c-d)";


    if(bracketsBalanced(s1)){
        printf("S1 is balanced\n");
    }else{
        printf("S1 is NOT balanced\n");
    }
    if(bracketsBalanced(s2)){
        printf("S2 is balanced\n");
    }else{
        printf("S2 is NOT balanced\n");
    }
    if(bracketsBalanced(s3)){
        printf("S3 is balanced\n");
    }else{
        printf("S3 is NOT balanced\n");
    }
}
