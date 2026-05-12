#pragma once

#include "veclib.hpp"

#define ANGLE_IN_DEGREES  0
#define ANGLE_IN_RADIANS  1

using namespace JMath;

template<class T>
inline T minlength( const std::array<T,3> &pa,
                    const std::array<T,3> &pb,
                    const std::array<T,3> &pc)
{
    T a  =  length( pb, pc );
    T b  =  length( pc, pa );
    T c  =  length( pa, pb );

    return min_value(a,b,c);
}

template<class T>
inline T maxlength( const std::array<T,3> &pa,
                    const std::array<T,3> &pb,
                    const std::array<T,3> &pc)
{
    T a  =  length( pb, pc );
    T b  =  length( pc, pa );
    T c  =  length( pa, pb );

    return max_value(a,b,c);
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline T area( const std::array<T,3> &pa,
               const std::array<T,3> &pb,
               const std::array<T,3> &pc)
{
    T a     =  length( pb, pc );
    T b     =  length( pc, pa );
    T c     =  length( pa, pb );
    T s     =  0.5*(a+b+c);
    T heron =  sqrt(s*(s-a)*(s-b)*(s-c));
    return heron;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline std::array<T,3> circumcenter( const std::array<T,3> &pa,
                                     const std::array<T,3> &pb,
                                     const std::array<T,3> &pc)
{
   // Source : Wikipedia ...
    std::array<T,3> coords;
    T a   =  length( pb, pc );
    T b   =  length( pc, pa );
    T c   =  length( pa, pb );

    T u   =  a*a*(b*b + c*c - a*a);
    T v   =  b*b*(c*c + a*a - b*b);
    T w   =  c*c*(a*a + b*b - c*c);

    coords[0] = (u*pa[0] + v*pb[0] + w*pc[0] )/(u+v+w);
    coords[1] = (u*pa[1] + v*pb[1] + w*pc[1] )/(u+v+w);
    coords[2] = (u*pa[2] + v*pb[2] + w*pc[2] )/(u+v+w);

    return coords;
}

template<class T>
inline std::array<T,3> angles( const std::array<T,3> &pa,
                               const std::array<T,3> &pb,
                               const std::array<T,3> &pc, 
			       int measure = ANGLE_IN_DEGREES)
{
    std::array<T,3> angles = {0, 0, 0};

    double a2   =  length2( pb, pc );
    double b2   =  length2( pc, pa );
    double c2   =  length2( pa, pb );
    double cosA =  (b2 + c2 - a2)/(2*sqrt(b2*c2) );
    double cosB =  (a2 + c2 - b2)/(2*sqrt(a2*c2) );
    double cosC =  (a2 + b2 - c2)/(2*sqrt(a2*b2) );

    if( cosA >  1.0) cosA =  1.0;
    if( cosA < -1.0) cosA = -1.0;
    angles[0] = acos(cosA);

    if( cosB >  1.0) cosB =  1.0;
    if( cosB < -1.0) cosB = -1.0;
    angles[1] = acos(cosB);

    if( cosC >  1.0) cosC =  1.0;
    if( cosC < -1.0) cosC = -1.0;
    angles[2] = acos(cosC);

    if( measure ==  ANGLE_IN_DEGREES) {
        angles[0] *= 180/M_PI;
        angles[1] *= 180/M_PI;
        angles[2] *= 180/M_PI;
    }
    return angles;
}

///////////////////////////////////////////////////////////////////////////////

template<class T>
inline T angleAt( const std::array<T,3> &pa,
                  const std::array<T,3> &pb,
                  const std::array<T,3> &pc, 
		  int measure = ANGLE_IN_DEGREES)
{
    T a2   =  length2( pb, pc );
    T b2   =  length2( pc, pa );
    T c2   =  length2( pa, pb );
    double cosA =  (b2 + c2 - a2)/(2*sqrt(b2*c2) );

    if( cosA >  1.0) cosA =  1.0;
    if( cosA < -1.0) cosA = -1.0;

    double angle;
    if( measure == ANGLE_IN_DEGREES)
        angle = 180*acos(cosA)/M_PI;
    else
        angle = acos(cosA);
    return angle;
}

////////////////////////////////////////////////////////////////////////////////

template<class T>
std::pair<T,int> maxangle( const std::array<T,3> &pa,
                           const std::array<T,3> &pb,
                           const std::array<T,3> &pc, 
			   int measure = ANGLE_IN_DEGREES)
{
    T a2   =  length2( pb, pc );
    T b2   =  length2( pc, pa );
    T c2   =  length2( pa, pb );

    T maxlen = max_value(a2,b2,c2);

    std::pair<T,int> result;

    if( maxlen == a2) {
        double cosA =  (b2 + c2 - a2)/(2*sqrt(b2*c2) );
        if( cosA >  1.0) cosA =  1.0;
        if( cosA < -1.0) cosA = -1.0;
        double angle = acos(cosA);
        if( measure == ANGLE_IN_DEGREES)  angle *= 180.0/M_PI;
        result.first  = angle;
        result.second = 0;
    }

    if( maxlen == b2 ) {
        double cosB =  (a2 + c2 - b2)/(2*sqrt(a2*c2) );
        if( cosB >  1.0) cosB =  1.0;
        if( cosB < -1.0) cosB = -1.0;
        double angle  = acos(cosB);
        if( measure == ANGLE_IN_DEGREES)  angle *= 180.0/M_PI;
        result.first  = angle;
        result.second = 1;
    }

    if( maxlen == c2 ) {
        double cosC =  (a2 + b2 - c2)/(2*sqrt(a2*b2) );
        if( cosC >  1.0) cosC =  1.0;
        if( cosC < -1.0) cosC = -1.0;
        double angle = acos(cosC);
        if( measure == ANGLE_IN_DEGREES)  angle *= 180.0/M_PI;
        result.first  = angle;
        result.second = 2;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////

template<class T>
std::pair<T,int> minangle( const std::array<T,3> &pa,
                           const std::array<T,3> &pb,
                           const std::array<T,3> &pc, 
			   int measure = ANGLE_IN_DEGREES)
{
    double a2   =  length2( pb, pc );
    double b2   =  length2( pc, pa );
    double c2   =  length2( pa, pb );

    double minlen = min_value(a2,b2,c2);

    std::pair<T,int> result;

    if( minlen == a2) {
        double cosA =  (b2 + c2 - a2)/(2*sqrt(b2*c2) );
        if( cosA >  1.0) cosA =  1.0;
        if( cosA < -1.0) cosA = -1.0;
        double angle = acos(cosA);
        if( measure == ANGLE_IN_DEGREES)  angle *= 180.0/M_PI;
        result.first  = angle;
        result.second = 0;
    }

    if( minlen == b2 ) {
        double cosB =  (a2 + c2 - b2)/(2*sqrt(a2*c2) );
        if( cosB >  1.0) cosB =  1.0;
        if( cosB < -1.0) cosB = -1.0;
        double angle  = acos(cosB);
        if( measure == ANGLE_IN_DEGREES)  angle *= 180.0/M_PI;
        result.first  = angle;
        result.second = 1;
    }

    if( minlen == c2 ) {
        double cosC =  (a2 + b2 - c2)/(2*sqrt(a2*b2) );
        if( cosC >  1.0) cosC =  1.0;
        if( cosC < -1.0) cosC = -1.0;
        double angle = acos(cosC);
        if( measure == ANGLE_IN_DEGREES)  angle *= 180.0/M_PI;
        result.first  = angle;
        result.second = 2;
    }

    return result;
}
//
////////////////////////////////////////////////////////////////////////////////
//
template<class T>
inline bool isObtuse( const std::array<T,3> &pa,
                      const std::array<T,3> &pb,
                      const std::array<T,3> &pc)
{
    auto result = maxangle(pa,pb,pc);
    if( result.first > 90.0001) return 1;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////

template<class T>
inline bool isRightTriangle( const std::array<T,3> &pa,
                             const std::array<T,3> &pb,
                             const std::array<T,3> &pc)
{
    auto result = maxangle(pa,pb,pc);
    if( std::abs(result.first - 90.0) < 0.0001) return 1;
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

template<class T>
inline bool isDegenerate( const std::array<T,3> &pa,
                          const std::array<T,3> &pb,
                          const std::array<T,3> &pc)
{
    auto result = maxangle(pa,pb,pc);
    if( result.first > 179.999) return 1;
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

template<class T>
inline bool isAcute( const std::array<T,3> &pa,
                     const std::array<T,3> &pb,
                     const std::array<T,3> &pc)
{
    auto result = maxangle(pa,pb,pc);
    if( result.first < 89.9999) return 1;
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

template<class T>
inline bool isEquilateral( const std::array<T,3> &pa,
                           const std::array<T,3> &pb,
                           const std::array<T,3> &pc)
{
    T a  =  length( pb, pc );
    T b  =  length( pc, pa );
    T c  =  length( pa, pb );
    return is_equal(a, b) && is_equal(b, c);
}

////////////////////////////////////////////////////////////////////////////////

template<class T>
inline bool isIsosceles( const std::array<T,3> &pa,
                         const std::array<T,3> &pb,
                         const std::array<T,3> &pc)
{
    T a  =  length( pb, pc );
    T b  =  length( pc, pa );
    T c  =  length( pa, pb );
    return is_equal(a, b) || is_equal(b, c) || is_equal(c, a);
}

////////////////////////////////////////////////////////////////////////////////

template<class T>
inline T perimeter( const std::array<T,3> &pa,
                    const std::array<T,3> &pb,
                    const std::array<T,3> &pc)
{
    return length(pb, pc) + length(pc, pa) + length(pa, pb);
}

////////////////////////////////////////////////////////////////////////////////

template<class T>
inline std::array<T,3> orthocenter( const std::array<T,3> &pa,
                                    const std::array<T,3> &pb,
                                    const std::array<T,3> &pc)
{
    // H = A + B + C - 2O (where O is circumcenter)
    auto o = circumcenter(pa, pb, pc);
    auto sum = add(pa, add(pb, pc));
    return sub(sum, scale(o, 2.0));
}

////////////////////////////////////////////////////////////////////////////////

template<class T>
inline T altitude( const std::array<T,3> &pa,
                   const std::array<T,3> &pb,
                   const std::array<T,3> &pc,
                   int vertex_index = 0)
{
    T a_area = area(pa, pb, pc);
    T base;
    if (vertex_index == 0) base = length(pb, pc);
    else if (vertex_index == 1) base = length(pc, pa);
    else base = length(pa, pb);

    if (base < 1e-15) return 0.0;
    return (2.0 * a_area) / base;
}
////////////////////////////////////////////////////////////////////////////////

template<class T>
inline std::array<T,3> normal( const std::array<T,3> &p0,
                               const std::array<T,3> &p1,
                               const std::array<T,3> &p2)
{
    auto p1p0   = make_vector( p1, p0);
    auto p2p0   = make_vector( p2, p0);
    auto normal = cross_product( p1p0, p2p0);

    double mag = magnitude( normal );
    normal[0] /= mag;
    normal[1] /= mag;
    normal[2] /= mag;

    return normal;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline std::array<T,3> centroid( const std::array<T,3> &pa,
                                 const std::array<T,3> &pb,
                                 const std::array<T,3> &pc)
{
    std::array<T,3> c;
    c[0] = (pa[0] + pb[0] + pc[0])/3.0;
    c[1] = (pa[1] + pb[1] + pc[1])/3.0;
    c[2] = (pa[2] + pb[2] + pc[2])/3.0;
    return c;
}
////////////////////////////////////////////////////////////////////////////////
template<class T>
inline std::array<T,3> barycoordinates( const std::array<T,3> &pa,
                                        const std::array<T,3> &pb,
                                        const std::array<T,3> &pc, 
					const std::array<T,3> &queryPoint)
{
    std::array<T,3> bcoords;

    T total_area = area(pa,pb,pc);

    bcoords[0] = area(pb,pc,queryPoint)/total_area;
    bcoords[1] = area(pc,pa,queryPoint)/total_area;
    bcoords[2] = area(pa,pb,queryPoint)/total_area;

    return bcoords;
}

////////////////////////////////////////////////////////////////////////////////

template<class T>
inline AABB<T> get_bounds(const std::array<T, 3>& p1,
                          const std::array<T, 3>& p2,
                          const std::array<T, 3>& p3) {
    AABB<T> bounds;
    for (int i = 0; i < 3; ++i) {
        bounds.min_pt[i] = min_value(p1[i], p2[i], p3[i]);
        bounds.max_pt[i] = max_value(p1[i], p2[i], p3[i]);
    }
    return bounds;
}

////////////////////////////////////////////////////////////////////////////////

template<class T>
inline bool contains(const std::array<T, 3>& p1,
                     const std::array<T, 3>& p2,
                     const std::array<T, 3>& p3,
                     const std::array<T, 3>& p) {
    auto bary = barycoordinates(p1, p2, p3, p);
    T eps = -1e-9;
    T one_eps = 1.0 + 1e-9;
    return (bary[0] >= eps && bary[0] <= one_eps &&
            bary[1] >= eps && bary[1] <= one_eps &&
            bary[2] >= eps && bary[2] <= one_eps);
}

////////////////////////////////////////////////////////////////////////////////

template<class T>
inline bool is_ccw(const std::array<T, 3>& p1,
                   const std::array<T, 3>& p2,
                   const std::array<T, 3>& p3,
                   const std::array<T, 3>& view_dir = {0, 0, 1}) {
    auto n = normal(p1, p2, p3);
    return dot_product(n, view_dir) > 0;
}

////////////////////////////////////////////////////////////////////////////////

template<class T>
inline T circumradius( const std::array<T,3> &pa,
                       const std::array<T,3> &pb,
                       const std::array<T,3> &pc)
{
    T a  =  length( pb, pc );
    T b  =  length( pc, pa );
    T c  =  length( pa, pb );
    T s  =  0.5*(a+b+c);

    T r  = 0.25*a*b*c/sqrt(s*(s-a)*(s-b)*(s-c));
    return r;
}

////////////////////////////////////////////////////////////////////////////////

template<class T>
inline bool ray_triangle_intersection( const std::array<T,3> &ray_origin,
                                       const std::array<T,3> &ray_direction,
                                       const std::array<T,3> &p1,
                                       const std::array<T,3> &p2,
                                       const std::array<T,3> &p3,
                                       T &t, T &u, T &v)
{
    auto e1 = make_vector(p2, p1);
    auto e2 = make_vector(p3, p1);
    auto h  = cross_product(ray_direction, e2);
    T a = dot_product(e1, h);

    if (a > -1e-15 && a < 1e-15) return false;

    T f = 1.0 / a;
    auto s = make_vector(ray_origin, p1);
    u = f * dot_product(s, h);

    if (u < 0.0 || u > 1.0) return false;

    auto q = cross_product(s, e1);
    v = f * dot_product(ray_direction, q);

    if (v < 0.0 || u + v > 1.0) return false;

    t = f * dot_product(e2, q);
    return t > 1e-15;
}
////////////////////////////////////////////////////////////////////////////////

template<class T>
inline std::array<T,3> incenter( const std::array<T,3> &pa,
                                 const std::array<T,3> &pb,
                                 const std::array<T,3> &pc)
{
    std::array<T,3> coords;
    T a  =  length( pb, pc );
    T b  =  length( pc, pa );
    T c  =  length( pa, pb );
    T t  =  a + b + c;

    coords[0] = (a*pa[0] + b*pb[0] + c*pc[0] )/t;
    coords[1] = (a*pa[1] + b*pb[1] + c*pc[1] )/t;
    coords[2] = (a*pa[2] + b*pb[2] + c*pc[2] )/t;

    return coords;
}
////////////////////////////////////////////////////////////////////////////////

template<class T>
inline T inradius( const std::array<T,3> &pa,
                   const std::array<T,3> &pb,
                   const std::array<T,3> &pc)
{
    T a  =  length( pb, pc );
    T b  =  length( pc, pa );
    T c  =  length( pa, pb );
    T s  =  a+b+c;

    T r     = 0.5*sqrt((b+c-a)*(c+a-b)*(a+b-c)/s);
    return r;
}
////////////////////////////////////////////////////////////////////////////////
