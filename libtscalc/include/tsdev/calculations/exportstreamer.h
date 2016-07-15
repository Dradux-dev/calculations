#ifndef tsdev_calculations_exportstreamer_h
#define tsdev_calculations_exportstreamer_h

#include <iostream>

#include "exporter.h"
#include "variable.h"

namespace tsdev {
    namespace calculations {
        template <typename T>
        struct _ExportStreamer {
            Exporter& exporter;
            Variable<T>& var;

            explicit _ExportStreamer(Exporter& exporter, Variable<T>& var)
                : exporter(exporter),
                  var(var)
            {}
        };

        template <typename T>
        _ExportStreamer<T> ExportStreamer(Exporter& exporter, Variable<T>& var) {
            return _ExportStreamer<T>(exporter, var);
        }

        template <typename T>
        std::ostream& operator <<(std::ostream& os, _ExportStreamer<T> es) {
            es.exporter.print(os, es.var);
            return os;
        }
    }
}

#endif
