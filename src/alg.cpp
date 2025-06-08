// Copyright 2022 NNTU-CS
#include "tree.h"

#include <vector>
#include <memory>
#include <algorithm>
#include <chrono>
#include <random>
#include <iostream>

PMNode::PMNode(char val) : value(val) {}

PMTree::PMTree(const std::vector<char>& elements) {
  root = std::make_shared<PMNode>('\0');
  build(root, elements);
}

std::shared_ptr<PMNode> PMTree::getRoot() const {
  return root;
}

void PMTree::build(std::shared_ptr<PMNode> node, std::vector<char> remaining) {
  if (remaining.empty()) return;

  std::sort(remaining.begin(), remaining.end());

  for (size_t i = 0; i < remaining.size(); ++i) {
    char val = remaining[i];
    std::shared_ptr<PMNode> child = std::make_shared<PMNode>(val);
    node->children.push_back(child);

    std::vector<char> next_remaining = remaining;
    next_remaining.erase(next_remaining.begin() + i);
    build(child, next_remaining);
  }
}

void PMTree::collect(std::shared_ptr<PMNode> node,
                     std::vector<char>& path,
                     std::vector<std::vector<char>>& result) {
  if (node->value != '\0') path.push_back(node->value);
  if (node->children.empty()) {
    if (!path.empty()) result.push_back(path);
  } else {
    for (auto& child : node->children) {
      collect(child, path, result);
    }
  }
  if (!path.empty()) path.pop_back();
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> path;
  tree.collect(tree.getRoot(), path, result);
  return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  auto all = getAllPerms(tree);
  if (num <= 0 || num > static_cast<int>(all.size())) return {};
  return all[num - 1];
}

int factorial(int n) {
  return (n <= 1) ? 1 : n * factorial(n - 1);
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  std::vector<char> result;
  std::vector<char> available;

  for (auto& child : tree.getRoot()->children)
    available.push_back(child->value);

  std::sort(available.begin(), available.end());

  --num;
  int n = static_cast<int>(available.size());

  while (n--) {
    int fact = factorial(n);
    int index = num / fact;
    num %= fact;
    if (index >= static_cast<int>(available.size())) return {};
    result.push_back(available[index]);
    available.erase(available.begin() + index);
  }

  return result;
}


