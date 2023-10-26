
#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <stdio.h>
#include <stdlib.h>

struct node {
  int data;
  struct node *next;
};

struct BigInteger {
  struct node *HEAD_node;
  long int leng;
  char SiGN;
};

struct node *insert_begin(struct node *HEAD_node, int val);
void insert_tail(struct BigInteger *num, int element);
long int leng(struct node *HEAD_node);
void display_linkedList(struct node *link);
void display(struct BigInteger b);
struct BigInteger initialize(char *s);
struct node *rev(struct node *HEAD_node);
int compare_twonodes(struct BigInteger num1, struct BigInteger num2);
struct BigInteger add(struct BigInteger num1, struct BigInteger num2);
struct BigInteger sub(struct BigInteger num1, struct BigInteger num2);
struct BigInteger mul(struct BigInteger num1, struct BigInteger num2);
struct BigInteger div1(struct BigInteger num1, struct BigInteger num2);
struct BigInteger mod(struct BigInteger num1, struct BigInteger num2);
void fREE_LL(struct BigInteger *num);

#endif 

