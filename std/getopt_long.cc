#include <unistd.h>
#include <iostream>
#include <string>
#include <getopt.h>

int main(int argc, char* argv[]) {
  int opt;
  static struct option long_options[] = {
    {"streaming", no_argument, NULL, 's'},
    {"output", required_argument, NULL, 'o'},
    {"input", required_argument, NULL, 'i'},
    {"help", no_argument, NULL, 'h'},
  };
  while ((opt = getopt_long(argc, argv, "so:i:hcu:", long_options, NULL)) != -1) {
    switch (opt) {
      case 's':
        std::cout << "streaming" << std::endl;
        break;
      case 'o':
        std::cout << "output: " << optarg << std::endl;
        break;
      case 'i':
        std::cout << "input: " << optarg << std::endl;
        break;
      case 'h':
        std::cout << "help" << std::endl;
        break;
      case 'c':
        std::cout << "channel" << std::endl;
        break;
      case 'u':
        std::cout << "url=" << optarg << std::endl;
        break;
      case '?':
        std::cout << "unknown option: " << (char)optopt << std::endl;
        break;
    }
  }


  return 0;
}