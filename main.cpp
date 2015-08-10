#include "inc/random_distribution.cpp"

int main() {
  
  std::vector<double> a;
  for(int i = 0; i<10000; i++) {
    a.push_back(0.1);
  }
  //std::cout << "size2: " << sizeof(q) << std::endl;
  
  clock_t startTime = clock(); 
  random_distribution q(a);
  std::cout << "Method 1: " << std::endl << "\t Initiate: " << clock() - startTime << std::endl;
  startTime = clock();  
  for(int i = 0; i < 10000000; i++) {
    q.dist();
  }
  std::cout << "\t Generate: " << clock() - startTime << std::endl;
  
  startTime = clock();
  random_distribution q2(a,2);
  std::cout << "Method 2: " << std::endl << "\t Initiate: " << clock() - startTime << std::endl;
  startTime = clock();  
  for(int i = 0; i < 10000000; i++) {
    q2.dist2();
  }
  std::cout << "\t Generate: " << clock() - startTime << std::endl;
    
  startTime = clock();
  random_distribution q3(a,3);
  std::cout << "Method 3: " << std::endl << "\t Initiate: " << clock() - startTime << std::endl;
  startTime = clock();  
  for(int i = 0; i < 10000000; i++) {
    q3.dist3();
  }
  std::cout << "\t Generate: " << clock() - startTime << std::endl;
  

  return 0;
}
