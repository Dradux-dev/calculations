#ifndef tsdev_calculations_stack_h
#define tsdev_calculations_stack_h

#include <vector>

#include "elementptr.h"

namespace tsdev {
    namespace calculations {
        template<typename T>
        struct Stack {
            using Node = ElementPtr<T>;

            std::vector<Node> nodes;

            Node createElement(Element<T>* element) {
                Node node(element);
                nodes.push_back(node);
                return node;
            }



            static Stack& instance() {
                static Stack<T> s;
                return s;
            }
        };
    }
}

#endif
