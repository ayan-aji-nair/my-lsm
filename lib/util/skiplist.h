#pragma once

#include "common/types.h"
#include <optional>
#include <string>


namespace mylsm {

  class Node {
  public:
      std::string key;
      std::string value;

      // Array to hold pointers to node of different level 
      Node **forward;
      Node(std::string, std::string, int);
      ~Node();
  };

  // Class for Skip list
  class SkipList{
      // Maximum level for this skip list
      static constexpr int MAXLVL = 16;
      // P is the fraction of the nodes with level 
      // i pointers also having level i+1 pointers
      float P;
      // current level of skip list
      int level;
      // pointer to header node
      Node *header;
  public:
      SkipList(float);
      ~SkipList();
      int randomLevel();
      Node* createNode(const Bytes&, const Bytes&, int);
      void insert(const Bytes&, const Bytes&);
      bool search(const Bytes&) const;
      void del(const Bytes&);
      std::optional<std::string> get(const Bytes&) const;
      void displayList();
  private:
      std::optional<Node*> returnElement(const Bytes&) const;
  };
}
