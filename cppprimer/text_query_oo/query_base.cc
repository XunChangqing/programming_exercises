#include "query_base.h"
#include <algorithm>

namespace masa_text_query {

QueryResult OrQuery::Eval(const QueryText &text) const {
  auto left = lhs_.Eval(text);
  auto right = rhs_.Eval(text);
  auto ret_lines = std::make_shared<std::set<QueryText::LineNo>>(
      left.lines_->begin(), left.lines_->begin());
  ret_lines->insert(right.lines_->begin(), right.lines_->end());
  return QueryResult(left.sought_, ret_lines, left.file_);
}

QueryResult AndQuery::Eval(const QueryText &text) const {
  auto left = lhs_.Eval(text);
  auto right = rhs_.Eval(text);
  auto ret_lines = std::make_shared<std::set<QueryText::LineNo>>();
  std::set_intersection(left.lines_->begin(), left.lines_->end(),
                        right.lines_->begin(), right.lines_->end(),
                        std::inserter(*ret_lines, ret_lines->begin()));
  return QueryResult(left.sought_, ret_lines, left.file_);
}

QueryResult NotQuery::Eval(const QueryText &text) const {
  auto result = query_.Eval(text);
  auto ret_lines = std::make_shared<std::set<QueryText::LineNo>>();
  auto beg = result.lines_->begin(), end = result.lines_->end();
  auto sz = result.file_->size();
  for (size_t n = 0; n != sz; ++n) {
    if (beg == end || *beg != n)
      ret_lines->insert(n);
    else if (beg != end)
      ++beg;
  }
  return QueryResult(result.sought_, ret_lines, result.file_);
}

QueryResult Query::Eval(const QueryText &text) const { return q_->Eval(text); }

std::string Query::Rep() const { return q_->Rep(); }
}
