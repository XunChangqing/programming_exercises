#ifndef QUERY_BASE_H_
#define QUERY_BASE_H_
#include "text_query.h"
#include <memory>
#include <string>
namespace masa_text_query {
class QueryBase;
class Query {
  friend Query operator~(const Query &);
  friend Query operator&(const Query &, const Query &);
  friend Query operator|(const Query &, const Query &);

public:
  explicit Query(const std::string &);
  QueryResult Eval(const QueryText &) const;
  std::string Rep() const;

private:
  explicit Query(std::shared_ptr<QueryBase> query) : q_(query) {}
  std::shared_ptr<QueryBase> q_;
};

class QueryBase {
  friend class Query;
  // friend QueryBase* operator~(const QueryBase*);

protected:
  // using QueryText::LineNo;
  QueryBase() = default;
  virtual ~QueryBase() = default;

private:
  virtual QueryResult Eval(const QueryText &) const = 0;
  virtual std::string Rep() const = 0;
  DISALLOW_COPY_AND_ASSIGN(QueryBase);
};

class WordQuery : public QueryBase {
private:
  // public:
  friend class Query;
  WordQuery(const std::string &s) : query_word_(s) {}
  virtual QueryResult Eval(const QueryText &t) const {
    return t.Query(query_word_);
  }
  virtual std::string Rep() const { return query_word_; }
  std::string query_word_;
};

inline Query::Query(const std::string &s) : q_(new WordQuery(s)) {}

class NotQuery : public QueryBase {
private:
  friend Query operator~(const Query &);
  NotQuery(const Query &q) : query_(q) {}
  virtual std::string Rep() const { return "~(" + query_.Rep() + ")"; }
  virtual QueryResult Eval(const QueryText &) const;
  Query query_;
};
inline Query operator~(const Query &operand) {
  return Query(std::shared_ptr<QueryBase>(new NotQuery(operand)));
}

class BinaryQuery : public QueryBase {
protected:
  BinaryQuery(const Query &l, const Query &r, std::string sym)
      : lhs_(l), rhs_(r), opsym_(sym) {}
  virtual std::string Rep() const {
    return "(" + lhs_.Rep() + opsym_ + rhs_.Rep() + ")";
  }

  Query lhs_, rhs_;
  std::string opsym_;
};

class AndQuery : public BinaryQuery {
private:
  friend Query operator&(const Query &l, const Query &r);
  AndQuery(const Query &left, const Query &right)
      : BinaryQuery(left, right, "&") {}
  virtual QueryResult Eval(const QueryText &text) const;
};
inline Query operator&(const Query &left, const Query &right) {
  return Query(std::shared_ptr<QueryBase>(new AndQuery(left, right)));
}

class OrQuery : public BinaryQuery {
private:
  friend Query operator|(const Query &left, const Query &right);
  OrQuery(const Query &left, const Query &right)
      : BinaryQuery(left, right, "|") {}
  virtual QueryResult Eval(const QueryText &text) const;
};
inline Query operator|(const Query &left, const Query &right) {
  return Query(std::shared_ptr<QueryBase>(new OrQuery(left, right)));
}

//inline QueryBase *operator~(const QueryBase *) {}
}
#endif
