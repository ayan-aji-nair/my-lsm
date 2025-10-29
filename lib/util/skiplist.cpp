// C++ code for inserting element in skip list
#include "skiplist.h"
#include <cstdint>
#include <iostream>
#include <cstring>

namespace mylsm {
  Node::Node(std::string key, std::string value, int level) : key(std::move(key)), value(std::move(value))
  {
      // Allocate memory to forward 
      forward = new Node*[level+1];

      // Fill forward array with 0(NULL)
      std::memset(forward, 0, sizeof(Node*)*(level+1));
  };

  Node::~Node() {
    delete[] forward;
  }

  SkipList::SkipList(float P)
  {
      this->P = P;
      level = 0;

      // create header node and initialize key to -1
      header = new Node("-1", "-1", MAXLVL);
  };

  SkipList::~SkipList() {
      Node* node = header;
      while (node) {
          Node* next = node->forward[0];
          delete node;
          node = next;
      }
  }

  // create random level for node
  int SkipList::randomLevel()
  {
      float r = (float)rand()/RAND_MAX;
      int lvl = 0;
      while (r < P && lvl < MAXLVL)
      {
          lvl++;
          r = (float)rand()/RAND_MAX;
      }
      return lvl;
  };

  // create new node
  Node* SkipList::createNode(const Bytes& key, const Bytes& value, int level)
  {
      Node *n = new Node(std::string(key), std::string(value), level);
      return n;
  };

  // Insert given key in skip list
  void SkipList::insert(const Bytes& key, const Bytes& value)
  {

      if (auto it = returnElement(key); it != nullptr) {
        (*it)->value = value;
        return;
      }

      Node *current = header;

      // create update array and initialize it
      Node *update[MAXLVL+1];
      std::memset(update, 0, sizeof(Node*)*(MAXLVL+1));

      /*    start from highest level of skip list
          move the current pointer forward while key 
          is greater than key of node next to current
          Otherwise inserted current in update and 
          move one level down and continue search
      */
      for (int i = level; i >= 0; i--)
      {
          while (current->forward[i] != NULL &&
                current->forward[i]->key < key)
              current = current->forward[i];
          update[i] = current;
      }

      /* reached level 0 and forward pointer to 
        right, which is desired position to 
        insert key. 
      */
      current = current->forward[0];

      /* if current is NULL that means we have reached
        to end of the level or current's key is not equal
        to key to insert that means we have to insert
        node between update[0] and current node */
      if (current == NULL || current->key != key)
      {
          // Generate a random level for node
          int rlevel = randomLevel();

          // If random level is greater than list's current
          // level (node with highest level inserted in 
          // list so far), initialize update value with pointer
          // to header for further use
          if (rlevel > level)
          {
              for (int i=level+1;i<rlevel+1;i++)
                  update[i] = header;

              // Update the list current level
              level = rlevel;
          }

          // create new node with random level generated
          Node* n = createNode(std::string(key), std::string(value), rlevel);

          // insert node by rearranging pointers 
          for (int i=0;i<=rlevel;i++)
          {
              n->forward[i] = update[i]->forward[i];
              update[i]->forward[i] = n;
          }
      }
  };

    // Delete element from skip list
  void SkipList::del(const Bytes& key)
  {
      Node *current = header;

      // create update array and initialize it
      Node *update[MAXLVL+1];
      std::memset(update, 0, sizeof(Node*)*(MAXLVL+1));

      /*    start from highest level of skip list
          move the current pointer forward while key 
          is greater than key of node next to current
          Otherwise inserted current in update and 
          move one level down and continue search
      */
      for(int i = level; i >= 0; i--)
      {
          while(current->forward[i] != NULL  &&
                current->forward[i]->key < key)
              current = current->forward[i];
          update[i] = current;
      }

      /* reached level 0 and forward pointer to 
        right, which is possibly our desired node.*/
      current = current->forward[0];

      // If current node is target node
      if(current != NULL and current->key == key)
      {
          /* start from lowest level and rearrange
            pointers just like we do in singly linked list
            to remove target node */
          for(int i=0;i<=level;i++)
          {
              /* If at level i, next node is not target 
                node, break the loop, no need to move 
                further level */
              if(update[i]->forward[i] != current)
                  break;

              update[i]->forward[i] = current->forward[i];
          }

          // Remove levels having no elements 
          while(level>0 &&
                header->forward[level] == 0)
              level--;
      }
  };

  // Search for element in skip list
  bool SkipList::search(const Bytes& key) const
  {
      Node *current = header;

      /*    start from highest level of skip list
          move the current pointer forward while key 
          is greater than key of node next to current
          Otherwise inserted current in update and 
          move one level down and continue search
      */
      for(int i = level; i >= 0; i--)
      {
          while(current->forward[i] &&
                current->forward[i]->key < key)
              current = current->forward[i];

      }

      /* reached level 0 and advance pointer to 
        right, which is possibly our desired node*/
      current = current->forward[0];

      // If current node have key equal to
      // search key, we have found our target node
      return current and current->key == key;
  };

  std::optional<Node*> SkipList::returnElement(const Bytes& key) const {
      Node *current = header;

      /*    start from highest level of skip list
          move the current pointer forward while key 
          is greater than key of node next to current
          Otherwise inserted current in update and 
          move one level down and continue search
      */
      for(int i = level; i >= 0; i--)
      {
          while(current->forward[i] &&
                current->forward[i]->key < key)
              current = current->forward[i];

      }

      /* reached level 0 and advance pointer to 
        right, which is possibly our desired node*/
      current = current->forward[0];

      // If current node have key equal to
      // search key, we have found our target node
      return current and current->key == key ? current : nullptr;
    
  }

  std::optional<std::string> SkipList::get(const Bytes& key) const {
      if (auto it = returnElement(key); it != nullptr) 
        return (*it)->value;

      return std::nullopt;
  }

  // Display skip list level wise
  void SkipList::displayList()
  {
    std::cout<<"\n*****Skip List*****"<<"\n";
      for (int i=0;i<=level;i++)
      {
          Node *node = header->forward[i];
          std::cout << "Level " << i << ": ";
          while (node != NULL)
          {
            std::cout << node->key<<" ";
              node = node->forward[i];
          }
          std::cout << "\n";
      }
  };
}
