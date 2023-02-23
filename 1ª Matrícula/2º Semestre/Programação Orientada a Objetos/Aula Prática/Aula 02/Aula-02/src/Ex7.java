import java.util.Scanner;

public class Ex7 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("x1: ");
        int x1 = sc.nextInt();
        System.out.print("y1: ");
        int y1 = sc.nextInt();
        System.out.print("x2: ");
        int x2 = sc.nextInt();
        System.out.print("y2: ");
        int y2 = sc.nextInt();

        double dp = (float)(Math.sqrt(Math.pow((x2 - x1), 2) + Math.pow((y2 - y1), 2)));

        System.out.println("A distância entre os pontos é de " + dp + "uc.");

        sc.close();
    }
}
