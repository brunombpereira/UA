import java.util.Scanner;

public class Ex9 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Número: ");
        int n = sc.nextInt();

        for (int i = n; i >= 0; i--) {
            if((i % 10) == 0)
                System.out.println(i);
            else
                System.out.print(i + " ");
        }

        sc.close();
    }
}
