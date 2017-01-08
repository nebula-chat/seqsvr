/*
 *  Copyright (c) 2016, https://github.com/nebula-im
 *  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef STORESVR_STORESVR_MANAGER_H_
#define STORESVR_STORESVR_MANAGER_H_

#include <folly/MemoryMapping.h>
#include <folly/Singleton.h>

#include "base/set.h"

// TODO(@benqi): 单机模拟set的allocsvr和storesvr
class StoreSvrManager {
public:
  ~StoreSvrManager();
  
  static std::shared_ptr<StoreSvrManager> GetInstance();
  
  bool Initialize(uint32_t set_id, const std::string& filepath);
  
  std::string GetSectionsData(uint32_t set_id, uint32_t alloc_id);
  bool GetSectionsData(uint32_t set_id, uint32_t alloc_id, std::string* data);
  
  uint64_t SetSectionsData(uint32_t set_id, uint32_t alloc_id, uint32_t section_id, uint64_t max_seq);
  
private:
  StoreSvrManager() = default;
  friend class folly::Singleton<StoreSvrManager>;
  
  int section_fd_ {-1};
  folly::MemoryMapping* section_max_seqs_mapping_ {nullptr};
  folly::Range<uint64_t*> mapping_mem_;
  
  uint32_t set_id_{1};
  
  bool inited_ = false;
};

#endif