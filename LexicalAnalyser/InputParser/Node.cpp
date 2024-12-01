//
// Created by Samni on 11/28/2024.
//

#include "Node.h"

bool Node::isLeaf() const {
    return this->left == nullptr && this->right == nullptr;
}
Node::Node(const char v) {
    this->value = v;
}