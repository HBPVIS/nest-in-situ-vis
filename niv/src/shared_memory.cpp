//------------------------------------------------------------------------------
// nest in situ vis
//
// Copyright (c) 2017 RWTH Aachen University, Germany,
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

#include "niv/shared_memory.hpp"

#include <string>
#include <utility>
#include <vector>

#include "conduit/conduit_node.hpp"
#include "conduit/conduit_schema.hpp"

namespace niv {

SharedMemory::SharedMemory(const Create&)
    : segment_{boost::interprocess::create_only, SegmentName(), InitialSize()},
      data_vector_{segment_.construct<DataVector>(DataVectorName())(
          DataVector::allocator_type(segment_.get_segment_manager()))},
      schema_string_{segment_.construct<SchemaString>(SchemaStringName())(
          SchemaString::allocator_type(segment_.get_segment_manager()))} {}
SharedMemory::SharedMemory(const Access&)
    : segment_{boost::interprocess::open_only, SegmentName()},
      data_vector_{segment_.find<DataVector>(DataVectorName()).first},
      schema_string_{segment_.find<SchemaString>(SchemaStringName()).first} {}

void SharedMemory::Destroy() {
  segment_.destroy<DataVector>(DataVectorName());
  segment_.destroy<SchemaString>(SchemaStringName());
  boost::interprocess::shared_memory_object::remove(SegmentName());
}

std::size_t SharedMemory::GetFreeSize() const {
  return segment_.get_free_memory();
}

void SharedMemory::Store(const conduit::Node& node) {
  StoreSchema(node);
  StoreData(node);
}

void SharedMemory::StoreSchema(const conduit::Node& node) {
  conduit::Schema schema;
  node.schema().compact_to(schema);
  Store(schema.to_json());
}

void SharedMemory::StoreData(const conduit::Node& node) {
  std::vector<conduit::uint8> data;
  node.serialize(data);
  Store(data);
}

void SharedMemory::Store(const std::vector<conduit::uint8>& data) {
  data_vector_->clear();
  data_vector_->assign(data.begin(), data.end());
}

void SharedMemory::Store(const std::string& schema) {
  schema_string_->clear();
  schema_string_->assign(schema.begin(), schema.end());
}

void SharedMemory::Update(const conduit::Node& node) {
  conduit::Node tmp;
  Read(&tmp);
  tmp.update(node);
  Store(tmp);
}

void SharedMemory::Read(conduit::Node* node) {
  auto schema = GetSchema();
  if (schema.empty()) {
    std::cout << "resetting node" << std::endl;
    node->reset();
  } else {
    auto data = GetData();
    std::cout << "reading data:" << std::endl;
    for (unsigned int i = 0; i < data.size() / 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        std::cout << int{data[8 * i + j]} << ' ';
      }
      std::cout << std::endl;
    }
    node->set_data_using_schema(conduit::Schema(schema), data.data());
  }
}

void SharedMemory::Listen(conduit::Node* node) {
  auto schema = GetSchema();
  auto raw_data = GetRawData();
  node->set_external_data_using_schema(conduit::Schema(schema), raw_data);
}

std::vector<conduit::uint8> SharedMemory::GetData() const {
  return std::vector<conduit::uint8>{data_vector_->begin(),
                                     data_vector_->end()};
}

conduit::uint8* SharedMemory::GetRawData() const {
  return data_vector_->data();
}

std::string SharedMemory::GetSchema() const {
  return std::string{schema_string_->begin(), schema_string_->end()};
}

}  // namespace niv
