#include "text_query.h"
#include <iostream>
#include <fstream>

void RunQuery(std::ifstream &infile) {
  // infile is an ifstream that is the file we want to query
  // store the file and build the query map
  masa_text_query::QueryText tq(infile);

  // iterate with the user: prompt for a word to find and print results
  while (true) {
    std::cout << "enter word to look for, or q to quit: ";
    std::string s;
    // stop if we hit end-of-file on the input or if a 'q' is entered
    if (!(std::cin >> s) || s == "q")
      break;
    // run the query and print the results
    print(std::cout, tq.Query(s)) << std::endl;
  }
}

int main(int argc, char **argv) {
  if (argc < 2)
    return -1;
  std::ifstream infilestr(argv[1]);
  RunQuery(infilestr);
  return 0;
}
