#include <gtest/gtest.h>
#include "../veclib.hpp"
#include <cmath>
#include <vector>

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
// Length Tests
// ============================================================================

TEST(VecLibLength, UnitDistance) {
    std::array<double, 3> a = {0.0, 0.0, 0.0};
    std::array<double, 3> b = {1.0, 0.0, 0.0};

    double len = JMath::length(a, b);
    EXPECT_NEAR(len, 1.0, EPSILON);
}

TEST(VecLibLength, Pythagorean3D) {
    std::array<double, 3> a = {0.0, 0.0, 0.0};
    std::array<double, 3> b = {3.0, 4.0, 0.0};

    // 3-4-5 triangle
    double len = JMath::length(a, b);
    EXPECT_NEAR(len, 5.0, EPSILON);
}

TEST(VecLibLength, ThreeDimensional) {
    std::array<double, 3> a = {1.0, 2.0, 2.0};
    std::array<double, 3> b = {0.0, 0.0, 0.0};

    // sqrt(1^2 + 2^2 + 2^2) = sqrt(9) = 3
    double len = JMath::length(a, b);
    EXPECT_NEAR(len, 3.0, EPSILON);
}

TEST(VecLibLength, Length2SquaredDistance) {
    std::array<double, 3> a = {0.0, 0.0, 0.0};
    std::array<double, 3> b = {3.0, 4.0, 0.0};

    double len2 = JMath::length2(a, b);
    EXPECT_NEAR(len2, 25.0, EPSILON);
}

TEST(VecLibLength, MagnitudeOfVector) {
    std::array<double, 3> v = {3.0, 4.0, 0.0};

    double mag = JMath::magnitude(v);
    EXPECT_NEAR(mag, 5.0, EPSILON);
}

// ============================================================================
// Dot Product Tests
// ============================================================================

TEST(VecLibDotProduct, OrthogonalVectors) {
    std::array<double, 3> a = {1.0, 0.0, 0.0};
    std::array<double, 3> b = {0.0, 1.0, 0.0};

    double dot = JMath::dot_product(a, b);
    EXPECT_NEAR(dot, 0.0, EPSILON);
}

TEST(VecLibDotProduct, ParallelVectors) {
    std::array<double, 3> a = {1.0, 0.0, 0.0};
    std::array<double, 3> b = {2.0, 0.0, 0.0};

    double dot = JMath::dot_product(a, b);
    EXPECT_NEAR(dot, 2.0, EPSILON);
}

TEST(VecLibDotProduct, OppositeVectors) {
    std::array<double, 3> a = {1.0, 0.0, 0.0};
    std::array<double, 3> b = {-1.0, 0.0, 0.0};

    double dot = JMath::dot_product(a, b);
    EXPECT_NEAR(dot, -1.0, EPSILON);
}

TEST(VecLibDotProduct, GeneralVectors) {
    std::array<double, 3> a = {1.0, 2.0, 3.0};
    std::array<double, 3> b = {4.0, 5.0, 6.0};

    // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
    double dot = JMath::dot_product(a, b);
    EXPECT_NEAR(dot, 32.0, EPSILON);
}

TEST(VecLibDotProduct, 2DVector) {
    std::array<double, 2> a = {3.0, 4.0};
    std::array<double, 2> b = {5.0, 6.0};

    // 3*5 + 4*6 = 15 + 24 = 39
    double dot = JMath::dot_product(a, b);
    EXPECT_NEAR(dot, 39.0, EPSILON);
}

// ============================================================================
// Cross Product Tests
// ============================================================================

TEST(VecLibCrossProduct, XAxisCrossYAxis) {
    std::array<double, 3> x = {1.0, 0.0, 0.0};
    std::array<double, 3> y = {0.0, 1.0, 0.0};

    auto cross = JMath::cross_product(x, y);

    // X × Y = Z
    EXPECT_NEAR(cross[0], 0.0, EPSILON);
    EXPECT_NEAR(cross[1], 0.0, EPSILON);
    EXPECT_NEAR(cross[2], 1.0, EPSILON);
}

TEST(VecLibCrossProduct, YAxisCrossXAxis) {
    std::array<double, 3> x = {1.0, 0.0, 0.0};
    std::array<double, 3> y = {0.0, 1.0, 0.0};

    auto cross = JMath::cross_product(y, x);

    // Y × X = -Z
    EXPECT_NEAR(cross[0], 0.0, EPSILON);
    EXPECT_NEAR(cross[1], 0.0, EPSILON);
    EXPECT_NEAR(cross[2], -1.0, EPSILON);
}

TEST(VecLibCrossProduct, ParallelVectorsZeroCross) {
    std::array<double, 3> a = {1.0, 2.0, 3.0};
    std::array<double, 3> b = {2.0, 4.0, 6.0};

    auto cross = JMath::cross_product(a, b);

    // Parallel vectors should give zero cross product
    EXPECT_NEAR(cross[0], 0.0, EPSILON);
    EXPECT_NEAR(cross[1], 0.0, EPSILON);
    EXPECT_NEAR(cross[2], 0.0, EPSILON);
}

TEST(VecLibCrossProduct, GeneralVectors) {
    std::array<double, 3> a = {1.0, 2.0, 3.0};
    std::array<double, 3> b = {4.0, 5.0, 6.0};

    auto cross = JMath::cross_product(a, b);

    // i(2*6 - 3*5) - j(1*6 - 3*4) + k(1*5 - 2*4)
    // i(-3) - j(-6) + k(-3)
    // (-3, 6, -3)
    EXPECT_NEAR(cross[0], -3.0, EPSILON);
    EXPECT_NEAR(cross[1], 6.0, EPSILON);
    EXPECT_NEAR(cross[2], -3.0, EPSILON);
}

// ============================================================================
// Unit Vector Tests
// ============================================================================

TEST(VecLibUnitVector, UnitVectorFromVector) {
    std::array<double, 3> v = {3.0, 4.0, 0.0};

    auto unit = JMath::unit_vector(v);

    // Length should be 1
    double mag = JMath::magnitude(unit);
    EXPECT_NEAR(mag, 1.0, EPSILON);

    // Direction should be preserved
    EXPECT_NEAR(unit[0], 0.6, EPSILON);  // 3/5
    EXPECT_NEAR(unit[1], 0.8, EPSILON);  // 4/5
    EXPECT_NEAR(unit[2], 0.0, EPSILON);
}

TEST(VecLibUnitVector, UnitVectorX) {
    std::array<double, 3> v = {5.0, 0.0, 0.0};

    auto unit = JMath::unit_vector(v);

    EXPECT_NEAR(unit[0], 1.0, EPSILON);
    EXPECT_NEAR(unit[1], 0.0, EPSILON);
    EXPECT_NEAR(unit[2], 0.0, EPSILON);
}

// ============================================================================
// Make Vector Tests
// ============================================================================

TEST(VecLibMakeVector, SimpleVector) {
    std::array<double, 3> head = {5.0, 5.0, 5.0};
    std::array<double, 3> tail = {1.0, 2.0, 3.0};

    auto vec = JMath::make_vector(head, tail);

    EXPECT_NEAR(vec[0], 4.0, EPSILON);
    EXPECT_NEAR(vec[1], 3.0, EPSILON);
    EXPECT_NEAR(vec[2], 2.0, EPSILON);
}

// ============================================================================
// Angle Between Vectors Tests
// ============================================================================

TEST(VecLibAngle, OrthogonalVectors) {
    std::array<double, 3> a = {1.0, 0.0, 0.0};
    std::array<double, 3> b = {0.0, 1.0, 0.0};

    double angle = JMath::angle(a, b);

    // Should be 90 degrees or pi/2 radians
    EXPECT_NEAR(angle, M_PI / 2.0, EPSILON);
}

TEST(VecLibAngle, ParallelVectors) {
    std::array<double, 3> a = {1.0, 0.0, 0.0};
    std::array<double, 3> b = {2.0, 0.0, 0.0};

    double angle = JMath::angle(a, b);

    EXPECT_NEAR(angle, 0.0, EPSILON);
}

TEST(VecLibAngle, OppositeVectors) {
    std::array<double, 3> a = {1.0, 0.0, 0.0};
    std::array<double, 3> b = {-1.0, 0.0, 0.0};

    double angle = JMath::angle(a, b);

    EXPECT_NEAR(angle, M_PI, EPSILON);
}

TEST(VecLibAngle, 45DegreeVectors) {
    std::array<double, 3> a = {1.0, 0.0, 0.0};
    std::array<double, 3> b = {1.0, 1.0, 0.0};

    double angle = JMath::angle(a, b);

    // Should be 45 degrees or pi/4 radians
    EXPECT_NEAR(angle, M_PI / 4.0, EPSILON);
}

// ============================================================================
// Min/Max Value Tests
// ============================================================================

TEST(VecLibMinMax, MaxValueThreeElements) {
    double max = JMath::max_value(1.0, 5.0, 3.0);
    EXPECT_NEAR(max, 5.0, EPSILON);
}

TEST(VecLibMinMax, MinValueThreeElements) {
    double min = JMath::min_value(1.0, 5.0, 3.0);
    EXPECT_NEAR(min, 1.0, EPSILON);
}

TEST(VecLibMinMax, MinValueFourElements) {
    double min = JMath::min_value(5.0, 2.0, 8.0, 1.0);
    EXPECT_NEAR(min, 1.0, EPSILON);
}

// ============================================================================
// Statistical Tests
// ============================================================================

TEST(VecLibStatistics, AverageValue) {
    std::vector<double> values = {1.0, 2.0, 3.0, 4.0, 5.0};

    double avg = JMath::average_value(values);
    EXPECT_NEAR(avg, 3.0, EPSILON);
}

TEST(VecLibStatistics, StandardDeviation) {
    std::vector<double> values = {1.0, 2.0, 3.0, 4.0, 5.0};

    double stddev = JMath::standard_deviation(values);

    // For [1, 2, 3, 4, 5], sample std dev should be approximately 1.58
    EXPECT_NEAR(stddev, 1.58, 0.01);
}

TEST(VecLibStatistics, MedianValue) {
    std::vector<double> values = {1.0, 3.0, 2.0, 5.0, 4.0};

    double median = JMath::mean_value(values);
    EXPECT_NEAR(median, 3.0, EPSILON);
}

// ============================================================================
// Coordinate Angle Tests
// ============================================================================

TEST(VecLibCoordinateAngle, AngleBetweenCoordinates) {
    // Angle from (1, 0) to (0, 1) should be pi/2
    double angle = JMath::angle(1.0, 0.0, 0.0, 1.0);

    // This function returns the angle difference
    EXPECT_NEAR(std::abs(angle), M_PI / 2.0, 0.01);
}

// ============================================================================
// Template Type Tests
// ============================================================================

TEST(VecLibTemplates, FloatType) {
    std::array<float, 3> v = {3.0f, 4.0f, 0.0f};

    float mag = JMath::magnitude(v);
    EXPECT_NEAR(mag, 5.0f, 1e-5f);
}

TEST(VecLibTemplates, IntegerType) {
    std::array<int, 3> v = {3, 4, 0};

    int mag = JMath::magnitude(v);
    EXPECT_NEAR(mag, 5, 1);  // Integer division/rounding
}

// ============================================================================
// Edge Cases
// ============================================================================

TEST(VecLibEdgeCases, ZeroMagnitudeVector) {
    std::array<double, 3> zero = {0.0, 0.0, 0.0};

    double mag = JMath::magnitude(zero);
    EXPECT_NEAR(mag, 0.0, EPSILON);
}

TEST(VecLibEdgeCases, AngleWithZeroVector) {
    std::array<double, 3> a = {1.0, 0.0, 0.0};
    std::array<double, 3> zero = {0.0, 0.0, 0.0};

    // Should handle gracefully - returns 0
    double angle = JMath::angle(a, zero);
    EXPECT_NEAR(angle, 0.0, EPSILON);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
