#ifndef tsdev_calculations_replacer_h
#define tsdev_calculations_replacer_h

#include <functional>
#include <string>
#include <vector>

namespace tsdev {
    namespace calculations {
        using Replacer = std::function<std::string(const std::vector<std::string>&)>;
    }
}

#endif
