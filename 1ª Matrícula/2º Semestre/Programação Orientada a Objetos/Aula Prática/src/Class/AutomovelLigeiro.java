package Class;

import java.util.Objects;

import static Utils.Validate.*;

public class AutomovelLigeiro extends VeiculoMotorizado{
    public int serialNumber, luggageCapacity;

    public AutomovelLigeiro(String plate, String brand, String model, int potency, int km, String companyName, int serialNumber, int luggageCapacity) {
        super(plate, brand, model, potency, km, companyName);

        if (validateSerialNumber(serialNumber) && validateLuggageCapacity(luggageCapacity)) {
            this.serialNumber = serialNumber;
            this.luggageCapacity = luggageCapacity;
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

    public int getLuggageCapacity() {
        return luggageCapacity;
    }

    public void setLuggageCapacity(int luggageCapacity) {
        this.luggageCapacity = luggageCapacity;
    }

    public String toString() {
        return "Matrícula: " + plate + "\nMarca: " + brand + "\nModelo: " + model + "\nPotência (cv): " + potency + "\nKm: " + km + "\nEmpresa de aluguer de veículos onde se encontra o veículo: " + companyName + "\nNúmero do quadro: " + serialNumber + "\nCapacidade da Bagageira: " + luggageCapacity;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        AutomovelLigeiro that = (AutomovelLigeiro) o;
        return serialNumber == that.serialNumber && luggageCapacity == that.luggageCapacity;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), serialNumber, luggageCapacity);
    }
}
