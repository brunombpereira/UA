package Class;

import java.util.Objects;

import static Utils.Validate.*;

public class PesadoMercadorias extends AutomovelPesado{
    private int maxLoad;

    public PesadoMercadorias(String plate, String brand, String model, int potency, int km, String companyName, int serialNumber, int weight, int maxLoad) {
        super(plate, brand, model, potency, km, companyName, serialNumber, weight);

        if (validateMaxLoad(maxLoad)) {
            this.maxLoad = maxLoad;
        }
    }


    public String toString() {
        return "Matrícula: " + plate + "\nMarca: " + brand + "\nModelo: " + model + "\nPotência (cv): " + potency + "\nNúmero do quadro: " + serialNumber + "\nPeso: " + weight + "\nCarga máxima: " + maxLoad;
    }

    public int getMaxLoad() {
        return maxLoad;
    }

    public void setMaxLoad(int maxLoad) {
        this.maxLoad = maxLoad;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        PesadoMercadorias that = (PesadoMercadorias) o;
        return maxLoad == that.maxLoad;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), maxLoad);
    }
}
