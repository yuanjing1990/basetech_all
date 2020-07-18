public class Scope {
    public static void main(String args[]) {
        int x = 25;
        System.out.println("x = " + x);
        {
            int y = 36;
            System.out.println("x = " + x);
            System.out.println("y = " + y);
        }
        System.out.println("x = " + x);
        // System.out.println("y = "+y);
    }
}