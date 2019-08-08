package com.lenovo.cui;

public class TestListener implements Listener {

	public boolean onChangedMessage(final long message,final long msgtType,final String strData,final byte[] byteData) {
		// TODO Auto-generated method stub
		System.out.println( "Hello World!     " + "message id:   "+message+  "message type:   "+ msgtType + "json data:" + strData);
		return true;
	}
	public boolean onStatusMessage(final long handle,final long message) {
		// TODO Auto-generated method stub
		System.out.println( "Hello World!     " + "message id:   "+message+  "the handle:   "+ handle);
		return true;
	}
}
