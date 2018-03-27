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

#ifndef NIV_TESTS_TEST_UTILITIES_VECTOR_ALL_NAN_OR_EMPTY_HPP_
#define NIV_TESTS_TEST_UTILITIES_VECTOR_ALL_NAN_OR_EMPTY_HPP_

#include <string>
#include <vector>

namespace Catch {
namespace Matchers {

class VectorAllNanOrEmpty : public Catch::MatcherBase<std::vector<double>> {
 public:
  bool match(const std::vector<double>& values) const override {
    bool retval = true;
    for (double v : values) {
      retval &= std::isnan(v);
    }
    return retval;
  }
  std::string describe() const override { return ""; }
};

}  // namespace Matchers
}  // namespace Catch

using Catch::Matchers::VectorAllNanOrEmpty;

#endif  // NIV_TESTS_TEST_UTILITIES_VECTOR_ALL_NAN_OR_EMPTY_HPP_
