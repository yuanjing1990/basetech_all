package RTTI;

import java.lang.reflect.*;
import java.io.*;

public class ShowMethodClean {
    static final String usage = "usage: \n" + "ShowMethodClean qualified.class.name\n"
            + "To show all methods in class or:\n" + "ShowMethodClean qualif.class.name 'word'\n"
            + "To search form methods involving 'word'";

    public static void main(String[] argv) {
        if (argv.length < 1) {
            System.out.println(usage);
            System.exit(0);
        }
        try {
            Class<?> c = Class.forName(argv[0]);
            Method[] m = c.getMethods();
            Constructor<?>[] ctor = c.getConstructors();
            String[] n = new String[m.length + ctor.length];
            for (int i = 0; i < m.length; ++i) {
                String s = m[i].toString();
                n[i] = StripQualifiers.strip(s);
            }
            for (int i = 0; i < ctor.length; i++) {
                String s = ctor[i].toString();
                n[i + m.length] = StripQualifiers.strip(s);
            }
            if (argv.length == 1)
                for (int i = 0; i < n.length; ++i)
                    System.out.println(n[i]);
            else
                for (int i = 0; i < n.length; ++i)
                    if (n[i].indexOf(argv[1]) != -1)
                        System.out.println(n[i]);
        } catch (ClassNotFoundException e) {
            System.out.println("No such class:" + e);
        }
    }
}

class StripQualifiers {
    private StreamTokenizer st;

    public StripQualifiers(String qualified) {
        st = new StreamTokenizer(new StringReader(qualified));
        st.ordinaryChar(' ');
    }

    public String getNext() {
        String s = null;
        try {
            if (st.nextToken() != StreamTokenizer.TT_EOF) {
                switch (st.ttype) {
                    case StreamTokenizer.TT_EOL:
                        s = null;
                        break;
                    case StreamTokenizer.TT_NUMBER:
                        s = Double.toString(st.nval);
                        break;
                    case StreamTokenizer.TT_WORD:
                        s = new String(st.sval);
                        break;
                    default:
                        s = String.valueOf((char) st.ttype);
                }
            }
        } catch (IOException e) {
            System.out.println(e);
        }
        return s;
    }

    public static String strip(String qualified) {
        StripQualifiers sq = new StripQualifiers(qualified);
        String s = "", si;
        while ((si = sq.getNext()) != null) {
            int lastDot = si.lastIndexOf('.');
            if (lastDot != -1)
                si = si.substring(lastDot + 1);
            s += si;
        }
        return s;
    }
}