package Class;

import java.util.Objects;

import static Utils.Validate.*;

public class PesadoPassageiros extends AutomovelPesado{
    private int maxPassengers;

    public PesadoPassageiros(String plate, String brand, String model, int potency, int km, String companyName, int serialNumber, int weight, int maxPassengers) {
        super(plate, brand, model, potency, km, companyName, serialNumber, weight);

        if (validateMaxPassengers(maxPassengers)) {
            this.maxPassengers = maxPassengers;
        }
    }


    public String toString() {
        return "Matrícula: " + plate + "\nMarca: " + brand + "\nModelo: " + model + "\nPotência (cv): " + potency + "\nNúmero do quadro: " + serialNumber + "\nPeso: " + weight + "\nNúmero máximo de passageiros: " + maxPassengers;
    }

    public int getMaxPassengers() {
        return maxPassengers;
    }

    public void setMaxPassengers(int maxPassengers) {
        this.maxPassengers = maxPassengers;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        PesadoPassageiros that = (PesadoPassageiros) o;
        return maxPassengers == that.maxPassengers;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), maxPassengers);
    }
}
