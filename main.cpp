#include "inc/random_distribution.cpp"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/discrete_distribution.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_rng.h>
#include <RandomLib/Random.hpp>
#include <RandomLib/RandomSelect.hpp>

#include <chrono>
#include <random>

std::string s("");

void testBoost() {
  
  int size = 10000;
  int max = 100000;
  boost::mt19937 gen;
  std::vector<double> a;
  clock_t startTime;
  
  for(int i = 0; i < 10; i++) {
    
  for(int i = 0; i<size; i++) {
    a.push_back(rand());
  }
    
  boost::random::discrete_distribution<> dist(a.begin(), a.end());

  std::cout << "\t Boost: " << std::endl << "\t\t Initiate: " << clock() - startTime << std::endl;
  startTime = clock();  
  for(int i = 0; i < max; i++) {
    dist(gen);
  }

  std::cout << "\t\t Generate: " << clock() - startTime << std::endl << std::endl;
  
  }
  
  for(int i = 0; i<size; i++) {
    a[i] = 1.0/size;
  }
  
  startTime = clock();
  
  boost::random::discrete_distribution<> dist2(a.begin(), a.end());

  std::cout << "\t Boost: " << std::endl << "\t\t Initiate: " << clock() - startTime << std::endl;
  startTime = clock();  
  for(int i = 0; i < max; i++) {
    dist2(gen);
  }

  std::cout << "\t\t Generate: " << clock() - startTime << std::endl << std::endl;

}

void test(int max, int size) {
  
  std::vector<double> a;
  std::vector<int> b;
  double d[size];

  for(int i = 0; i<size; i++) {
    a.push_back(1.0/size);
    b.push_back(1);
    d[i] = rand();;
  }
  
  //s += std::to_string(max);
  //s += "\t";
  s += std::to_string(size);
  s += "\t";
  
  int sum = 0;
  
  std::cout << std::endl << "Max: " << max << ";\t Size: " << size << std::endl << std::endl;
    
  boost::mt19937 gen;
  
  
  const gsl_rng_type * T;
  gsl_rng * r;

  gsl_rng_env_setup();

  T = gsl_rng_default;
  r = gsl_rng_alloc(T);
  
  RandomLib::Random r2; 
  
  sum = 0;
  clock_t startTime = clock(); 
  
  
  
  //RandomLib
  
  sum = 0;
  startTime = clock();
  RandomLib::RandomSelect<int> sel(b.begin(), b.end());
  s += std::to_string(clock() - startTime);
  s += "\t";
  std::cout << "\t RandomLib: " << std::endl << "\t\t Initiate: " << clock() - startTime << std::endl;
  startTime = clock();  
  for(int i = 0; i < max; i++) {
    sum += sel(r2);
  }
  s += std::to_string(clock() - startTime);
  s += "\t";
  std::cout << "\t\t Generate: " << clock() - startTime << std::endl << "\t\t Sum: " << sum << std::endl;
  
  
  //gnu science
  
  sum = 0;
  startTime = clock();
  gsl_ran_discrete_t * table = gsl_ran_discrete_preproc(size, d);
  s += std::to_string(clock() - startTime);
  s += "\t";
  std::cout << "\t Gnu Science: " << std::endl << "\t\t Initiate: " << clock() - startTime << std::endl;
  startTime = clock();  
  for(int i = 0; i < max; i++) {
    sum += gsl_ran_discrete(r, table);
  }
  s += std::to_string(clock() - startTime);
  s += "\t";
  std::cout << "\t\t Generate: " << clock() - startTime << std::endl << "\t\t Sum: " << sum << std::endl;
  
  gsl_rng_free(r);

  
  //boost
  
  sum = 0;
  startTime = clock();
  boost::random::discrete_distribution<> dist(a.begin(), a.end());
  //boost::random::discrete_distribution<> dist(b, b+size);
  s += std::to_string(clock() - startTime);
  s += "\t";
  std::cout << "\t Boost: " << std::endl << "\t\t Initiate: " << clock() - startTime << std::endl;
  startTime = clock();  
  for(int i = 0; i < max; i++) {
    sum += dist(gen);
  }
  s += std::to_string(clock() - startTime);
  s += "\t";
  std::cout << "\t\t Generate: " << clock() - startTime << std::endl << "\t\t Sum: " << sum << std::endl;
  
  
  //std::dsicrete_distribution
  
  sum = 0;
  startTime = clock();
  std::discrete_distribution<int> std_dist(b.begin(), b.end());
  s += std::to_string(clock() - startTime);
  s += "\t";
  std::cout << "\t std::discrete_distribution: " << std::endl << "\t\t Initiate: " << clock() - startTime << std::endl;
  startTime = clock();  
  for(int i = 0; i < max; i++) {
    sum += std_dist(gen);
  }
  s += std::to_string(clock() - startTime);
  s += "\t";
  std::cout << "\t\t Generate: " << clock() - startTime << std::endl << "\t\t Sum: " << sum << std::endl;
  
  /*
  //table-lookup
  
  sum = 0;
  startTime = clock();
  random_distribution q(a);
  s += std::to_string(clock() - startTime);
  s += "\t";
  std::cout << "\t Method 1: " << std::endl << "\t\t Initiate: " << clock() - startTime << std::endl;
  startTime = clock();  
  for(int i = 0; i < max; i++) {
    sum += q.dist();
  }
  s += std::to_string(clock() - startTime);
  s += "\t";
  std::cout << "\t\t Generate: " << clock() - startTime << std::endl << "\t\t Sum: " << sum << std::endl;
  //std::cout << "\t\t i0: " << q.i0 << "\t i1: " << q.i1 <<  "\t i2: " << q.i2 <<  "\t i3: " << q.i3 << std::endl;

  
  //table-lookup + histogram
  
  sum = 0;
  startTime = clock();
  random_distribution q2(a,2);
  s += std::to_string(clock() - startTime);
  s += "\t";
  std::cout << "\t Method 2: " << std::endl << "\t\t Initiate: " << clock() - startTime << std::endl;
  startTime = clock();  
  for(int i = 0; i < max; i++) {
    sum += q2.dist2();
  }
  s += std::to_string(clock() - startTime);
  s += "\t";
  std::cout << "\t\t Generate: " << clock() - startTime << std::endl << "\t\t Sum: " << sum << std::endl;
    
  
  //binary search
  
  sum = 0;
  startTime = clock();
  random_distribution q3(a,3);
  s += std::to_string(clock() - startTime);
  s += "\t";
  std::cout << "\t Method 3: " << std::endl << "\t\t Initiate: " << clock() - startTime << std::endl;
  startTime = clock();  
  for(int i = 0; i < max; i++) {
    sum += q3.dist3();
  }
  s += std::to_string(clock() - startTime);
  s += "\t";
  std::cout << "\t\t Generate: " << clock() - startTime << std::endl << "\t\t Sum: " << sum << std::endl;  
  */
  s += "\n";
}

int main() {
  
  
  for(int i = 10000; i <= 1000000; i += 10000)
    test(100000, i);
  
  std::ofstream output("data.txt");
  output << s;
  output.close();
  //testBoost();
  
  return 0;
}
