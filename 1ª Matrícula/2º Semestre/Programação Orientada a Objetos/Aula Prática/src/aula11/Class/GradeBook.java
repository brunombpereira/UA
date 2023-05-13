package aula11.Class;

import java.io.FileReader;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;
import java.util.Objects;
import java.util.Scanner;

public class GradeBook {
    private final List<Student> students = new LinkedList<>();

    public void load(String file) throws IOException {
        Scanner sc = new Scanner(new FileReader("src/aula11/" + file));

        while (sc.hasNext()) {
            String[] data = sc.nextLine().split("\\|");

            String name = data[0];
            List<Double> grades = new LinkedList<>();

            for (int i = 1; i < data.length; i++) {
                grades.add(Double.parseDouble(data[i]));
            }

            students.add(new Student(name, grades));
        }


    }

    public  void addStudent(Student student) {
        students.add(student);
    }

    public void removeStudent(String name) {
        students.remove(getStudent(name));
    }

    public Student getStudent(String name) {
        return students.stream().filter(student -> student.getName().equals(name)).findFirst().orElse(null);
    }

    public double calculateAverageGrade(String name) {
        Student student = getStudent(name);

        if (Objects.isNull(student)) {
            return 0;
        }

        return student.getGrades().stream().mapToDouble(Double::doubleValue).average().orElse(0);
    }

    public void printAllStudents() {
        students.forEach(student -> System.out.println(student.getName() + " " + student.getGrades()));
    }
}
