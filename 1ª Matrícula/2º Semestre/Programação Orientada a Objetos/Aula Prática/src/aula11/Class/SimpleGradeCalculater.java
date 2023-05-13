package aula11.Class;

import aula11.Interfaces.IGradeCalculator;

import java.util.List;

public class SimpleGradeCalculater implements IGradeCalculator {
        public double calculate(List<Double> grades) {
            return grades.stream().mapToDouble(Double::doubleValue).average().orElse(0);
        }
}
