#ifndef tsdev_calculations_elementptr_h
#define tsdev_calculations_elementptr_h

#include <string>
#include <vector>

#include "element.h"
#include "formatter.h"


namespace tsdev {
    namespace calculations {
        // Simple std::shared_ptr Wrapper to enable template operators
        template <typename T>
        struct ElementPtr {
            typename Element<T>::Ptr ptr;

            ElementPtr() = default;
            ElementPtr(const ElementPtr &ptr) = default;

            template <typename Y>
            explicit ElementPtr(Y* p)
                : ptr(p)
            {}

            ElementPtr(typename Element<T>::Ptr ptr)
                : ptr(ptr)
            {}

            void reset(T* p) {
                ptr.reset(p);
            }

            Element<T>& operator*() {
                return *ptr;
            }

            const Element<T>& operator*() const {
                return *ptr;
            }

            Element<T>* operator->() {
                return ptr.get();
            }

            const Element<T>* operator->() const {
                return ptr.get();
            }

            virtual std::string getPrintCommands(int level, int maxLevel, bool showNames, Formatter& formatter) const {
                std::string elementName = ptr->getName();
                if(elementName.length() > 0 && showNames) {
                    return elementName;
                }

                return ptr->getPrintCommands(level, maxLevel, showNames, formatter);
            }

            template <typename TCast>
            std::shared_ptr<TCast> dynamic_pointer_cast() const {
                return std::dynamic_pointer_cast<TCast>(this->ptr);
            }
        };
    }
}

#endif
