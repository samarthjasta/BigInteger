#include "BigInteger.h"

#include <stdio.h>
#include <stdlib.h>

struct node *insert_begin_begin_begin_begin_begin(struct node *HEAD_node, int val) {
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  if (!temp) {
    printf("Memory Not Allocated!");
    exit(1);
  }
  temp->data = val;
  temp->next = HEAD_node;
  return temp;
}

void insert_begin_tail(struct BigInteger *num, int element) {
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  if (temp == NULL) {
    printf("memory allocation failed\n");
    return;
  }
  temp->data = element;
  temp->next = NULL;
  num->leng += 1;
  if (num->HEAD_node == NULL) {
    num->HEAD_node = temp;
    return;
  }
  struct node *itr = num->HEAD_node;
  while (itr->next != NULL) {
    itr = itr->next;
  }
  itr->next = temp;
}

long int leng(struct node *HEAD_node) {
  long int count = 0;
  while (HEAD_node) {
    HEAD_node = HEAD_node->next;
    count++;
  }
  return count;
}

void display_linkedList(struct node *link) {
  if (!link)
    return;
  display_linkedList(link->next);
  printf("%d", link->data);
}

void display(struct BigInteger b) {
  if (b.HEAD_node == NULL) {
    printf("0");
    return;
  }
  if (b.SiGN == '-')
    printf("-");
  display_linkedList(b.HEAD_node);
}

struct BigInteger initialize(char *s) {
  struct BigInteger b;
  b.HEAD_node = NULL;
  if (s[0] == '-')
    b.SiGN = '-';
  else
    b.SiGN = '+';
  int i;
  if (b.SiGN == '-')
    i = 1;
  else
    i = 0;
  for (i; s[i] != '\0'; i++) {
    b.HEAD_node = insert_begin_begin_begin_begin_begin(b.HEAD_node, s[i] - '0'); 
  }
  b.leng = leng(b.HEAD_node);
  return b;
}

struct node *rev(struct node *HEAD_node) {
  struct node *back = NULL, *front = NULL, *current = HEAD_node;
  while (current != NULL) {
    front = current->next;
    current->next = back;
    back = current;
    current = front;
  }
  return back;
}

int compare_twonodes(struct BigInteger num1, struct BigInteger num2) {
  if (num2.leng > num1.leng) {
    return -1; 
  } else if (num2.leng == num1.leng) {
    int return_val = 0;
    num1.HEAD_node = rev(num1.HEAD_node);
    num2.HEAD_node = rev(num2.HEAD_node);
    struct node *HEAD_node1 = num1.HEAD_node, *HEAD_node2 = num2.HEAD_node;
    while (HEAD_node1 != NULL && HEAD_node2 != NULL) {
      if (HEAD_node2->data > HEAD_node1->data) {
        return_val = -1; 
        break;
      } else if (HEAD_node1->data > HEAD_node2->data) { 
        return_val = 1; 
        break;
      }
      HEAD_node1 = HEAD_node1->next;
      HEAD_node2 = HEAD_node2->next;
    }
    num1.HEAD_node = rev(num1.HEAD_node);
    num2.HEAD_node = rev(num2.HEAD_node);
    return return_val;
  }
  return 1; 
}

struct BigInteger add(struct BigInteger num1, struct BigInteger num2) {
  struct BigInteger num3;
  num3.HEAD_node = NULL;
  num3.SiGN = '+';
  num3.leng = 0;

  if (num1.SiGN == '-' && num2.SiGN == '-') {
    num3.SiGN = '-';
  } else if (num1.SiGN == '-') {
    num1.SiGN = '+';
    num3 = sub(num2, num1);
    num1.SiGN = '-';
    return num3;
  } else if (num2.SiGN == '-') {
    num2.SiGN = '+';
    num3 = sub(num1, num2);
    num2.SiGN = '-';
    return num3;
  }

  struct node *l1 = num1.HEAD_node, *l2 = num2.HEAD_node;
  int sum, carry = 0;

  while (l1 != NULL || l2 != NULL || carry != 0) {
    int d1 = (l1 != NULL) ? l1->data : 0;
    int d2 = (l2 != NULL) ? l2->data : 0;

    sum = d1 + d2 + carry;
    carry = sum / 10;
    insert_begin_tail(&num3, sum % 10);

    if (l1 != NULL)
      l1 = l1->next;
    if (l2 != NULL)
      l2 = l2->next;
  }
  num3.leng = leng(num3.HEAD_node);
  return num3;
}

struct BigInteger sub(struct BigInteger num1, struct BigInteger num2) {
  struct BigInteger num3;
  num3.HEAD_node = NULL;
  num3.SiGN = '+';
  num3.leng = 0;

  if (num1.SiGN == '-' && num2.SiGN == '+') {
    num1.SiGN = '+';
    num3 = add(num1, num2);
    num1.SiGN = '-';
    num3.SiGN = '-';
    return num3;
  } else if (num1.SiGN == '+' && num2.SiGN == '-') {
    num2.SiGN = '+';
    num3 = add(num1, num2);
    num2.SiGN = '-';
    return num3;
  } else if (num1.SiGN == '-' && num2.SiGN == '-') {
    num2.SiGN = '+';
    num1.SiGN = '+';
    num3 = sub(num2, num1);
    num2.SiGN = '-';
    num1.SiGN = '-';
    return num3;
  } else if (compare_twonodes(num1, num2) == -1) {
    struct BigInteger temp = num1;
    num1 = num2;
    num2 = temp;
  }

  struct node *l1 = num1.HEAD_node, *l2 = num2.HEAD_node;
  int diff, borrow = 0;

  while (l1 != NULL || l2 != NULL) {
    int d1 = (l1 != NULL) ? l1->data : 0;
    int d2 = (l2 != NULL) ? l2->data : 0;

    diff = d1 - d2 - borrow;

    if (diff < 0) {
      diff += 10;
      borrow = 1;
    } else {
      borrow = 0;
    }

    insert_begin_tail(&num3, diff);

    if (l1 != NULL)
      l1 = l1->next;
    if (l2 != NULL)
      l2 = l2->next;
  }
  num3.HEAD_node = rev(num3.HEAD_node);
  while (num3.HEAD_node != NULL && num3.HEAD_node->data == 0) {
    struct node *temp = num3.HEAD_node;
    num3.HEAD_node = num3.HEAD_node->next;
    free(temp);
  }
  num3.HEAD_node = rev(num3.HEAD_node);
  num3.leng = leng(num3.HEAD_node);
  return num3;
}

struct BigInteger mul(struct BigInteger num1, struct BigInteger num2) {
  struct node *n1 = num1.HEAD_node, *n2 = num2.HEAD_node;
  struct BigInteger num3 = initialize(""); 
  num3.leng = 0;
  if (n1 == NULL || n2 == NULL) {
    return num3;
  }
  struct BigInteger mid, result = initialize("");
  int carry = 0, product = 0, i = 0;
  while (n2 != NULL) {
    n1 = num1.HEAD_node;
    carry = 0;
    mid = initialize("");
    for (int j = 0; j < i; j++) {
      insert_begin_tail(&mid, 0);
    }
    while (n1 != NULL) {
      product = (n1->data) * (n2->data) + carry;
      insert_begin_tail(&mid, product % 10);
      carry = product / 10;
      n1 = n1->next;
    }

    if (carry > 0) {
      insert_begin_tail(&mid, carry);
    }

    result = add(mid, result);
    struct node *current = mid.HEAD_node;
    while (current != NULL) {
      struct node *temp = current;
      current = current->next;
      free(temp);
    }

    n2 = n2->next;
    i++;
  }
  if (num1.SiGN != num2.SiGN) {
    result.SiGN = '-';
  }
  return result;
}

struct BigInteger div1(struct BigInteger num1, struct BigInteger num2) {
  struct BigInteger num3 = initialize("0");
  num3.leng = 0;
  num3.SiGN = '+';
  char sig = '+';
  int flag = 0;
  if (num2.leng == 1 && num2.HEAD_node->data == 0) {
    printf("Error division by zero");
    return num3;
  }
  if (num1.SiGN != num2.SiGN)
    sig = '-';
  char t1 = num1.SiGN;
  char t2 = num2.SiGN;
  num1.SiGN = '+';
  num2.SiGN = '+';
  struct BigInteger temp = add(num2, initialize("0"));
  while (compare_twonodes(num1, temp) >= 0) {
    temp = add(temp, num2);
    num3 = add(num3, initialize("1"));
    flag = 1;
  }
  struct BigInteger zero = initialize("0");
  if (flag)
    num3.SiGN = sig;
  num1.SiGN = t1;
  num2.SiGN = t2;
  return num3;
}

struct BigInteger mod(struct BigInteger num1, struct BigInteger num2) {
  struct BigInteger num3 = initialize("0");
  num3.leng = 0;
  num3.SiGN = '+';
  char sig = '+';
  int flag = 0;
  if (num2.leng == 1 && num2.HEAD_node->data == 0) {
    printf("Error division by zero");
    return num3;
  }
  if (num1.SiGN != num2.SiGN)
    sig = '-';
  char t1 = num1.SiGN;
  char t2 = num2.SiGN;
  num1.SiGN = '+';
  num2.SiGN = '+';
  struct BigInteger temp = add(num2, initialize("0"));
  while (compare_twonodes(num1, temp) >= 0) {
    temp = add(temp, num2);
    num3 = add(num3, initialize("1"));
  }
  struct BigInteger temp2 = sub(temp, num2);
  struct BigInteger modu = sub(num1, temp2);
  num1.SiGN = t1;
  num2.SiGN = t2;
  return modu;
}
