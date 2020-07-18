public class BreakOp {
    public static void main(String args[]) {
        for (int n = 1; n <= 10; n++) {
            if (n % 2 == 0)
                continue;
            System.out.println("continue n=" + n);
        }

        for (int n = 1; n <= 10; n++) {
            if (n == 6)
                break;
            System.out.println("break n=" + n);
        }
    }
}