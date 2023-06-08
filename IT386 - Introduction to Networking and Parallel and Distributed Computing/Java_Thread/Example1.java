/** Example1.java
 *  Approach 1: Creating threads by extending class Thread.
 * IT 386 - Spring 2023
 *  Compile with: javac Example1.java
 *  Run with: java Example1
 *
  */
public class Example1 extends Thread {
  /* 1) Create run() method contains the code that is executed by the thread */
  @Override
  public void run(){
    System.out.println("Hey I am " + Thread.currentThread().getName());
  }


  public static void main(String[] args) {
      /* 2) Create a thread object and start the thread*/
     Thread th1 = new Example1();
     th1.start();
     th1.join();
     /* 3) printing stament to print current thread name (main thread)*/
     System.out.println("From Main: Hey, I am " + Thread.currentThread().getName());
  }
}
