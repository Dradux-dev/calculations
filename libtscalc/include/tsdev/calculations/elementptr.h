#ifndef tsdev_calculations_elementptr_h
#define tsdev_calculations_elementptr_h

#include <string>
#include <vector>

#include "element.h"
#include "formatter.h"


namespace tsdev {
    namespace calculations {
        /**
         * Pointer class for the elements.
         *
         * @param T Data type of the stored element.
         *
         * @author Tarek Schwarzinger
         */
        template <typename T>
        struct ElementPtr {
            // Simple std::shared_ptr Wrapper to enable template operators
            typename Element<T>::Ptr ptr;

            ElementPtr() = default;
            ElementPtr(const ElementPtr &ptr) = default;

            /**
             * @brief Pointer constructor
             *
             * Creates a new element pointer with specified content.
             *
             * @param Y Type of the given pointer.
             * @param p The given pointer.
             */
            template <typename Y>
            explicit ElementPtr(Y* p)
                : ptr(p)
            {}


            /**
             * @brief Shared pointer constructor
             *
             * Creates a new element pointer by a given shared pointer.
             *
             * @param ptr The given shared pointer.
             */
            ElementPtr(typename Element<T>::Ptr ptr)
                : ptr(ptr)
            {}

            /**
             * Resets the element pointer and stores a new element pointer
             * in it.
             *
             * @param p The new element address.
             */
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

            /**
             * @brief String conversion
             *
             * Converts the element stored in this pointer to a string.
             *
             * @param level The actual level in the tree.
             * @param maxLevel The maximum level in the tree.
             * @param showNames Defines if the names shall be displayed or not.
             * @param formatter The output formatter.
             *
             * @return Returns the created string.
             */
            virtual std::string getPrintCommands(int level, int maxLevel, bool showNames, Formatter& formatter) const {
                std::string elementName = ptr->getName();
                if(elementName.length() > 0 && showNames) {
                    return elementName;
                }

                return ptr->getPrintCommands(level, maxLevel, showNames, formatter);
            }

            /**
             * @brief Pointer typecast
             *
             * Casts the stored pointer.
             *
             * @param TCast The destination data type for the cast.
             */
            template <typename TCast>
            std::shared_ptr<TCast> dynamic_pointer_cast() const {
                return std::dynamic_pointer_cast<TCast>(this->ptr);
            }
        };
    }
}

#endif
