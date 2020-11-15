#ifndef DEF_H
#define DEF_H

typedef enum { false, true } bool;

typedef struct ListNode {
  char *key;
  int level;
  struct ListNode *next;
} ListNode;

bool insertNode(ListNode **head, char *k, int l);
bool findDuplicate(ListNode *head, char *k, int l);

#endif  // DEF_H
