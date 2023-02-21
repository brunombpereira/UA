import java.util.Scanner;

public class Ex2 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Temperatura em Cº: ");
        double t = sc.nextDouble();
        System.out.println(t + "Cº corresponde a " + ((1.8 * t) + 32) + "Fº.");
        sc.close();
    }
}
