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

#ifndef __ELASTOS_TEXT_ATTRIBUTEDCHARACTERITERATORATTRIBUTE_H__
#define __ELASTOS_TEXT_ATTRIBUTEDCHARACTERITERATORATTRIBUTE_H__

#include "Elastos.CoreLibrary.IO.h"
#include "Elastos.CoreLibrary.Text.h"
#include "elastos/core/Object.h"

using Elastos::Core::Object;
using Elastos::IO::ISerializable;
using Elastos::Text::IAttributedCharacterIteratorAttribute;

namespace Elastos {
namespace Text {

class AttributedCharacterIteratorAttribute
    : public Object
    , public IAttributedCharacterIteratorAttribute
    , public ISerializable
{
public:
    CAR_INTERFACE_DECL()

    ECode GetClassID(
        /* [out] */ ClassID* clsid);

    CARAPI constructor(
        /* [in] */ const String& name);

    /**
     * Returns the name of this attribute.
     *
     * @return the name of this attribute.
     */
    CARAPI GetName(
        /* [out] */ String* name);

    /**
     * Resolves a deserialized instance to the correct constant attribute.
     */
    CARAPI ReadResolve(
        /* [out] */ IInterface** resolve);

    /**
     * Compares this attribute with the specified object. Checks if both
     * objects are the same instance. It is defined final so all subclasses
     * have the same behavior for this method.
     *
     * @param object
     *            the object to compare against.
     * @return {@code true} if the object passed is equal to this instance;
     *         {@code false} otherwise.
     */
    CARAPI Equals(
        /* [in] */ IInterface * obj,
        /* [out] */ Boolean * value);

    /**
     * Calculates the hash code for objects of type {@code Attribute}. It
     * is defined final so all sub types calculate their hash code
     * identically.
     *
     * @return the hash code for this instance of {@code Attribute}.
     */
    CARAPI GetHashCode(
        /* [out] */ Int32 * value);

    /**
     * Returns the name of the class followed by a "(", the name of the
     * attribute, and a ")".
     *
     * @return the string representing this instance.
     */
    CARAPI ToString(
        /* [out] */ String * str);

public:
    const static AutoPtr<IAttributedCharacterIteratorAttribute> INPUT_METHOD_SEGMENT;

    const static AutoPtr<IAttributedCharacterIteratorAttribute> LANGUAGE;

    const static AutoPtr<IAttributedCharacterIteratorAttribute> READING;

private:
    String mName;
};

} // namespace Text
} // namespace Elastos

#endif //__ELASTOS_TEXT_ATTRIBUTEDCHARACTERITERATORATTRIBUTE_H__
