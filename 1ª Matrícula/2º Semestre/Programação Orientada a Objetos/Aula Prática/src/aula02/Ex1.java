package aula02;

import java.util.Scanner;

public class Ex1 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Distância em Kilómetros: ");
        double distancia_kilometros = sc.nextDouble();
        System.out.println(distancia_kilometros + "km equivale a " + distancia_kilometros/1.609 + " milhas.");
        sc.close();
    }
}