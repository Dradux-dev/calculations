#include <iostream>

#include <initializer_list>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../lib/variable.h"
#include "../lib/elementptr.h"
#include "../lib/exporter.h"
#include "../lib/value.h"
#include "../lib/plus.h"
#include "../lib/multiplicate.h"
#include "../lib/latex.h"
#include "../lib/divide.h"
#include "../lib/pow.h"
#include "../lib/reference.h"
#include "../lib/minus.h"
#include "../lib/double.h"
#include "../lib/sin.h"

using namespace tsdev::calculations;

int main()
{
    /*
     * Ein Kind mit einem Gewicht von 20kg setzt sich in ein Kettenkarussel. Die Kette ist an einer Scheibe
     * mit einem Durchmesser von 5m befestigt. Die Kette selbst besitzt eine Länge von 7m. Das Karussell
     * dreht sich mit einer Winkelgeschwindigkeit von 1.15 rad s^-1.
     */

    // [N] -> [kg m / s^2]
    UnitTable::instance().add(
        {std::make_pair<std::string, int>("N", 1)},
        {std::make_pair<std::string, int>("m", 1), std::make_pair<std::string, int>("kg", 1), std::make_pair<std::string, int>("s", -2)}
    );

    // Gegebene Werte
    Double m("m", 20.00f, {std::make_pair<std::string, int>("kg", 1)});
    Double d("d", 5.00f, {std::make_pair<std::string, int>("m", 1)});
    Double l("l", 7.00f, {std::make_pair<std::string, int>("m", 1)});
    Double w("\\omega", 1.15f, {std::make_pair<std::string, int>("s", -1)});

    // Gewichtskraft
    Double g("g", 9.81f, {std::make_pair<std::string, int>("m", 1), std::make_pair<std::string, int>("s", -2)});
    Double F_g("F_{g}");
    F_g = m * g;

    // Radialkraft
    Double F_r("F_{r}");
    Double r("r");
    r = d/2.0 + l;
    F_r = m * Pow(w,2) * Ref(r);

    // Gesamtkraft
    Double F("F");
    F = Ref(F_g) + Ref(F_r);

    // LaTeX export
    Exporter exporter(std::shared_ptr<Formatter>(new LatexFormatter()));
    std::cout << "Masse: " << std::endl;
    exporter.print(std::cout, m);
    std::cout << "\\vspace{0.5cm}" << std::endl;

    std::cout << "Durchmesser: " << std::endl;
    exporter.print(std::cout, d);
    std::cout << "\\vspace{0.5cm}" << std::endl;

    std::cout << "L\\\"ange: " << std::endl;
    exporter.print(std::cout, l);
    std::cout << "\\vspace{0.5cm}" << std::endl;

    std::cout << "Winkelgeschwindigkeit: " << std::endl;
    exporter.print(std::cout, w);
    std::cout << "\\vspace{0.5cm}" << std::endl;

    std::cout << "Erdbeschleunigungskonstante: " << std::endl;
    exporter.print(std::cout, g);
    std::cout << "\\vspace{0.5cm}" << std::endl;

    std::cout << "Gewichtskraft: " << std::endl;
    exporter.print(std::cout, F_g);
    std::cout << "\\vspace{0.5cm}" << std::endl;

    std::cout << "Radius: " << std::endl;
    exporter.print(std::cout, r);
    std::cout << "\\vspace{0.5cm}" << std::endl;

    std::cout << "Radialkraft: " << std::endl;
    exporter.print(std::cout, F_r);
    std::cout << "\\vspace{0.5cm}" << std::endl;

    std::cout << "Kraft: " << std::endl;
    exporter.print(std::cout, F);
    std::cout << "\\vspace{0.5cm}" << std::endl;

    Double alpha("\\alpha", 90, {std::make_pair<std::string, int>("deg", 1)});
    Double sin_alpha("\\alpha_{sin}");

    std::cout << "Sinus Beispiel: " << std::endl;
    sin_alpha = Sin(alpha);
    exporter.print(std::cout, alpha);
    exporter.print(std::cout, sin_alpha);
    std::cout << "\\vspace{0.5cm}" << std::endl;

    return 0;
}
