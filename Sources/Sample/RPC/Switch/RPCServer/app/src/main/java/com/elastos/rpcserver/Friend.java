package com.elastos.rpcserver;


public class Friend {
    String mUid;
    boolean mConnected;
    boolean mSessionConnected = false;

    Friend(String uid, boolean online) {
        mUid = uid;
        mConnected = online;
    }
}
