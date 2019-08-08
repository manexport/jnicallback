package com.lenovo.cui;

public interface Listener {
	public boolean onChangedMessage(final long message,final long msgtType,final String strData,final byte[] byteData);
	public boolean onStatusMessage(final long handle,final long message);
}

