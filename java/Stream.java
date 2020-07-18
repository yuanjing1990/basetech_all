import java.io.*;

public class Stream {
    public static FilenameFilter filter(final String afn) {
        return new FilenameFilter() {
            String fn = afn;

            public boolean accept(File dir, String n) {
                String f = new File(n).getName();
                return f.indexOf(fn) != -1;
            }
        };
    }

    public static void main(final String args[]) {
        // System.out.println("Hello World!");
        try {
            File path = new File(".");
            String[] list;
            if (args.length == 0)
                list = path.list();
            else
                list = path.list(new FilenameFilter() {
                    public boolean accept(File dir, String n) {
                        String f = new File(n).getName();
                        return f.indexOf(args[0]) != -1;
                    }
                });
            for (int i = 0; i < list.length; i++) {
                File f = new File(list[i]);

                System.out.print(f.getAbsolutePath() + "\t" + f.canRead() + "\t" + f.canWrite() + "\t" + f.getName()
                        + "\t" + f.getParent() + "\t" + f.getPath() + "\t" + f.length() + "\t" + f.lastModified()
                        + "\t");
                if (f.isFile())
                    System.out.println("File");
                else if (f.isDirectory())
                    System.out.println("Directory");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

class DirFilter implements FilenameFilter {
    String afn;

    DirFilter(String afn) {
        this.afn = afn;
    };

    public boolean accept(File dir, String name) {
        String f = new File(name).getName();
        return f.indexOf(afn) != -1;
    }
}
