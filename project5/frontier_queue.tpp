#include "frontier_queue.hpp"

// TODO: implement this the same way we implemented pop in the heap lecture. Compare states using getFCost.
template <typename T>
State<T> frontier_queue<T>::pop()
{
  // int i = 0;
  // State<T> lowest_state(-1,-1,-1);
  // while (queue.size() != i) {
  //   if (queue[i].getFCost() < queue[i-1].getFCost()) {
  //     lowest_state = queue[i]; // remove state with lowest f-cost
  //   }
  //   i++;
  // }
  
  // return lowest_state;
  return State<T>(T(),0,0);
}

template <typename T>
void frontier_queue<T>::push(const T &p, std::size_t cost, std::size_t heur)
{
  State<T> pushed_state(p, cost, heur); // create a state to add from the parameters
  queue.push_back(pushed_state); // add state to the queue
  int i = queue.size()-1;

  while(i > 0) { // loop through until you reach the root
    // similar to min heap implementation
    int parent = (i-1)/2; // parent is located at (location of current - 1)/2

    if(queue[i].getFCost() < queue[parent].getFCost()) { // put higher in the queue if f value is lower
      std::swap(queue[i], queue[parent]); // swap the current with the parent
    }
    else { 
      break;
    }
  }
}

template <typename T>
bool frontier_queue<T>::empty() // done
{
  return queue.empty(); // using built-in vector function
}

template <typename T>
bool frontier_queue<T>::contains(const T &p)
{
  // exception: queue is empty
  if(queue.empty()) {
    return false;
  }

  for(int i = 0; i < queue.size(); i++) {
    if(queue[i].getValue() == p) {
      return true; // queue contains the item
    }
  }

  return false; // queue are not contains the item
}

template <typename T>
void frontier_queue<T>::replaceif(const T &p, std::size_t cost)
{

  // TODO
}
