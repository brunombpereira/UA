package aula06;

import Class.Date;
import Class.Aluno;
import Class.Professor;
import Class.Bolseiro;

public class Ex1 {
    public static void main(String[] args) {
        Aluno al = new Aluno ("Andreia Melo", 98556789, new Date(1990, 7, 18), new Date(2018, 9, 1));
        Professor p1 = new Professor("Andreia Melo", 98556789, new Date(1990, 7, 18), "Auxiliar", "DETI");
        Bolseiro bls = new Bolseiro ("Igor Santos", 89765439, new Date(1985, 5, 11), new Date(2018, 5, 20), p1, 900);
        bls.setScholarship(1050);

        System.out.println(al + "\n");
        System.out.println(bls);
    }
}