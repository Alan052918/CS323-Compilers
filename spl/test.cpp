#include <iostream>
#include <vector>

typedef struct Type {
  int a;
} Type;

int main() {
  std::vector<Type *> list;
  Type *type = (Type *)malloc(sizeof(Type));
  type->a = 12;
  list.push_back(type);
  for (Type *t : list) {
    std::cout << t->a << '\n';
  }

  std::vector<int> q;
  q.push_back(12);
  q.push_back(34);
  q.push_back(45);
  for (int i : q) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}
