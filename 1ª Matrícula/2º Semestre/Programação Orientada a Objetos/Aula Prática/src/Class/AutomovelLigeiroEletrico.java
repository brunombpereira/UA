package Class;

import Interfaces.VeiculoEletrico;

import static Utils.Validate.*;

public class AutomovelLigeiroEletrico extends AutomovelLigeiro implements VeiculoEletrico {
    private int autonomy;

    public AutomovelLigeiroEletrico(String plate, String brand, String model, int potency, int km, String companyName, int serialNumber, int luggageCapacity, int autonomy) {
        super(plate, brand, model, potency, km, companyName, serialNumber, luggageCapacity);

        if (validateAutonomy(autonomy)) {
            this.autonomy = autonomy;
        }
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
    public int getSerialNumber() {
        return super.getSerialNumber();
    }

    @Override
    public void setSerialNumber(int serialNumber) {
        super.setSerialNumber(serialNumber);
    }

    @Override
    public int getLuggageCapacity() {
        return super.getLuggageCapacity();
    }

    @Override
    public void setLuggageCapacity(int luggageCapacity) {
        super.setLuggageCapacity(luggageCapacity);
    }

    @Override
    public String toString() {
        return super.toString();
    }

    @Override
    public boolean equals(Object o) {
        return super.equals(o);
    }

    @Override
    public int hashCode() {
        return super.hashCode();
    }

    @Override
    public int autonomia() {
        return autonomy;
    }

    @Override
    public void carregar(int percentagem) {
        autonomy += (autonomy / (percentagem / 100));
    }

    public int getAutonomy() {
        return autonomy;
    }

    public void setAutonomy(int autonomy) {
        this.autonomy = autonomy;
    }
}
