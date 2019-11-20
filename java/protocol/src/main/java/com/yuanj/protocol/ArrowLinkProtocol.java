package com.yuanj.protocol;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

public class ArrowLinkProtocol {
    private static final byte L1_HEADER_MAGIC = (byte) 0xAB;     /*header magic number */
    private static final byte L1_HEADER_VERSION = 0x00;     /*protocol version */
    private static final byte L1_HEADER_SIZE = 8;      /*L1 header length*/
    private static final byte L1_HEADER_ACK = 0x10;     /*data */

    /**************************************************************************
     * define L1 header byte order
     ***************************************************************************/
    private static final byte L1_HEADER_MAGIC_POS = (0);
    private static final byte L1_HEADER_PROTOCOL_VERSION_POS = (1);
    private static final byte L1_PAYLOAD_LENGTH_HIGH_BYTE_POS = (2);        /* L1 payload lengh high byte */
    private static final byte L1_PAYLOAD_LENGTH_LOW_BYTE_POS = (3);
    private static final byte L1_HEADER_CRC16_HIGH_BYTE_POS = (4);
    private static final byte L1_HEADER_CRC16_LOW_BYTE_POS = (5);
    private static final byte L1_HEADER_SEQ_ID_HIGH_BYTE_POS = (6);
    private static final byte L1_HEADER_SEQ_ID_LOW_BYTE_POS = (7);

    private static final byte L2_HEADER_SIZE = (5);      /*L2 payload header*/
    private static final byte L2_HEADER_VERSION = (0x00);   /*L2 header version*/

    /**************************************************************************
     * define L2 header byte order
     ***************************************************************************/
    private static final byte L2_GRP_HEADER_POS = (0);
    private static final byte L2_VER_HEADER_POS = (1);
    private static final byte L2_CMD_HEADER_POS = (2);
    private static final byte L2_CMD_LEN_HIGH_POS = (3);
    private static final byte L2_CMD_LEN_LOW_POS = (4);

    public static arrowLinkFunc mArrowLinkFunc;
    /*Control information*/
    private final int ARROW_MX_RETRY = 0;
    private final int ARROW_TTYPE_READY = 1;
    private final int ARROW_TTYPE_SEND = 2;
    private final int ARROW_TTYPE_DELAY = 3;
    private final int ARROW_TTYPE_REPROCESS = 4;
    private final int ARROW_MAX_SEND_DATA = 100;
    private final int ARROW_MAX_BUFF = 5;
    /*Public variable*/
    private short mSeqId = 0;
    private Timer mDelayTimer;
    private boolean mDelayTimerOn = false;
    private int mRetry = 0;
    private int mLinkRetry = 0;
    private int mTypeState = ARROW_TTYPE_READY;
    private int mBuffHeader = 0;
    private int mBuffTail = 0;
    @SuppressWarnings("rawtypes")
    private ArrayList[] mBuffSequence = new ArrayList[ARROW_MAX_BUFF];
    private byte[] mDataOut = null;
    private int mDataOffect = 0;
    private boolean mDataPakEnd = false;
    private byte[] mPayload;
    private byte[] mDataIn = null;
    private int mDataInCmd = 0;
    private short mDataInSeq = 0;
    private int mDataInOffect = 0;
    private int mDataInLength = 0;
    private int mDataInCRC = 0;
    private byte mDataInVer = 0;
    private List<byte[]> mDataList = new ArrayList<>();
    /**
     * System Core stop 1 seconds action timer handler.
     */
    class ArrowLinkDelayHandlerThread extends Thread {
        @Override
        public void run() {
            super.run();
        }

        public void handleMessage(int msgId) {
            switch (msgId) {
                case ARROW_TTYPE_READY:
                    break;
                case ARROW_TTYPE_SEND:
                    /*Send package again, since there is no Link ACK message*/
                    GenDbg.d(GenDbg.TLINK, "ARROW_TTYPE_SEND");
                    arrowLinkReSend();
                    break;
                case ARROW_TTYPE_DELAY:
                    arrowLinkSyncRetry();
                    GenDbg.d(GenDbg.TLINK, "ARROW_TTYPE_DELAY");
                    break;
                case ARROW_TTYPE_REPROCESS:
                    GenDbg.d(GenDbg.TLINK, "ARROW_TTYPE_REPROCESS");
                    if (mDataList != null && mDataList.size() > 0) {
                        allinkL1ProcessData(mDataList.get(0));
                        mDataList.remove(0);
                    }
                    break;
                default:
                    break;
            }
        }
    }
    ArrowLinkDelayHandlerThread arrowLinkDelayHandlerThread = new ArrowLinkDelayHandlerThread();

    /**
     * Initial interface function.
     *
     * @param mFunc interface function, it is custom interface function defined by arrowLinkFunc.
     * @return
     */
    public byte alInit(arrowLinkFunc mFunc) {
        mArrowLinkFunc = mFunc;
        alReInit();
        return 0;
    }

    /**
     * Initial parameters.
     */
    private void alReInit() {
        mSeqId = 0;
        mDataOut = null;
        mDataOffect = 0;
        mDataInCmd = 0;
        mDataInOffect = 0;
        mDataInLength = 0;
        mLinkRetry = 0;
        mDataPakEnd = false;
        mBuffHeader = 0;
        mBuffTail = 0;
        mTypeState = ARROW_TTYPE_READY;
        mDelayTimer = new Timer();
        mPayload = null;
        arrowLinkDelayCancel();
        GenDbg.d(GenDbg.TLINK, "alReInit");
        for (int i = 0; i < ARROW_MAX_BUFF; i++)
            mBuffSequence[i] = new ArrayList<byte[]>();
    }

    /**
     * Generate 1 second delay.
     *
     * @return Return 0.
     */
    public byte alDeinit() {
        arrowLinkDelayCancel();
        mSeqId = 0;
        mArrowLinkFunc = null;
        return 0;
    }

    /**
     * Package.
     *
     * @param gid     Command group.
     * @param cid     Command.
     * @param payload Data.
     * @return if mArrowLinkFunc == null ,return 1; else return 0;
     */
    @SuppressWarnings("unchecked")
    public byte allinkL1SendData(byte gid, byte cid, byte[] payload) {
        if (mArrowLinkFunc == null) {
            GenDbg.e(GenDbg.TLINK, "Send OverFunction null");
            return 1;
        }

        if (payload != null) {
            GenDbg.d(GenDbg.TLINK, GenUtil.bytesToHexString(payload));
            arrowLinkDebug("WeSent:" + GenUtil.bytesToHexString(payload));
        } else {
            arrowLinkDebug("WeSent: null payload");
        }

        byte[] l2packdata = linkL2PackData(gid, cid, payload);
        byte[] l1packdata = linkL1PackData(l2packdata);
        mBuffSequence[mBuffTail].clear();
        for(int i= 0; i < l1packdata.length; ++i) {
            mBuffSequence[mBuffTail].add(l1packdata[i]);
        }
        mBuffTail = (mBuffTail + 1) >= ARROW_MAX_BUFF ? 0 : (mBuffTail + 1);

        if (mTypeState == ARROW_TTYPE_READY) {
            arrowLinkAsyncSend();
        }
        return 0;
    }

    /**
     * Data processing.
     *
     * @param payload Data.
     * @return 1 - interface is null or invalid data,
     * 0 - data processing successfully
     */
    public byte allinkL1ProcessData(byte[] payload) {
        final byte[] data = payload;
        int paylen = 0;
        if (payload != null)
            paylen = payload.length;

        if (mArrowLinkFunc == null) {
            GenDbg.e(GenDbg.TLINK, "Process OverFunction null");
            return 1;
        }

        arrowLinkDebug("WeRev:" + GenUtil.bytesToHexString(payload));

        while (paylen != 0) {
            if (mDataInLength == 0) {
                if ((payload.length >= L1_HEADER_SIZE) &&
                        (payload[L1_HEADER_MAGIC_POS] == L1_HEADER_MAGIC) && ((payload[L1_HEADER_PROTOCOL_VERSION_POS] & 0x0F) == L1_HEADER_VERSION)) {
                    mDataInVer = payload[L1_HEADER_PROTOCOL_VERSION_POS];
                    mDataInLength = U16_GET(payload[L1_PAYLOAD_LENGTH_HIGH_BYTE_POS], payload[L1_PAYLOAD_LENGTH_LOW_BYTE_POS]);
                    mDataInOffect = payload.length - L1_HEADER_SIZE;
                    mDataInOffect = mDataInOffect > mDataInLength ? mDataInLength : mDataInOffect;
                    mDataIn = new byte[mDataInLength];
                    short seq = (short) U16_GET(payload[L1_HEADER_SEQ_ID_HIGH_BYTE_POS], payload[L1_HEADER_SEQ_ID_LOW_BYTE_POS]);
                    if ((mDataInSeq + 1) != seq) {
                        GenDbg.e(GenDbg.TLINK, "New msg seq err,l:" + (mDataInSeq + 1) + " r:" + seq);
                    }
                    mDataInSeq = seq;
                    mDataInCRC = U16_GET(payload[L1_HEADER_CRC16_HIGH_BYTE_POS], payload[L1_HEADER_CRC16_LOW_BYTE_POS]);
                    System.arraycopy(payload, L1_HEADER_SIZE, mDataIn, 0, mDataInOffect);
                    GenDbg.d(GenDbg.TLINK, "New msg:" + mDataInCmd + " length," + mDataInLength);
                    arrowLinkDebug("New msg:" + mDataInCmd + " length," + mDataInLength);
                    paylen -= (mDataInOffect + L1_HEADER_SIZE);
                } else {
                    GenDbg.e(GenDbg.TLINK, "Error Invaild Msg");
                    mDataList.add(data);
                    return 1;
                }
            } else {
                if (mDataIn != null) {
                    int offect = mDataInLength - mDataInOffect;
                    offect = payload.length > offect ? offect : payload.length;
                    System.arraycopy(payload, 0, mDataIn, mDataInOffect, offect);
                    mDataInOffect += offect;
                    paylen -= offect;
                    GenDbg.d(GenDbg.TLINK, "Msg Patch:" + mDataInOffect + " length," + mDataInLength);
                } else {
                    arrowLinkDebug("Error Rev Null Msg");
                    return 1;
                }
            }

            payload = Arrays.copyOfRange(payload, payload.length - paylen, payload.length);
            if (payload != null)
                paylen = payload.length;
            else
                paylen = 0;
            if (mDataInOffect >= mDataInLength) {
                if ((mDataInVer & L1_HEADER_ACK) != 0) {
                    arrowLinkDebug("LINK_ACK");
                    arrowLinkAck();
                    //linkL1Ack(mDataInSeq);
                } else {
                    int localCRC = ArrowLinkUtil.alcrc16(mDataIn.length, mDataIn);
                    if (mDataInCRC == localCRC) {
                        linkL1Ack(mDataInSeq);
                        linkL2DataResolve(mDataIn);
                    } else {
                        arrowLinkDebug("CRC Error, link:" + Integer.toHexString(mDataInCRC) + " local:" + Integer.toHexString(localCRC));
                    }
                }
                mDataInCRC = 0;
                mDataInVer = 0;
                mDataInLength = 0;
                mDataInOffect = 0;
                mDataIn = null;
            }
        }
        return 0;
    }

    /**
     * Full package send success, wait for Link ACK message.
     */
    public void alAck() {
        mRetry = 0;
        arrowLinkDelayCancel();
        if (mDataPakEnd) {
            arrowLinkDebug("Wait Link Ack");
            arrowLinkDelayTask(ARROW_TTYPE_SEND);
        } else {
            arrowLinkDebug("Data Send Ack");
            arrowLinkAsyncSend();
        }
    }

    /**
     * Get data high 8 bits.
     *
     * @param data 16 bits data.
     * @return The high 8 bits data of input data.
     */
    private byte DATAHIGH(int data) {
        return (byte) ((data >> 8) & 0xFF);
    }

    /**
     * Get data low 8 bits.
     *
     * @param data 16 bits data.
     * @return The low 8 bits data of input data.
     */
    private byte DATALOW(int data) {
        return (byte) (data & 0xFF);
    }

    /**
     * Get 16 bits data from two 8 bits data.
     *
     * @param high The high 8 bits data.
     * @param low  The low 8 bits data.
     * @return 16 bits data.
     */
    private int U16_GET(byte high, byte low) {
        int dataU16 = ((high << 8) & 0xFF00) | (low & 0xFF);

        return (dataU16 & 0xFFFF);
    }

    /**
     * Re-send data.
     */
    private void arrowLinkReSend() {
        mDataOffect = 0;

        if (mLinkRetry >= ARROW_MX_RETRY) {
            arrowLinkDelayCancel();
            if (mArrowLinkFunc != null) {
                mArrowLinkFunc.alerr();
                arrowLinkDebug("Error Resend, next message");
                arrowLinkAck();
            }
            return;
        } else {
            mLinkRetry++;
            arrowLinkAsyncSend();
        }
    }

    /**
     * Asynchronous send data.
     */
    private void arrowLinkAsyncSend() {
        if ((mDataOut != null) && (mDataOffect < mDataOut.length)) {
            arrowLinkSyncSend();
            return;
        }
        if (mBuffHeader == mBuffTail) {
            return;
        }
        mDataOut = new byte[mBuffSequence[mBuffHeader].size()];
        System.arraycopy(mDataOut, 0, mBuffSequence[mBuffHeader], 0, mDataOut.length);
        mBuffHeader = (mBuffHeader + 1) >= ARROW_MAX_BUFF ? 0 : (mBuffHeader + 1);

        mDataOffect = 0;
        GenDbg.d(GenDbg.TLINK, GenUtil.bytesToHexString(mDataOut));

        arrowLinkSyncSend();
    }

    /**
     * Synchronous send data.
     */
    private void arrowLinkSyncSend() {
        int length = mDataOut.length - mDataOffect;
        length = length > ARROW_MAX_SEND_DATA ? ARROW_MAX_SEND_DATA : length;

        mPayload = new byte[length];
        System.arraycopy(mDataOut, mDataOffect, mPayload, 0, length);

        mDataOffect += length;

        if (mDataOffect >= mDataOut.length)
            mDataPakEnd = true;
        mArrowLinkFunc.alsend(mPayload);
        arrowLinkDelayTask(ARROW_TTYPE_DELAY);
    }

    private void arrowLinkSyncRetry() {
        if (mRetry >= ARROW_MX_RETRY) {
            arrowLinkDelayCancel();
            mArrowLinkFunc.alerr();
            arrowLinkDebug("Error Max Retry, next message");
            arrowLinkAck();
        } else {
            mRetry++;
            if (mArrowLinkFunc != null) {
                if (mPayload != null) {
                    mArrowLinkFunc.alsend(mPayload);
                    arrowLinkDebug("arrowLinkSyncRetry");
                    GenDbg.d(GenDbg.TLINK, "arrowLinkSyncRetry");
                }
            } else
                GenDbg.e(GenDbg.TLINK, "Func null!!!");
        }
    }

    /**
     * Generate ACK.
     */
    private void arrowLinkAck() {
        mRetry = 0;
        mLinkRetry = 0;
        mDataPakEnd = false;
        mDataOut = null;
        mPayload = null;
        arrowLinkDelayCancel();
        arrowLinkAsyncSend();
//        arrowLinkDelayHandler.obtainMessage(ARROW_TTYPE_REPROCESS).sendToTarget();
        arrowLinkDelayHandlerThread.handleMessage(ARROW_TTYPE_REPROCESS);
    }

    /**
     * Log out debug information.
     *
     * @param str The content to show.
     */
    private void arrowLinkDebug(String str) {
        if (mArrowLinkFunc != null)
            mArrowLinkFunc.almsg(str);
    }

    /**
     * System Core start 1 seconds timer.
     *
     * @param type Current state, it is an Integer.
     */
    private void arrowLinkDelayTask(final int type) {
        int delay = 0, period = 0;

        if (!mDelayTimerOn)
            mDelayTimerOn = true;
        else
            return;

        switch (type) {
            case ARROW_TTYPE_READY:
                return;
            case ARROW_TTYPE_SEND:
                delay = 2000;
                period = 2000;
                break;
            case ARROW_TTYPE_DELAY:
                delay = 2000;
                period = 200;
                break;
        }
        mTypeState = type;
        mDelayTimer = new Timer();
        mDelayTimer.schedule(new TimerTask() {
            public void run() {
//                Message message = new Message();
//                message.what = type;
//                arrowLinkDelayHandler.sendMessage(message);
                arrowLinkDelayHandlerThread.handleMessage(type);
            }
        }, delay, period);

        GenDbg.d(GenDbg.TLINK, "Timer create");
    }

    /**
     * System Core stop 1 seconds timer.
     */
    private void arrowLinkDelayCancel() {
        mTypeState = ARROW_TTYPE_READY;
        if (mDelayTimerOn) {
            mDelayTimerOn = false;
            mDelayTimer.cancel();
            GenDbg.d(GenDbg.TLINK, "Timer cancel");
        }
    }

    /*************************************************************
     * L1 send content implementation
     * @param payload
     *        Data.
     **************************************************************/

    private byte[] linkL1PackData(byte[] payload) {
        byte[] packdata = new byte[payload.length + L1_HEADER_SIZE];
        /*fill header*/
        packdata[L1_HEADER_MAGIC_POS] = L1_HEADER_MAGIC;           /* Magic */
        packdata[L1_HEADER_PROTOCOL_VERSION_POS] = L1_HEADER_VERSION;       /* protocol version */
        packdata[L1_PAYLOAD_LENGTH_HIGH_BYTE_POS] = DATAHIGH(payload.length);    /* length high byte */
        packdata[L1_PAYLOAD_LENGTH_LOW_BYTE_POS] = DATALOW(payload.length);      /* length low byte */
        /*cal crc*/
        int crc16_ret = ArrowLinkUtil.alcrc16(payload.length, payload);
        packdata[L1_HEADER_CRC16_HIGH_BYTE_POS] = DATAHIGH(crc16_ret);
        packdata[L1_HEADER_CRC16_LOW_BYTE_POS] = DATALOW(crc16_ret);

        /*sequence id*/
        packdata[L1_HEADER_SEQ_ID_HIGH_BYTE_POS] = DATAHIGH(mSeqId);
        packdata[L1_HEADER_SEQ_ID_LOW_BYTE_POS] = DATALOW(mSeqId);

        //prepare for send L2 content
        System.arraycopy(payload, 0, packdata, L1_HEADER_SIZE, payload.length);

        mSeqId++;
        return packdata;
    }

    /*PUBLIC data function*/

    /**
     * Generate L1 ACK.
     *
     * @param seq 16 bits data.
     */
    private void linkL1Ack(short seq) {

        byte[] packdata = new byte[L1_HEADER_SIZE];

        /*fill header*/
        packdata[L1_HEADER_MAGIC_POS] = L1_HEADER_MAGIC;           /* Magic */
        packdata[L1_HEADER_PROTOCOL_VERSION_POS] = L1_HEADER_VERSION | L1_HEADER_ACK;       /* protocol version */
        packdata[L1_PAYLOAD_LENGTH_HIGH_BYTE_POS] = 0;    /* length high byte */
        packdata[L1_PAYLOAD_LENGTH_LOW_BYTE_POS] = 0;      /* length low byte */
        /*cal crc*/
        int crc16_ret = 0;
        packdata[L1_HEADER_CRC16_HIGH_BYTE_POS] = DATAHIGH(crc16_ret);
        packdata[L1_HEADER_CRC16_LOW_BYTE_POS] = DATALOW(crc16_ret);

        //sequence id
        packdata[L1_HEADER_SEQ_ID_HIGH_BYTE_POS] = DATAHIGH(seq);
        packdata[L1_HEADER_SEQ_ID_LOW_BYTE_POS] = DATALOW(seq);

        arrowLinkDebug("L1 ACK");
        /*Directly send ACK*/
        mArrowLinkFunc.alsend(packdata);
    }

    /**
     * L2 send content implementation
     *
     * @param gid     command group
     * @param cmdid   command
     * @param payload data
     * @return data package
     */
    private byte[] linkL2PackData(byte gid, byte cmdid, byte[] payload) {
        int length = 0;
        if (payload != null)
            length = payload.length;
        byte[] packdata = new byte[L2_HEADER_SIZE + length];
        packdata[L2_GRP_HEADER_POS] = gid;
        packdata[L2_VER_HEADER_POS] = L2_HEADER_VERSION;
        packdata[L2_CMD_HEADER_POS] = cmdid;
        packdata[L2_CMD_LEN_HIGH_POS] = DATAHIGH(length);
        packdata[L2_CMD_LEN_LOW_POS] = DATALOW(length);

        if (length != 0)
            System.arraycopy(payload, 0, packdata, L2_HEADER_SIZE, length);
        return packdata;
    }

    /**
     * L2 data resolve
     *
     * @param payload data
     */
    private void linkL2DataResolve(byte[] payload) {
        GenDbg.d(GenDbg.TLINK, "linkL2DataResolve");

        if ((payload.length >= L2_HEADER_SIZE) && (payload[L2_VER_HEADER_POS] == L2_HEADER_VERSION)) {
            byte gid = payload[L2_GRP_HEADER_POS];
            byte cid = payload[L2_CMD_HEADER_POS];
            byte[] payNew = new byte[payload.length - L2_HEADER_SIZE];
            System.arraycopy(payload, L2_HEADER_SIZE, payNew, 0, payNew.length);
            mArrowLinkFunc.alproc(gid, cid, payNew);
        } else {
            GenDbg.d(GenDbg.TLINK, "L2 invaild package");
        }
    }

    /**
     * Override interface function.
     */
    public interface arrowLinkFunc {
        byte alsend(byte[] payload);

        byte alproc(byte gid, byte cid, byte[] payload);

        void alerr();

        void almsg(String msg);
    }
}
