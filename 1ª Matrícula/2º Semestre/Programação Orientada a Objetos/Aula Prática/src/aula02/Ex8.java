package aula02;

import java.util.Scanner;

public class Ex8 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Cateto A: ");
        double a = sc.nextDouble();
        System.out.print("Cateto B: ");
        double b = sc.nextDouble();

        double h = Math.sqrt(Math.pow(a, 2) + Math.pow(b, 2));
        double ang = Math.toDegrees(Math.acos(a / b));

        if (a >=0 && b >= 0)
            System.out.println("A hipotnusa é igual a " + h + " e o ângulo é de " + ang + "º.");
        else
            System.out.println("Os valores que inseriu não são válidos.");
            
        sc.close();
    }
}
