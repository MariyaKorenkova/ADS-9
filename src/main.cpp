// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <vector>
#include "tree.h"

int main() {
  std::ofstream plot("result/plot.csv");
  plot << "n,getAllPerms,getPerm1,getPerm2\n";

  for (int n = 2; n <= 9; ++n) {
    std::vector<char> input;
    for (int i = 0; i < n; ++i)
      input.push_back('1' + i);

    PMTree tree(input);

    std::random_device rd;
    std::mt19937 gen(rd());
    int total = 1;
    for (int i = 1; i <= n; ++i) total *= i;
    std::uniform_int_distribution<> dis(1, total);
    int k = dis(gen);

    auto start = std::chrono::high_resolution_clock::now();
    getAllPerms(tree);
    auto end = std::chrono::high_resolution_clock::now();
    auto t_all = std::chrono::duration_cast<std::chrono::microseconds>(
                   end - start).count();

    start = std::chrono::high_resolution_clock::now();
    getPerm1(tree, k);
    end = std::chrono::high_resolution_clock::now();
    auto t_p1 = std::chrono::duration_cast<std::chrono::microseconds>(
                  end - start).count();

    start = std::chrono::high_resolution_clock::now();
    getPerm2(tree, k);
    end = std::chrono::high_resolution_clock::now();
    auto t_p2 = std::chrono::duration_cast<std::chrono::microseconds>(
                  end - start).count();

    plot << n << "," << t_all << "," << t_p1 << "," << t_p2 << "\n";
    std::cout << "n=" << n << " done\n";
  }

  plot.close();
  return 0;
}

