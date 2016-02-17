#include <string>
#include <list>
#include <vector>
#include "Clause.h"

using namespace std;


class QueryEvaluator {
public:
    QueryEvaluator();
    list<string> evaluate(vector<Clause>,vector<Clause>,vector<Pattern>);
}
