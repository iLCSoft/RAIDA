// -*- C++ -*-
#ifndef AIDA_SETTINGS_H
#define AIDA_SETTINGS_H 1

#include <string>
#include <vector>
namespace AIDA {

class Settings {

public:

  virtual ~Settings() {}

  Settings();

  Settings(const std::string defaultValue, 
	   const std::string value, 
	   const std::vector<std::string> options);

  virtual std::string getDefaultValue() const;
  virtual std::string getValue() const;
  virtual std::vector<std::string> getOptions() const;

  virtual bool setDefaultValue(const std::string defaultValue);
  virtual bool setValue(const std::string value);
  virtual bool setOptions(const std::vector<std::string> options);
  virtual bool addOption(std::string option);

protected:

  std::string _defaultValue;
  std::string _value;
  std::vector<std::string> _options;

};
} // namespace AIDA
#endif /* ifndef AIDA_SETTINGS_H */
