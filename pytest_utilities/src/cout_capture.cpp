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

SUPPRESS_WARNINGS_BEGIN
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#if __GNUC__ >= 7
#pragma GCC diagnostic ignored "-Wregister"
#endif
#include "boost/python.hpp"
SUPPRESS_WARNINGS_END

#include <iostream>  // NOLINT
#include <string>    // NOLINT

namespace test_utilities {

class CoutCapture {
 public:
  CoutCapture() { original_rdbuf_ = std::cout.rdbuf(cout_stream_.rdbuf()); }
  ~CoutCapture() { std::cout.rdbuf(original_rdbuf_); }

  bool operator==(const std::string& other) const {
    return cout_stream_.str() == other;
  }

  std::string ToString() const { return "\"" + cout_stream_.str() + "\""; }

 private:
  std::streambuf* original_rdbuf_;
  std::stringstream cout_stream_;
};

}  // namespace test_utilities

BOOST_PYTHON_MODULE(pytest_utilities) {
  using boost::python::class_;
  using boost::python::def;
  using boost::python::init;

  class_<test_utilities::CoutCapture, boost::noncopyable>("CoutCapture")
      .def("ToString", &test_utilities::CoutCapture::ToString);
}
