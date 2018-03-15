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

#include "catch/Catch.hpp"

#include "niv/consumer/arbor_multimeter.hpp"
#include "niv/nest_test_data.hpp"

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

SCENARIO("ArborMultimeter lists the timesteps",
         "[niv][niv::consumer][niv::consumer::ArborMultimeter]") {
  GIVEN("a multimeter providing access to some data") {
    niv::consumer::ArborMultimeter multimeter(
        niv::testing::ANY_MULTIMETER_NAME);
    multimeter.SetNode(&niv::testing::ANY_NEST_DATA);

    THEN("the multimeter provides correct timesteps") {
      REQUIRE(multimeter.GetTimestepsString() ==
              niv::testing::AnyTimesString());
    }
  }

  GIVEN("a multimeter with an incorrect name providing access to some data") {
    niv::consumer::ArborMultimeter multimeter(
        niv::testing::NOT_A_MULTIMETER_NAME);
    multimeter.SetNode(&niv::testing::ANY_NEST_DATA);

    THEN("the multimeter does not provide timesteps") {
      REQUIRE(multimeter.GetTimestepsString().empty());
    }
  }
}

SCENARIO("ArborMultimeter lists attributes for a timestep",
         "[niv][niv::consumer][niv::consumer::ArborMultimeter]") {
  GIVEN("a multimeter providing access to some data") {
    niv::consumer::ArborMultimeter multimeter(
        niv::testing::ANY_MULTIMETER_NAME);
    multimeter.SetNode(&niv::testing::ANY_NEST_DATA);

    WHEN("attributes are requested") {
      auto attributes{multimeter.GetAttributes(niv::testing::ANY_TIME)};
      THEN("the multimeter provides the attributes") {
        REQUIRE(attributes == niv::testing::ANY_ATTRIBUTES);
      }
    }

    WHEN("attributes are requested for an invalid timestep") {
      auto attributes{multimeter.GetAttributes(niv::testing::NOT_A_TIME)};
      THEN("the multimeter does not provide attributes") {
        REQUIRE(attributes.empty());
      }
    }
  }

  GIVEN("a multimeter with an incorrect name providing access to some data") {
    niv::consumer::ArborMultimeter multimeter(
        niv::testing::NOT_A_MULTIMETER_NAME);
    multimeter.SetNode(&niv::testing::ANY_NEST_DATA);

    WHEN("attributes are requested") {
      auto attributes{multimeter.GetAttributes(niv::testing::ANY_TIME)};
      THEN("the multimeter does not provide attributes") {
        REQUIRE(attributes.empty());
      }
    }
  }
}

SCENARIO(
    "ArborMultimeter lists the neuron ids stored for an attribute in a "
    "timestep",
    "[niv][niv::consumer][niv::consumer::ArborMultimeter]") {
  GIVEN("a multimeter providing access to some data") {
    niv::consumer::ArborMultimeter multimeter(
        niv::testing::ANY_MULTIMETER_NAME);
    multimeter.SetNode(&niv::testing::ANY_NEST_DATA);

    WHEN("neuron ids are requested") {
      auto ids{multimeter.GetNeuronIds(niv::testing::ANY_TIME,
                                       niv::testing::ANY_ATTRIBUTE)};
      THEN("the multimeter provides the ids") {
        REQUIRE(ids == niv::testing::ANY_IDS);
      }
    }

    WHEN("neuron ids are requested for an invalid timestep") {
      auto ids{multimeter.GetNeuronIds(niv::testing::NOT_A_TIME,
                                       niv::testing::ANY_ATTRIBUTE)};
      THEN("the multimeter does not provide ids") { REQUIRE(ids.empty()); }
    }

    WHEN("neuron ids are requested for an invalid attribute") {
      auto ids{multimeter.GetNeuronIds(niv::testing::ANY_TIME,
                                       niv::testing::NOT_AN_ATTRIBUTE)};
      THEN("the multimeter does not provide ids") { REQUIRE(ids.empty()); }
    }
  }

  GIVEN("a multimeter with an incorrect name providing access to some data") {
    niv::consumer::ArborMultimeter multimeter(
        niv::testing::NOT_A_MULTIMETER_NAME);
    multimeter.SetNode(&niv::testing::ANY_NEST_DATA);

    WHEN("neuron ids are requested") {
      auto ids{multimeter.GetNeuronIds(niv::testing::ANY_TIME,
                                       niv::testing::ANY_ATTRIBUTE)};
      THEN("the multimeter does not provide ids") { REQUIRE(ids.empty()); }
    }
  }
}

SCENARIO("ArborMultimeter retrieves datum for time, attribute, neuron",
         "[niv][niv::consumer][niv::consumer::ArborMultimeter]") {
  GIVEN("a multimeter providing access to some data") {
    niv::consumer::ArborMultimeter multimeter(
        niv::testing::ANY_MULTIMETER_NAME);
    multimeter.SetNode(&niv::testing::ANY_NEST_DATA);

    WHEN("requesting data") {
      const double datum = multimeter.GetDatum(niv::testing::ANY_TIME,
                                               niv::testing::ANOTHER_ATTRIBUTE,
                                               niv::testing::THIRD_ID);
      THEN("it is correct") {
        const std::size_t DATUM_OFFSET{niv::testing::ANY_TIME_OFFSET +
                                       niv::testing::ANOTHER_ATTRIBUTE_OFFSET +
                                       niv::testing::THIRD_ID_OFFSET};
        REQUIRE(datum == Approx(niv::testing::ANY_VALUES[DATUM_OFFSET]));
      }
    }

    WHEN("requesting datum at an invalid time") {
      const double datum = multimeter.GetDatum(niv::testing::NOT_A_TIME,
                                               niv::testing::ANOTHER_ATTRIBUTE,
                                               niv::testing::THIRD_ID);
      THEN("nan is returned") { REQUIRE(std::isnan(datum)); }
    }

    WHEN("requesting datum for an invalid attribute") {
      const double datum = multimeter.GetDatum(niv::testing::ANY_TIME,
                                               niv::testing::NOT_AN_ATTRIBUTE,
                                               niv::testing::THIRD_ID);
      THEN("nan is returned") { REQUIRE(std::isnan(datum)); }
    }

    WHEN("requesting datum for an invalid neuron id") {
      const double datum = multimeter.GetDatum(niv::testing::ANY_TIME,
                                               niv::testing::ANOTHER_ATTRIBUTE,
                                               niv::testing::NOT_AN_ID);
      THEN("nan is returned") { REQUIRE(std::isnan(datum)); }
    }
  }

  GIVEN("a multimeter with an incorrect name providing access to some data") {
    niv::consumer::ArborMultimeter multimeter(
        niv::testing::NOT_A_MULTIMETER_NAME);
    multimeter.SetNode(&niv::testing::ANY_NEST_DATA);

    WHEN("requesting data") {
      const double datum = multimeter.GetDatum(niv::testing::ANY_TIME,
                                               niv::testing::ANOTHER_ATTRIBUTE,
                                               niv::testing::THIRD_ID);

      THEN("nan is returned") { REQUIRE(std::isnan(datum)); }
    }
  }
}

SCENARIO("ArborMultimeter provides time series data",
         "[niv][niv::consumer][niv::consumer::ArborMultimeter]") {
  std::vector<double> expected;
  for (auto time_offset : niv::testing::TIME_OFFSETS) {
    const auto DATUM_INDEX{time_offset +
                           niv::testing::ANOTHER_ATTRIBUTE_OFFSET +
                           niv::testing::THIRD_ID_OFFSET};
    expected.push_back(niv::testing::ANY_VALUES[DATUM_INDEX]);
  }
  const std::vector<double> nans(niv::testing::ANY_TIMES.size(), std::nan(""));

  GIVEN("a multimeter providing access to some data") {
    niv::consumer::ArborMultimeter multimeter(
        niv::testing::ANY_MULTIMETER_NAME);
    multimeter.SetNode(&niv::testing::ANY_NEST_DATA);

    WHEN("requesting time series data for an attribute and a neuron id") {
      const std::vector<double> values{multimeter.GetTimeSeriesData(
          niv::testing::ANOTHER_ATTRIBUTE, niv::testing::THIRD_ID)};

      THEN("the time series is correct") { REQUIRE(values == expected); }
    }

    WHEN(
        "requesting time series data for an invalid attribute and a neuron "
        "id") {
      const std::vector<double> values{multimeter.GetTimeSeriesData(
          niv::testing::NOT_AN_ATTRIBUTE, niv::testing::THIRD_ID)};

      THEN("the time series is all nans or empty") {
        REQUIRE_THAT(values, VectorAllNanOrEmpty());
      }
    }

    WHEN(
        "requesting time series data for an  attribute and an invalid neuron "
        "id") {
      const std::vector<double> values{multimeter.GetTimeSeriesData(
          niv::testing::ANOTHER_ATTRIBUTE, niv::testing::NOT_AN_ID)};

      THEN("the time series is all nans or empty") {
        REQUIRE_THAT(values, VectorAllNanOrEmpty());
      }
    }
  }

  GIVEN("a multimeter with an incorrect name providing access to some data") {
    niv::consumer::ArborMultimeter multimeter(
        niv::testing::NOT_A_MULTIMETER_NAME);
    multimeter.SetNode(&niv::testing::ANY_NEST_DATA);

    WHEN("requesting time series data for an attribute and a neuron id") {
      const std::vector<double> values{multimeter.GetTimeSeriesData(
          niv::testing::ANOTHER_ATTRIBUTE, niv::testing::THIRD_ID)};

      THEN("the time series is all nans or empty") {
        REQUIRE_THAT(values, VectorAllNanOrEmpty());
      }
    }
  }
}

SCENARIO("ArborMultimeter provides time step data for all neurons",
         "[niv][niv::consumer][niv::consumer::ArborMultimeter]") {
  std::vector<double> expected;
  for (std::size_t i = 0; i < niv::testing::ANY_IDS.size(); ++i) {
    const auto ID_OFFSET{i * niv::testing::ID_STRIDE};
    const auto DATUM_INDEX{niv::testing::THIRD_TIME_OFFSET +
                           niv::testing::ANOTHER_ATTRIBUTE_OFFSET + ID_OFFSET};
    expected.push_back(niv::testing::ANY_VALUES[DATUM_INDEX]);
  }

  GIVEN("a multimeter providing access to some data") {
    niv::consumer::ArborMultimeter multimeter(
        niv::testing::ANY_MULTIMETER_NAME);
    multimeter.SetNode(&niv::testing::ANY_NEST_DATA);

    WHEN("requesting time step data for an attribute") {
      const std::vector<double> values{multimeter.GetTimestepData(
          niv::testing::THIRD_TIME, niv::testing::ANOTHER_ATTRIBUTE)};

      THEN("the time step data is correct") { REQUIRE(values == expected); }
    }

    WHEN("requesting time step data for an invalid time step") {
      const std::vector<double> values{multimeter.GetTimestepData(
          niv::testing::NOT_A_TIME, niv::testing::ANOTHER_ATTRIBUTE)};

      THEN("the time step data is all nans or empty") {
        REQUIRE_THAT(values, VectorAllNanOrEmpty());
      }
    }

    WHEN("requesting time step data for an invalid attribute") {
      const std::vector<double> values{multimeter.GetTimestepData(
          niv::testing::THIRD_TIME, niv::testing::NOT_AN_ATTRIBUTE)};

      THEN("the time step data is all nans or empty") {
        REQUIRE_THAT(values, VectorAllNanOrEmpty());
      }
    }
  }

  GIVEN("a multimeter with an incorrect name providing access to some data") {
    niv::consumer::ArborMultimeter multimeter(
        niv::testing::NOT_A_MULTIMETER_NAME);
    multimeter.SetNode(&niv::testing::ANY_NEST_DATA);

    WHEN("requesting time step data for an attribute") {
      const std::vector<double> values{multimeter.GetTimestepData(
          niv::testing::THIRD_TIME, niv::testing::ANOTHER_ATTRIBUTE)};

      THEN("the time step data is all nans or empty") {
        REQUIRE_THAT(values, VectorAllNanOrEmpty());
      }
    }
  }
}
