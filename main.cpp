#include <iostream>
#include <cstring>
#include <string>

using namespace std;


struct Node{
  char data;
  Node* next; 

};






Node* peek(Node*& head){
  if (head->next != NULL){
    return head;
  }else{
    return NULL;
  }
}

void push(Node*& head, Node* insertNewNode){

  if (head->next == NULL){
    head->next = insertNewNode; 
  }else if(head->next != NULL){
    insertNewNode->next = head->next;
    head->next = insertNewNode; 


    }
  }
  


void pop(Node*& head){
  if (head->next == NULL){
    return; 
  }
  else if (head->next->next == NULL){
    head->next == NULL; 

  }else{
    head->next = head->next->next;
    
  }
}

void enqueue(Node*& head, Node* insertNewNode){
  Node* current = head;
  while (current->next == NULL){
    current->next = insertNewNode; 
  }

}

void dequeue(Node*& head){

  if (head == NULL){
    return; 

  }else if (head->next == NULL){
    delete head; 


  }else{
    Node* temp = head;
    head = head->next;
    delete temp;
    
  }
}



int main(){
  char input[100];
  char prefix[] = "PREFIX";
  char postfix[] = "POSTFIX";
  char infix[] = "INFIX";
  char quit[] = "QUIT";
  char noSpaceInput[100];
  int count = 0;



  cout<< "Type in a Mathematical Expression seperated by spaces. Output will be postfix";
  cin.getline(input, 100, '\n');

  for (int n = 0; n < strlen(input); n++){
    if (input[n] != ' '){
      noSpaceInput[count] = input[n];
      count++;

    }

  }	for (int j = 0; j<strlen(noSpaceInput); j++){
	  cout<<noSpaceInput[j];

	}



  


  
  return 0;
}
