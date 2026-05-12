# Trilib

A modern C++ header-only library for triangle mathematics and 3D geometric computations. Trilib provides efficient, template-based functions for working with triangles and vectors using `std::array`.

## Features

- **Triangle Operations**
  - Edge length calculations (`minlength()`, `maxlength()`)
  - Angle computations (`angles()`, `angleAt()`, `maxangle()`, `minangle()`)
  - Triangle classification (`isObtuse()`, `isAcute()`, `isDegenerate()`)
  - Area calculation using Heron's formula
  - Normal vector computation (cross product based)

- **Geometric Properties**
  - Centroid calculation
  - Circumcenter and circumradius (circumscribed circle)
  - Incenter and inradius (inscribed circle)
  - Barycentric coordinate calculation

- **Vector Math Utilities**
  - Vector operations (dot product, cross product, length)
  - Unit vector normalization
  - Statistical functions (mean, standard deviation)
  - Angle calculations between vectors
  - Random value generation

- **Template-Based Design**
  - Works with any numeric type (int, float, double)
  - Header-only implementation - no compilation needed
  - Built on standard C++ containers (`std::array`)

## Installation

Simply include the header files in your project:

```cpp
#include "trilib.hpp"  // For triangle functions
#include "veclib.hpp"  // For vector utilities
```

No compilation step is needed - just copy the `.hpp` files to your include directory.

## Quick Start

### Basic Triangle Operations

```cpp
#include "trilib.hpp"
#include <iostream>

int main() {
    // Define three vertices of a triangle
    std::array<double, 3> p1 = {0.0, 0.0, 0.0};
    std::array<double, 3> p2 = {4.0, 0.0, 0.0};
    std::array<double, 3> p3 = {0.0, 3.0, 0.0};

    // Calculate area
    double area = trilib::area(p1, p2, p3);
    std::cout << "Area: " << area << std::endl;  // Output: Area: 6

    // Get triangle angles
    auto [a, b, c] = trilib::angles(p1, p2, p3);
    std::cout << "Angles: " << a << ", " << b << ", " << c << std::endl;

    // Calculate centroid
    auto centroid = trilib::centroid(p1, p2, p3);
    std::cout << "Centroid: (" << centroid[0] << ", "
              << centroid[1] << ", " << centroid[2] << ")" << std::endl;

    // Check triangle type
    if (trilib::isAcute(p1, p2, p3)) {
        std::cout << "Triangle is acute" << std::endl;
    }

    return 0;
}
```

### Vector Operations

```cpp
#include "veclib.hpp"
#include <iostream>

int main() {
    // Create vectors
    std::array<double, 3> v1 = {1.0, 0.0, 0.0};
    std::array<double, 3> v2 = {0.0, 1.0, 0.0};

    // Calculate length
    double len = veclib::length(v1);

    // Calculate dot product
    double dot = veclib::dot_product(v1, v2);

    // Calculate cross product
    auto cross = veclib::cross_product(v1, v2);

    // Get unit vector
    auto unit = veclib::unit_vector(v1);

    return 0;
}
```

## API Reference

### Triangle Functions (trilib.hpp)

#### Edge Lengths
- `minlength(p1, p2, p3)` - Returns the shortest edge
- `maxlength(p1, p2, p3)` - Returns the longest edge

#### Angles
- `angles(p1, p2, p3)` - Returns all three angles as a tuple
- `angleAt(vertex, other1, other2)` - Returns angle at a specific vertex
- `maxangle(p1, p2, p3)` - Returns the largest angle
- `minangle(p1, p2, p3)` - Returns the smallest angle

#### Classification
- `isObtuse(p1, p2, p3)` - Check if triangle is obtuse (>90°)
- `isAcute(p1, p2, p3)` - Check if triangle is acute (<90°)
- `isRightTriangle(p1, p2, p3)` - Check if triangle is right-angled (90°)
- `isEquilateral(p1, p2, p3)` - Check if all sides are equal
- `isIsosceles(p1, p2, p3)` - Check if at least two sides are equal
- `isDegenerate(p1, p2, p3)` - Check if triangle is degenerate (area ≈ 0)
- `is_ccw(p1, p2, p3, view_dir)` - Check if triangle is oriented counter-clockwise

#### Properties
- `area(p1, p2, p3)` - Calculate area using Heron's formula
- `perimeter(p1, p2, p3)` - Calculate sum of edge lengths
- `normal(p1, p2, p3)` - Calculate surface normal vector
- `get_bounds(p1, p2, p3)` - Get Axis-Aligned Bounding Box (AABB)
- `contains(p1, p2, p3, p)` - Check if point p is inside the triangle
- `centroid(p1, p2, p3)` - Calculate center of mass
- `circumcenter(p1, p2, p3)` - Calculate center of circumscribed circle
- `circumradius(p1, p2, p3)` - Calculate radius of circumscribed circle
- `incenter(p1, p2, p3)` - Calculate center of inscribed circle
- `inradius(p1, p2, p3)` - Calculate radius of inscribed circle
- `orthocenter(p1, p2, p3)` - Calculate center where altitudes intersect
- `altitude(p1, p2, p3, vertex)` - Calculate height from a vertex to opposite edge
- `barycoordinates(p, p1, p2, p3)` - Calculate barycentric coordinates of point p

#### Intersections
- `ray_triangle_intersection(...)` - Möller–Trumbore ray-triangle hit test

### Vector Functions (veclib.hpp)

#### Basic Operations
- `length(v)` / `magnitude(v)` - Vector length
- `length2(v)` - Squared length (faster)
- `dot_product(v1, v2)` - Dot product
- `cross_product(v1, v2)` - Cross product (3D vectors)
- `unit_vector(v)` - Normalize to unit length
- `add(a, b)` / `sub(a, b)` / `scale(a, s)` - Vector arithmetic

#### Spatial Utilities
- `distance_to_line(p, a, b)` / `closest_point_on_line(...)`
- `distance_to_segment(p, a, b)`
- `distance_to_plane(p, p0, n)` / `closest_point_on_plane(...)`
- `ray_plane_intersection(...)` - Ray-plane intersection test
- `aabb_intersect(aabb1, aabb2)` - Check if two bounding boxes overlap

#### General Utilities
- `angle(v1, v2)` - Angle between vectors
- `make_vector(p1, p2)` - Create vector from two points
- `median_value(v)` / `average_value(v)` - Median and average of vector components
- `projection(a, b)` / `reflection(v, n)` - Geometric vector operations
- `lerp(a, b, t)` - Linear interpolation
- `is_equal(a, b, eps)` - Robust floating point comparison
- `standard_deviation(v)` - Standard deviation of components
- `random_value(min, max)` - Generate random value in range

## Use Cases

- **3D Graphics** - Mesh processing, collision detection, ray-triangle intersection
- **Computational Geometry** - Geometric algorithms, spatial analysis
- **Game Development** - Triangle-based physics, mesh manipulation
- **Scientific Computing** - Geometric simulations and analysis
- **CAD/CAM** - Surface analysis and manipulation

## Requirements

- C++17 or later (for structured bindings and other modern features)
- Standard C++ library

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

## Author

Created as a utility library for geometric computations.

## Acknowledgments

Built on the foundation of standard C++ mathematical and geometric principles.
