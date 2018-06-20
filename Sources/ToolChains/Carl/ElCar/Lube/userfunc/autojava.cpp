//=========================================================================
// Copyright (C) 2018 The Elastos Open Source Project
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

#include <lube.h>
#ifndef _apple
#include <malloc.h>
#endif

static char s_szStringBuf[128];
static char s_szJavaType[128];

const char* _JavaMethodSignature(const CLSModule *pModule, const TypeDescriptor* pType)
{
    assert(NULL != pType);

    const char *pszType = NULL;
    switch (pType->mType) {
        case Type_Char32: {
            pszType = "C";
            break;
        }
        case Type_Int32: {
            pszType = "I";
            break;
        }
        case Type_Int64: {
            pszType = "J";
            break;
        }
        case Type_Byte: {
            pszType = "B";
            break;
        }
        case Type_Boolean: {
            pszType = "Z";
            break;
        }
        case Type_Float: {
            pszType = "F";
            break;
        }
        case Type_Double: {
            pszType = "D";
            break;
        }
        case Type_String: {
            pszType = "Ljava/lang/String;";
            break;
        }
        case Type_interface: {
            strcpy(s_szStringBuf, "Lorg/elastos/xxx/");
            strcat(s_szStringBuf, pModule->mInterfaceDirs[pType->mIndex]->mName);
            strcat(s_szStringBuf, ";");
            pszType = s_szStringBuf;
            break;
        }
        case Type_ArrayOf: {
            CARDataType type = pType->mNestedType->mType;
            if (type == Type_Char32) {
                pszType = "[C";
            }
            else if (type == Type_Int32) {
                pszType = "[I";
            }
            else if (type == Type_Int64) {
                pszType = "[J";
            }
            else if (type == Type_Byte) {
                pszType = "[B";
            }
            else if (type == Type_Boolean) {
                pszType = "[Z";
            }
            else if (type == Type_Float) {
                pszType = "[F";
            }
            else if (type == Type_Double) {
                pszType = "[D";
            }
            else if (type == Type_String) {
                pszType = "[Ljava/lang/String;";
            }
            else if (type == Type_interface) {
                strcpy(s_szStringBuf, "[Lorg/elastos/xxx/");
                strcat(s_szStringBuf, pModule->mInterfaceDirs[pType->mNestedType->mIndex]->mName);
                strcat(s_szStringBuf, ";");
                pszType = s_szStringBuf;
            }
            else {
                pszType = "Unknown";
                fprintf(stderr, "Unsupport array type: [%d]\n", type);
            }
            break;
        }
        default: {
            pszType = "Unknown";
            fprintf(stderr, "Unsupport parameter type: [%d]\n", pType->mType);
            break;
        }
    }

    return pszType;
}

const char* GenerateJavaTypeString(const CLSModule *pModule, const TypeDescriptor *pType)
{
    switch (pType->mType) {
        case Type_Char32: {
            return "char";
        }
        case Type_Int32: {
            return "int";
        }
        case Type_Int64: {
            return "long";
        }
        case Type_Byte: {
            return "byte";
        }
        case Type_Boolean: {
            return "boolean";
        }
        case Type_Float: {
            return "float";
        }
        case Type_Double: {
            return "double";
        }
        case Type_String: {
            return "String";
        }
        case Type_interface: {
            return pModule->mInterfaceDirs[pType->mIndex]->mName;
        }
        case Type_ArrayOf: {
            CARDataType type = pType->mNestedType->mType;
            if (type == Type_Char32) {
                return "char[]";
            }
            else if (type == Type_Int32) {
                return "int[]";
            }
            else if (type == Type_Int64) {
                return "long[]";
            }
            else if (type == Type_Byte) {
                return "byte[]";
            }
            else if (type == Type_Boolean) {
                return "boolean[]";
            }
            else if (type == Type_Float) {
                return "float[]";
            }
            else if (type == Type_Double) {
                return "double[]";
            }
            else if (type == Type_String) {
                return "String[]";
            }
            else if (type == Type_interface) {
                strcpy(s_szJavaType, pModule->mInterfaceDirs[pType->mNestedType->mIndex]->mName);
                strcat(s_szJavaType, "[]");
                return s_szJavaType;
            }
        }
        default: {
            fprintf(stderr, "Unsupport parameter type: [%d]\n", pType->mType);
            return "Unknown";
        }
    }
}

const char* GenerateJavaJniTypeString(const TypeDescriptor *pType)
{
    switch (pType->mType) {
        case Type_Char32: {
            return "jchar";
        }
        case Type_Int32: {
            return "jint";
        }
        case Type_Int64: {
            return "jlong";
        }
        case Type_Byte: {
            return "jbyte";
        }
        case Type_Boolean: {
            return "jboolean";
        }
        case Type_Float: {
            return "jfloat";
        }
        case Type_Double: {
            return "jdouble";
        }
        case Type_String: {
            return "jstring";
        }
        case Type_interface: {
            return "jobject";
        }
        case Type_ArrayOf: {
            CARDataType type = pType->mNestedType->mType;
            if (type == Type_Char32) {
                return "jcharArray";
            }
            else if (type == Type_Int32) {
                return "jintArray";
            }
            else if (type == Type_Int64) {
                return "jlongArray";
            }
            else if (type == Type_Byte) {
                return "jbyteArray";
            }
            else if (type == Type_Boolean) {
                return "jbooleanArray";
            }
            else if (type == Type_Float) {
                return "jfloatArray";
            }
            else if (type == Type_Double) {
                return "jdoubleArray";
            }
            else if (type == Type_String || type == Type_interface) {
                return "jobjectArray";
            }
        }
        default: {
            fprintf(stderr, "Unsupport parameter type: [%d]\n", pType->mType);
            return "Unknown";
        }
    }
}

const char* GetJniMethodInvokeType(const TypeDescriptor *pType)
{
    if (pType == NULL) {
        return "Void";
    }

    switch (pType->mType) {
        case Type_Char32: {
            return "Char";
        }
        case Type_Int32: {
            return "Int";
        }
        case Type_Int64: {
            return "Long";
        }
        case Type_Byte: {
            return "Byte";
        }
        case Type_Boolean: {
            return "Boolean";
        }
        case Type_Float: {
            return "Float";
        }
        case Type_Double: {
            return "Double";
        }
        default: {
            return "Object";
        }
    }
}

const char* GenerateSimpleTypeString(const TypeDescriptor *pType)
{
        switch (pType->mType) {
        case Type_Char16:
            return "Char16";
        case Type_Char32:
           return  "Char32";
        case Type_Byte:
            return  "Byte";
        case Type_Boolean:
            return  "Boolean";
        case Type_Int8:
            return  "Int8";
        case Type_Int16:
            return  "Int16";
        case Type_Int32:
            return  "Int32";
        case Type_Int64:
            return  "Int64";
        case Type_UInt16:
            return  "UInt16";
        case Type_UInt32:
            return  "UInt32";
        case Type_UInt64:
            return  "UInt64";
        case Type_String:
            return  "String";
        case Type_Float:
            return  "Float";
        case Type_Double:
            return  "Double";
        case Type_PVoid:
            return  "PVoid";
        case Type_ECode:
            return  "ECode";
        default:
            fprintf(stderr, "Unsupport parameter type: [%d]\n", pType->mType);
            return "Unknown";
        }
}

int _GenerateClassPackageNameInJni(PLUBECTX pCtx, PVOID pvArg)
{
    assert(NULL != pCtx->m_pClass && pvArg == pCtx->m_pClass);

    ClassDirEntry *pClsDir = pCtx->m_pClass;
    CLSModule* pModule = pCtx->m_pModule;

    char szContent[512];
    sprintf(szContent, "org/elastos/%s" , pModule->mName);
    pCtx->PutString(szContent);

    if (pClsDir->mNameSpace != NULL && pClsDir->mNameSpace[0] != '\0') {
        char *pszNamespace = (char*)malloc(strlen(pClsDir->mNameSpace) + 1);
        strcpy(pszNamespace, pClsDir->mNameSpace);
        char *begin = pszNamespace;
        pCtx->PutString("/");
        while (begin != NULL) {
            char *dot = strchr(begin, '.');
            if (dot != NULL) {
                *dot = '/';
                begin = dot + 1;
            }
            else begin = NULL;
        }
        pCtx->PutString(pszNamespace);
        free(pszNamespace);
    }
    sprintf(szContent, "/%s" , pClsDir->mName);
    pCtx->PutString(szContent);
    return LUBE_OK;
}

int _GenerateJavaConstructor(PLUBECTX pCtx, PSTATEDESC pDesc, PVOID pvArg, const char* className)
{
    assert(NULL != pCtx->m_pClass && NULL != pCtx->m_pInterface && pvArg == pCtx->m_pInterface);

    InterfaceDirEntry *pItfDir = pCtx->m_pInterface;
    assert(pItfDir->mDesc != NULL);

    ClassDirEntry* pClsDir = pCtx->m_pClass;

    char szContent[512];
    static int loadLibraryFlag = 0;
    //If there are multi-interfaces, these codes is only one. the System.loadLibrary must be record once.
    if (loadLibraryFlag == 0) {
        CLSModule* module = pCtx->m_pModule;
        assert(module != NULL);

        pCtx->PutString("    static {\n");
        pCtx->PutString("        System.loadLibrary(\"Elastos.Runtime\");\n");
        pCtx->PutString("        System.loadLibrary(\"Elastos.CoreLibrary\");\n");

        sprintf(szContent, "        System.loadLibrary(\"%s\");\n", module->mName);
        pCtx->PutString(szContent);

        pCtx->PutString("        //TODO : Your jni so, please fill it.\n");
        pCtx->PutString("        System.loadLibrary(\"Your_Jni\");\n");
        pCtx->PutString("    }\n\n");

        pCtx->PutString("    private long mCarObj = 0;\n\n");

        loadLibraryFlag = 1;
    }

    // generate nativeInit
    for (int i = 0; i < pItfDir->mDesc->mMethodCount; i++) {
        MethodDescriptor* methodDesc = pItfDir->mDesc->mMethods[i];
        assert(methodDesc != NULL);

        sprintf(szContent, "    private native long native_%s(", pClsDir->mName);
        pCtx->PutString(szContent);

        for (int j = 0; j < methodDesc->mParamCount - 1; j++) {
            ParamDescriptor* paraDesc = methodDesc->mParams[j];
            assert(paraDesc != NULL);

            if (j != 0) {
                pCtx->PutString(", ");
            }

            sprintf(szContent, "%s %s", GenerateJavaTypeString(pCtx->m_pModule, &paraDesc->mType), paraDesc->mName);
            pCtx->PutString(szContent);
        }
        pCtx->PutString(");\n");
    }
    sprintf(szContent, "    private native void native_%s_Destroy(long carobj);\n\n", pClsDir->mName);
    pCtx->PutString(szContent);

    // generate constructors
    for (int i = 0; i < pItfDir->mDesc->mMethodCount; i++) {
        MethodDescriptor* methodDesc = pItfDir->mDesc->mMethods[i];
        assert(methodDesc != NULL);

        if (pClsDir->mDesc->mAttribs & ClassAttrib_singleton) {
            sprintf(szContent, "    private static class %sHelper {\n", pClsDir->mName);
            pCtx->PutString(szContent);
            sprintf(szContent, "        private static final %s INSTANCE = new %s();\n", pClsDir->mName, pClsDir->mName);
            pCtx->PutString(szContent);
            pCtx->PutString("    }\n\n");
            sprintf(szContent, "    public static %s getInstance() {\n", pClsDir->mName);
            pCtx->PutString(szContent);
            sprintf(szContent, "        return %sHelper.INSTANCE;\n", pClsDir->mName);
            pCtx->PutString(szContent);
            pCtx->PutString("    }\n\n");
            pCtx->PutString("    private");
        }
        else {
            pCtx->PutString("    public");
        }

        sprintf(szContent, " %s(", pClsDir->mName);
        pCtx->PutString(szContent);

        if (methodDesc->mParamCount > 0) {
            for (int j = 0; j < methodDesc->mParamCount - 1; j++) {
                ParamDescriptor* paraDesc = methodDesc->mParams[j];
                assert(paraDesc != NULL);

                if (j != 0) {
                    pCtx->PutString(", ");
                }

                sprintf(szContent, "%s %s", GenerateJavaTypeString(pCtx->m_pModule, &paraDesc->mType), paraDesc->mName);
                pCtx->PutString(szContent);
            }

            // Function body.
            pCtx->PutString(") {\n");
            sprintf(szContent, "        mCarObj = native_%s(", pClsDir->mName);
            pCtx->PutString(szContent);
            for (int j = 0; j < methodDesc->mParamCount - 1; j++) {
                ParamDescriptor* paraDesc = methodDesc->mParams[j];

                if (j != 0) {
                    pCtx->PutString(", ");
                }

                sprintf(szContent, "%s", paraDesc->mName);
                pCtx->PutString(szContent);
            }
            pCtx->PutString(");\n");
            pCtx->PutString("        //TODO: Add your code here\n");
            pCtx->PutString("    }\n\n");
        }
    }

    pCtx->PutString("    public long getCarObject() {\n");
    pCtx->PutString("        return mCarObj;\n");
    pCtx->PutString("    }\n\n");

    pCtx->PutString("    // invoke destroy to release car object\n");
    pCtx->PutString("    public void destroy() {\n");
    sprintf(szContent, "        native_%s_Destroy(mCarObj);\n", pClsDir->mName);
    pCtx->PutString(szContent);
    pCtx->PutString("    }\n\n");

    return LUBE_OK;
}

int _GenerateJavaClassConstructor(PLUBECTX pCtx, PSTATEDESC pDesc, PVOID pvArg)
{
    return _GenerateJavaConstructor(pCtx, pDesc, pvArg, "Impl");
}

int _GenerateJavaClassImpl(PLUBECTX pCtx, PSTATEDESC pDesc, PVOID pvArg)
{
    assert(NULL != pCtx->m_pInterface && pvArg == pCtx->m_pInterface);

    InterfaceDirEntry *pItfDir = pCtx->m_pInterface;
    assert(pItfDir->mDesc != NULL);

    char szContent[512];
    static int loadLibraryFlag = 0;
    //If there are multi-interfaces, these codes is only one. the System.loadLibrary must be record once.
    for (int i = 0; i < pItfDir->mDesc->mMethodCount; i++) {
        MethodDescriptor* methodDesc = pItfDir->mDesc->mMethods[i];
        assert(methodDesc != NULL);

        const char* retTypeStr = "void";
        CARDataType retType;
        int outParaPos = -1;
        if (methodDesc->mParamCount > 0) {
            for (int j = 0; j < methodDesc->mParamCount; j++) {
                ParamDescriptor* paraDesc = methodDesc->mParams[j];
                assert(paraDesc != NULL);

                if (paraDesc->mAttribs & ParamAttrib_out) {
                    outParaPos = j;
                    retTypeStr = GenerateJavaTypeString(pCtx->m_pModule, &paraDesc->mType);
                    retType = paraDesc->mType.mType;
                    break;
                }
            }
        }

        sprintf(szContent, "    public %s %s(", retTypeStr, methodDesc->mName);
        pCtx->PutString(szContent);
        if (methodDesc->mParamCount > 0) {
            for (int j = 0; j < methodDesc->mParamCount; j++) {
                ParamDescriptor* paraDesc = methodDesc->mParams[j];
                assert(paraDesc != NULL);

                if (paraDesc->mAttribs & ParamAttrib_in) {
                    // Before [out] parameter print.
                    if (j == 0) {
                        pCtx->PutString("\n");
                    }

                    if (j > 0 && (outParaPos == -1 || j < outParaPos)) {
                        pCtx->PutString(",\n");
                    }

                    sprintf(szContent, "        /* [in] */ %s %s",
                        GenerateJavaTypeString(pCtx->m_pModule, &paraDesc->mType), paraDesc->mName);
                    pCtx->PutString(szContent);
                }
            }
        }

        // Function body.
        pCtx->PutString(") {\n");
        pCtx->PutString("        //TODO: Add your code here\n");
        if (outParaPos >= 0) {
            switch(retType) {
                case Type_String:
                    pCtx->PutString("        return \"NULL\";\n");
                    break;
                case Type_interface:
                case Type_ArrayOf:
                    pCtx->PutString("        return null;\n");
                    break;
                default:
                    pCtx->PutString("        return 0;\n");
                    break;
            }
        }

        pCtx->PutString("    }\n\n");
    }

    return LUBE_OK;
}


int _GenerateJavaClassUserConstructor(PLUBECTX pCtx, PSTATEDESC pDesc, PVOID pvArg)
{
    return _GenerateJavaConstructor(pCtx, pDesc, pvArg, "User");
}

int _GenerateJavaClassUser(PLUBECTX pCtx, PSTATEDESC pDesc, PVOID pvArg)
{
    assert(NULL != pCtx->m_pInterface && pvArg == pCtx->m_pInterface);

    InterfaceDirEntry *pItfDir = pCtx->m_pInterface;
    assert(pItfDir->mDesc != NULL);
    ClassDirEntry* pClsDir = pCtx->m_pClass;

    char szContent[512];
    for (int i = 0; i < pItfDir->mDesc->mMethodCount; i++) {
        MethodDescriptor* methodDesc = pItfDir->mDesc->mMethods[i];
        assert(methodDesc != NULL);

        const char* retType = "void";
        int outParaPos = -1;
        if (methodDesc->mParamCount > 0) {
            for (int j = 0; j < methodDesc->mParamCount; j++) {
                ParamDescriptor* paraDesc = methodDesc->mParams[j];
                assert(paraDesc != NULL);

                if (paraDesc->mAttribs & ParamAttrib_out) {
                    outParaPos = j;
                    retType = GenerateJavaTypeString(pCtx->m_pModule, &paraDesc->mType);
                    break;
                }
            }
        }

        sprintf(szContent, "    public %s %s(", retType, methodDesc->mName);
        pCtx->PutString(szContent);
        if (methodDesc->mParamCount > 0) {
            for (int j = 0; j < methodDesc->mParamCount; j++) {
                ParamDescriptor* paraDesc = methodDesc->mParams[j];
                assert(paraDesc != NULL);

                if (paraDesc->mAttribs & ParamAttrib_in) {
                    // Before [out] parameter print.
                    if (j == 0) {
                        pCtx->PutString("\n");
                    }

                    if (j > 0 && (outParaPos == -1 || j < outParaPos)) {
                        pCtx->PutString(",\n");
                    }

                    const char* paraType = GenerateJavaTypeString(pCtx->m_pModule, &paraDesc->mType);

                    sprintf(szContent, "        /* [in] */ %s %s", paraType, paraDesc->mName);
                    pCtx->PutString(szContent);
                }
            }
        }

        pCtx->PutString(")\n");

        // Function body.
        char szNativeDefineParameters[1024] = {0};
        pCtx->PutString("    {\n");
        if (methodDesc->mParamCount == 0) {
            sprintf(szContent, "        native_%s_%s_%s(mCarObj);\n",
                    pClsDir->mName, pItfDir->mName, methodDesc->mName);
            pCtx->PutString(szContent);
        }
        else {
            char szParameters[1024] = {0};

            for (int j = 0; j < methodDesc->mParamCount; j++) {
                ParamDescriptor* paraDesc = methodDesc->mParams[j];
                assert(paraDesc != NULL);

                if (paraDesc->mAttribs & ParamAttrib_in) {
                    if (j > 0 && (outParaPos == -1 || j < outParaPos)) {
                        strcat(szParameters, ", ");
                        strcat(szNativeDefineParameters, ", ");
                    }

                    sprintf(szContent, "%s", paraDesc->mName);
                    strcat(szParameters, szContent);

                    sprintf(szContent, "%s %s", GenerateJavaTypeString(pCtx->m_pModule, &paraDesc->mType), paraDesc->mName);
                    strcat(szNativeDefineParameters, szContent);
                }
            }

            //Call the method and process the return value.
            if (outParaPos >= 0) {
                if (strlen(szParameters) > 0) {
                    sprintf(szContent, "        return native_%s_%s_%s(mCarObj, %s);\n",
                            pClsDir->mName, pItfDir->mName, methodDesc->mName, szParameters);
                }
                else {
                    sprintf(szContent, "        return native_%s_%s_%s(mCarObj);\n",
                            pClsDir->mName, pItfDir->mName, methodDesc->mName);
                }
            }
            else {
                sprintf(szContent, "        native_%s_%s_%s(mCarObj, %s);\n",
                        pClsDir->mName, pItfDir->mName, methodDesc->mName, szParameters);
            }

            pCtx->PutString(szContent);
        }

        pCtx->PutString("    }\n\n");

        //Record nativeXX function.
        if (strlen(szNativeDefineParameters) > 0) {
            sprintf(szContent, "    private native %s native_%s_%s_%s(long carobj, %s);\n\n",
                    retType, pClsDir->mName, pItfDir->mName, methodDesc->mName, szNativeDefineParameters);
            pCtx->PutString(szContent);
        }
        else {
            sprintf(szContent, "    private native %s native_%s_%s_%s(long carobj);\n\n",
                    retType, pClsDir->mName, pItfDir->mName, methodDesc->mName);
            pCtx->PutString(szContent);
        }
    }

    return LUBE_OK;
}

int GenerateJavaJniCppInit(PLUBECTX pCtx, PSTATEDESC pDesc, PVOID pvArg, const char* suffix)
{
    assert(NULL != pCtx->m_pInterface && pvArg == pCtx->m_pInterface);

    InterfaceDirEntry *pItfDir = pCtx->m_pInterface;
    assert(pItfDir->mDesc != NULL);
    ClassDirEntry *pClass = pCtx->m_pClass;

    char szContent[512];
    static int onceFlag = 0;
    //If there are multi-interfaces, these codes is only one. the nativeInit method must be record once.
    if (onceFlag == 0) {
        CLSModule* module = pCtx->m_pModule;
        assert(module != NULL);

        pCtx->PutString("#include \"");
        pCtx->PutString(module->mName);
        pCtx->PutString(".h\"\n\n");

        onceFlag = 1;
    }

    // get interface name
    char szInterfaceName[128];
    ClassDirEntry *pClsDir = pCtx->m_pClass;
    for (int i = 0; i < pClsDir->mDesc->mInterfaceCount; i++) {
        ClassInterface *pClsIntf = pClsDir->mDesc->mInterfaces[i];

        if (pClsIntf->mAttribs & ClassInterfaceAttrib_outer) {
            continue;
        }
        InterfaceDirEntry *pClassItfDir = pCtx->m_pModule->mInterfaceDirs[pClsIntf->mIndex];
        strcpy(szInterfaceName, pClassItfDir->mName);
        break;
    }


    for (int i = 0; i < pItfDir->mDesc->mMethodCount; i++) {
        MethodDescriptor* methodDesc = pItfDir->mDesc->mMethods[i];
        assert(methodDesc != NULL);

        sprintf(szContent, "jlong JNICALL native_%s%d(\n", pClass->mName, i);
        pCtx->PutString(szContent);
        pCtx->PutString("    /* [in] */ JNIEnv* env,\n    /* [in] */ jobject jobj");
        if (methodDesc->mParamCount > 1) {
            for (int j = 0; j < methodDesc->mParamCount - 1; j++) {
                ParamDescriptor* paraDesc = methodDesc->mParams[j];
                assert(paraDesc != NULL);

                if (paraDesc->mAttribs & ParamAttrib_in) {
                    pCtx->PutString(",\n");

                    sprintf(szContent, "    /* [in] */ %s j%s", GenerateJavaJniTypeString(&paraDesc->mType), paraDesc->mName);
                    pCtx->PutString(szContent);
                }
            }
        }
        pCtx->PutString(")\n");

        // Function body.
        pCtx->PutString("{\n");

        sprintf(szContent, "    %s* pElaClsObj;\n", szInterfaceName);
        pCtx->PutString(szContent);
        if (methodDesc->mParamCount == 1) {
            sprintf(szContent, "    ECode ec = %s::", pClass->mName);
            pCtx->PutString(szContent);
            if (pClass->mDesc->mAttribs & ClassAttrib_singleton) {
                pCtx->PutString("AcquireSingleton(&pElaClsObj);\n");
            }
            else {
                pCtx->PutString("New(&pElaClsObj);\n");
            }
        }
        else {
            char szParameters[256];
            memset(szParameters, 0, 256);

            for (int j = 0; j < methodDesc->mParamCount - 1; j++) {
                ParamDescriptor* paraDesc = methodDesc->mParams[j];

                if (j != 0) {
                    strcat(szParameters, ", ");
                }

                if (paraDesc->mType.mType == Type_String) {
                    sprintf(szContent, "    const char* str%d = env->GetStringUTFChars(j%s, NULL);\n", j + 1, paraDesc->mName);
                    pCtx->PutString(szContent);

                    sprintf(szContent, "String(str%d)", j + 1);
                    strcat(szParameters, szContent);
                }
                else if (paraDesc->mType.mType == Type_ArrayOf) {
                    const char* arrayType = GenerateJavaJniTypeString(&paraDesc->mType);
                    const char* arrayItemType = GenerateJavaJniTypeString(paraDesc->mType.mNestedType);
                    const char* nestedType = Type2CString(pCtx->m_pModule, paraDesc->mType.mNestedType);
                    sprintf(szContent, "    int _len%d = env->GetArrayLength(j%s);\n", j + 1, paraDesc->mName);
                    pCtx->PutString(szContent);
                    sprintf(szContent, "    AutoPtr<ArrayOf<%s> > _array%d = ArrayOf<%s>::Alloc(_len%d);\n", nestedType, j + 1, nestedType, j + 1);
                    pCtx->PutString(szContent);
                    sprintf(szContent, "    if(!_array%d) return E_OUT_OF_MEMORY;\n", j + 1);
                    pCtx->PutString(szContent);

                    if (paraDesc->mType.mNestedType->mType == Type_String) {
                        sprintf(szContent, "    for (Int32 i = 0; i < _len%d; i++) {\n", j + 1);
                        pCtx->PutString(szContent);
                        sprintf(szContent, "        jstring _item = (jstring)env->GetObjectArrayElement(j%s, i);\n", paraDesc->mName);
                        pCtx->PutString(szContent);
                        pCtx->PutString("        const char* __str = env->GetStringUTFChars(_item, NULL);\n");
                        sprintf(szContent, "        (*_array%d)[i] = String(__str);\n", j + 1);
                        pCtx->PutString(szContent);
                        pCtx->PutString("        env->ReleaseStringUTFChars(_item, __str);\n");
                        pCtx->PutString("    }\n");
                    }
                    else if (paraDesc->mType.mNestedType->mType == Type_interface) {
                        sprintf(szContent, "    for (Int32 i = 0; i < _len%d; i++) {\n", j + 1);
                        pCtx->PutString(szContent);
                        sprintf(szContent, "        jobject _item = env->GetObjectArrayElement(j%s, i);\n", paraDesc->mName);
                        pCtx->PutString(szContent);
                        pCtx->PutString("        jclass _clazz = env->GetObjectClass(_item);\n");
                        pCtx->PutString("        jmethodID _methodId = env->GetMethodID(_clazz, \"getCarObject\", \"()J\");\n");
                        pCtx->PutString("        jlong _carobj = env->CallLongMethod(_item, _methodId);\n");
                        sprintf(szContent, "        (*_array%d)[i] = %s::Probe((Interface*)_carobj);\n", j + 1, nestedType);
                        pCtx->PutString(szContent);
                        pCtx->PutString("    }\n");
                    }
                    else {
                        sprintf(szContent, "    %s* _items%d = env->Get%sArrayElements(j%s, 0);\n",
                                arrayItemType, j + 1, GetJniMethodInvokeType(paraDesc->mType.mNestedType), paraDesc->mName);
                        pCtx->PutString(szContent);

                        sprintf(szContent, "    for (Int32 i = 0; i < _len%d; i++) {\n", j + 1);
                        pCtx->PutString(szContent);
                        sprintf(szContent, "        (*_array%d)[i] = _items%d[i];\n", j + 1, j + 1);
                        pCtx->PutString(szContent);
                        pCtx->PutString("    }\n");
                        sprintf(szContent, "    env->Release%sArrayElements(j%s, _items%d, 0);\n",
                                GetJniMethodInvokeType(paraDesc->mType.mNestedType), paraDesc->mName, j + 1);
                        pCtx->PutString(szContent);
                    }
                    pCtx->PutString("\n");

                    sprintf(szContent, "*_array%d", j + 1);
                    strcat(szParameters, szContent);
                }
                else if (paraDesc->mType.mType == Type_interface) {
                    const char * typeStr = pCtx->m_pModule->mInterfaceDirs[paraDesc->mType.mIndex]->mName;
                    sprintf(szContent, "    jclass _clazz%d = env->GetObjectClass(j%s);\n", j + 1, paraDesc->mName);
                    pCtx->PutString(szContent);
                    sprintf(szContent, "    jmethodID _methodId%d = env->GetMethodID(_clazz%d, \"getCarObject\", \"()J\");\n",
                            j + 1, j + 1);
                    pCtx->PutString(szContent);
                    sprintf(szContent, "    jlong _carobj%d = env->CallLongMethod(j%s, _methodId%d);\n",
                            j + 1, paraDesc->mName, j + 1);
                    pCtx->PutString(szContent);
                    sprintf(szContent, "    %s* _interface%d = %s::Probe((IInterface*)_carobj%d);\n\n",
                            typeStr, j + 1, typeStr, j + 1);
                    pCtx->PutString(szContent);

                    sprintf(szContent, "_interface%d", j + 1);
                    strcat(szParameters, szContent);
                }
                else {
                    sprintf(szContent, "j%s", paraDesc->mName);
                    strcat(szParameters, szContent);
                }
            }
            sprintf(szContent, "    ECode ec = %s::New(", pClass->mName);
            pCtx->PutString(szContent);
            sprintf(szContent, "%s, &pElaClsObj);\n", szParameters);
            pCtx->PutString(szContent);

            for (int m = 0; m < methodDesc->mParamCount - 1; m++) {
                ParamDescriptor* paraDesc = methodDesc->mParams[m];
                if (paraDesc->mType.mType != Type_String) continue;
                sprintf(szContent, "    env->ReleaseStringUTFChars(j%s, str%d);\n", paraDesc->mName, m + 1);
                pCtx->PutString(szContent);
            }

        }
        pCtx->PutString("    if(FAILED(ec)) return 0;\n\n");

        pCtx->PutString("    JavaVM* jvm;\n");
        pCtx->PutString("    env->GetJavaVM(&jvm);\n");
        pCtx->PutString("    IJavaInterface::Probe(pElaClsObj)->JavaInit((Handle64)jvm, (Handle64)&jobj);\n");
        pCtx->PutString("    return (jlong)pElaClsObj;\n");

        pCtx->PutString("}\n\n");
    }

    sprintf(szContent, "void JNICALL native_%s_Destroy(\n", pClass->mName);
    pCtx->PutString(szContent);
    pCtx->PutString("    /* [in] */ JNIEnv* env,\n    /* [in] */ jobject jobj,\n");
    pCtx->PutString("    /* [in] */ jlong carobj)\n{\n");
    pCtx->PutString("    IInterface* pElaClsObj = (IInterface*)carobj;\n");
    pCtx->PutString("    pElaClsObj->Release();\n}\n");

    return LUBE_OK;
}

int _GenerateJavaJniCppInit(PLUBECTX pCtx, PSTATEDESC pDesc, PVOID pvArg)
{
    return GenerateJavaJniCppInit(pCtx, pDesc, pvArg, "User");
}

void ReleaseStringUTFChars(PLUBECTX pCtx, MethodDescriptor* pMethodDesc)
{
    char szContent[512];
    for (int i = 0; i < pMethodDesc->mParamCount; i++) {
        ParamDescriptor* paraDesc = pMethodDesc->mParams[i];
        if (!(paraDesc->mAttribs & ParamAttrib_in)
            || strcmp(GenerateJavaJniTypeString(&paraDesc->mType), "jstring")) continue;

        sprintf(szContent, "    env->ReleaseStringUTFChars(j%s, str%d);\n", paraDesc->mName, i + 1);
        pCtx->PutString(szContent);
    }
}

int _GenerateJavaJniCpp(PLUBECTX pCtx, PSTATEDESC pDesc, PVOID pvArg)
{
    assert(NULL != pCtx->m_pInterface && pvArg == pCtx->m_pInterface);

    InterfaceDirEntry *pItfDir = pCtx->m_pInterface;
    assert(pItfDir->mDesc != NULL);
    ClassDirEntry* pClsDir = pCtx->m_pClass;

    char szContent[512];
    for (int i = 0; i < pItfDir->mDesc->mMethodCount; i++) {
        MethodDescriptor* methodDesc = pItfDir->mDesc->mMethods[i];
        assert(methodDesc != NULL);

        const TypeDescriptor *pType = NULL;
        int outParaPos = -1;
        if (methodDesc->mParamCount > 0) {
            for (int j = 0; j < methodDesc->mParamCount; j++) {
                ParamDescriptor* paraDesc = methodDesc->mParams[j];
                assert(paraDesc != NULL);

                if (paraDesc->mAttribs & ParamAttrib_out) {
                    outParaPos = j;
                    pType = &paraDesc->mType;
                    break;
                }
            }
        }

        if (pType == NULL) {
            pCtx->PutString("void");
        }
        else {
            sprintf(szContent, "%s", GenerateJavaJniTypeString(pType));
            pCtx->PutString(szContent);
        }
        sprintf(szContent, " JNICALL native_%s_%s_%s(\n", pClsDir->mName, pItfDir->mName, methodDesc->mName);
        pCtx->PutString(szContent);

        if (methodDesc->mParamCount == 0) {
            pCtx->PutString("    /* [in] */ JNIEnv* env,\n    /* [in] */ jobject jobj,\n    /* [in] */ jlong carobj)\n");
        }
        else {
            pCtx->PutString("    /* [in] */ JNIEnv* env,\n    /* [in] */ jobject jobj,\n    /* [in] */ jlong carobj");
            for (int j = 0; j < methodDesc->mParamCount; j++) {
                ParamDescriptor* paraDesc = methodDesc->mParams[j];
                assert(paraDesc != NULL);

                if (paraDesc->mAttribs & ParamAttrib_in) {
                    // Before [out] parameter print.
                    if (j == 0) {
                        pCtx->PutString(",\n");
                    }

                    if (j > 0 && (outParaPos == -1 || j < outParaPos)) {
                        pCtx->PutString(",\n");
                    }

                    sprintf(szContent, "    /* [in] */ %s j%s", GenerateJavaJniTypeString(&paraDesc->mType), paraDesc->mName);
                    pCtx->PutString(szContent);
                }
            }
            pCtx->PutString(")\n");
        }

        // Function body.
        pCtx->PutString("{\n");
        pCtx->PutString("    IInterface* pElaClsObj = (IInterface*)carobj;\n");
        if (methodDesc->mParamCount == 0) {
            sprintf(szContent, "    %s::Probe(pElaClsObj)->%s();\n", pItfDir->mName, methodDesc->mName);
            pCtx->PutString(szContent);
        }
        else {
            char szParameters[256];
            memset(szParameters, 0, 256);
            for (int j = 0; j < methodDesc->mParamCount; j++) {
                ParamDescriptor* paraDesc = methodDesc->mParams[j];
                assert(paraDesc != NULL);

                if (paraDesc->mAttribs & ParamAttrib_in) {
                    if (j > 0 && (outParaPos == -1 || j < outParaPos)) {
                        strcat(szParameters, ", ");
                    }

                    if (paraDesc->mType.mType == Type_String) {
                        sprintf(szContent, "    const char* str%d = env->GetStringUTFChars(j%s, NULL);\n", j + 1, paraDesc->mName);
                        pCtx->PutString(szContent);

                        sprintf(szContent, "String(str%d)", j + 1);
                        strcat(szParameters, szContent);
                    }
                    else if (paraDesc->mType.mType == Type_ArrayOf) {
                        const char* arrayType = GenerateJavaJniTypeString(&paraDesc->mType);
                        const char* arrayItemType = GenerateJavaJniTypeString(paraDesc->mType.mNestedType);
                        const char* nestedType = Type2CString(pCtx->m_pModule, paraDesc->mType.mNestedType);
                        sprintf(szContent, "    int _len%d = env->GetArrayLength(j%s);\n", j + 1, paraDesc->mName);
                        pCtx->PutString(szContent);
                        sprintf(szContent, "    AutoPtr<ArrayOf<%s> > _array%d = ArrayOf<%s>::Alloc(_len%d);\n", nestedType, j + 1, nestedType, j + 1);
                        pCtx->PutString(szContent);
                        sprintf(szContent, "    if(!_array%d) return;\n", j + 1);
                        pCtx->PutString(szContent);

                        if (paraDesc->mType.mNestedType->mType == Type_String) {
                            sprintf(szContent, "    for (Int32 i = 0; i < _len%d; i++) {\n", j + 1);
                            pCtx->PutString(szContent);
                            sprintf(szContent, "        jstring _item = (jstring)env->GetObjectArrayElement(j%s, i);\n", paraDesc->mName);
                            pCtx->PutString(szContent);
                            pCtx->PutString("        const char* __str = env->GetStringUTFChars(_item, NULL);\n");
                            sprintf(szContent, "        (*_array%d)[i] = String(__str);\n", j + 1);
                            pCtx->PutString(szContent);
                            pCtx->PutString("        env->ReleaseStringUTFChars(_item, __str);\n");
                            pCtx->PutString("    }\n");
                        }
                        else if (paraDesc->mType.mNestedType->mType == Type_interface) {
                            sprintf(szContent, "    for (Int32 i = 0; i < _len%d; i++) {\n", j + 1);
                            pCtx->PutString(szContent);
                            sprintf(szContent, "        jobject _item = env->GetObjectArrayElement(j%s, i);\n", paraDesc->mName);
                            pCtx->PutString(szContent);
                            pCtx->PutString("        jclass _clazz = env->GetObjectClass(_item);\n");
                            pCtx->PutString("        jmethodID _methodId = env->GetMethodID(_clazz, \"getCarObject\", \"()J\");\n");
                            pCtx->PutString("        jlong _carobj = env->CallLongMethod(_item, _methodId);\n");
                            sprintf(szContent, "        (*_array%d)[i] = %s::Probe((IInterface*)_carobj);\n",
                                    j + 1, pCtx->m_pModule->mInterfaceDirs[paraDesc->mType.mNestedType->mIndex]->mName);
                            pCtx->PutString(szContent);
                            pCtx->PutString("    }\n");
                        }
                        else {
                            sprintf(szContent, "    %s* _items%d = env->Get%sArrayElements(j%s, 0);\n",
                                    arrayItemType, j + 1, GetJniMethodInvokeType(paraDesc->mType.mNestedType), paraDesc->mName);
                            pCtx->PutString(szContent);

                            sprintf(szContent, "    for (Int32 i = 0; i < _len%d; i++) {\n", j + 1);
                            pCtx->PutString(szContent);

                            sprintf(szContent, "        (*_array%d)[i] = _items%d[i];\n", j + 1, j + 1);
                            pCtx->PutString(szContent);
                            pCtx->PutString("    }\n");
                            sprintf(szContent, "    env->Release%sArrayElements(j%s, _items%d, 0);\n",
                                    GetJniMethodInvokeType(paraDesc->mType.mNestedType), paraDesc->mName, j + 1);
                            pCtx->PutString(szContent);
                        }
                        pCtx->PutString("\n");
                        sprintf(szContent, "*_array%d", j + 1);
                        strcat(szParameters, szContent);
                    }
                    else if (paraDesc->mType.mType == Type_interface) {
                        const char * typeStr = pCtx->m_pModule->mInterfaceDirs[paraDesc->mType.mIndex]->mName;
                        sprintf(szContent, "\n    jclass _clazz%d = env->GetObjectClass(j%s);\n", j + 1, paraDesc->mName);
                        pCtx->PutString(szContent);
                        sprintf(szContent, "    jmethodID _methodId%d = env->GetMethodID(_clazz%d, \"getCarObject\", \"()J\");\n",
                                j + 1, j + 1);
                        pCtx->PutString(szContent);
                        sprintf(szContent, "    jlong _carobj%d = env->CallLongMethod(j%s, _methodId%d);\n",
                                j + 1, paraDesc->mName, j + 1);
                        pCtx->PutString(szContent);
                        sprintf(szContent, "    %s* _interface%d = %s::Probe((IInterface*)_carobj%d);\n\n",
                                typeStr, j + 1, typeStr, j + 1);
                        pCtx->PutString(szContent);

                        sprintf(szContent, "_interface%d", j + 1);
                        strcat(szParameters, szContent);
                    }
                    else {
                        sprintf(szContent, "j%s", paraDesc->mName);
                        strcat(szParameters, szContent);
                    }
                }
            }

            //Call the method and process the return value.
            if (outParaPos >= 0) {
                if (pType->mType == Type_String) {
                    pCtx->PutString("    String _retValue;\n");
                    if (methodDesc->mParamCount != 1) {
                        sprintf(szContent, "    %s::Probe(pElaClsObj)->%s(%s, &_retValue);\n", pItfDir->mName, methodDesc->mName, szParameters);
                    }
                    else {
                        sprintf(szContent, "    %s::Probe(pElaClsObj)->%s(&_retValue);\n", pItfDir->mName, methodDesc->mName);
                    }

                    pCtx->PutString(szContent);

                    ReleaseStringUTFChars(pCtx, methodDesc);

                    pCtx->PutString("    return env->NewStringUTF(_retValue.string());\n");
                }
                else if (pType->mType == Type_ArrayOf) {
                    const char* nestedType = Type2CString(pCtx->m_pModule, pType->mNestedType);
                    const char* arrayType = GenerateJavaJniTypeString(pType);
                    const char* arrayItemType = GenerateJavaJniTypeString(pType->mNestedType);
                    sprintf(szContent, "    AutoPtr<ArrayOf<%s> > _retValue;\n", nestedType);
                    pCtx->PutString(szContent);
                    if (methodDesc->mParamCount != 1) {
                        sprintf(szContent, "    %s::Probe(pElaClsObj)->%s(%s, (ArrayOf<%s>**)&_retValue);\n",
                                pItfDir->mName, methodDesc->mName, szParameters, nestedType);
                    }
                    else {
                        sprintf(szContent, "    %s::Probe(pElaClsObj)->%s((ArrayOf<%s>**)&_retValue);\n",
                                pItfDir->mName, methodDesc->mName, nestedType);
                    }
                    pCtx->PutString(szContent);

                    if (pType->mNestedType->mType == Type_String) {
                        pCtx->PutString("    jclass _retClazz = env->FindClass(\"java/lang/String\");\n");
                        sprintf(szContent, "    %s retArray = env->NewObjectArray(_retValue->GetLength(), _retClazz, NULL);\n", arrayType);
                        pCtx->PutString(szContent);
                        pCtx->PutString("    if (retArray == NULL) return NULL;\n");

                        pCtx->PutString("    for (Int32 i = 0; i < _retValue->GetLength(); i++) {\n");
                        pCtx->PutString("        jstring _str = env->NewStringUTF((*_retValue)[i].string());\n");
                        pCtx->PutString("        env->SetObjectArrayElement(retArray, i, _str);\n");
                        pCtx->PutString("    }\n\n");
                    }
                    else if (pType->mNestedType->mType == Type_interface) {
                        const char* interfaceName = pCtx->m_pModule->mInterfaceDirs[pType->mNestedType->mIndex]->mName;
                        pCtx->PutString("\n    //TOOD: please fix the package name of the interface.\n");
                        pCtx->PutString("    assert(0);\n");
                        sprintf(szContent, "    jclass _retClazz = env->FindClass(\"org/elastos/xxx/%s\");\n", interfaceName);
                        pCtx->PutString(szContent);
                        sprintf(szContent, "    %s retArray = env->NewObjectArray(_retValue->GetLength(), _retClazz, NULL);\n", arrayType);
                        pCtx->PutString(szContent);
                        pCtx->PutString("    if (retArray == NULL) return NULL;\n");

                        pCtx->PutString("    for (Int32 i = 0; i < _retValue->GetLength(); i++) {\n");
                        pCtx->PutString("        Handle64 _jobj;\n");
                        pCtx->PutString("        IJavaInterface::Probe((*_retValue)[i])->GetJavaObject(&_jobj);\n");
                        pCtx->PutString("        env->SetObjectArrayElement(retArray, i, *((jobject*)_jobj));\n");
                        pCtx->PutString("    }\n\n");
                    }
                    else {
                        sprintf(szContent, "    %s retArray = env->New%sArray(_retValue->GetLength());\n",
                                arrayType, GetJniMethodInvokeType(pType->mNestedType));
                        pCtx->PutString(szContent);
                        pCtx->PutString("    if (retArray == NULL) return NULL;\n");

                        sprintf(szContent, "    %s _fill[_retValue->GetLength()];\n", arrayItemType);
                        pCtx->PutString(szContent);
                        pCtx->PutString("    for (Int32 i = 0; i < _retValue->GetLength(); i++) {\n");
                        pCtx->PutString("        _fill[i] = (*_retValue)[i];\n");
                        pCtx->PutString("    }\n");
                        sprintf(szContent, "    env->Set%sArrayRegion(retArray, 0, _retValue->GetLength(), _fill);\n\n",
                            GetJniMethodInvokeType(pType->mNestedType));
                        pCtx->PutString(szContent);
                    }

                    pCtx->PutString("    return retArray;\n");
                }
                else if (pType->mType == Type_interface) {
                    const char* interfaceName = pCtx->m_pModule->mInterfaceDirs[pType->mIndex]->mName;
                    sprintf(szContent, "    AutoPtr<%s*> _retValue;\n", interfaceName);
                    pCtx->PutString(szContent);
                    if (methodDesc->mParamCount != 1) {
                        sprintf(szContent, "    %s::Probe(pElaClsObj)->%s(%s, (%s**)&_retValue);\n",
                                pItfDir->mName, methodDesc->mName, szParameters, interfaceName);
                    }
                    else {
                        sprintf(szContent, "    %s::Probe(pElaClsObj)->%s((%s**)&_retValue);\n",
                                pItfDir->mName, methodDesc->mName, interfaceName);
                    }
                    pCtx->PutString(szContent);

                    pCtx->PutString("    Handle64 _jobj;\n");
                    pCtx->PutString("    IJavaInterface::Probe(_retValue)->GetJavaObject(&_jobj);\n");
                    pCtx->PutString("    return *((jobject*)_jobj);\n");
                }
                else {
                    sprintf(szContent, "    %s _retValue = 0;\n", GenerateSimpleTypeString(pType));
                    pCtx->PutString(szContent);
                    if (methodDesc->mParamCount != 1) {
                        sprintf(szContent, "    %s::Probe(pElaClsObj)->%s(%s, &_retValue);\n", pItfDir->mName, methodDesc->mName, szParameters);
                    }
                    else {
                        sprintf(szContent, "    %s::Probe(pElaClsObj)->%s(&_retValue);\n", pItfDir->mName, methodDesc->mName);
                    }

                    pCtx->PutString(szContent);
                    ReleaseStringUTFChars(pCtx, methodDesc);
                    pCtx->PutString("    return _retValue;\n");
                }
            }
            else {
                sprintf(szContent, "    %s::Probe(pElaClsObj)->%s(%s);\n", pItfDir->mName, methodDesc->mName, szParameters);
                pCtx->PutString(szContent);
                ReleaseStringUTFChars(pCtx, methodDesc);
            }
        }

        if ((pItfDir->mDesc->mMethodCount - 1) == i) {
            pCtx->PutString("}\n");
        }
        else {
            pCtx->PutString("}\n\n");
        }
    }

    return LUBE_OK;
}

void GenerateJniOnloadInitDeclare(PLUBECTX pCtx, PSTATEDESC pDesc, InterfaceDirEntry* pItfDir)
{
    ClassDirEntry *pClsDir = pCtx->m_pClass;
    char szContent[256];
    char signature[128];

    for (int mi = 0; mi < pItfDir->mDesc->mMethodCount; mi++) {
        sprintf(szContent, "    {\"native_%s\", ", pClsDir->mName);
        pCtx->PutString(szContent);
        MethodDescriptor* methodDesc = pItfDir->mDesc->mMethods[mi];
        assert(methodDesc != NULL);

        if (methodDesc->mParamCount > 1) {
            memset(signature, 0, 128);

            for (int j = 0; j < methodDesc->mParamCount; j++) {
                ParamDescriptor* paraDesc = methodDesc->mParams[j];
                assert(paraDesc != NULL);

                if (paraDesc->mAttribs & ParamAttrib_in) {
                    strcat(signature, _JavaMethodSignature(pCtx->m_pModule, &paraDesc->mType));
                }
            }

            sprintf(szContent, "\"(%s)J\", (void*)native_%s%d", signature, pClsDir->mName, mi);
            pCtx->PutString(szContent);
        }
        else {
            sprintf(szContent, "\"()J\", (void*)native_%s%d", pClsDir->mName, mi);
            pCtx->PutString(szContent);
        }
        pCtx->PutString("},\n");
    }

    sprintf(szContent, "    {\"native_%s_Destroy\", \"(J)V\", (void*)native_%s_Destroy},\n",
            pClsDir->mName, pClsDir->mName);
    pCtx->PutString(szContent);
}

int _GenerateJniRegister(PLUBECTX pCtx, ClassDirEntry* pClass)
{
    CLSModule* pModule = pCtx->m_pModule;
    char szContent[256];

    sprintf(szContent, "int register%sMethod(JNIEnv * env) {\n", pClass->mName);
    pCtx->PutString(szContent);
    pCtx->PutString("    jclass clazz = env->FindClass(\"");
    _GenerateClassPackageNameInJni(pCtx, pClass);
    pCtx->PutString("\");\n");
    pCtx->PutString("    if (clazz == NULL) return JNI_FALSE;\n\n");
    pCtx->PutString("    int ret = env->RegisterNatives(clazz, gMethods, sizeof(gMethods)/sizeof(JNINativeMethod));\n");
    pCtx->PutString("    if (ret < 0) return ret;\n\n");
    pCtx->PutString("    return JNI_TRUE;\n");
    pCtx->PutString("};");

    return LUBE_OK;
}

int _GenerateJavaJniCppJniRegister(PLUBECTX pCtx, PSTATEDESC pDesc, PVOID pvArg)
{
    assert(NULL != pCtx->m_pClass && pvArg == pCtx->m_pClass);

    ClassDirEntry *pClsDir = pCtx->m_pClass;
    char szContent[512];
    char signature[128];

    pCtx->PutString("\nstatic const JNINativeMethod gMethods[] = {\n");

    for (int i = 0; i < pCtx->m_pModule->mInterfaceCount; i++) {
        InterfaceDirEntry *pItfDir = pCtx->m_pModule->mInterfaceDirs[i];
        // generate nativeInit declare
        if (pItfDir->mDesc->mAttribs & InterfaceAttrib_clsobj) {
            GenerateJniOnloadInitDeclare(pCtx, pDesc, pItfDir);
        }
    }

    for (int i = 0; i < pClsDir->mDesc->mInterfaceCount; i++) {
        ClassInterface *pClsIntf = pClsDir->mDesc->mInterfaces[i];

        if (pClsIntf->mAttribs & ClassInterfaceAttrib_outer) {
            continue;
        }

        InterfaceDirEntry *pItfDir = pCtx->m_pModule->mInterfaceDirs[pClsIntf->mIndex];
        for (int mi = 0; mi < pItfDir->mDesc->mMethodCount; mi++) {
            MethodDescriptor* methodDesc = pItfDir->mDesc->mMethods[mi];
            assert(methodDesc != NULL);

            bool interfaceParam = FALSE;
            const TypeDescriptor *pType = NULL;
            int outParaPos = -1;
            if (methodDesc->mParamCount > 0) {
                for (int j = 0; j < methodDesc->mParamCount; j++) {
                    ParamDescriptor* paraDesc = methodDesc->mParams[j];
                    assert(paraDesc != NULL);

                    if (paraDesc->mType.mType == Type_interface ||
                        (paraDesc->mType.mType == Type_ArrayOf && paraDesc->mType.mNestedType->mType == Type_interface)) {
                        interfaceParam = TRUE;
                    }

                    if (paraDesc->mAttribs & ParamAttrib_out) {
                        outParaPos = j;
                        pType = &paraDesc->mType;
                        break;
                    }
                }

                memset(signature, 0, 128);

                for (int j = 0; j < methodDesc->mParamCount; j++) {
                    ParamDescriptor* paraDesc = methodDesc->mParams[j];
                    assert(paraDesc != NULL);

                    if (paraDesc->mAttribs & ParamAttrib_in) {
                        strcat(signature, _JavaMethodSignature(pCtx->m_pModule, &paraDesc->mType));
                    }
                }

                const char* retTypeSignature = "V";
                if (pType) {
                    retTypeSignature = _JavaMethodSignature(pCtx->m_pModule, pType);
                }

                if (interfaceParam) {
                    pCtx->PutString("    //TODO: please fix the package name of the interface.\n");
                }
                sprintf(szContent, "    {\"native_%s_%s_%s\", \"(J%s)%s\", (void*)native_%s_%s_%s},\n",
                        pClsDir->mName, pItfDir->mName, methodDesc->mName, signature,
                        retTypeSignature, pClsDir->mName, pItfDir->mName, methodDesc->mName);
                pCtx->PutString(szContent);
            }
            else {
                sprintf(szContent, "    {\"native_%s_%s_%s\", \"(J)V\", (void*)native_%s_%s_%s},\n",
                        pClsDir->mName, pItfDir->mName, methodDesc->mName,
                        pClsDir->mName, pItfDir->mName, methodDesc->mName);
                pCtx->PutString(szContent);
            }
        }
    }

    pCtx->PutString("};\n\n");

    _GenerateJniRegister(pCtx, pClsDir);

    return LUBE_OK;
}

int _GenerateJavaImplJniCpp(PLUBECTX pCtx, PSTATEDESC pDesc, PVOID pvArg)
{
    return GenerateJavaJniCppInit(pCtx, pDesc, pvArg, "Impl");
}

int _GenerateJavaImplJniCppRegister(PLUBECTX pCtx, PSTATEDESC pDesc, PVOID pvArg)
{
    assert(NULL != pCtx->m_pInterface && pvArg == pCtx->m_pInterface);

    InterfaceDirEntry *pItfDir = pCtx->m_pInterface;
    assert(pItfDir->mDesc != NULL);
    ClassDirEntry *pClsDir = pCtx->m_pClass;

    pCtx->PutString("\nstatic const JNINativeMethod gMethods[] = {\n");

    GenerateJniOnloadInitDeclare(pCtx, pDesc, pItfDir);

    pCtx->PutString("};\n\n");

    _GenerateJniRegister(pCtx, pClsDir);

    return LUBE_OK;
}

int _GenerateDefalutCarClassCpp(PLUBECTX pCtx, PSTATEDESC pDesc, PVOID pvArg)
{
    assert(NULL != pCtx->m_pInterface && pvArg == pCtx->m_pInterface);

    InterfaceDirEntry *pItfDir = pCtx->m_pInterface;
    assert(pItfDir->mDesc != NULL);

    ClassDirEntry *pClass = pCtx->m_pClass;
    char szContent[512];
    for (int i = 0; i < pItfDir->mDesc->mMethodCount; i++) {
        MethodDescriptor* methodDesc = pItfDir->mDesc->mMethods[i];
        assert(methodDesc != NULL);

        const TypeDescriptor *pType = NULL;
        int outParaPos = -1;
        if (methodDesc->mParamCount > 0) {
            for (int j = 0; j < methodDesc->mParamCount; j++) {
                ParamDescriptor* paraDesc = methodDesc->mParams[j];
                assert(paraDesc != NULL);

                if (paraDesc->mAttribs & ParamAttrib_out) {
                    outParaPos = j;
                    pType = &paraDesc->mType;
                    break;
                }
            }
        }

        sprintf(szContent, "ECode %s::%s(", pClass->mName, methodDesc->mName);
        pCtx->PutString(szContent);

        const char* tmpType = NULL;
        const char* outParaName = NULL;
        char signature[128] = {0};
        strcat(signature, "(");
        char outSign[32] = {0};
        if (methodDesc->mParamCount == 0) {
            pCtx->PutString(")\n");
            strcat(signature, ")V");
        }
        else {
            pCtx->PutString("\n");
            for (int j = 0; j < methodDesc->mParamCount; j++) {
                ParamDescriptor* paraDesc = methodDesc->mParams[j];
                assert(paraDesc != NULL);

                if (paraDesc->mAttribs & ParamAttrib_in) {
                    if (j > 0 && (outParaPos == -1 || j < outParaPos)) {
                        pCtx->PutString(",\n");
                    }

                    tmpType = Type2CString(pCtx->m_pModule, &paraDesc->mType);
                    if (paraDesc->mType.mType == Type_String) {
                        sprintf(szContent, "    /* [in] */ const String& %s", paraDesc->mName);
                    }
                    else if (paraDesc->mType.mType == Type_ArrayOf) {
                        if (0 == paraDesc->mType.mPointer) {
                            sprintf(szContent, "    /* [in] */ const %s & %s", tmpType, paraDesc->mName);
                        }
                        else {
                            assert (1 == m_pParam->mType.mPointer);
                            sprintf(szContent, "    /* [in] */ %s* %s", tmpType, paraDesc->mName);
                        }
                    }
                    else {
                        sprintf(szContent, "    /* [in] */ %s %s", tmpType, paraDesc->mName);
                    }

                    pCtx->PutString(szContent);
                    strcat(signature, _JavaMethodSignature(pCtx->m_pModule, &paraDesc->mType));
                }

                if (paraDesc->mAttribs & ParamAttrib_out) {
                    if (methodDesc->mParamCount > 1) {
                        pCtx->PutString(",\n");
                    }

                    if (paraDesc->mAttribs & ParamAttrib_callee) {
                        pCtx->PutString("    /* [out, callee] */ ");
                    }
                    else {
                        pCtx->PutString("    /* [out] */ ");
                    }

                    if (1 == paraDesc->mType.mPointer &&
                        (paraDesc->mType.mType == Type_ArrayOf || paraDesc->mType.mType == Type_interface)) {
                        sprintf(szContent, "%s* %s", Type2CString(pCtx->m_pModule, &paraDesc->mType), paraDesc->mName);
                    }
                    else {
                        sprintf(szContent, "%s %s", Type2CString(pCtx->m_pModule, &paraDesc->mType), paraDesc->mName);
                    }
                    pCtx->PutString(szContent);

                    // For signature
                    strcat(outSign, _JavaMethodSignature(pCtx->m_pModule, &paraDesc->mType));
                    outParaName = paraDesc->mName;
                }
            }
            pCtx->PutString(")\n");

            if (strlen(outSign) > 0) {
                strcat(signature, ")");
                strcat(signature, outSign);
            }
            else {
                strcat(signature, ")V");
            }
        }

        // Function body.
        pCtx->PutString("{\n    JNIEnv* env = GetEnv();\n");
        pCtx->PutString("    jclass cls = env->GetObjectClass(mObj);\n");
        for (int j = 0; j < methodDesc->mParamCount; j++) {
            ParamDescriptor* paraDesc = methodDesc->mParams[j];
            if (paraDesc->mType.mType == Type_interface ||
                (paraDesc->mType.mType == Type_ArrayOf && paraDesc->mType.mNestedType->mType == Type_interface)) {
                pCtx->PutString("\n    //TODO: please fix the package name of the interface.\n");
                pCtx->PutString("    assert(0);\n");
                break;
            }
        }
        sprintf(szContent, "    jmethodID method = env->GetMethodID(cls, \"%s\", \"%s\");\n" , methodDesc->mName, signature);
        pCtx->PutString(szContent);

        char paramsContent[512];
        paramsContent[0] = '\0';
        int count = outParaPos >= 0 ? methodDesc->mParamCount - 1 : methodDesc->mParamCount;
        for (int j = 0; j < count; j++) {
            ParamDescriptor* paraDesc = methodDesc->mParams[j];
            assert(paraDesc != NULL);
            strcat(paramsContent, ", ");

            if (paraDesc->mType.mType == Type_String) {
                sprintf(szContent, "    jstring _jstr%d = env->NewStringUTF(%s.string());\n", j + 1, paraDesc->mName);
                pCtx->PutString(szContent);

                sprintf(szContent, "_jstr%d", j + 1);
                strcat(paramsContent, szContent);
            }
            else if (paraDesc->mType.mType == Type_ArrayOf) {

                const char* nestedType = Type2CString(pCtx->m_pModule, paraDesc->mType.mNestedType);
                const char* arrayType = GenerateJavaJniTypeString(&paraDesc->mType);
                const char* arrayItemType = GenerateJavaJniTypeString(paraDesc->mType.mNestedType);

                if (paraDesc->mType.mNestedType->mType == Type_String) {
                    sprintf(szContent, "    jclass _clazz%d = env->FindClass(\"java/lang/String\");\n", j + 1);
                    pCtx->PutString(szContent);
                    sprintf(szContent, "    %s _jarray%d = env->NewObjectArray(%s.GetLength(), _clazz%d, NULL);\n",
                        arrayType, j + 1, paraDesc->mName, j + 1);
                    pCtx->PutString(szContent);
                }
                else if (paraDesc->mType.mNestedType->mType == Type_interface) {
                    pCtx->PutString("\n    //TODO: please fix the package name of the interface.\n");
                    pCtx->PutString("    assert(0);\n");
                    sprintf(szContent, "    jclass _clazz%d = env->FindClass(\"org/elastos/xxx/%s\");\n",
                            j + 1, pCtx->m_pModule->mInterfaceDirs[paraDesc->mType.mNestedType->mIndex]->mName);
                    pCtx->PutString(szContent);
                    sprintf(szContent, "    %s _jarray%d = env->NewObjectArray(%s.GetLength(), _clazz%d, NULL);\n",
                        arrayType, j + 1, paraDesc->mName, j + 1);
                    pCtx->PutString(szContent);
                }
                else {
                    sprintf(szContent, "    %s _jarray%d = env->New%sArray(%s.GetLength());\n",
                        arrayType, j + 1, GetJniMethodInvokeType(paraDesc->mType.mNestedType), paraDesc->mName);
                    pCtx->PutString(szContent);
                }

                sprintf(szContent, "    if (_jarray%d == NULL) {\n", j + 1);
                pCtx->PutString(szContent);
                pCtx->PutString("        Detach();\n        return E_OUT_OF_MEMORY;\n    }\n\n");

                if (paraDesc->mType.mNestedType->mType == Type_String) {
                    sprintf(szContent, "    for (Int32 i = 0; i < %s.GetLength(); i++) {\n", paraDesc->mName);
                    pCtx->PutString(szContent);
                    sprintf(szContent, "        jstring _str = env->NewStringUTF(%s[i].string());\n", paraDesc->mName);
                    pCtx->PutString(szContent);
                    sprintf(szContent, "        env->SetObjectArrayElement(_jarray%d, i, _str);\n", j + 1);
                    pCtx->PutString(szContent);
                    pCtx->PutString("    }\n\n");
                }
                else if (paraDesc->mType.mNestedType->mType == Type_interface) {
                    sprintf(szContent, "    for (Int32 i = 0; i < %s.GetLength(); i++) {\n", paraDesc->mName);
                    pCtx->PutString(szContent);
                    pCtx->PutString("        Handle64 jobj;\n");
                    sprintf(szContent, "        IJavaInterface::Probe(%s[i])->GetJavaObject(&jobj);\n", paraDesc->mName);
                    pCtx->PutString(szContent);
                    sprintf(szContent, "        env->SetObjectArrayElement(_jarray%d, i, *((jobject*)jobj));\n", j + 1);
                    pCtx->PutString(szContent);
                    pCtx->PutString("    }\n\n");
                }
                else {
                    sprintf(szContent, "    %s _fill%d[%s.GetLength()];\n", arrayItemType, j + 1, paraDesc->mName);
                    pCtx->PutString(szContent);
                    sprintf(szContent, "    for (Int32 i = 0; i < %s.GetLength(); i++) {\n", paraDesc->mName);
                    pCtx->PutString(szContent);
                    sprintf(szContent, "        _fill%d[i] = %s[i];\n", j + 1, paraDesc->mName);
                    pCtx->PutString(szContent);
                    pCtx->PutString("    }\n");
                    sprintf(szContent, "    env->Set%sArrayRegion(_jarray%d, 0, %s.GetLength(), _fill%d);\n\n",
                        GetJniMethodInvokeType(paraDesc->mType.mNestedType), j + 1, paraDesc->mName, j + 1);
                    pCtx->PutString(szContent);
                }

                sprintf(szContent, "_jarray%d", j + 1);
                strcat(paramsContent, szContent);
            }
            else if (paraDesc->mType.mType == Type_interface) {
                sprintf(szContent, "    Handle64 _jobj%d;\n", j + 1);
                pCtx->PutString(szContent);
                sprintf(szContent, "    IJavaInterface::Probe(%s)->GetJavaObject(&_jobj%d);\n", paraDesc->mName, j + 1);
                pCtx->PutString(szContent);
                sprintf(szContent, "*((jobject*)_jobj%d)", j + 1);
                strcat(paramsContent, szContent);
            }
            else {
                strcat(paramsContent, paraDesc->mName);
            }
        }

        tmpType = GetJniMethodInvokeType(pType);
        if (outParaPos >= 0) {
            if (pType->mType == Type_String) {
                sprintf(szContent, "    jstring _jstr = (jstring)env->Call%sMethod(cls, method%s);\n" , tmpType, paramsContent);
                pCtx->PutString(szContent);

                pCtx->PutString("    const char* __str = env->GetStringUTFChars(_jstr, NULL);\n");
                sprintf(szContent, "    *%s = String(__str);\n", outParaName);
                pCtx->PutString(szContent);
                pCtx->PutString("    env->ReleaseStringUTFChars(_jstr, __str);\n");
            }
            else if (pType->mType == Type_ArrayOf) {
                const char* arrayType = GenerateJavaJniTypeString(pType);
                const char* carType = Type2CString(pCtx->m_pModule, pType->mNestedType);
                const char* arrayItemType = GenerateJavaJniTypeString(pType->mNestedType);
                sprintf(szContent, "    %s _jarray = (%s)env->Call%sMethod(cls, method%s);\n", arrayType, arrayType, tmpType, paramsContent);
                pCtx->PutString(szContent);
                pCtx->PutString("    int _len = env->GetArrayLength(_jarray);\n");
                sprintf(szContent, "    AutoPtr<ArrayOf<%s> > _array = ArrayOf<%s>::Alloc(_len);\n", carType, carType);
                pCtx->PutString(szContent);
                pCtx->PutString("    if (!_array) {\n");
                pCtx->PutString("        Detach();\n        return E_OUT_OF_MEMORY;\n    }\n\n");

                if (pType->mNestedType->mType == Type_String) {
                    pCtx->PutString("    for (Int32 i = 0; i < _len; i++) {\n");
                    pCtx->PutString("        jstring _item = (jstring)env->GetObjectArrayElement(_jarray, i);\n");
                    pCtx->PutString("        const char* __str = env->GetStringUTFChars(_item, NULL);\n");
                    pCtx->PutString("        (*_array)[i] = String(__str);\n");
                    pCtx->PutString("        env->ReleaseStringUTFChars(_item, __str);\n");
                    pCtx->PutString("    }\n");
                }
                else if (pType->mNestedType->mType == Type_interface) {
                    pCtx->PutString("    \n");
                    pCtx->PutString("    for (Int32 i = 0; i < _len; i++) {\n");
                    pCtx->PutString("        jobject _item = env->GetObjectArrayElement(_jarray, i);\n");
                    pCtx->PutString("        jclass _clazz = env->GetObjectClass(_item);\n");
                    pCtx->PutString("        jmethodID _methodId = env->GetMethodID(_clazz, \"getCarObject\", \"()J\");\n");
                    pCtx->PutString("        jlong _carobj = env->CallLongMethod(_item, _methodId);\n");
                    sprintf(szContent, "        (*_array)[i] = %s::Probe((IInterface*)_carobj);\n",
                            pCtx->m_pModule->mInterfaceDirs[pType->mNestedType->mIndex]->mName);
                    pCtx->PutString(szContent);
                    pCtx->PutString("        (*_array)[i]->AddRef();\n");
                    pCtx->PutString("    }\n");
                }
                else {
                    sprintf(szContent, "    %s* _items = env->Get%sArrayElements(_jarray, 0);\n",
                            arrayItemType, GetJniMethodInvokeType(pType->mNestedType));
                    pCtx->PutString(szContent);
                    pCtx->PutString("    for (Int32 i = 0; i < _len; i++) {\n");
                    pCtx->PutString("        (*_array)[i] = _items[i];\n");
                    pCtx->PutString("    }\n");
                    sprintf(szContent, "    env->Release%sArrayElements(_jarray, _items, 0);\n",
                            GetJniMethodInvokeType(pType->mNestedType));
                    pCtx->PutString(szContent);
                }
                sprintf(szContent, "    *%s = _array;\n" , outParaName);
                pCtx->PutString(szContent);
                sprintf(szContent, "    (*%s)->AddRef();\n" , outParaName);
                pCtx->PutString(szContent);
            }
            else if (pType->mType == Type_interface) {
                sprintf(szContent, "    jobject _jobj = env->Call%sMethod(cls, method%s);\n" , tmpType, paramsContent);
                pCtx->PutString(szContent);

                pCtx->PutString("    jclass _clazz = env->GetObjectClass(_jobj);\n");
                pCtx->PutString("    jmethodID _methodId = env->GetMethodID(_clazz, \"getCarObject\", \"()J\");\n");
                pCtx->PutString("    jlong _carobj = env->CallLongMethod(_jobj, _methodId);\n");
                sprintf(szContent, "    *%s = %s::Probe((IInterface*)_carobj);\n" , outParaName, pCtx->m_pModule->mInterfaceDirs[pType->mIndex]->mName);
                pCtx->PutString(szContent);
                sprintf(szContent, "    (*%s)->AddRef();\n" , outParaName);
                pCtx->PutString(szContent);
            }
            else {
                sprintf(szContent, "    *%s = (%s)env->Call%sMethod(cls, method%s);\n" ,
                        outParaName, GenerateJavaTypeString(pCtx->m_pModule, pType), tmpType, paramsContent);
                pCtx->PutString(szContent);
            }
        }
        else {
            sprintf(szContent, "    env->Call%sMethod(cls, method%s);\n" , tmpType, paramsContent);
            pCtx->PutString(szContent);
        }
        pCtx->PutString("    Detach();\n");

        pCtx->PutString("    return NOERROR;\n");

        if ((pItfDir->mDesc->mMethodCount - 1) == i) {
            pCtx->PutString("}\n\n");
        }
        else {
            pCtx->PutString("}\n\n");
        }
    }

    return LUBE_OK;
}

int _GenerateJavaInterface(PLUBECTX pCtx, PSTATEDESC pDesc, PVOID pvArg)
{
    assert(NULL != pCtx->m_pInterface && pvArg == pCtx->m_pInterface);

    InterfaceDirEntry *pItfDir = pCtx->m_pInterface;
    assert(pItfDir->mDesc != NULL);

    char szContent[512];
    sprintf(szContent, "public interface %s {\n\n" , pItfDir->mName);
    pCtx->PutString(szContent);
    for (int i = 0; i < pItfDir->mDesc->mMethodCount; i++) {
        MethodDescriptor* methodDesc = pItfDir->mDesc->mMethods[i];
        assert(methodDesc != NULL);

        const char* returnType = "void";
        for (int j = 0; j < methodDesc->mParamCount; j++) {
            ParamDescriptor* paraDesc = methodDesc->mParams[j];
            assert(paraDesc != NULL);

            if (paraDesc->mAttribs & ParamAttrib_out) {
                returnType = GenerateJavaTypeString(pCtx->m_pModule, &paraDesc->mType);
                break;
            }
        }

        sprintf(szContent, "    public %s %s(" , returnType, methodDesc->mName);
        pCtx->PutString(szContent);

        for (int j = 0; j < methodDesc->mParamCount; j++) {
            ParamDescriptor* paraDesc = methodDesc->mParams[j];
            assert(paraDesc != NULL);

            if (paraDesc->mAttribs & ParamAttrib_out) break;

            if (j == 0) {
                pCtx->PutString("\n");
            }
            else {
                pCtx->PutString(",\n");
            }
            sprintf(szContent, "        /* [in] */ %s %s" ,
                GenerateJavaTypeString(pCtx->m_pModule, &paraDesc->mType), paraDesc->mName);
            pCtx->PutString(szContent);
        }

        pCtx->PutString(");\n\n");
    }

    pCtx->PutString("}\n");
    return LUBE_OK;
}

int _GeneratePackageNameByInterface(PLUBECTX pCtx, PSTATEDESC pDesc, PVOID pvArg)
{
    assert(NULL != pCtx->m_pInterface && pvArg == pCtx->m_pInterface);

    InterfaceDirEntry *pItfDir = pCtx->m_pInterface;
    CLSModule* pModule = pCtx->m_pModule;

    char szContent[512];
    sprintf(szContent, "package org.elastos.%s" , pModule->mName);
    pCtx->PutString(szContent);

    if (pItfDir->mNameSpace != NULL && pItfDir->mNameSpace[0] != '\0') {
        sprintf(szContent, ".%s" , pItfDir->mNameSpace);
        pCtx->PutString(szContent);
    }

    pCtx->PutString(";\n");
    return LUBE_OK;
}

int _GeneratePackageNameByClass(PLUBECTX pCtx, PSTATEDESC pDesc, PVOID pvArg)
{
    assert(NULL != pCtx->m_pClass && pvArg == pCtx->m_pClass);

    ClassDirEntry *pClsDir = pCtx->m_pClass;
    CLSModule* pModule = pCtx->m_pModule;

    char szContent[512];
    sprintf(szContent, "package org.elastos.%s" , pModule->mName);
    pCtx->PutString(szContent);

    if (pClsDir->mNameSpace != NULL && pClsDir->mNameSpace[0] != '\0') {
        sprintf(szContent, ".%s" , pClsDir->mNameSpace);
        pCtx->PutString(szContent);
    }

    pCtx->PutString(";\n");
    return LUBE_OK;
}
