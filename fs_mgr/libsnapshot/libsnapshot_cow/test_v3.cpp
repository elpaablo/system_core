// Copyright (C) 2023 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <sys/stat.h>

#include <cstdio>
#include <iostream>
#include <memory>
#include <string_view>

#include <android-base/file.h>
#include <android-base/logging.h>
#include <gtest/gtest.h>
#include <libsnapshot/cow_reader.h>
#include <libsnapshot/cow_writer.h>
#include "cow_decompress.h"
#include "libsnapshot/cow_format.h"
#include "writer_v3.h"
using android::base::unique_fd;
using testing::AssertionFailure;
using testing::AssertionResult;
using testing::AssertionSuccess;

namespace android {
namespace snapshot {

class CowOperationV3Test : public ::testing::Test {
  protected:
    virtual void SetUp() override {
        cow_ = std::make_unique<TemporaryFile>();
        ASSERT_GE(cow_->fd, 0) << strerror(errno);
    }

    virtual void TearDown() override { cow_ = nullptr; }

    unique_fd GetCowFd() { return unique_fd{dup(cow_->fd)}; }

    std::unique_ptr<TemporaryFile> cow_;
};

}  // namespace snapshot
}  // namespace android