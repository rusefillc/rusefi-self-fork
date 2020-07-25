package com.rusefi.io;

/**
 * @author Andrey Belomutskiy
 *         3/1/2017
 */
public interface ConnectionStateListener {
    ConnectionStateListener VOID = new AbstractConnectionStateListener();

    /**
     * This method is invoked once we have connection & configuration from controller
     */
    void onConnectionEstablished();

    void onConnectionFailed();
}
