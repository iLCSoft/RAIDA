#include <RAIDA/Settings.h>


using namespace AIDA;

Settings::Settings()
{

}

Settings::Settings(const std::string defaultValue,
		   const std::string value,
		   const std::vector<std::string> options)
{
  _defaultValue = defaultValue;
  _value = value;
  _options = options;
}

std::string Settings::getDefaultValue() const
{
  return _defaultValue;
}

std::string Settings::getValue() const
{
  return _value;
}

std::vector<std::string> Settings::getOptions() const
{
  return _options;
}

bool Settings::setDefaultValue(const std::string defaultValue)
{
  _defaultValue = defaultValue;
  return true;
}

bool Settings::setValue(const std::string value)
{
  _value = value;
  return true;
}

bool Settings::setOptions(const std::vector<std::string> options)
{
  _options = options;
  return true;
}

bool Settings::addOption(std::string option)
{
  _options.push_back(option);
  return true;
}

