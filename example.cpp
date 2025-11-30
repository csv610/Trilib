#include "trilib.hpp"
#include "veclib.hpp"
#include <iostream>
#include <iomanip>

using namespace JMath;

int main() {
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "=== Trilib Examples ===" << std::endl << std::endl;

    // Example 1: Basic Triangle Operations
    std::cout << "--- Triangle Operations ---" << std::endl;
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {4.0, 0.0, 0.0};
    std::array<double, 3> p3 = {0.0, 3.0, 0.0};

    std::cout << "Triangle vertices:" << std::endl;
    std::cout << "  P1: (" << p1[0] << ", " << p1[1] << ", " << p1[2] << ")" << std::endl;
    std::cout << "  P2: (" << p2[0] << ", " << p2[1] << ", " << p2[2] << ")" << std::endl;
    std::cout << "  P3: (" << p3[0] << ", " << p3[1] << ", " << p3[2] << ")" << std::endl;

    // Calculate area
    double triangle_area = area(p1, p2, p3);
    std::cout << "Area: " << triangle_area << std::endl;

    // Get edge lengths
    std::cout << "Min edge length: " << minlength(p1, p2, p3) << std::endl;
    std::cout << "Max edge length: " << maxlength(p1, p2, p3) << std::endl;

    // Get angles
    auto [angle_p1, angle_p2, angle_p3] = angles(p1, p2, p3);
    std::cout << "Angles (degrees):" << std::endl;
    std::cout << "  At P1: " << angle_p1 << std::endl;
    std::cout << "  At P2: " << angle_p2 << std::endl;
    std::cout << "  At P3: " << angle_p3 << std::endl;

    // Triangle classification
    std::cout << "Classification:" << std::endl;
    std::cout << "  Acute: " << (isAcute(p1, p2, p3) ? "Yes" : "No") << std::endl;
    std::cout << "  Obtuse: " << (isObtuse(p1, p2, p3) ? "Yes" : "No") << std::endl;
    std::cout << "  Degenerate: " << (isDegenerate(p1, p2, p3) ? "Yes" : "No") << std::endl;

    std::cout << std::endl;

    // Example 2: Geometric Properties
    std::cout << "--- Geometric Properties ---" << std::endl;

    // Centroid
    auto centroid_pt = centroid(p1, p2, p3);
    std::cout << "Centroid: (" << centroid_pt[0] << ", "
              << centroid_pt[1] << ", " << centroid_pt[2] << ")" << std::endl;

    // Circumcenter and circumradius
    auto circumcenter_pt = circumcenter(p1, p2, p3);
    double circumradius_val = circumradius(p1, p2, p3);
    std::cout << "Circumcenter: (" << circumcenter_pt[0] << ", "
              << circumcenter_pt[1] << ", " << circumcenter_pt[2] << ")" << std::endl;
    std::cout << "Circumradius: " << circumradius_val << std::endl;

    // Incenter and inradius
    auto incenter_pt = incenter(p1, p2, p3);
    double inradius_val = inradius(p1, p2, p3);
    std::cout << "Incenter: (" << incenter_pt[0] << ", "
              << incenter_pt[1] << ", " << incenter_pt[2] << ")" << std::endl;
    std::cout << "Inradius: " << inradius_val << std::endl;

    // Normal vector
    auto normal_vec = normal(p1, p2, p3);
    std::cout << "Normal vector: (" << normal_vec[0] << ", "
              << normal_vec[1] << ", " << normal_vec[2] << ")" << std::endl;

    std::cout << std::endl;

    // Example 3: Vector Operations
    std::cout << "--- Vector Operations ---" << std::endl;
    std::array<double, 3> v1 = {3.0, 4.0, 0.0};
    std::array<double, 3> v2 = {1.0, 0.0, 0.0};

    std::cout << "Vector v1: (" << v1[0] << ", " << v1[1] << ", " << v1[2] << ")" << std::endl;
    std::cout << "Vector v2: (" << v2[0] << ", " << v2[1] << ", " << v2[2] << ")" << std::endl;

    // Vector operations
    double mag_v1 = magnitude(v1);
    std::cout << "Magnitude of v1: " << mag_v1 << std::endl;

    double dot = dot_product(v1, v2);
    std::cout << "Dot product (v1 · v2): " << dot << std::endl;

    auto cross = cross_product(v1, v2);
    std::cout << "Cross product (v1 × v2): (" << cross[0] << ", "
              << cross[1] << ", " << cross[2] << ")" << std::endl;

    // Unit vector
    auto unit = unit_vector(v1);
    std::cout << "Unit vector of v1: (" << unit[0] << ", "
              << unit[1] << ", " << unit[2] << ")" << std::endl;

    // Angle between vectors
    double angle_val = angle(v1, v2);
    std::cout << "Angle between v1 and v2 (radians): " << angle_val << std::endl;

    std::cout << std::endl;

    // Example 4: Barycentric Coordinates
    std::cout << "--- Barycentric Coordinates ---" << std::endl;
    std::array<double, 3> point = {1.0, 1.0, 0.0};
    auto bary = barycoordinates(p1, p2, p3, point);
    std::cout << "Barycentric coordinates of point (1, 1, 0):" << std::endl;
    std::cout << "  Lambda 1: " << bary[0] << std::endl;
    std::cout << "  Lambda 2: " << bary[1] << std::endl;
    std::cout << "  Lambda 3: " << bary[2] << std::endl;
    std::cout << "  Sum (should be ~1.0): " << (bary[0] + bary[1] + bary[2]) << std::endl;

    return 0;
}
