package aula02;

import java.util.Scanner;

public class Ex5 {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Velocidade média do primeiro trajeto: ");
        double v1 = sc.nextDouble();
        System.out.print("Distância percorrida no primeiro trajeto: ");
        double d1 = sc.nextDouble();
        System.out.print("Velocidade média do segundo trajeto: ");
        double v2 = sc.nextDouble();
        System.out.print("Distância percorrida no segundo trajeto: ");
        double d2 = sc.nextDouble();
        
        double vmf = (d2 - d1) / (v2 - v1);

        if (v1 >= 0 && d1 >= 0 && v2 >= 0 && d2 >= 0)
            System.out.println("A velocidade média final é de " + vmf + "kmH.");
        else
            System.out.println("Os valores que inseriu não são válidos.");

        sc.close();
    }
}
