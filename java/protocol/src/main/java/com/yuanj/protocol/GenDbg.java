package com.yuanj.protocol;

import java.io.File;
import java.io.FileOutputStream;
import java.text.SimpleDateFormat;
import java.util.Date;

public class GenDbg {
    private static final String TAG = "RCLINK";
    /**
     * Used to control log out. It is changed by 6 click on version number in ArrowAboutActivity.
     * true - log out, false - no log out
     */
    public static boolean D = true;
    public static boolean isFile = false;
    /**
     * The debug information belongs to BT.
     */
    public static String TBT = "BT";
    /**
     * The debug information belongs to CoreService.
     */
    public static String TCORE = "CO";
    /**
     * The debug information belongs to UI.
     */
    public static String TUI = "UI";
    /**
     * The debug information belongs to Link Protocol.
     */
    public static String TLINK = "LK";
    /**
     * The debug information belongs to message.
     */
    public static String TMSG = "MSG";
    private static String mFilePath = "Log/";
    private static String mFileName = "RCLINK.txt";
    /**
     * Compute log function.The color will be blue.
     * @param TAG
     *         Message tag, it is a String.
     * @param msg
     *         message to be show, it is a String.
     */

    /**
     * Compute log function.The color will be blue.
     *
     * @param tag Message tag, it is a String.
     * @param msg message to be show, it is a String.
     */
    public static void d(String tag, String msg) {
        if (D) {
            if (isFile) {
                String str = "[" + tag + "]" + msg;
                saveAplinkLog(str);
            } else {
                System.out.println(TAG + "[" + tag + "]" + msg);
            }
        } else {
            return;
        }
    }

    /**
     * Output error log.The color will be red.
     *
     * @param tag Message tag, it is a String.
     * @param msg message to be show, it is a String.
     */
    public static void e(String tag, String msg) {
        if (D) {
            if (isFile) {
                String str = "[" + tag + "]" + msg;
                saveAplinkLog(str);
            } else
                System.out.println(TAG + "[" + tag + "]" + msg);
        } else {
            return;
        }
    }

    private static String saveAplinkLog(String data) {
        SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd-HH-mm-ss-SSS");
        String time = format.format(new Date());
        String contents = time + '\t' + data + '\n';
        saveFile(contents);
        return null;
    }

    private static void saveFile(String str) {
        File f = new File(mFilePath);
        if (!f.exists()) {
            f.mkdirs();
        }
        File file = null;
        if (mFilePath != null)
            file = new File(mFilePath + mFileName);
        try {
            if (!file.exists()) {
                file.createNewFile();
            }
            FileOutputStream outStream = new FileOutputStream(file, true);
            outStream.write(str.getBytes());
            outStream.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }


    public static void rmFile() {
        File file = null;
        if (mFilePath != null)
            file = new File(mFilePath + mFileName);

        if (file.exists()) {
            if (file.isFile())
                file.delete();
        }
    }
}
