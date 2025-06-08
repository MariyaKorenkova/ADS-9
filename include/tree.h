// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class PMNode {
 public:
  explicit PMNode(char val);
  char value;
  std::vector<std::shared_ptr<PMNode>> children;
};

class PMTree {
 public:
  explicit PMTree(const std::vector<char>& elements);
  std::shared_ptr<PMNode> getRoot() const;

  void collect(std::shared_ptr<PMNode> node, std::vector<char>& path,
               std::vector<std::vector<char>>& result);

 private:
  std::shared_ptr<PMNode> root;
  void build(std::shared_ptr<PMNode> node, std::vector<char> remaining);
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_

