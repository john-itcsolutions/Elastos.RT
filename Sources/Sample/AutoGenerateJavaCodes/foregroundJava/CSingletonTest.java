
package org.elastos.Elastos.AutoGenerateJavaCodes;

//this java class will implement the elastos interface.
public class CSingletonTest implements ITestCar2 {
    private native void native_CSingletonTest();
    private native void native_CSingletonTest_Destroy();

    private static class CSingletonTestHelper {
        private static final CSingletonTest INSTANCE = new CSingletonTest();
    }

    public static CSingletonTest getInstance() {
        return CSingletonTestHelper.INSTANCE;
    }

    private CSingletonTest() {
        native_CSingletonTest();
        //TODO: Add your code here
    }

    // invoke destroy to release car object
    public void destroy() {
        native_CSingletonTest_Destroy();
    }


    public void SetInt2(
        /* [in] */ int value) {
        //TODO: Add your code here
    }

    public String Update(
        /* [in] */ String value1,
        /* [in] */ String value2,
        /* [in] */ String value3) {
        //TODO: Add your code here
        return "NULL";
    }

    public void Test1(
        /* [in] */ String name,
        /* [in] */ int[] array) {
        //TODO: Add your code here
    }

    public void Test2(
        /* [in] */ String[] strArray,
        /* [in] */ int[] intArray) {
        //TODO: Add your code here
    }

    public String[] Test3(
        /* [in] */ int i) {
        //TODO: Add your code here
        return null;
    }

    public void Test4() {
        //TODO: Add your code here
    }

    public String Test5() {
        //TODO: Add your code here
        return "NULL";
    }

    public float[] Test6(
        /* [in] */ int i,
        /* [in] */ String str) {
        //TODO: Add your code here
        return null;
    }


}
