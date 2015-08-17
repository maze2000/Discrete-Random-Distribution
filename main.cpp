#include "inc/random_distribution.cpp"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/discrete_distribution.hpp>
#include <iostream>
#include <fstream>
#include <string>

std::string s("");

void test(int max, int size) {
  
  std::vector<double> a;
  //double b[size];
  for(int i = 0; i<size; i++) {
    a.push_back(1.0/size);
    //b[i] = 1.0/size;
  }
  //double* c = &a[0];
  
  s += std::to_string(max);
  s += "\t";
  s += std::to_string(size);
  s += "\t";
  
  int sum = 0;
  
  std::cout << std::endl << "Max: " << max << ";\t Size: " << size << std::endl << std::endl;
  
  sum = 0;
  clock_t startTime = clock(); 
  
  
  boost::mt19937 gen;
  
  double probabilities[] = {
    0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 
    0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 
    0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 
    0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 
    0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 
    0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 
    0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 
    0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 
    0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 
    0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01
  };
  
  boost::random::discrete_distribution<> dist(probabilities);
  std::cout << "\t Boost: " << std::endl << "\t\t Initiate: " << clock() - startTime << std::endl;
  startTime = clock();  
  for(int i = 0; i < max; i++) {
    sum += dist(gen);
  }
  s += std::to_string(clock() - startTime);
  s += "\t";
  std::cout << "\t\t Generate: " << clock() - startTime << std::endl << "\t\t Sum: " << sum << std::endl;
  
  sum = 0;
  startTime = clock(); 
  random_distribution q(a);
  std::cout << "\t Method 1: " << std::endl << "\t\t Initiate: " << clock() - startTime << std::endl;
  startTime = clock();  
  for(int i = 0; i < max; i++) {
    sum += q.dist();
  }
  s += std::to_string(clock() - startTime);
  s += "\t";
  std::cout << "\t\t Generate: " << clock() - startTime << std::endl << "\t\t Sum: " << sum << std::endl;
  
  sum = 0;
  startTime = clock();
  random_distribution q2(a,2);
  std::cout << "\t Method 2: " << std::endl << "\t\t Initiate: " << clock() - startTime << std::endl;
  startTime = clock();  
  for(int i = 0; i < max; i++) {
    sum += q2.dist2();
  }
  s += std::to_string(clock() - startTime);
  s += "\t";
  std::cout << "\t\t Generate: " << clock() - startTime << std::endl << "\t\t Sum: " << sum << std::endl;
    
  sum = 0;
  startTime = clock();
  random_distribution q3(a,3);
  std::cout << "\t Method 3: " << std::endl << "\t\t Initiate: " << clock() - startTime << std::endl;
  startTime = clock();  
  for(int i = 0; i < max; i++) {
    sum += q3.dist3();
  }
  s += std::to_string(clock() - startTime);
  s += "\t";
  std::cout << "\t\t Generate: " << clock() - startTime << std::endl << "\t\t Sum: " << sum << std::endl;  
  
  s += "\n";
}

int main() {
  
  test(100000, 100); /*
  test(100000, 1000);
  test(100000, 2000);
  test(100000, 3000);
  test(100000, 4000);
  test(100000, 5000);
  test(100000, 6000);
  test(100000, 7000);
  test(100000, 8000);
  test(100000, 9000);
  test(100000, 10000);
  test(100000, 11000);
  test(100000, 12000);
  test(100000, 13000);
  test(100000, 14000);
  test(100000, 15000);
  test(100000, 16000);
  test(100000, 17000);
  test(100000, 18000);
  test(100000, 19000); 
  //test(100000, 100000);
  
  //test(1000000, 10000);
  //test(10000000, 10000);
  //test(100000000, 10000);
  
  std::ofstream output("data.txt");
  output << s;
  output.close(); */
  
  return 0;
}
