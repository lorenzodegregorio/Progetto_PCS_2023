#ifndef __EMPTY_H
#define __EMPTY_H

#include <iostream>

namespace ProjectLibrary
{
  class Empty
  {
    public:
      void Show() const { std::cout<< "Hello world;"<< std::endl; }
  };
  class Delaunay
  {
  public:
      // Esegui l'algoritmo di triangolazione di Delaunay
      std::vector<Triangle> triangulation = delaunayTriangulation(points);

      // Stampa i triangoli della triangolazione
      for (const Triangle& triangle : triangulation) {
          void Show() const {std::cout << "Triangle: " << triangle.a << ", " << triangle.b << ", " << triangle.c << std::endl; }
      }
  };
  return 0;
}

#endif // __EMPTY_H
