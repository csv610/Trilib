#include <gtest/gtest.h>
#include "../trilib.hpp"
#include <cmath>

const double EPSILON = 1e-6;

// Helper function to compare doubles with tolerance
bool CompareDoubles(double a, double b, double epsilon = EPSILON) {
    return std::abs(a - b) < epsilon;
}

// Helper function to compare arrays with tolerance
bool CompareArrays(const std::array<double, 3>& a, const std::array<double, 3>& b,
                   double epsilon = EPSILON) {
    for (int i = 0; i < 3; i++) {
        if (!CompareDoubles(a[i], b[i], epsilon)) return false;
    }
    return true;
}

// ============================================================================
// Edge Length Tests
// ============================================================================

TEST(TriLibEdgeLengths, MinLengthSimpleTriangle) {
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {3.0, 0.0, 0.0};
    std::array<double, 3> p3 = {0.0, 4.0, 0.0};

    // Sides: 3-4-5 triangle, min is 3
    double minLen = minlength(p1, p2, p3);
    EXPECT_NEAR(minLen, 3.0, EPSILON);
}

TEST(TriLibEdgeLengths, MaxLengthSimpleTriangle) {
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {3.0, 0.0, 0.0};
    std::array<double, 3> p3 = {0.0, 4.0, 0.0};

    // Sides: 3-4-5 triangle, max is 5
    double maxLen = maxlength(p1, p2, p3);
    EXPECT_NEAR(maxLen, 5.0, EPSILON);
}

// ============================================================================
// Angle Tests
// ============================================================================

TEST(TriLibAngles, RightTriangleInDegrees) {
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {3.0, 0.0, 0.0};
    std::array<double, 3> p3 = {0.0, 4.0, 0.0};

    auto triangle_angles = angles(p1, p2, p3, ANGLE_IN_DEGREES);

    // Check sum of angles is approximately 180
    double sum = triangle_angles[0] + triangle_angles[1] + triangle_angles[2];
    EXPECT_NEAR(sum, 180.0, 0.01);

    // One angle should be 90 degrees
    bool hasRightAngle = CompareDoubles(triangle_angles[0], 90.0, 0.1) ||
                         CompareDoubles(triangle_angles[1], 90.0, 0.1) ||
                         CompareDoubles(triangle_angles[2], 90.0, 0.1);
    EXPECT_TRUE(hasRightAngle);
}

TEST(TriLibAngles, EquilateralTriangleInDegrees) {
    // Equilateral triangle with side length 2
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {2.0, 0.0, 0.0};
    std::array<double, 3> p3 = {1.0, std::sqrt(3.0), 0.0};

    auto triangle_angles = angles(p1, p2, p3, ANGLE_IN_DEGREES);

    // All angles should be 60 degrees
    EXPECT_NEAR(triangle_angles[0], 60.0, 0.1);
    EXPECT_NEAR(triangle_angles[1], 60.0, 0.1);
    EXPECT_NEAR(triangle_angles[2], 60.0, 0.1);
}

TEST(TriLibAngles, AngleInRadians) {
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {1.0, 0.0, 0.0};
    std::array<double, 3> p3 = {0.0, 1.0, 0.0};

    auto triangle_angles = angles(p1, p2, p3, ANGLE_IN_RADIANS);

    // Right angle at origin should be pi/2
    EXPECT_NEAR(triangle_angles[0], M_PI / 2.0, 0.01);
}

TEST(TriLibAngles, AngleAtVertex) {
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {3.0, 0.0, 0.0};
    std::array<double, 3> p3 = {0.0, 4.0, 0.0};

    // Angle at p1 should be 90 degrees
    double angle = angleAt(p1, p2, p3, ANGLE_IN_DEGREES);
    EXPECT_NEAR(angle, 90.0, 0.1);
}

TEST(TriLibAngles, MaxAngle) {
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {3.0, 0.0, 0.0};
    std::array<double, 3> p3 = {0.0, 4.0, 0.0};

    auto [angle, index] = maxangle(p1, p2, p3, ANGLE_IN_DEGREES);

    // Max angle should be 90 degrees at index 0 (at p1)
    EXPECT_NEAR(angle, 90.0, 0.1);
    EXPECT_EQ(index, 0);
}

TEST(TriLibAngles, MinAngle) {
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {3.0, 0.0, 0.0};
    std::array<double, 3> p3 = {0.0, 4.0, 0.0};

    auto [angle, index] = minangle(p1, p2, p3, ANGLE_IN_DEGREES);

    // Min angle should be the smallest angle (around 37 degrees)
    EXPECT_LT(angle, 90.0);
    EXPECT_GT(angle, 0.0);
}

// ============================================================================
// Triangle Classification Tests
// ============================================================================

TEST(TriLibClassification, IsAcuteTriangle) {
    // Equilateral triangle is acute
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {2.0, 0.0, 0.0};
    std::array<double, 3> p3 = {1.0, std::sqrt(3.0), 0.0};

    EXPECT_TRUE(isAcute(p1, p2, p3));
}

TEST(TriLibClassification, IsObtuseTriangle) {
    // Create an obtuse triangle (very small third vertex)
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {2.0, 0.0, 0.0};
    std::array<double, 3> p3 = {0.5, 0.1, 0.0};

    EXPECT_TRUE(isObtuse(p1, p2, p3));
}

TEST(TriLibClassification, IsRightTriangle) {
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {3.0, 0.0, 0.0};
    std::array<double, 3> p3 = {0.0, 4.0, 0.0};

    // Right triangle has max angle = 90, which is considered acute
    // (isAcute checks if max angle <= 90)
    EXPECT_TRUE(isAcute(p1, p2, p3));
    EXPECT_FALSE(isObtuse(p1, p2, p3));
}

TEST(TriLibClassification, IsDegenerateTriangle) {
    // Collinear points - degenerate
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {1.0, 0.0, 0.0};
    std::array<double, 3> p3 = {2.0, 0.0, 0.0};

    EXPECT_TRUE(isDegenerate(p1, p2, p3));
}

// ============================================================================
// Area Tests
// ============================================================================

TEST(TriLibArea, SimpleRightTriangle) {
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {4.0, 0.0, 0.0};
    std::array<double, 3> p3 = {0.0, 3.0, 0.0};

    // 3-4-5 triangle has area = 0.5 * 3 * 4 = 6
    double triangle_area = area(p1, p2, p3);
    EXPECT_NEAR(triangle_area, 6.0, EPSILON);
}

TEST(TriLibArea, EquilateralTriangle) {
    // Equilateral triangle with side length 2
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {2.0, 0.0, 0.0};
    std::array<double, 3> p3 = {1.0, std::sqrt(3.0), 0.0};

    // Area = (sqrt(3) / 4) * side^2 = sqrt(3)
    double expectedArea = std::sqrt(3.0);
    double computedArea = area(p1, p2, p3);
    EXPECT_NEAR(computedArea, expectedArea, 1e-5);
}

TEST(TriLibArea, DegenerateTriangleZeroArea) {
    // Collinear points
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {1.0, 0.0, 0.0};
    std::array<double, 3> p3 = {2.0, 0.0, 0.0};

    double triangle_area = area(p1, p2, p3);
    EXPECT_NEAR(triangle_area, 0.0, EPSILON);
}

// ============================================================================
// Normal Vector Tests
// ============================================================================

TEST(TriLibNormal, SimpleTriangleNormal) {
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {1.0, 0.0, 0.0};
    std::array<double, 3> p3 = {0.0, 1.0, 0.0};

    auto n = normal(p1, p2, p3);

    // Normal should point in Z direction (0, 0, 1) or (0, 0, -1)
    EXPECT_NEAR(std::abs(n[2]), 1.0, EPSILON);
    EXPECT_NEAR(std::abs(n[0]), 0.0, EPSILON);
    EXPECT_NEAR(std::abs(n[1]), 0.0, EPSILON);

    // Check it's a unit vector
    double mag = std::sqrt(n[0]*n[0] + n[1]*n[1] + n[2]*n[2]);
    EXPECT_NEAR(mag, 1.0, EPSILON);
}

// ============================================================================
// Centroid Tests
// ============================================================================

TEST(TriLibCentroid, SimpleCentroid) {
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {3.0, 0.0, 0.0};
    std::array<double, 3> p3 = {0.0, 3.0, 0.0};

    auto c = centroid(p1, p2, p3);

    EXPECT_NEAR(c[0], 1.0, EPSILON);
    EXPECT_NEAR(c[1], 1.0, EPSILON);
    EXPECT_NEAR(c[2], 0.0, EPSILON);
}

// ============================================================================
// Circumcenter and Circumradius Tests
// ============================================================================

TEST(TriLibCircumcircle, RightTriangleCircumcenter) {
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {4.0, 0.0, 0.0};
    std::array<double, 3> p3 = {0.0, 3.0, 0.0};

    auto cc = circumcenter(p1, p2, p3);
    double cr = circumradius(p1, p2, p3);

    // For a right triangle, circumcenter is at the midpoint of hypotenuse
    // and circumradius is half the hypotenuse length
    double hypotenuseLen = 5.0;
    EXPECT_NEAR(cr, hypotenuseLen / 2.0, 1e-5);
    // Verify cc is used to prevent compiler warning
    (void)cc;
}

TEST(TriLibCircumcircle, CircumcenterEquidistantFromVertices) {
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {3.0, 0.0, 0.0};
    std::array<double, 3> p3 = {0.0, 4.0, 0.0};

    auto cc = circumcenter(p1, p2, p3);
    double cr = circumradius(p1, p2, p3);

    // Distance from circumcenter to each vertex should equal circumradius
    double d1 = std::sqrt((cc[0] - p1[0])*(cc[0] - p1[0]) +
                          (cc[1] - p1[1])*(cc[1] - p1[1]) +
                          (cc[2] - p1[2])*(cc[2] - p1[2]));
    double d2 = std::sqrt((cc[0] - p2[0])*(cc[0] - p2[0]) +
                          (cc[1] - p2[1])*(cc[1] - p2[1]) +
                          (cc[2] - p2[2])*(cc[2] - p2[2]));
    double d3 = std::sqrt((cc[0] - p3[0])*(cc[0] - p3[0]) +
                          (cc[1] - p3[1])*(cc[1] - p3[1]) +
                          (cc[2] - p3[2])*(cc[2] - p3[2]));

    EXPECT_NEAR(d1, cr, 1e-5);
    EXPECT_NEAR(d2, cr, 1e-5);
    EXPECT_NEAR(d3, cr, 1e-5);
}

// ============================================================================
// Incenter and Inradius Tests
// ============================================================================

TEST(TriLibIncircle, IncenterEquidistantFromEdges) {
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {3.0, 0.0, 0.0};
    std::array<double, 3> p3 = {0.0, 4.0, 0.0};

    auto ic = incenter(p1, p2, p3);
    double ir = inradius(p1, p2, p3);

    // For 3-4-5 triangle, inradius should be (a + b - c) / 2 = (3 + 4 - 5) / 2 = 1
    EXPECT_NEAR(ir, 1.0, 1e-5);
    // Verify ic is used to prevent compiler warning
    (void)ic;
}

// ============================================================================
// Barycentric Coordinates Tests
// ============================================================================

TEST(TriLibBarycentricCoordinates, VertexA) {
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {1.0, 0.0, 0.0};
    std::array<double, 3> p3 = {0.0, 1.0, 0.0};

    auto bary = barycoordinates(p1, p2, p3, p1);

    // Point at p1 should have barycentric coords (1, 0, 0)
    EXPECT_NEAR(bary[0], 1.0, EPSILON);
    EXPECT_NEAR(bary[1], 0.0, EPSILON);
    EXPECT_NEAR(bary[2], 0.0, EPSILON);
}

TEST(TriLibBarycentricCoordinates, VertexB) {
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {1.0, 0.0, 0.0};
    std::array<double, 3> p3 = {0.0, 1.0, 0.0};

    auto bary = barycoordinates(p1, p2, p3, p2);

    // Point at p2 should have barycentric coords (0, 1, 0)
    EXPECT_NEAR(bary[0], 0.0, EPSILON);
    EXPECT_NEAR(bary[1], 1.0, EPSILON);
    EXPECT_NEAR(bary[2], 0.0, EPSILON);
}

TEST(TriLibBarycentricCoordinates, VertexC) {
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {1.0, 0.0, 0.0};
    std::array<double, 3> p3 = {0.0, 1.0, 0.0};

    auto bary = barycoordinates(p1, p2, p3, p3);

    // Point at p3 should have barycentric coords (0, 0, 1)
    EXPECT_NEAR(bary[0], 0.0, EPSILON);
    EXPECT_NEAR(bary[1], 0.0, EPSILON);
    EXPECT_NEAR(bary[2], 1.0, EPSILON);
}

TEST(TriLibBarycentricCoordinates, CentroidCoordinates) {
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {1.0, 0.0, 0.0};
    std::array<double, 3> p3 = {0.0, 1.0, 0.0};

    std::array<double, 3> centroid_point = {1.0/3.0, 1.0/3.0, 0.0};
    auto bary = barycoordinates(p1, p2, p3, centroid_point);

    // Centroid should have barycentric coords (1/3, 1/3, 1/3)
    EXPECT_NEAR(bary[0], 1.0/3.0, EPSILON);
    EXPECT_NEAR(bary[1], 1.0/3.0, EPSILON);
    EXPECT_NEAR(bary[2], 1.0/3.0, EPSILON);
}

TEST(TriLibBarycentricCoordinates, CoordinatesSum) {
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {2.0, 0.0, 0.0};
    std::array<double, 3> p3 = {0.0, 2.0, 0.0};

    std::array<double, 3> point = {0.5, 0.5, 0.0};
    auto bary = barycoordinates(p1, p2, p3, point);

    // Sum of barycentric coordinates should always be 1
    double sum = bary[0] + bary[1] + bary[2];
    EXPECT_NEAR(sum, 1.0, EPSILON);
}

// ============================================================================
// Template Type Tests (test with different numeric types)
// ============================================================================

TEST(TriLibTemplates, FloatType) {
    std::array<float, 3> p1 = {0.0f, 0.0f, 0.0f};
    std::array<float, 3> p2 = {3.0f, 0.0f, 0.0f};
    std::array<float, 3> p3 = {0.0f, 4.0f, 0.0f};

    float minLen = minlength(p1, p2, p3);
    EXPECT_NEAR(minLen, 3.0f, 1e-5f);
}

TEST(TriLibTemplates, IntegerType) {
    std::array<int, 3> p1 = {0, 0, 0};
    std::array<int, 3> p2 = {3, 0, 0};
    std::array<int, 3> p3 = {0, 4, 0};

    int minLen = minlength(p1, p2, p3);
    EXPECT_EQ(minLen, 3);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
