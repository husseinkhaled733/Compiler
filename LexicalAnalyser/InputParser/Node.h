//
// Created by Samni on 11/28/2024.
//

#ifndef NODE_H
#define NODE_H

class Node {
    public:
        explicit Node(char v);
        Node() = default;
        char value;
        Node* left{};
        Node* right{};
};



#endif //NODE_H
