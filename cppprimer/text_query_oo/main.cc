#include "text_query.h"
#include "query_base.h"
#include <iostream>
#include <fstream>

void RunQuery(std::ifstream &infile) {
  // infile is an ifstream that is the file we want to query
  // store the file and build the query map
  masa_text_query::QueryText tq(infile);
  //masa_text_query::WordQuery wquery("hello");
  //masa_text_query::WordQuery wquery2(wquery);

  // masa_text_query::Query re =
  // masa_text_query::Query("hello") & masa_text_query::Query("yes") |
  // masa_text_query::Query("you");
  masa_text_query::Query re = ~masa_text_query::Query("hello");
  std::cout << re.Rep() << std::endl;
  print(std::cout, re.Eval(tq)) << std::endl;

  // iterate with the user: prompt for a word to find and print results
  //while (true) {
    //std::cout << "enter word to look for, or q to quit: ";
    //std::string s;
    //// stop if we hit end-of-file on the input or if a 'q' is entered
    //if (!(std::cin >> s) || s == "q")
      //break;
    //// run the query and print the results
    //print(std::cout, tq.Query(s)) << std::endl;
  //}
}

int main(int argc, char **argv) {
  if (argc < 2)
    return -1;
  std::ifstream infilestr(argv[1]);
  RunQuery(infilestr);
  return 0;
}
