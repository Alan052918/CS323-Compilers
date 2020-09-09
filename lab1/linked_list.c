#include "linked_list.h"

node *linked_list_init() {
  node *head = (node *)malloc(sizeof(node));
  head->count = 0;
  head->next = NULL;
  return head;
}

void linked_list_free(node *head) {
  node *cur = head;
  node *last;
  while (cur != NULL) {
    last = cur;
    cur = cur->next;
    free(last);
  }
}

char linked_list_string[0x10000];

char *linked_list_tostring(node *head) {
  node *cur = head->next;
  char *position;
  int length = 0;
  while (cur != NULL) {
    position = linked_list_string + length;
    length += sprintf(position, "%d", cur->value);
    cur = cur->next;
    if (cur != NULL) {
      position = linked_list_string + length;
      length += sprintf(position, "->");
    }
  }
  position = linked_list_string + length;
  length += sprintf(position, "%c", '\0');
  return linked_list_string;
}

int linked_list_size(node *head) { return head->count; }

void linked_list_append(node *head, int val) {
  node *cur = head;
  node *new_node;
  while (cur->next != NULL) {
    cur = cur->next;
  }
  new_node = (node *)malloc(sizeof(node));
  new_node->value = val;
  new_node->next = NULL;
  cur->next = new_node;
  head->count++;
}

/* your implementation goes here */

void linked_list_insert(node *head, int val, int index) {
  node *cur = head;
  node *new_node;
  if (index >= linked_list_size(head) || index < 0) {
    return;
  }
  while (index--) {
    cur = cur->next;
  }
  new_node = (node *)malloc(sizeof(node));
  new_node->value = val;
  new_node->next = cur->next;
  cur->next = new_node;
  head->count++;
}

void linked_list_delete(node *head, int index) {
  node *cur = head;
  node *del;
  if (index >= linked_list_size(head) || index < 0) {
    return;
  }
  while (index--) {
    cur = cur->next;
  }
  del = cur->next;
  if (cur->next->next != NULL) {
    cur->next = cur->next->next;
  }
  free(del);
  head->count--;
}

void linked_list_remove(node *head, int val) {
  node *cur = head;
  node *del;
  int found = 0;
  while (cur->next != NULL) {
    if (cur->next->value == val) {
      found = 1;
      break;
    }
    cur = cur->next;
  }
  if (!found) {
    return;
  }
  del = cur->next;
  if (cur->next->next != NULL) {
    cur->next = cur->next->next;
  } else {
    cur->next = NULL;
  }
  free(del);
  head->count--;
}

void linked_list_remove_all(node *head, int val) {
  node *cur = head;
  node *del;
  while (cur->next) {
    if (cur->next->value == val) {
      del = cur->next;
      if (cur->next->next != NULL) {
        cur->next = cur->next->next;
      } else {
        cur->next = NULL;
      }
      free(del);
      head->count--;
    } else {
      cur = cur->next;
    }
  }
}

int linked_list_get(node *head, int index) {
  node *cur = head->next;
  if (index >= linked_list_size(head) || index < 0) {
    return INT32_MIN;
  }
  while (index--) {
    cur = cur->next;
  }
  return cur->value;
}

int linked_list_search(node *head, int val) {
  node *cur = head->next;
  int found = 0;
  int id = 0;
  while (cur != NULL) {
    if (cur->value == val) {
      found = 1;
      break;
    }
    cur = cur->next;
    id++;
  }
  if (found) {
    return id;
  }
  return -1;
}

node *linked_list_search_all(node *head, int val) {
  node *cur = head->next;
  node *idHead = linked_list_init();
  int id = 0;
  while (cur != NULL) {
    if (cur->value == val) {
      linked_list_append(idHead, id);
    }
    cur = cur->next;
    id++;
  }
  return idHead;
}
