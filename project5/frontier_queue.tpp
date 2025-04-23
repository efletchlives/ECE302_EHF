#include "frontier_queue.hpp"

template <typename T>
State<T> frontier_queue<T>::pop()
{

  // TODO: implement this the same way we implemented pop in the heap lecture. Compare states using getFCost.

  return State<T>(T(), 0, 0);
}

template <typename T>
void frontier_queue<T>::push(const T &p, std::size_t cost, std::size_t heur)
{

  // TODO: implement this the same way we implemented push in the heap lecture.
}

template <typename T>
bool frontier_queue<T>::empty()
{
  return queue.empty(); // using built-in vector function
}

template <typename T>
bool frontier_queue<T>::contains(const T &p)
{
  int i = 0;

  while(true) {
    if (queue[i].getValue() == p) {
      break;
    }
    else {
      i++;
    }
    // exception: if no items in vector are the specified item
    if(i == queue.size() - 1) {
      return false;
    }
  }

  return true; // queue contains the item
}

template <typename T>
void frontier_queue<T>::replaceif(const T &p, std::size_t cost)
{

  // TODO
}
