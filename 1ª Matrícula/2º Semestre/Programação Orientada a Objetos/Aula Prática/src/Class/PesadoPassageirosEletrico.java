package Class;

import Interfaces.VeiculoEletrico;

import java.util.Objects;

import static Utils.Validate.*;

public class PesadoPassageirosEletrico extends PesadoPassageiros implements VeiculoEletrico {
    private int autonomy;

    public PesadoPassageirosEletrico(String plate, String brand, String model, int potency, int km, String companyName, int serialNumber, int weight, int maxPassengers, int autonomy) {
        super(plate, brand, model, potency, km, companyName, serialNumber, weight, maxPassengers);

        if (validateAutonomy(autonomy)) {
            this.autonomy = autonomy;
        }
    }

    public PesadoPassageirosEletrico(String plate, String brand, String model, int potency, int km, String companyName, int serialNumber, int weight, int maxPassengers) {
        super(plate, brand, model, potency, km, companyName, serialNumber, weight, maxPassengers);
    }

    @Override
    public String toString() {
        return super.toString();
    }

    @Override
    public int getMaxPassengers() {
        return super.getMaxPassengers();
    }

    @Override
    public void setMaxPassengers(int maxPassengers) {
        super.setMaxPassengers(maxPassengers);
    }

    public int getAutonomy() {
        return autonomy;
    }

    public void setAutonomy(int autonomy) {
        this.autonomy = autonomy;
    }

    @Override
    public String getPlate() {
        return super.getPlate();
    }

    @Override
    public void setPlate(String plate) {
        super.setPlate(plate);
    }

    @Override
    public String getBrand() {
        return super.getBrand();
    }

    @Override
    public void setBrand(String brand) {
        super.setBrand(brand);
    }

    @Override
    public String getModel() {
        return super.getModel();
    }

    @Override
    public void setModel(String model) {
        super.setModel(model);
    }

    @Override
    public int getPotency() {
        return super.getPotency();
    }

    @Override
    public void setPotency(int potency) {
        super.setPotency(potency);
    }

    @Override
    public String getCompanyName() {
        return super.getCompanyName();
    }

    @Override
    public void setCompanyName(String companyName) {
        super.setCompanyName(companyName);
    }

    @Override
    public void trajeto(int quilometros) {
        super.trajeto(quilometros);
    }

    @Override
    public int ultimoTrajeto() {
        return super.ultimoTrajeto();
    }

    @Override
    public int distanciaTotal() {
        return super.distanciaTotal();
    }

    @Override
    public int getSerialNumber() {
        return super.getSerialNumber();
    }

    @Override
    public void setSerialNumber(int serialNumber) {
        super.setSerialNumber(serialNumber);
    }

    @Override
    public int getWeight() {
        return super.getWeight();
    }

    @Override
    public void setWeight(int weight) {
        super.setWeight(weight);
    }

    @Override
    public int autonomia() {
        return 0;
    }

    @Override
    public void carregar(int percentagem) {

    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        PesadoPassageirosEletrico that = (PesadoPassageirosEletrico) o;
        return autonomy == that.autonomy;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), autonomy);
    }
}
