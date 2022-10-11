#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
vector<double> take_doub(string str);
double manhattan_distance(vector<double> location);
double getVectorOData(vector<double> vecFile1, vector<double> vecFile2);


int main(int argc, char *argv[]) {
  string file1Name = argv[1];
  string file2Name = argv[2];
  
  char line1[200];
  char line2[200];

  ifstream File1;
  ifstream File2;

  File1.open(file1Name);
  File2.open(file2Name);

  if (!File1.is_open() || !File2.is_open()) {
    cout << "Failed: Are you sure that file exists?" << endl;
    return 0;
  }
  
  int num1 = 0;
  int num2 = 0;
  
  double distanceTemp = 0;

  while (!File1.eof()) {
    File1.getline(line1, 200);
    vector<double> vecFile1;
    vecFile1 = take_doub(line1);

    if (vecFile1.size() >= 3) {
      num1 = vecFile1.at(0);
      }
      while (!File2.eof()) {
        File2.getline(line2, 200);
        vector<double> vecFile2;
        vecFile2 = take_doub(line2);
        
        if (vecFile2.size() >= 3) {
          num2 = vecFile2.at(0);
          }

          distanceTemp = getVectorOData(vecFile1, vecFile2);
          if(distanceTemp != 0){
          printf("Distance from %i and from %i: %.2f\n", num1, num2, distanceTemp);
          }
      }
      File2.clear();
      File2.seekg(0);
  }

  File1.close();
  File2.close();

  cout << endl;
  return 0;
}

double getVectorOData(vector<double> vecFile1, vector<double> vecFile2) {
  double distTotal = 0.0;
  
  if (vecFile2.size() >= 3 && vecFile1.size() >= 3) {
    int vecPlacement = 1;
    
    while(vecFile1.size() > vecPlacement){
      distTotal += (vecFile1.at(vecPlacement) - vecFile2.at(vecPlacement));

      vecPlacement++;
    }
    if(distTotal < 0) distTotal = -distTotal;
  }
  
  return distTotal;
}

vector<double> take_doub(string str) {
  stringstream ss(str);
  vector<double> result;
  char ch;
  double tmp;
  while (ss >> tmp) {
    result.push_back(tmp);
    ss >> ch;
  }
  return result;
}

double manhattan_distance(vector<double> location) {
  double distance = 0.0;
  double dif = 0.0;
  for (int i = 0; i < location.size(); i = i + 2) {
    dif = location.at(i) - location.at(i + 1);
    if (dif < 0)
      dif = -dif;
    distance = distance + dif;
  }
  return distance;
}