package aula08;

import Class.*;
import Enums.FishState;
import Enums.MeatType;
import Enums.WeekDay;

public class Ex2 {

	public static void main(String[] args) {
		Ementa ementa = new Ementa("Especial Primavera", "Snack da UA");
		Prato[] pratos = new Prato[WeekDay.values().length];
		for (int i = 0; i < pratos.length; i++) {
			pratos[i] = randPrato(i + 1);
			System.out.println("A sair .. " + pratos[i]);

			// Adiciona 2 ingredientes a cada prato
			int ingred = 1;
			do {
				Alimento aux = randAlimento();
				if (pratos[i].getAlimentos() != null && pratos[i].getAlimentos().size() < 2) {
					pratos[i].addIngrediant(aux);
					System.out.println("\tIngrediente " + ingred + " adicionado: " + aux);
					ingred++;
				} else {
					System.out.println("\tERRO: não é possível adicionar Ingrediente " + ingred + ": " + aux);
				}
			} while (ingred < 3);

			ementa.addMeal(pratos[i], WeekDay.values()[i]);
		}
		System.out.println("\nEmenta final\n--------------------");
		System.out.println(ementa);
	}

	public static Alimento randAlimento() {
		Alimento res = switch ((int) (Math.random() * 4)) {
			case 0 -> new Carne(300 , 22.3, 345.3, MeatType.FRANGO);
			case 1 -> new Peixe(200, 31.3, 25.3, FishState.CONGELADO);
			case 2 -> new Legume(150, 21.3, 22.4, "Couve Flor");
			case 3 -> new Cereal(110, 19.3, 32.4, "Milho");
			default -> null;
		};
		return res;
	}

	public static Prato randPrato(int i) {
		return switch ((int) (Math.random() * 3)) {
			case 0 -> new Prato("combinado n." + i);
			case 1 -> new PratoVegetariano("combinado n." + i);
			case 2 -> new PratoDieta("combinado n." + i);
			default -> null;
		};
	}

}