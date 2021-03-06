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

#include "elastos/security/PolicySpi.h"
#include "elastos/security/Policy.h"

namespace Elastos {
namespace Security {

PolicySpi::~PolicySpi()
{}

PolicySpi::PolicySpi()
{
    // default constructor
}

void PolicySpi::EngineRefresh()
{
    // do nothing in default implementation
}

AutoPtr<PermissionCollection> PolicySpi::EngineGetPermissions(
    /* [in] */ ICodeSource* codesource)
{
    return Policy::UNSUPPORTED_EMPTY_COLLECTION;
}

AutoPtr<PermissionCollection> PolicySpi::EngineGetPermissions(
    /* [in] */ IProtectionDomain* domain)
{
    return Policy::UNSUPPORTED_EMPTY_COLLECTION;
}

} // namespace Security
} // namespace Elastos
