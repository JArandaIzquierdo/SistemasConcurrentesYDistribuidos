// Creacion de varias hebras que impriman por pantalla cualquier cosa

import java.lang.Thread;
import java.lang.Runnable;
import java.lang.InterruptedException;

public class VariasHebras{

    public static void main (String []args){
        Hebra h = new Hebra(5);
        h.thr.start();

        try{
            h.thr.join();
        }catch (InterruptedException ex){

        }
    }
}

class Hebra implements Runnable {

    private int n;
    Thread thr;
    Hebra[]hebras;

    public void run(){
        System.out.println("Prueba hebra ");
    }

    // Creacion de la hebra
    Hebra(int n){
        this.n = n;
        thr = new Thread(this);
    }
}
