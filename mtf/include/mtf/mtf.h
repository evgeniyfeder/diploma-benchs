#pragma once

#include <memory>

template <typename T>
class mtf_t
{
private:
   struct node_t
   {
      T data;
      std::shared_ptr<node_t> next;

      explicit node_t(T const & data, std::shared_ptr<node_t> next = nullptr) : data(data), next(next) {}
   };

   void mtf(std::shared_ptr<node_t> ptr, std::shared_ptr<node_t> prev)
   {
      if (prev)
      {
         prev->next = ptr->next;

         ptr->next = head_;
         head_ = ptr;
         sum_cost_ += alpha_;
      }
   }

   std::shared_ptr<node_t> next(std::shared_ptr<node_t> x)
   {
      sum_cost_ += 1;
      return x->next;
   }

public:
   explicit mtf_t(std::size_t alpha) : sum_cost_(0), alpha_(alpha) {}

   bool find(T const & x)
   {
      if (!head_)
         return false;

      std::shared_ptr<node_t> p = head_, prev;
      while (p->next != nullptr)
      {
         if (p->data == x)
         {
            mtf(p, prev);
            return true;
         }

         prev = p;
         p = next(p);
      }

      return false;
   }

   void push_back(T const & x)
   {
      if (!head_)
      {
         head_ = std::make_shared<node_t>(x);
         return;
      }

      std::shared_ptr<node_t> p = head_;
      while (p->next != nullptr)
      {
         p = p->next;
      }

      p->next = std::make_shared<node_t>(x);
   }

   std::size_t sum_cost()
   {
      return sum_cost_;
   }

private:
   std::size_t sum_cost_, alpha_;
   std::shared_ptr<node_t> head_;
};