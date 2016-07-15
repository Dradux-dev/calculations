#include <iostream>

#include <initializer_list>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <tsdev/calculations/calculations.h>

using namespace tsdev::calculations;

int main()
{
    /*
     * Ein Kind mit einem Gewicht von 20kg setzt sich in ein Kettenkarussel. Die Kette ist an einer Scheibe
     * mit einem Durchmesser von 5m befestigt. Die Kette selbst besitzt eine Länge von 7m. Das Karussell
     * dreht sich mit einer Winkelgeschwindigkeit von 1.15 rad s^-1.
     */

    // [N] -> [kg m / s^2]
    UnitTable::instance().add("N", "m kg / s^2");

    // Gegebene Werte
    Double m("m", 20.00f, "kg");
    Double d("d", 5.00f, "m");
    Double l("l", 7.00f, "m");
    Double w("\\omega", 1.15f, "1 / s");

    // Gewichtskraft
    Double g("g", 9.81f, "m / s^2");
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

    std::cout << "Durchmesser: " << std::endl;
    exporter.print(std::cout, d);

    std::cout << "L\\\"ange: " << std::endl;
    exporter.print(std::cout, l);

    std::cout << "Winkelgeschwindigkeit: " << std::endl;
    exporter.print(std::cout, w);

    std::cout << "Erdbeschleunigungskonstante: " << std::endl;
    exporter.print(std::cout, g);

    std::cout << "Gewichtskraft: " << std::endl;
    exporter.print(std::cout, F_g);

    std::cout << "Radius: " << std::endl;
    exporter.print(std::cout, r);

    std::cout << "Radialkraft: " << std::endl;
    exporter.print(std::cout, F_r);

    std::cout << "Kraft: " << std::endl;
    exporter.print(std::cout, F);

    Double alpha("\\alpha", 90, "deg");
    Double sin_alpha("\\alpha_{sin}");
    sin_alpha = Sin(alpha);

    std::cout << "Winkel $\\alpha$: " << std::endl;
    exporter.print(std::cout, alpha);

    std::cout << "Sinus $\\alpha$: " << std::endl;
    exporter.print(std::cout, sin_alpha);

    std::cout << "Sinus Beispiel: " << std::endl
              << ExportStreamer(exporter, sin_alpha);

    return 0;
}
