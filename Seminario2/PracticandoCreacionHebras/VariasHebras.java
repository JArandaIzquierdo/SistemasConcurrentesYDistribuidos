// Creacion de varias hebras que impriman por pantalla cualquier cosa

import java.lang.Thread;
import java.lang.Runnable;
import java.lang.InterruptedException;

public class VariasHebras{

   public static void main (String []args){
        Hebra[]hebras = new Hebra[50]; // Creamos un vector de hebras

        // Insertamos las hebra sen el vector y las iniciamos con start
        for (int i=0; i< 50; i++){
            hebras[i] = new Hebra(5);
            hebras[i].thr.start();
        }

        // Recorremos el vector y hacemos el join de cada hebra
        for (int i=0; i < 50; i++){
            try{
                hebras[i].thr.join();
            }catch (InterruptedException ex){

            }
        }
    }
}

class Hebra implements Runnable {

    private int n;
    Thread thr;

    public void run(){
        System.out.println(" Prueba de hebra ");
    }
    // Creacion de la hebra
    Hebra(int n){
        this.n = n;
        thr = new Thread(this);
    }
}
