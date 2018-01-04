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

#ifndef NIV_INCLUDE_NIV_SHARED_MEMORY_SYNCHRONIZATION_HPP_
#define NIV_INCLUDE_NIV_SHARED_MEMORY_SYNCHRONIZATION_HPP_

SUPPRESS_WARNINGS_BEGIN
#include "boost/interprocess/sync/named_mutex.hpp"
#include "boost/interprocess/sync/scoped_lock.hpp"
SUPPRESS_WARNINGS_END

namespace niv {

class SharedMemorySynchronization {
 public:
  class Create {};
  class Access {};

  using ManagedMutex = boost::interprocess::named_mutex;
  using ManagedScopedLock = boost::interprocess::scoped_lock<ManagedMutex>;

  SharedMemorySynchronization() = delete;
  explicit SharedMemorySynchronization(
      const SharedMemorySynchronization::Create&);
  explicit SharedMemorySynchronization(
      const SharedMemorySynchronization::Access&);
  SharedMemorySynchronization(const SharedMemorySynchronization&) = delete;
  SharedMemorySynchronization(SharedMemorySynchronization&&) = delete;
  virtual ~SharedMemorySynchronization() = default;

  SharedMemorySynchronization& operator=(const SharedMemorySynchronization&) =
      delete;
  SharedMemorySynchronization& operator=(SharedMemorySynchronization&&) =
      delete;

  void Destroy();

  ManagedScopedLock ScopedLock();
  bool TryLock();
  void Unlock();

  static constexpr const char* MutexName() { return "niv-shared-mutex"; }

 private:
  ManagedMutex mutex_;
};

}  // namespace niv

#endif  // NIV_INCLUDE_NIV_SHARED_MEMORY_SYNCHRONIZATION_HPP_
