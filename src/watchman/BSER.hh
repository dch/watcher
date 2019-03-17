#ifndef BSER_H
#define BSER_H

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

enum BSERType {
  ARRAY = 0x00,
  OBJECT = 0x01,
  STRING = 0x02,
  INT8 = 0x03,
  INT16 = 0x04,
  INT32 = 0x05,
  INT64 = 0x06,
  REAL = 0x07,
  BOOL_TRUE = 0x08,
  BOOL_FALSE = 0x09,
  NUL = 0x0a,
  TEMPLATE = 0x0b
};

class BSERValue;

class BSER {
public:
  typedef std::vector<BSER> Array;
  typedef std::unordered_map<std::string, BSER> Object;

  BSER();
  BSER(BSER::Array value);
  BSER(BSER::Object value);
  BSER(std::string value);
  BSER(const char *value);
  BSER(int64_t value);
  BSER(double value);
  BSER(bool value);
  BSER(std::istream &iss);

  BSER::Array arrayValue();
  BSER::Object objectValue();
  std::string stringValue();
  int64_t intValue();
  double doubleValue();
  bool boolValue();
  void encode(std::ostream &oss);

  static int64_t decodeLength(std::istream &iss);
  std::string encode();
private:
  std::shared_ptr<BSERValue> m_ptr;
};

class BSERValue {
protected:
  friend class BSER;
  virtual BSER::Array arrayValue() { return BSER::Array(); }
  virtual BSER::Object objectValue() { return BSER::Object(); }
  virtual std::string stringValue() { return std::string(); }
  virtual int64_t intValue() { return 0; }
  virtual double doubleValue() { return 0; }
  virtual bool boolValue() { return false; }
  virtual void encode(std::ostream &oss) {}
  virtual ~BSERValue() {}
};

#endif
