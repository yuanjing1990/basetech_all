
public class RollDie {
    public static void main(String args[]) {
        int frequency[], face;
        frequency = new int[7];
        for (int roll = 1; roll <= 6000; roll++) {
            face = 1 + (int) (Math.random() % 6);
            frequency[face]++;
        }
        for (int i = 1; i <= 6; i++)
            System.out.print("Frequency(" + i + ")\t" + frequency[i] + "\n");
    }
}