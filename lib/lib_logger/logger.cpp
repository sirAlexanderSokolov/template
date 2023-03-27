#include "logger.hpp"

/* COLOR CODES */

// Name          | FG | BG
// -----------------------
// Black           30  40
// Red             31  41
// Green           32  42
// Yellow          33  43
// Blue            34  44
// Magenta         35  45
// Cyan            36  46
// White           37  47
// Bright Black    90  100
// Bright Red      91  101
// Bright Green    92  102
// Bright Yellow   93  103
// Bright Blue     94  104
// Bright Magenta  95  105
// Bright Cyan     96  106
// Bright White    97  107

/* BOOST FORMAT EXAMPLES */
// std::cout << boost::format{"%d %d %d"} % 1 % 2 % 3 << std::endl;
// std::cout << boost::format{"%1% %2% %3%"} % "2018-01-12" % "info" %
// (boost::format{"%1% was open"} % "test.txt") << std::endl;
// boost::str((boost::format(fmt) % ... % args));
