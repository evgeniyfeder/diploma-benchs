#include "mtf.h"
#include "lazy_mtf.h"
#include "opt.h"

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

int main()
{
   const std::size_t ALPHA = 100, LIST_SIZE = 1000, M = ALPHA * LIST_SIZE;
   std::cout << "ALPHA: " << ALPHA << " LIST_SIZE:"  << LIST_SIZE << std::endl;

   mtf_t<std::size_t> mtf(ALPHA);
   lazy_mtf_t<std::size_t> lazy_mtf(ALPHA);

   for (std::size_t i = 0; i < LIST_SIZE; ++i)
   {
      mtf.push_back(i);
      lazy_mtf.push_back(i);
   }

   std::vector<std::size_t> requests;

   requests.reserve(M);
   for (std::size_t i = 0; i < M; i++)
   {
      requests.push_back(i % LIST_SIZE);
   }

   std::shuffle(requests.begin(), requests.end(), std::mt19937(std::random_device()()));

   for (std::size_t req: requests)
   {
      mtf.find(req);
      lazy_mtf.find(req);
   }

   std::cout << "MTF:" << mtf.sum_cost() << std::endl;
   std::cout << "LAZY_MTF:" << lazy_mtf.sum_cost() << std::endl;
   std::cout << "OPT:" << count_opt_operations(requests) << std::endl;
}