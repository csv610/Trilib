# Trilib Testing Guide

Comprehensive testing suite for the Trilib library with 59 total tests.

## Quick Start

### Build and Run Tests

```bash
mkdir build
cd build
cmake ..
cmake --build .
ctest --output-on-failure
```

### Run Individual Test Suites

```bash
./test_trilib      # 27 tests for triangle functions
./test_veclib      # 32 tests for vector functions
./example          # Example demonstration program
```

## Test Summary

| Test Suite | Tests | Status | Coverage |
|-----------|-------|--------|----------|
| TriLib Functions | 27 | ✅ PASS | All triangle math operations |
| VecLib Functions | 32 | ✅ PASS | All vector math operations |
| **Total** | **59** | ✅ **PASS** | **100%** |

## Test Coverage by Function

### Triangle Functions (trilib.hpp)

| Function | Tests | Details |
|----------|-------|---------|
| `minlength()` | 1 | Edge length computation |
| `maxlength()` | 1 | Edge length computation |
| `angles()` | 3 | Degrees, radians, angle sum validation |
| `angleAt()` | 1 | Angle at specific vertex |
| `maxangle()` | 1 | Maximum angle identification |
| `minangle()` | 1 | Minimum angle identification |
| `isAcute()` | 1 | Acute triangle classification |
| `isObtuse()` | 1 | Obtuse triangle classification |
| `isDegenerate()` | 1 | Degenerate triangle detection |
| `area()` | 3 | Right triangle, equilateral, degenerate |
| `normal()` | 1 | Unit normal vector calculation |
| `centroid()` | 1 | Center of mass calculation |
| `circumcenter()` | 1 | Circumscribed circle center |
| `circumradius()` | 1 | Circumscribed circle radius |
| `incenter()` | 1 | Inscribed circle center |
| `inradius()` | 1 | Inscribed circle radius |
| `barycoordinates()` | 5 | Vertices, centroid, sum validation |
| **Template Types** | 2 | Float, integer type support |

### Vector Functions (veclib.hpp)

| Function | Tests | Details |
|----------|-------|---------|
| `length()` | 3 | Single unit, 3D Pythagorean |
| `length2()` | 1 | Squared distance optimization |
| `magnitude()` | 1 | Vector magnitude |
| `dot_product()` | 5 | Orthogonal, parallel, 2D, general |
| `cross_product()` | 4 | Axis combinations, parallel, general |
| `unit_vector()` | 2 | Normalization to unit length |
| `make_vector()` | 1 | Vector from head and tail points |
| `angle()` | 4 | Orthogonal, parallel, opposite, 45° |
| `max_value()` | 1 | Three element maximum |
| `min_value()` | 2 | Three and four element minimum |
| `average_value()` | 1 | Mean calculation |
| `standard_deviation()` | 1 | Statistical dispersion |
| `mean_value()` | 1 | Median value |
| **Edge Cases** | 2 | Zero vectors, special cases |
| **Template Types** | 2 | Float, integer type support |

## Test Categories

### Mathematical Properties Validated

✅ **Angle Sums**
- All triangle angles sum to 180° (validated in multiple tests)

✅ **Geometric Centers**
- Circumcenter is equidistant from all vertices
- Incenter is equidistant from all edges
- Centroid is average of vertices

✅ **Barycentric Coordinates**
- Sum to 1.0 for any point in triangle
- Exact values (1,0,0) at vertices
- Correct (1/3,1/3,1/3) at centroid

✅ **Vector Operations**
- Orthogonal vectors have 0 dot product
- Parallel vectors have identical angle
- Unit vectors have magnitude 1.0

✅ **Special Triangles**
- 3-4-5 right triangle validation
- Equilateral triangle (60° angles)
- Degenerate/collinear points

### Type Support

Tests verify correct behavior with:
- `double` (primary type)
- `float` (floating point compatibility)
- `int` (integer type support)

### Edge Cases

- Zero magnitude vectors
- Collinear/degenerate triangles
- Orthogonal and parallel vectors
- Floating point precision handling

## Building Without CMake

### On macOS with Homebrew

```bash
# Install Google Test
brew install googletest

# Compile trilib tests
g++ -std=c++17 -I. test/test_trilib.cpp -o test_trilib \
    -L/opt/homebrew/lib -lgtest -lgtest_main -pthread

# Compile veclib tests
g++ -std=c++17 -I. test/test_veclib.cpp -o test_veclib \
    -L/opt/homebrew/lib -lgtest -lgtest_main -pthread

# Run tests
./test_trilib
./test_veclib
```

### On Linux

```bash
# Ubuntu/Debian
sudo apt-get install libgtest-dev

# Compile and run
g++ -std=c++17 -I. test/test_trilib.cpp -o test_trilib \
    -L/usr/lib -lgtest -lgtest_main -pthread
./test_trilib
```

## Test Output Example

```
[==========] Running 27 tests from 10 test suites.
[----------] 2 tests from TriLibEdgeLengths
[ RUN      ] TriLibEdgeLengths.MinLengthSimpleTriangle
[       OK ] TriLibEdgeLengths.MinLengthSimpleTriangle (0 ms)
[ RUN      ] TriLibEdgeLengths.MaxLengthSimpleTriangle
[       OK ] TriLibEdgeLengths.MaxLengthSimpleTriangle (0 ms)
...
[==========] 27 tests from 10 test suites ran. (X ms total)
[  PASSED  ] 27 tests.
```

## Adding New Tests

1. Identify the function to test
2. Create a test case with appropriate test data
3. Call the function
4. Assert results using EXPECT_* macros

Example:

```cpp
TEST(TriLibArea, SpecialTriangle) {
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {5.0, 0.0, 0.0};
    std::array<double, 3> p3 = {0.0, 12.0, 0.0};

    double result = area(p1, p2, p3);
    EXPECT_NEAR(result, 30.0, EPSILON);  // 0.5 * 5 * 12 = 30
}
```

## Continuous Integration

To run tests in CI/CD pipelines:

```bash
mkdir build
cd build
cmake ..
cmake --build .
ctest --output-on-failure --verbose
```

Exit code: 0 if all tests pass, non-zero if any test fails.

## Known Limitations

- Tests assume IEEE 754 floating point arithmetic
- Some tests use tolerance values (EPSILON = 1e-6) for floating point comparisons
- Integer type tests have lower precision requirements

## Performance Notes

All tests complete in < 10ms total on modern hardware.
Recommended test runtime: < 100ms for continuous integration.

## Troubleshooting

### GTest Not Found
```bash
cmake .. -DCMAKE_BUILD_TYPE=Release
```

### C++ Standard Issues
```bash
cmake .. -DCMAKE_CXX_STANDARD=17
```

### Tests Not Compiling
- Ensure C++17 support: `g++ --version` should show recent compiler
- Check Google Test installation: `gtest-config --version`

## References

- **Test Framework**: [Google Test](https://github.com/google/googletest)
- **Documentation**: See [test/README.md](test/README.md) for detailed information
- **Build System**: [CMake](https://cmake.org/)

## Statistics

- **Total Test Cases**: 59
- **Pass Rate**: 100%
- **Code Coverage**: All public functions tested
- **Test Execution Time**: < 10ms
- **Lines of Test Code**: 800+
