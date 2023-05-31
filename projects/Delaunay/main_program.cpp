#include "empty_class.hpp"

int main()
{
  ProjectLibrary::Empty empty;

  empty.Show();
      // Importa i dati dai file Test1.csv e Test2.csv
      std::vector<Point> points;
      std::ifstream file1("Test1.csv");
      std::ifstream file2("Test2.csv");

      if (file1.is_open() && file2.is_open()) {
          std::string line;
          while (std::getline(file1, line)) {
              std::stringstream ss(line);
              Point point;
              ss >> point.id >> point.x >> point.y;
              points.push_back(point);
          }

          while (std::getline(file2, line)) {
              std::stringstream ss(line);
              Point point;
              ss >> point.id >> point.x >> point.y;
              points.push_back(point);
          }
          file1.close();
          file2.close();
          else {
              std::cout << "Errore nell'apertura dei file." << std::endl;
          }
          ProjectLibrary::Delaunay delaunay;

          delaunay.Show();

  return 0;
}
