#include "text_query.h"
#include <sstream>

namespace masa_text_query {
QueryText::QueryText(std::ifstream &infile)
    : file_(new std::vector<std::string>) {
  std::string text;
  while (std::getline(infile, text)) {
    file_->push_back(text);
    int n = file_->size() - 1;
    std::string word;
    std::istringstream line(text);
    while (line >> word) {
      auto &lines = wm_[word];
      if (!lines) {
        lines.reset(new std::set<QueryText::LineNo>);
      }
      lines->insert(n);
    }
  }
}

QueryResult QueryText::Query(std::string &s) {
  static std::shared_ptr<std::set<QueryText::LineNo>> nodata(
      new std::set<QueryText::LineNo>);
  auto loc = wm_.find(s);
  if (loc == wm_.end()) {
    return QueryResult(s, nodata, file_);
  } else {
    return QueryResult(s, loc->second, file_);
  }
}

// return the plural version of word if ctr is greater than 1
std::string make_plural(size_t ctr, const std::string &word, const std::string &ending) {
  return (ctr > 1) ? word + ending : word;
}

std::ostream &print(std::ostream &ostr, const QueryResult &result) {
  ostr << result.sought_ << " occurs " << result.lines_->size() << " "
       << make_plural(result.lines_->size(), "time", "s") << std::endl;
  // print each line in which the word appeared
  for (auto num : *result.lines_) // for every element in the set
    ostr << "\t(line " << num + 1 << ") " << *(result.file_->begin() + num)
         << std::endl;
  return ostr;
}

} // end namespace masa_text_query
