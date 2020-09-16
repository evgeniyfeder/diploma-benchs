#pragma once

#include <memory>
#include <vector>
#include <map>

template <typename T>
std::size_t count_opt_operations(std::vector<T> requests)
{
   T max_item = {};
   for (auto && request : requests)
      max_item = std::max(max_item, request);

   auto comp = [](T const & a, T const & b) { return a > b; };
   std::map<T, std::size_t, decltype(comp)> count(comp);
   for (auto && request : requests)
      count[request]++;

   std::size_t i = 0, sum = 0;
   for (auto & [key, value]: count)
      sum += value * (i++);
   return sum;
}