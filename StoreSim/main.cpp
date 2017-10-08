
#include "StoreSimulator.hpp"
#include <iostream>

int main(){
  StoreSimulator s;
  std::cout << "~~~Begin Simulations~~~" << std::endl;
  std::cout << "Testing 8 normal, 0 self checkout." << std::endl;
  s.startSimulation(8, 0);
  std::cout << std::endl;

  std::cout << "Testing 6 normal, 4 self checkout." << std::endl;
  s.startSimulation(6, 4);
  std::cout << "(Repeat to confirm results)" << std::endl;
  s.startSimulation(6, 4);
  std::cout << std::endl;

  std::cout << "Testing 4 normal, 8 self checkout." << std::endl;
  s.startSimulation(4, 8);
  std::cout << std::endl;

  std::cout << "Testing 2 normal, 12 self checkout." << std::endl;
  s.startSimulation(2, 12);
  std::cout << std::endl;

  std::cout << "Testing 0 normal, 16 self checkout." << std::endl;
  s.startSimulation(0, 16);
  return 0;
}
