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

#include "Elastos.CoreLibrary.IO.h"
#include "elastos/coredef.h"
#include "elastos/security/SignatureSpi.h"
#include "elastos/utility/logging/Logger.h"

using Elastos::IO::IBuffer;
using Elastos::Utility::Logging::Logger;

namespace Elastos {
namespace Security {

CAR_INTERFACE_IMPL(SignatureSpi, Object, ISignatureSpi)
SignatureSpi::SignatureSpi()
{}

SignatureSpi::~SignatureSpi()
{}

ECode SignatureSpi::EngineInitSign(
    /* [in] */ IPrivateKey* privateKey,
    /* [in] */ ISecureRandom* random)
{
    mAppRandom = random;
    return EngineInitSign(privateKey);
}

ECode SignatureSpi::EngineUpdate(
    /* [in] */ IByteBuffer* input)
{
    Boolean result;
    if (IBuffer::Probe(input)->HasRemaining(&result), !result) {
        return NOERROR;
    }
    AutoPtr< ArrayOf<Byte> > tmp;
    if (IBuffer::Probe(input)->HasArray(&result), result) {
        input->GetArray((ArrayOf<Byte>**)&tmp);
        Int32 offset;
        IBuffer::Probe(input)->GetArrayOffset(&offset);
        Int32 position;
        IBuffer::Probe(input)->GetPosition(&position);
        Int32 limit;
        IBuffer::Probe(input)->GetLimit(&limit);
        // try {
        ECode ec = EngineUpdate(tmp, offset + position, limit - position);
        if (FAILED(ec)) return E_RUNTIME_EXCEPTION;
        // } catch (SignatureException e) {
        //     throw new RuntimeException(e); //Wrap SignatureException
        // }
        IBuffer::Probe(input)->SetPosition(limit);
    }
    else {
        Int32 limit;
        IBuffer::Probe(input)->GetLimit(&limit);
        Int32 position;
        IBuffer::Probe(input)->GetPosition(&position);
        tmp = ArrayOf<Byte>::Alloc(limit - position);
        input->Get(tmp);
        // try {
        ECode ec = EngineUpdate(tmp, 0, tmp->GetLength());
        if (FAILED(ec)) return E_RUNTIME_EXCEPTION;
        // } catch (SignatureException e) {
        //     throw new RuntimeException(e); //Wrap SignatureException
        // }
    }
    return NOERROR;
}

ECode SignatureSpi::EngineSign(
    /* [in, out] */ ArrayOf<Byte>* outbuf,
    /* [in] */ Int32 offset,
    /* [in] */ Int32 len,
    /* [out] */ Int32* number)
{
    VALIDATE_NOT_NULL(number);
    *number = 0;
    AutoPtr< ArrayOf<Byte> > tmp;
    FAIL_RETURN(EngineSign((ArrayOf<Byte>**)&tmp));
    if (tmp == NULL) {
        *number = 0;
        return NOERROR;
    }
    if (len < tmp->GetLength()) {
        Logger::E("SignatureSpi", "The value of len parameter is less than the actual signature length");
        return E_SIGNATURE_EXCEPTION;
    }
    if (offset < 0) {
        Logger::E("SignatureSpi", "offset < 0");
        return E_SIGNATURE_EXCEPTION;
    }
    if (offset + len > outbuf->GetLength()) {
        Logger::E("SignatureSpi", "offset + len > outbuf.length");
        return E_SIGNATURE_EXCEPTION;
    }
    outbuf->Copy(offset, tmp, 0, tmp->GetLength());
    *number = tmp->GetLength();
    return NOERROR;
}

ECode SignatureSpi::EngineVerify(
    /* [in] */ ArrayOf<Byte>* sigBytes,
    /* [in] */ Int32 offset,
    /* [in] */ Int32 length,
    /* [out] */ Boolean* result)
{
    VALIDATE_NOT_NULL(result);
    AutoPtr< ArrayOf<Byte> > tmp = ArrayOf<Byte>::Alloc(length);
    tmp->Copy(0, sigBytes, offset, length);
    return EngineVerify(tmp, result);
}

ECode SignatureSpi::EngineSetParameter(
    /* [in] */ IAlgorithmParameterSpec* params)
{
    return E_UNSUPPORTED_OPERATION_EXCEPTION;
}

ECode SignatureSpi::EngineGetParameters(
    /* [out] */ IAlgorithmParameters** params)
{
    return E_UNSUPPORTED_OPERATION_EXCEPTION;
}

ECode SignatureSpi::Clone(
    /* [out] */ IInterface** object)
{
    return NOERROR;
}

} // namespace Security
} // namespace Elastos
