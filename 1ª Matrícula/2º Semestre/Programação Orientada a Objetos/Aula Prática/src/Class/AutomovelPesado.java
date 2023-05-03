package Class;

import java.util.Objects;

import static Utils.Validate.*;

public class AutomovelPesado extends VeiculoMotorizado{
    public int serialNumber, weight;

    public AutomovelPesado(String plate, String brand, String model, int potency, int km, String companyName, int serialNumber, int weight) {
        super(plate, brand, model, potency, km, companyName);

        if (validateSerialNumber(serialNumber) && validateWeight(weight)) {
            this.serialNumber = serialNumber;
            this.weight = weight;
        }
    }


    public String getPlate() {
        return plate;
    }

    public void setPlate(String plate) {
        this.plate = plate;
    }

    public String getBrand() {
        return brand;
    }

    public void setBrand(String brand) {
        this.brand = brand;
    }

    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public int getPotency() {
        return potency;
    }

    public void setPotency(int potency) {
        this.potency = potency;
    }

    @Override
    public String getCompanyName() {
        return companyName;
    }

    @Override
    public void setCompanyName(String companyName) {
        this.companyName = companyName;
    }

    public int getSerialNumber() {
        return serialNumber;
    }

    public void setSerialNumber(int serialNumber) {
        this.serialNumber = serialNumber;
    }

    public int getWeight() {
        return weight;
    }

    public void setWeight(int weight) {
        this.weight = weight;
    }

    public String toString() {
        return "Matrícula: " + plate + "\nMarca: " + brand + "\nModelo: " + model + "\nPotência (cv): " + potency + "\nNúmero do quadro: " + serialNumber + "\nPeso: " + weight;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        AutomovelPesado that = (AutomovelPesado) o;
        return serialNumber == that.serialNumber && weight == that.weight;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), serialNumber, weight);
    }
}
