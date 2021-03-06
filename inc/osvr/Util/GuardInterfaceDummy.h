/** @file
    @brief Header

    @date 2015

    @author
    Sensics, Inc.
    <http://sensics.com/osvr>
*/

// Copyright 2015 Sensics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef INCLUDED_GuardInterfaceDummy_h_GUID_3882E1F8_E44A_4D95_E4D3_6C60A9C94F05
#define INCLUDED_GuardInterfaceDummy_h_GUID_3882E1F8_E44A_4D95_E4D3_6C60A9C94F05

// Internal Includes
#include <osvr/Util/GuardInterface.h>

// Library/third-party includes
// - none

// Standard includes
// - none

namespace osvr {
namespace util {
    class DummyGuard : public GuardInterface {
      public:
        virtual bool lock() { return true; }
        virtual ~DummyGuard() {}
    };

} // namespace util
} // namespace osvr

#endif // INCLUDED_GuardInterfaceDummy_h_GUID_3882E1F8_E44A_4D95_E4D3_6C60A9C94F05
