package com.yuanj.protocol;

public class CommandDef {
    /*Group list*/
    public static final byte GEN_GROUP = (byte) 0xB0;
    public static final byte CTL_GROUP = (byte) 0xB1;
    public static final byte IFO_GROUP = (byte) 0xB2;
    public static final byte TST_GROUP = (byte) 0xB3;

    /**Gen Begin******************************************************/
    // GEN Group Command
    public static final byte GEN_RC_TIME_IND = 0x01;
    public static final byte GEN_RC_TIME_RLT = (byte) 0x81;
    public static final byte GEN_RC_GPS_INFO_IND = 0x02;
    public static final byte GEN_RC_INVALID = (byte) 0xFF;
    /**Gen End********************************************************/

    /**CTL Begin******************************************************/
    // CTL Group Command
    public static final byte CTL_RC_MODE_IND = 0x01;
    public static final byte CTL_RC_PLAY_PAUSE_IND = 0x02;
    public static final byte CTL_RC_SEEK_UP_IND = 0x03;
    public static final byte CTL_RC_SEEK_DOWN_IND = 0x04;
    public static final byte CTL_RC_VOL_UP_IND = 0x05;
    public static final byte CTL_RC_VOL_DOWN_IND = 0x06;
    public static final byte CTL_RC_BACK_IND = 0x07;
    public static final byte CTL_RC_HOME_IND = 0x08;
    public static final byte CTL_RC_INVALID = (byte) 0xFF;

    //key status
    public static final byte KEY_STATUS_RELEASE = 0x00;
    public static final byte KEY_STATUS_PRESS = 0x01;
    /**CTL End********************************************************/

    // Operate Result
    public static final byte[] SUCCESS = {0x00};
    public static final byte[] ILLSTATE = {0x01};
    public static final byte[] ILLPARAM = {0x02};
    public static final byte[] FAIL = {0x04};
}
