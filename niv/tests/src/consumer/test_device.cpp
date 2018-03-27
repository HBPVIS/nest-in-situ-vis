//------------------------------------------------------------------------------
// nest in situ vis
//
// Copyright (c) 2017-2018 RWTH Aachen University, Germany,
// Virtual Reality & Immersive Visualisation Group.
//------------------------------------------------------------------------------
//                                 License
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
//------------------------------------------------------------------------------

#include <string>
#include <vector>

#include "catch/catch.hpp"

#include "niv/consumer/device.hpp"
#include "niv/nest_test_data.hpp"

namespace {

class Device : public niv::consumer::Device {
 public:
  explicit Device(const std::string& name) : niv::consumer::Device(name) {}
  Device(const Device&) = delete;
  Device(Device&&) = delete;
  ~Device() = default;

  Device& operator=(const Device&) = delete;
  Device& operator=(Device&&) = delete;

  void Update() override {}
};

}  // namespace

namespace Catch {
namespace Matchers {
namespace Vector {
template <typename T>
struct EqualsApproxMatcher : MatcherBase<std::vector<T>, std::vector<T> > {
  explicit EqualsApproxMatcher(std::vector<T> const& comparator)
      : comparator_(comparator) {}

  bool match(std::vector<T> const& v) const CATCH_OVERRIDE {
    // !TBD: This currently works if all elements can be compared using !=
    // - a more general approach would be via a compare template that defaults
    // to using !=. but could be specialised for, e.g. std::vector<T> etc
    // - then just call that directly
    if (comparator_.size() != v.size()) return false;
    for (size_t i = 0; i < v.size(); ++i)
      if (Approx(comparator_[i]) != v[i]) return false;
    return true;
  }
  virtual std::string describe() const CATCH_OVERRIDE {
    return "Equals: " + Catch::toString(comparator_);
  }
  std::vector<T> const& comparator_;
};
}  // namespace Vector

template <typename T>
Vector::EqualsApproxMatcher<T> EqualsApprox(std::vector<T> const& comparator) {
  return Vector::EqualsApproxMatcher<T>(comparator);
}

}  // namespace Matchers
}  // namespace Catch

SCENARIO("NestMultimeter lists the timesteps",
         "[niv][niv::consumer][niv::consumer::Device]") {
  GIVEN("a device providing access to some data") {
    ::Device device(niv::testing::ANY_DEVICE_NAME);
    device.SetNode(&niv::testing::ANY_NEST_DATA);

    THEN("the device provides correct timesteps as strings") {
      REQUIRE(device.GetTimestepsString() == niv::testing::ANY_TIMES_STRING);
    }
    THEN("the device provides correct timesteps as doubles") {
      REQUIRE_THAT(device.GetTimesteps(),
                   Catch::Matchers::EqualsApprox(niv::testing::ANY_TIMES));
    }
  }

  GIVEN("a device with an incorrect name providing access to some data") {
    ::Device multimeter(niv::testing::NOT_A_DEVICE_NAME);
    multimeter.SetNode(&niv::testing::ANY_NEST_DATA);

    THEN("the device does not provide timesteps as strings") {
      REQUIRE(multimeter.GetTimestepsString().empty());
    }
    THEN("the device does not provide timesteps as doubles") {
      REQUIRE(multimeter.GetTimesteps().empty());
    }
  }
}
