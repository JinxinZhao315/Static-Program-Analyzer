#ifndef TESTWRAPPER_H
#define TESTWRAPPER_H

#include <string>
#include <iostream>
#include <list>

// include your other headers here
#include "AbstractWrapper.h"
#include <set>
#include "../../spa/src/QPS/include/PQLDriver.h"
#include "../../spa/src/pkb/include/PKB.h"
#include "../../spa/src/source_processor/include/SourceProcessor.h"

class TestWrapper : public AbstractWrapper {
 public:
  // default constructor
  TestWrapper();
  
  // destructor
  ~TestWrapper();
  
  // method for parsing the SIMPLE source
  virtual void parse(std::string filename);
  
  // method for evaluating a query
  virtual void evaluate(std::string query, std::list<std::string>& results);

private:
    PKB pkb;
    SourceProcessor sourceProcessor;
};

#endif
