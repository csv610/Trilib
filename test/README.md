# Trilib Tests

Comprehensive test suite for the Trilib library using Google Test framework.

## Files

- **test_trilib.cpp** - Tests for triangle mathematics functions
- **test_veclib.cpp** - Tests for vector mathematics functions

## Test Coverage

### Triangle Tests (test_trilib.cpp)

- **Edge Length Tests**: `minlength()`, `maxlength()`
- **Angle Tests**: `angles()`, `angleAt()`, `maxangle()`, `minangle()`
- **Classification Tests**: `isAcute()`, `isObtuse()`, `isDegenerate()`
- **Area Tests**: `area()` with various triangle types
- **Normal Vector Tests**: `normal()`
- **Centroid Tests**: `centroid()`
- **Circumcircle Tests**: `circumcenter()`, `circumradius()`
- **Incircle Tests**: `incenter()`, `inradius()`
- **Barycentric Coordinate Tests**: `barycoordinates()`
- **Template Type Tests**: Tests with float, double, and int types

### Vector Tests (test_veclib.cpp)

- **Length Tests**: `length()`, `length2()`, `magnitude()`
- **Dot Product Tests**: `dot_product()` for 2D and 3D vectors
- **Cross Product Tests**: `cross_product()`
- **Unit Vector Tests**: `unit_vector()`
- **Vector Creation Tests**: `make_vector()`
- **Angle Tests**: `angle()` between vectors
- **Min/Max Tests**: `min_value()`, `max_value()`
- **Statistical Tests**: `average_value()`, `standard_deviation()`, `mean_value()`
- **Coordinate Angle Tests**: Angle from 2D coordinates
- **Template Type Tests**: Tests with different numeric types
- **Edge Case Tests**: Zero vectors, special cases

## Building Tests

### Using CMake (Recommended)

```bash
# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build
cmake --build .

# Run tests
ctest --output-on-failure
```

Or run tests directly:
```bash
./test_trilib
./test_veclib
```

### Alternative: Manual Compilation

First, install Google Test:
```bash
# macOS with Homebrew
brew install googletest

# Ubuntu/Debian
sudo apt-get install libgtest-dev

# Manual build
git clone https://github.com/google/googletest.git
cd googletest
mkdir build && cd build
cmake ..
make && sudo make install
```

Then compile tests:
```bash
g++ -std=c++17 -I/path/to/trilib -I/usr/local/include test_trilib.cpp -o test_trilib -L/usr/local/lib -lgtest -lgtest_main -pthread
g++ -std=c++17 -I/path/to/trilib -I/usr/local/include test_veclib.cpp -o test_veclib -L/usr/local/lib -lgtest -lgtest_main -pthread

./test_trilib
./test_veclib
```

## Test Organization

Tests are organized into logical groups:
- Each function has its own test class or group
- Tests cover normal cases, edge cases, and special triangle types
- Tests verify mathematical properties (e.g., angle sums, distances)

## Special Test Cases

### Triangles Tested

- **3-4-5 Right Triangle**: Pythagorean triangle for validation
- **Equilateral Triangle**: All angles 60°, all sides equal
- **Degenerate Triangle**: Collinear points (zero area)
- **Obtuse Triangle**: One angle > 90°

### Mathematical Invariants Verified

- Sum of angles = 180°
- Barycentric coordinates sum to 1
- Circumcenter equidistant from all vertices
- Incenter equidistant from all edges
- Normal vector is unit length

## Expected Results

All tests should pass with output similar to:
```
[==========] Running XX tests from X test suites.
[==========] XX tests from ... (duration) OK
```

## Adding New Tests

To add new tests:

1. Identify the function to test
2. Create a test case with `TEST(ClassName, TestName)` macro
3. Set up test data
4. Call the function
5. Assert expected results using `EXPECT_*` macros

Example:
```cpp
TEST(TriLibArea, NewTriangleType) {
    std::array<double, 3> p1 = {...};
    std::array<double, 3> p2 = {...};
    std::array<double, 3> p3 = {...};

    double result = area(p1, p2, p3);
    EXPECT_NEAR(result, expected_value, EPSILON);
}
```

## Troubleshooting

### Google Test Not Found
Make sure to install Google Test or let CMake fetch it automatically:
```bash
cmake .. -DCMAKE_BUILD_TYPE=Release
```

### Compilation Errors
Ensure C++17 is enabled:
```bash
cmake .. -DCMAKE_CXX_STANDARD=17
```

### Tests Not Running
Make sure you're in the build directory:
```bash
cd build
./test_trilib
./test_veclib
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

Return code will be 0 if all tests pass, non-zero if any test fails.
