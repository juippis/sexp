/**
 *
 * Copyright (c) 2022, [Ribose Inc](https://www.ribose.com).
 * All rights reserved.
 * This file is a part of RNP sexp library
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other matrials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <sexp-tests.h>

using namespace sexp;

namespace {
class CompatTests : public testing::Test {
protected:
  static void SetUpTestSuite() {
  };

  static void TearDownTestSuite() {}
};

TEST_F(CompatTests, Canonical) {
  std::string keyfile(sexp_samples_folder + "/gpg/canonical.key");
  std::ifstream ifs(keyfile, std::ifstream::binary);
  EXPECT_FALSE(ifs.fail());

  if (!ifs.fail()) {
    sexpInputStream is(&ifs);
    sexpObject *obj = is.setByteSize(8)->getChar()->scanObject();

    char fn[L_tmpnam];
    std::tmpnam(fn);
    std::ofstream ofs(fn, std::iostream::binary);
    EXPECT_FALSE(ofs.fail());

    if (!ofs.fail()) {
      sexpOutputStream os(&ofs);
      os.printCanonical(obj);
      ofs.close();
      EXPECT_TRUE(compare_binary_files(keyfile, fn));
    }
    unlink(fn);
  }
}

TEST_F(CompatTests, Advanced) {
  std::string keyfile(sexp_samples_folder + "/gpg/advanced.key");
  std::string expectedfile(sexp_samples_folder + "/gpg/advanced.expected");
  std::ifstream ifs(keyfile, std::ifstream::binary);
  EXPECT_FALSE(ifs.fail());

  if (!ifs.fail()) {
    sexpInputStream is(&ifs);
    sexpObject *obj = is.setByteSize(8)->getChar()->scanObject();

    char fn[L_tmpnam];
    std::tmpnam(fn);
    std::ofstream ofs(fn, std::iostream::binary);
    EXPECT_FALSE(ofs.fail());

    if (!ofs.fail()) {
      sexpOutputStream os(&ofs);
      os.setMaxColumn(100);
      os.printAdvanced(obj);
      ofs << std::endl;
      ofs.close();
      EXPECT_TRUE(compare_binary_files(expectedfile, fn));
    }
    unlink(fn);
  }
}

} // namespace