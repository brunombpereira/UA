package Class;

import java.util.Objects;

import static Utils.Validate.*;

public class Taxi extends AutomovelLigeiro{
    private int licenseNumber;

    public Taxi(String plate, String brand, String model, int potency, int km, String companyName, int serialNumber, int luggageCapacity, int licenseNumber) {
        super(plate, brand, model, potency, km, companyName, serialNumber, luggageCapacity);

        if (validateLicenceNumber(licenseNumber)) {
            this.licenseNumber = licenseNumber;
        }
    }


    public String toString() {
        return "Matrícula: " + plate + "\nMarca: " + brand + "\nModelo: " + model + "\nPotência (cv): " + potency + "\nNúmero do quadro: " + serialNumber + "\nCapacidade da Bagageira: " + luggageCapacity + "\nNúmero da licença: " + licenseNumber;
    }

    public int getLicenseNumber() {
        return licenseNumber;
    }

    public void setLicenseNumber(int licenseNumber) {
        this.licenseNumber = licenseNumber;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        Taxi taxi = (Taxi) o;
        return licenseNumber == taxi.licenseNumber;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), licenseNumber);
    }
}
