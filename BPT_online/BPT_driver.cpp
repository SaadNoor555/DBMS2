// Searching on a B+ tree in C++

#include "bpt_header.h"

int main() {
  BPTree node;
  node.insert(5);
  node.insert(15);
  node.insert(25);
  node.insert(35);
  node.insert(45);
  node.insert(55);
  node.insert(40);
  node.insert(30);
  node.insert(20);
  node.display(node.getRoot());

  node.search(15);
}