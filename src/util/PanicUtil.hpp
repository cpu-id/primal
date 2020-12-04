#pragma once

#include "../Vendor.hpp"

//Primal region: "Critical".
namespace Primal {

    class PanicUtil {

    public:

        /**
         *
         * @point - Fast exit application due to internal crash, with additional info print support. (!Only debug mode)
         *
         * @args  - Caller: Call-in trace. Reason: Exception reason.
         *
         */

        static void Release (const char* caller, const char* reason);

    };

};