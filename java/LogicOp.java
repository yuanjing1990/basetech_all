public class LogicOp {
    public static void main(String args[]) {
        int a = 9;
        int b = 6;
        int c = 6;
        boolean d, e, f, g;
        d = !(a > b);
        e = (a > b) && (a < b);
        f = (b == c) || (a < b);
        g = (b == c) && (a < b);
        System.out.println("d = " + d);
        System.out.println("e = " + e);
        System.out.println("f = " + f);
        System.out.println("g = " + g);
    }
}