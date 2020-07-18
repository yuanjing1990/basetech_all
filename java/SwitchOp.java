public class SwitchOp {
    public static void main(String args[]) {
        float a = 9;
        float b = 3;
        float result = 0;
        char op = '+';
        switch (op) {
            case '+':
                result = a + b;
                break;
            case '-':
                result = a - b;
                break;
            case '*':
                result = a * b;
                break;
            case '/':
                result = a / b;
                break;
            default:
                result = 0;
        }
        System.out.println("result = " + result);
    }
}