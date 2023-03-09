package aula03;

import java.util.Scanner;

public class Ex4 {

    public static double calcularNotaFinal(double notaP, double notaT) {
        if (notaP < 7.0 || notaT < 7.0) {
            return 66.0;
        } else {
            return Math.round((0.4 * notaT + 0.6 * notaP) * 10) / 10.0;
        }
    }

    public static int calcularPauta(double notaFinal) {
        if (notaFinal >= 9.5) {
            return (int) Math.round(notaFinal);
        } else {
            return 66;
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        System.out.print("Número de alunos na turma: ");
        int numAlunos = sc.nextInt();
        
        double[][] notas = new double[numAlunos][2];
        
        for (int i = 0; i < numAlunos; i++) {
            notas[i][0] = Math.round((Math.random() * 20.0) * 100) / 100.0;
            notas[i][1] = Math.round((Math.random() * 20.0) * 10) / 10.0;
        }
        
        System.out.println("NotaT\tNotaP\tPauta");
        for (int i = 0; i < numAlunos; i++) {
            double notaT = notas[i][0];
            double notaP = notas[i][1];
            double notaFinal = calcularNotaFinal(notaP, notaT);
            int pauta = calcularPauta(notaFinal);
            System.out.println(notaT + "\t" + notaP + "\t" + pauta);
        }
        
        sc.close();
    }
}
