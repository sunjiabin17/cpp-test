#include <iostream>
#include <string>
#include <getopt.h>


int main(int argc, char** argv) {
  int opt;
  while ((opt = getopt(argc, argv, "if:lr")) != -1) {
    switch (opt) {
      case 'i':
      case 'l':
      case 'r':
        std::cout << "option: " << (char)opt << std::endl;
        break;
      case 'f':
        std::cout << "filename: " << optarg << std::endl;
        break;
      case ':':
        std::cout << "option needs a value" << std::endl;
        break;
      case '?':
        std::cout << "unknown option: " << (char)optopt << std::endl;
        break;
    }
  }



}