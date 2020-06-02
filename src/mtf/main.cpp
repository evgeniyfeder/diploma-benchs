#include "mtf/mtf.h"
#include "mtf/lazy_mtf.h"
#include "mtf/opt.h"

#include <cli11/CLI11.hpp>

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

int main(int argc, char * argv[])
{
   CLI::App app("mtf tester");

   std::size_t start = 100, step = 100, count = 100;
   std::size_t list_size = 100;
   std::string request_variant = "random";
   std::string output_f;

   app.add_option("--alpha-start,-a", start, "constant for matching model start value");
   app.add_option("--alpha-step", step, "constant for matching model step");
   app.add_option("--count,-c", count, "count");
   app.add_option("--list-size,-s", list_size, "size for the input list");
   app.add_option("--output,-o", output_f, "path to output csv file")->required();
   app.add_set("--fill", request_variant, {"random", "seq", "one-two"});

   CLI11_PARSE(app, argc, argv);

   std::ofstream output(output_f, std::ios::trunc);

   for (std::size_t i = 0; i < count; i++)
   {
      std::size_t alpha = start + i * step, m = alpha * list_size;
      std::cout << alpha << std::endl;

      mtf_t<std::size_t> mtf(alpha);
      lazy_mtf_t<std::size_t> lazy_mtf(alpha);

      for (std::size_t i = 0; i < list_size; ++i)
      {
         mtf.push_back(i);
         lazy_mtf.push_back(i);
      }

      std::vector<std::size_t> requests;

      requests.reserve(m);
      for (std::size_t i = 0; i < m; i++)
      {
         if (request_variant == "seq")
            requests.push_back(i % list_size);
         else if (request_variant == "random")
            requests.push_back(std::rand() % list_size);
         else if (request_variant == "one-two")
            requests.push_back(i % 2);
      }

      std::shuffle(requests.begin(), requests.end(), std::mt19937(std::random_device()()));

      for (std::size_t req: requests)
      {
         mtf.find(req);
         lazy_mtf.find(req);
      }

      std::size_t opt_const = count_opt_operations(requests);
      output << alpha << ", " << static_cast<double>(mtf.sum_cost()) / opt_const
             << ", " << static_cast<double>(lazy_mtf.sum_cost()) / opt_const << std::endl;
   }
}