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

#include "niv/shared_memory.hpp"

#include <string>
#include <utility>
#include <vector>

#include "conduit/conduit_node.hpp"
#include "conduit/conduit_schema.hpp"

namespace niv {

SharedMemory::SharedMemory(const Create&)
    : segment_{boost::interprocess::create_only, SegmentName(), InitialSize()},
      node_storage_{ConstructSchemaStorage(), ConstructDataStorage()},
      reference_count_{ConstructReferenceCount()} {}

SharedMemory::SchemaStorage* SharedMemory::ConstructSchemaStorage() {
  return segment_.construct<SchemaStorage>(SchemaStorageName())(
      SchemaStorage::allocator_type(segment_.get_segment_manager()));
}

SharedMemory::DataStorage* SharedMemory::ConstructDataStorage() {
  return segment_.construct<DataStorage>(DataStorageName())(
      DataStorage::allocator_type(segment_.get_segment_manager()));
}

int* SharedMemory::ConstructReferenceCount() {
  return segment_.construct<int>(ReferenceCountName())(0);
}

SharedMemory::SharedMemory(const Access&)
    : segment_{boost::interprocess::open_only, SegmentName()},
      node_storage_{FindSchemaStorage(), FindDataStorage()},
      reference_count_{FindReferenceCount()} {
  ++(*reference_count_);
}

SharedMemory::SchemaStorage* SharedMemory::FindSchemaStorage() {
  return segment_.find<SchemaStorage>(SchemaStorageName()).first;
}

SharedMemory::DataStorage* SharedMemory::FindDataStorage() {
  return segment_.find<DataStorage>(DataStorageName()).first;
}

int* SharedMemory::FindReferenceCount() {
  return segment_.find<int>(ReferenceCountName()).first;
}

SharedMemory::~SharedMemory() { --(*reference_count_); }

void SharedMemory::Destroy() {
  segment_.destroy<SchemaStorage>(SchemaStorageName());
  segment_.destroy<DataStorage>(DataStorageName());
  boost::interprocess::shared_memory_object::remove(SegmentName());
}

std::size_t SharedMemory::GetFreeSize() const {
  return segment_.get_free_memory();
}

void SharedMemory::Store(const conduit::Node& node) {
  node_storage_.Store(node);
}

void SharedMemory::Update(const conduit::Node& node) {
  node_storage_.Update(node);
}

conduit::Node SharedMemory::Read() { return node_storage_.Read(); }

conduit::Node SharedMemory::Listen() { return node_storage_.Listen(); }

void SharedMemory::Clear() { node_storage_.Clear(); }
bool SharedMemory::IsEmpty() const { return node_storage_.IsEmpty(); }

int SharedMemory::GetReferenceCount() const { return *reference_count_; }

}  // namespace niv
