// Copyright (c) 2015, Baidu.com, Inc. All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TTLKV_COMPACT_STRATEGY_H_
#define TTLKV_COMPACT_STRATEGY_H_

#include "leveldb/compact_strategy.h"
#include "tera/proto/table_schema.pb.h"
#include "leveldb/raw_key_operator.h"

namespace tera {
namespace io {

class KvCompactStrategy : public leveldb::CompactStrategy {
public:
    KvCompactStrategy(const TableSchema& schema);
    virtual ~KvCompactStrategy();

    virtual bool Drop(const leveldb::Slice& k, uint64_t n);

    // tera-specific, based on all-level iterators.
    // used in LowLevelScan
    virtual bool ScanDrop(const leveldb::Slice& k, uint64_t n);

    virtual bool ScanMergedValue(leveldb::Iterator* it, std::string* merged_value);

    virtual bool MergeAtomicOPs(leveldb::Iterator* it, std::string* merged_value,
                                std::string* merged_key);

    virtual const char* Name() const;

private:
    TableSchema schema_;
    const leveldb::RawKeyOperator* raw_key_operator_;
};

class KvCompactStrategyFactory : public leveldb::CompactStrategyFactory {
public:
    KvCompactStrategyFactory(const TableSchema& schema);
    virtual KvCompactStrategy* NewInstance();
    virtual const char* Name() const {
        return "tera.TTLKvCompactStrategyFactory";
    }

private:
    TableSchema schema_;
};

} // namespace io
} // namespace tera

#endif /* TTLKV_COMPACT_STRATEGY_H_ */
