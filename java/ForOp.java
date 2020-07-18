public class ForOp {
    public static void main(String args[]) {
        for (int n = 10, result = 1; n > 0; n--) {
            result *= n;
            if (n == 1)
                System.out.println("10! = " + result);
        }

        System.out.println("i	j	k");
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++) {
                    System.out.println(i + "\t" + j + "\t" + k);
                }
    }
}