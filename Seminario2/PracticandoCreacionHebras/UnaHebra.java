/* Crear una hebra y que se implima algo por pantalla*/


import java.lang.Thread;
import java.lang.Runnable;
import java.lang.InterruptedException;

public class UnaHebra{

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

    public void run(){
        System.out.println("Prueba hebra 1");
    }

    // Creacion de la hebra
    Hebra(int n){
        this.n = n;
        thr = new Thread(this);
    }
}
