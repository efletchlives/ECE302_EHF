#include "frontier_queue.hpp"

// TODO: implement this the same way we implemented pop in the heap lecture. Compare states using getFCost.
template <typename T>
State<T> frontier_queue<T>::pop()
{
  State<T> removed_state = queue.front(); // store removed state to return later
  queue[0] = queue.back(); // replace root with last element
  queue.pop_back(); // remove root and shrink heap

  // heapify down
  int i = 0;
  int left, right; // children
  
  while((i*2 + 1) < queue.size()) { // loop while a child is still possible
    int pos = i; // store possible new position of current
    left = i*2 + 1; // left child of position i is stored at (i*2) + 1
    right = i*2 + 2; // right child of position i is stored at (i*2) + 2
    int smaller = left; 
    // find smaller child
    if (queue[left].getFCost() > queue[right].getFCost()) {
      smaller = right;
    }
    else {
      smaller = left;
    }

    // compare current with smaller child
    if(queue[pos].getFCost() > queue[smaller].getFCost()) { // if current > smaller child, swap
      std::swap(queue[i], queue[smaller]);
      i = smaller;
    }
    else {
      break;
    }
  }
  return removed_state;
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

  for (int i = 0; i < queue.size(); i++) {
    if(queue[i].getValue() == p) {

      if(cost < queue[i].getFCost()) { // if the path cost is lower
        queue[i].updatePathCost(cost); // change path cost to more optimized path
        std::size_t og_cost = queue[i].getFCost();
        queue.erase(queue.begin() + i); // remove original state
        push(p, cost, og_cost-cost); // push the new state to the queue
      }
    }
  }
  // TODO
}
