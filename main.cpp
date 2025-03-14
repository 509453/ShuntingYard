#include <iostream>
#include <cstring>
#include <string>
#include <cctype>

/*Sources: my sister helped me :)
GeeksforGeeks 
DIYA


*/

using namespace std;

//struct for Node 
struct Node{
  char data;
  Node* next; 
  Node* right; 
  Node* left; 

};

// returns top of the stack 
Node* peek(Node*& head){
  if (head== NULL){
    return NULL;
  }else{
    return head;
  }
}
//Last in first out 
//pushing number or operator to the stack
void push(Node*& head, char element){
    Node* newNode = new Node; 
    newNode -> data = element;
    newNode->next = head; 
    head = newNode; 

  }
  
  
  //pop out a Node from the top
void pop(Node*& head){
  if (head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

//First in first out 
//add to the queue
void enqueue(Node*& head, char element){
    Node* newNode = new Node;
    newNode->data = element;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}


//remove from queue 
void dequeue(Node*& head){
if (head!=NULL){
    Node* temp = head;
    head = head->next;
    delete temp;
    
  }
}
//returns the operators precedence to help us with Shunting Yard Algorithm
int precedence(char operators){
    if (operators == '-' || operators == '+'){
        return 1; 
    }else if (operators == '*' || operators == '/'){
        return 2;
    }else if (operators == '^'){
        return 3;
    }
    return 0; 
}



void ShuntingYardAlg(Node*& head, char* input, char* output){
   Node* operatorStack = NULL; //empty stack to store 
    int outputIndex = 0;

    for (int i = 0; i < strlen(input); i++) {
        char current = input[i]; //traverse through the mathematical expression

        if (current >= '0' && current <= '9') { //if digit queue it 
            enqueue(head, current); 
        }
        else if (current == '(') { // if it is ( put it in stack 
            push(operatorStack, current);  
        }
        else if (current == ')') {
            while (peek(operatorStack) != NULL && peek(operatorStack)->data != '(') {
                enqueue(head, peek(operatorStack)->data);
                pop(operatorStack); // if it is ) find ( and push the rest to queue
            }
            pop(operatorStack);  
        } //if same precedence then in order 
        else if (precedence(current) > 0) {  
            while (peek(operatorStack) != NULL && precedence(peek(operatorStack)->data) >= precedence(current)) {
                enqueue(head, peek(operatorStack)->data);
                pop(operatorStack);
            }
            push(operatorStack, current);
        }
    }

 // After the while loop, pop the remaining items from the operator stack into the output queue. */
    while (peek(operatorStack) != NULL) {
        enqueue(head, peek(operatorStack)->data);
        pop(operatorStack);
    }
}


void binaryTreeExpression(Node*& root, Node*& outputQueue) {
    Node* stack[100]; //stack for nodes 
    int top = -1; // stack pointer

    
    Node* temp = outputQueue;
    while (temp != NULL) {
        char current = temp->data;
        temp = temp->next;

        if (isdigit(current)) {
            //if it's a digit, create a new node and push it to the stack
            Node* newNode = new Node;
            newNode->data = current;
            newNode->left = newNode->right = NULL;
            stack[++top] = newNode;
        } else if (precedence(current) > 0) {
            //if it's an operator pop two nodes from the stack and make them children of the operator
            Node* rightNode = stack[top--]; // Right child
            Node* leftNode = stack[top--];  //left child 

            //operator nodes 
            Node* operatorNode = new Node;
            operatorNode->data = current;
            operatorNode->left = leftNode;
            operatorNode->right = rightNode;

            //push new operator back stack
            stack[++top] = operatorNode;
        }
    }

   //need this for tree 
    root = stack[top];
}

//TOOK DIYAS HELP
void infixPrint(Node*& head){
    
    // infix 
    if (head!= NULL){
        infixPrint(head->left);
        cout<< head->data << " ";
        infixPrint(head->right);
    }
}
//basically reverse of postfix 
void prefixPrint(Node*& head){
    if (head!= NULL){
        cout<< head->data << " ";
        prefixPrint(head->left);
        prefixPrint(head->right);
    }
    
}

void postfixPrint(Node*& head){
    if(head!=NULL){
        postfixPrint(head->left);
        postfixPrint(head->right);
        cout<< head->data << " ";
    }
    
}


int main(){
    //variables 
  char input[100];
  char prefix[] = "PREFIX";
  char postfix[] = "POSTFIX";
  char infix[] = "INFIX";
  char quit[] = "QUIT";
  char noSpaceInput[100];
  int count = 0;
  bool stillPlaying = true; 



  cout<< "Type in a mathematical expression"<<endl;
  cin.getline(input, 100, '\n');
  cin.ignore();

  for (int n = 0; n < strlen(input); n++){
    if (input[n] != ' '){
      noSpaceInput[count] = input[n];
      count++;
    }
  }	
  
  //initialize
  Node* outputQueue = NULL; 
  Node* expressionTree = NULL;
    while (stillPlaying == true){
        cout<< "What would you like to print: postfix, infix or prefix" <<endl; 
        cin.getline(input, 100);
        if (strcmp(input, postfix)== 0){
          ShuntingYardAlg(outputQueue, noSpaceInput, postfix);
      binaryTreeExpression(expressionTree, outputQueue);
      
      cout << "Postfix: ";
      postfixPrint(expressionTree); 
      cout << endl;
        }else if (strcmp(input, infix)==0){
              ShuntingYardAlg(outputQueue, noSpaceInput, postfix);

              binaryTreeExpression(expressionTree, outputQueue);

      cout << "Infix: ";
      infixPrint(expressionTree); 
      cout << endl;
        }else if (strcmp(input, prefix)==0){
              ShuntingYardAlg(outputQueue, noSpaceInput, postfix);
                binaryTreeExpression(expressionTree, outputQueue);
                 cout << "Prefix: ";
                 prefixPrint(expressionTree); 
      cout << endl;
        }else if (strcmp(input, quit)==0){
            stillPlaying = false; 
        }
    }
  


  
  return 0;
}
