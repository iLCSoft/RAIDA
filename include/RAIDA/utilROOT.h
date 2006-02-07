#ifndef AIDA_UTILROOT_H
#define AIDA_UTILROOT_H 1
#include <string>

namespace AIDA {

std::string AIDAInternalTitle(const std::string & title, int type);

std::string extractName(const std::string & pathName);

} // namespace AIDA
#endif /* ifndef AIDA_UTILROOT_H */

