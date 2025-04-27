#include "frontier_queue.hpp"

// TODO: implement this the same way we implemented pop in the heap lecture. Compare states using getFCost.
template <typename T>
State<T> frontier_queue<T>::pop()
{
  State<T> removed_state = queue.front(); // store removed state to return later
  queue.at(0) = queue.back(); // replace root with last element
  queue.pop_back(); // remove root and shrink heap

  // heapify down
  if(!queue.empty()) {
    heapRebuild(0);
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

    if(queue.at(i).getFCost() < queue.at(parent).getFCost()) { // put higher in the queue if f value is lower
      std::swap(queue.at(i), queue.at(parent)); // swap the current with the parent
      i = parent; // move the index up the heap
    }
    else { 
      break; // makes complexity O(log n)
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
    if(queue.at(i).getValue() == p) {
      return true; // queue contains the item
    }
  }

  return false; // queue does not contain the item
}

template <typename T>
void frontier_queue<T>::replaceif(const T &p, std::size_t cost)
{
  int index = -1;
  for(int i = 0; i < queue.size(); i++) {
    if(queue.at(i).getValue() == p) {
      index = i;
      break;
    }
  }

  // exception: replacement is not possible
  if(index == -1) {
    return;
  }

  if(cost < queue.at(index).getPathCost()) { // if the path cost is lower
    queue.at(index).updatePathCost(cost); // change path cost to more optimized path

    int child = index;
    while(child > 0) {
      int parent = (child-1)/2;
      if(queue.at(child).getFCost() < queue.at(parent).getFCost()) {
        std::swap(queue.at(child), queue.at(parent)); // swap child and parent
        child = parent; // bubble up
      }
      else {
        break;
      }
    }
  }     
    
}


// heap rebuild and helper functions
template <typename T>
void frontier_queue<T>::heapRebuild(const int index)
{
  int left_child = 2 * index + 1;
  int right_child = 2 * index + 2;
  int smallest = index;

  if (left_child < queue.size() && queue[left_child].getFCost() < queue[smallest].getFCost()) {
    smallest = left_child;
  }

  if (right_child < queue.size() && queue[right_child].getFCost() < queue[smallest].getFCost()) {
    smallest = right_child;
  }

  if (smallest != index) {
    std::swap(queue[index], queue[smallest]);
    heapRebuild(smallest); // heapify down
  }
} // end heapRebuild

