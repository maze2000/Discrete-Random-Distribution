#include<iostream>
#include<utility>
#include<cmath>
#include<stdlib.h>
#include<limits.h>

const int size = 4;
int table[255*size][4];
unsigned int t[4];
const int x = 255;
int K[size];
int V[size];

void initiate(std::pair<int, unsigned int>* a)
{

    for(int i = 0; i < 255*size; i++) {
        for(int j = 0; j < 4; j++)
            table[i][j] = -1;
    }

    int counter;
    for(int k = 0; k < 4; k++)
    {
        counter = 0;
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < (int) ((a[i].second >> k*8) & x); j++)
            {
                    table[counter][k] = a[i].first;
                    counter++;
            }
        }
        t[k] = counter;
	std::cout << counter << std::endl;
    }
    t[3] = t[3] << 24;
    t[2] = t[3] + (t[2] << 16);
    t[1] = t[2] + (t[1] << 8);
    t[0] = t[1] + t[0];
    
   //std::cout << table[103][0] << std::endl;
    
    /*
    int q = 0;
    std::cin >> q;
    for(int j = -1; j < 10; j++){
      counter = 0;
      for(int i = 0; i < 255*size; i++) {
	 if (table[i][q]==j)
	  counter++;
      }
      	std::cout << counter << std::endl; 
      
    }*/
}

/*
void initiate2(std::pair<int, unsigned int>* a)
{
    int counter = 0;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < (int) ((a[i].second & (x << (24))) >> 24); j++)
        {
                table[counter][3] = a[i].first;
                counter++;
        }
    }
    for(; counter < 255*size; counter++)
        table[counter][3] = -1;

    double avg = 1/size;
    int max = 0;
    int min = 0;

    for(int i = 0; i < size; i++)
    {
        K[i] = i;
        V[i] = (i+1) * avg;
    }

    for(int i = 0; i < size; i++)
    {
        for(int j = 1; j < size; j++)
        {
            if (a[j].second > a[max].second)
                max = j;
            if (a[j].second < a[max].second)
                min = j;
        }
        K[min] = max;
        V[min] = (min-1) * avg + a[min].second;
        a[max].second = a[max].second - (avg-a[min].second);
        a[min].second = avg;
    }

}
*/

int generate(unsigned int random) {
  
    if(random < t[3])
        return table[random >> 24][3];
    if(random < t[2])
        return table[(random-t[3]) >> 16][2];
    if(random < t[1])
        return table[(random-t[2]) >> 8][1];
    if(random < t[0])
        return table[random - t[1]][0];
    std::cout << "ERR" << std::endl;
    return 0;
    
}
/*
int generate2(unsigned int random) {

    if(table[random&255][3] >= 0)
        return table[random&255][3];
    double i = ((double) random)/pow(2,32);
    int j = 5*i;
    //std::cout << j << std::endl;

    if (random < V[j])
        return j;
    return K[j];
}
*/
int main() {

    std::pair<int,unsigned int> a[size];
    for(int i = 0; i < size; i++) {
        a[i] = std::make_pair(i+1,INT_MAX/size);
    }
    /*a[0].second = INT_MAX/size * 1/2;
    a[1].second = INT_MAX/size * 1/2;
    a[2].second = INT_MAX/size;
    a[3].second = INT_MAX/size * 2;*/
    initiate(a);
    int random;
    int sum = 0;
    for(int i = 0; i < 100000; i++) {
      random = generate(rand());
      sum += random;
    }
    std::cout << sum << std::endl;
}
