#ifndef TEXT_QUERY_H_
#define TEXT_QUERY_H_
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <memory>

#define DISALLOW_COPY_AND_ASSIGN(TypeName)                                     \
  TypeName(const TypeName &);                                                  \
  void operator=(const TypeName &)

namespace masa_text_query {
class QueryResult;

class QueryText {
public:
  using LineNo = std::vector<std::string>::size_type;
  // typedef std::vector<std::string>::size_type LineNo;
  QueryText(std::ifstream &infile);
  QueryResult Query(std::string &s);

  std::shared_ptr<std::vector<std::string>> file_;
  std::map<std::string, std::shared_ptr<std::set<QueryText::LineNo>>> wm_;

private:
  DISALLOW_COPY_AND_ASSIGN(QueryText);
};

std::ostream &print(std::ostream &, const QueryResult &);
class QueryResult {
  friend std::ostream &print(std::ostream &, const QueryResult &);

public:
  QueryResult(std::string sought, std::shared_ptr<std::set<QueryText::LineNo>> lines,
              std::shared_ptr<std::vector<std::string>> file)
      : sought_(sought), lines_(lines), file_(file) {}

  // private:
  std::string sought_;
  std::shared_ptr<std::set<QueryText::LineNo>> lines_;
  std::shared_ptr<std::vector<std::string>> file_;

private:
  // DISALLOW_COPY_AND_ASSIGN(QueryResult);
};

} // end namespace masa_text_query

#endif
