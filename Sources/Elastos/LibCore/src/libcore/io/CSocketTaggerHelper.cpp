//=========================================================================
// Copyright (C) 2012 The Elastos Open Source Project
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
//=========================================================================

#include "libcore/io/CSocketTaggerHelper.h"
#include "libcore/io/SocketTagger.h"

namespace Libcore {
namespace IO {

CAR_SINGLETON_IMPL(CSocketTaggerHelper)

CAR_INTERFACE_IMPL(CSocketTaggerHelper, Singleton, ISocketTaggerHelper)

ECode CSocketTaggerHelper::Set(
    /* [in] */ ISocketTagger* tagger)
{
    return SocketTagger::Set(tagger);
}

ECode CSocketTaggerHelper::Get(
    /* [out] */ ISocketTagger** tagger)
{
    return SocketTagger::Get(tagger);
}

} // namespace IO
} // namespace Libcore