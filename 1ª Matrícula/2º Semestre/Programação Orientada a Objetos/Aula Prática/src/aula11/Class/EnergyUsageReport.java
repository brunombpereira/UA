package aula11.Class;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class EnergyUsageReport {
    private final List<Customer> customers = new LinkedList<>();
    public void load(String filename) throws IOException {
        Scanner sc = new Scanner(new FileReader("src/aula11/" + filename));

        while (sc.hasNext()) {
            String[] data = sc.nextLine().split("\\|");

            int customerId = Integer.parseInt(data[0]);
            List<Double> meterReadings = new LinkedList<>();

            for (int i = 1; i < data.length; i++) {
                meterReadings.add(Double.parseDouble(data[i]));
            }

            customers.add(new Customer(customerId, meterReadings));
        }
    }

    public void addCustomer(Customer customer) {
        customers.add(customer);
    }

    public void removeCustomer(int customerId) {
        customers.remove(getCustomer(customerId));
    }

    public Customer getCustomer(int customerId) {
        return customers.stream().filter(customer -> customer.getCustomerId() == customerId).findFirst().orElse(null);
    }

    public double calculateTotalUsage(int customerId) {
        Customer customer = getCustomer(customerId);

        if (customer == null) {
            return 0;
        }

        return customer.getMeterReadings().stream().mapToDouble(Double::doubleValue).sum();
    }

    public void generateReport(String filename) throws IOException {
        for (Customer customer : customers) {
            Files.writeString(Path.of("src/aula11/" + filename), customer.getCustomerId() + " | " + calculateTotalUsage(customer.getCustomerId()) + "\n", (new File("src/aula11/" + filename)).exists() ? java.nio.file.StandardOpenOption.APPEND : java.nio.file.StandardOpenOption.CREATE);
        }
    }
}
