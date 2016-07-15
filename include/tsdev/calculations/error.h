#ifndef tsdev_calculations_error_h
#define tsdev_calculations_error_h

namespace tsdev {
    namespace calculations {
        template <typename T>
        struct Error  {
            T value;
            T error;

            Error() = default;
            Error(const Error& error) = default;

            Error(T value)
                : value(value),
                  error()
            {}

            Error(T value, T error)
                : value(value),
                  error(error)
            {}

            T relativeError() {
                return error / value;
            }
        };

        using DoubleError = Error<double>;

        template <typename T>
        Error<T> operator+(const Error<T>& lhs, const Error<T>& rhs) {
            return Error<T>(
                lhs.value + rhs.value,
                lhs.error + rhs.error
            );
        }

        template <typename T>
        Error<T> operator+(const Error<T>& lhs, const T& rhs) {
            return lhs + Error<T>(rhs);
        }

        template <typename T>
        Error<T> operator+(const T& lhs, const Error<T>& rhs) {
            return Error<T>(lhs) + rhs;
        }

        template <typename T>
        Error<T> operator-(const Error<T>& lhs, const Error<T>& rhs) {
            return Error<T>(
                lhs.value - rhs.value,
                lhs.error - rhs.error
            );
        }

        template <typename T>
        Error<T> operator-(const Error<T>& lhs, const T& rhs) {
            return lhs - Error<T>(rhs);
        }

        template <typename T>
        Error<T> operator-(const T& lhs, const Error<T>& rhs) {
            return Error<T>(lhs) - rhs;
        }

        template <typename T>
        Error<T> operator*(const Error<T>& lhs, const Error<T>& rhs) {
            return Error<T>(
                lhs.value * rhs.value,
                (lhs.value * rhs.value) * (lhs.relativeError() + rhs.relativeError())
            );
        }

        template <typename T>
        Error<T> operator*(const Error<T>& lhs, const T& rhs) {
            return lhs * Error<T>(rhs);
        }

        template <typename T>
        Error<T> operator*(const T& lhs, const Error<T>& rhs) {
            return Error<T>(lhs) * rhs;
        }

        template <typename T>
        Error<T> operator/(const Error<T>& lhs, const Error<T>& rhs) {
            return Error<T>(
                lhs.value / rhs.value,
                (lhs.value / rhs.value) * (lhs.relativeError() - rhs.relativeError())
            );
        }

        template <typename T>
        Error<T> operator/(const Error<T>& lhs, const T& rhs) {
            return lhs / Error<T>(rhs);
        }

        template <typename T>
        Error<T> operator/(const T& lhs, const Error<T>& rhs) {
            return Error<T>(lhs) / rhs;
        }
    }
}

#endif
