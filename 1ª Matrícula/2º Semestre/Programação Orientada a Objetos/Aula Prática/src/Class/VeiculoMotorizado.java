package Class;

import Interfaces.KmPercorridos;

import java.util.Objects;

import static Utils.Validate.*;

public abstract class VeiculoMotorizado implements KmPercorridos {
    protected String plate, brand, model, companyName;
    protected int potency, km, lastTrip;

    public VeiculoMotorizado(String plate, String brand, String model, int potency, int km, String companyName) {
        if (validatePlate(plate) && validatePotency(potency)) {
            this.plate = plate;
            this.brand = brand;
            this.model = model;
            this.potency = potency;
            this.km = km;
            this.companyName = companyName;
        }
    }

    public abstract String toString();
    public abstract String getPlate();
    public abstract void setPlate(String plate);
    public abstract String getBrand();
    public abstract void setBrand(String brand);
    public abstract String getModel();
    public abstract void setModel(String model);
    public abstract int getPotency();
    public abstract void setPotency(int potency);
    public abstract String getCompanyName();
    public abstract void setCompanyName(String companyName);

    @Override
    public void trajeto(int quilometros) {
        this.lastTrip = quilometros;
        this.km += quilometros;
    }

    @Override
    public int ultimoTrajeto() {
        return lastTrip;
    }

    @Override
    public int distanciaTotal() {
        return km;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        VeiculoMotorizado that = (VeiculoMotorizado) o;
        return potency == that.potency && km == that.km && lastTrip == that.lastTrip && Objects.equals(plate, that.plate) && Objects.equals(brand, that.brand) && Objects.equals(model, that.model) && Objects.equals(companyName, that.companyName);
    }

    @Override
    public int hashCode() {
        return Objects.hash(plate, brand, model, companyName, potency, km, lastTrip);
    }
}
