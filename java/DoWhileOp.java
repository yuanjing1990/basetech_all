public class DoWhileOp {
    public static void main(String args[]) {
        int n = 10;
        long result = 1;
        do {
            result *= n--;
            System.out.println("result = " + result);
        } while (n >= 1);
    }
}