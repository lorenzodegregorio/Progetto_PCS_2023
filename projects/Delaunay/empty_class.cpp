#include "empty_class.hpp"

namespace ProjectLibrary
{
struct Point {
    int id;
    double x, y;
};

struct Triangle {
    int a, b, c;
};

// Calcola l'area di un triangolo
double calculateArea(const Point& p1, const Point& p2, const Point& p3) {
    return std::abs((p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) / 2.0);
}

// Verifica se un punto è interno al circumcerchio di un triangolo
bool isInsideCircumcircle(const Point& p, const std::vector<Point>& points, const Triangle& triangle) {
    const Point& p1 = points[triangle.a];
    const Point& p2 = points[triangle.b];
    const Point& p3 = points[triangle.c];

    double ax = p1.x - p.x;
    double ay = p1.y - p.y;
    double bx = p2.x - p.x;
    double by = p2.y - p.y;
    double cx = p3.x - p.x;
    double cy = p3.y - p.y;

    double det = (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by)) * 2.0;
    if (det <= 0)
        return false;

    double d11 = ax * ax + ay * ay;
    double d22 = bx * bx + by * by;
    double d33 = cx * cx + cy * cy;

    double center_x = (d11 * (by - cy) + d22 * (cy - ay) + d33 * (ay - by)) / det;
    double center_y = (d11 * (cx - bx) + d22 * (ax - cx) + d33 * (bx - ax)) / det;

    double radius = std::sqrt((ax - center_x) * (ax - center_x) + (ay - center_y) * (ay - center_y));

    double distance = std::sqrt((p.x - center_x) * (p.x - center_x) + (p.y - center_y) * (p.y - center_y));

    return distance <= radius;
}

// Esegue l'algoritmo di triangolazione di Delaunay
std::vector<Triangle> delaunayTriangulation(const std::vector<Point>& points) {
    std::vector<Triangle> triangles;

    // Estrae i tre punti non collineari per creare il primo triangolo
    Point p1 = points[0];
    Point p2 = points[1];
    Point p3 = points[2];
    Triangle firstTriangle = {0, 1, 2};
    triangles.push_back(firstTriangle);

    // Per ogni nuovo punto Q
    for (int i = 3; i < points.size(); i++) {
        const Point& q = points[i];
        std::vector<Triangle> invalidTriangles;

        // ...
        // Trova i triangoli che contengono il punto e li marca come invalidi
        for (const Triangle& triangle : triangles) {
            if (isInsideCircumcircle(q, points, triangle)) {
                invalidTriangles.push_back(triangle);
            }
        }

        // Unisce il punto Q con i vertici dei triangoli invalidi per creare una sottotriangolazione
        for (const Triangle& invalidTriangle : invalidTriangles) {
            Triangle t1 = { invalidTriangle.a, invalidTriangle.b, i };
            Triangle t2 = { invalidTriangle.b, invalidTriangle.c, i };
            Triangle t3 = { invalidTriangle.c, invalidTriangle.a, i };
            triangles.push_back(t1);
            triangles.push_back(t2);
            triangles.push_back(t3);
        }

        // Verifica l'ipotesi di Delaunay sulla nuova triangolazione e apporta eventuali modifiche
        for (const Triangle& triangle : triangles) {
            int a = triangle.a;
            int b = triangle.b;
            int c = triangle.c;

            for (const Point& point : points) {
                if ((point.id != a) && (point.id != b) && (point.id != c)) {
                    if (isInsideCircumcircle(point, points, triangle)) {
                        Triangle t1 = { a, b, point.id };
                        Triangle t2 = { b, c, point.id };
                        Triangle t3 = { c, a, point.id };
                        triangles.push_back(t1);
                        triangles.push_back(t2);
                        triangles.push_back(t3);

                        // Rimuovi il triangolo corrente dalla triangolazione
                        triangles.erase(std::remove(triangles.begin(), triangles.end(), triangle), triangles.end());

                        // Verifica l'ipotesi di Delaunay sui nuovi triangoli creati
                        delaunayTriangulation(points);
                        break;
                    }
                }
            }
        }

        return triangles;
    }
}
