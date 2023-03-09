package aula02;

import java.util.Scanner;

public class Ex3 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Quantidade de água (em kilogramas): ");
        double m = sc.nextDouble();
        System.out.print("Temperatura inicial: ");
        double ti = sc.nextDouble();
        System.out.print("Temperatura final: ");
        double tf = sc.nextDouble();
        double q = m * (tf - ti) * 4184;
        System.out.println("A energia necessária para aquecer a água são " + q + "joules.");
        sc.close();
    }    
}
