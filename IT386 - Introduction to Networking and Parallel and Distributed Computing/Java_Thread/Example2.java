/** Example2.java
 *  Approach 2: Creating threads by implementing interface Runnable.
 * IT 386 - Spring 2023
 *  * TODO:
 *   1. Implement run() method that prints current thread name
 *   2. Have main thread print current thread name
 *   3. Create and start  2 threads
  */
public class Example2 implements Runnable {
  // 1. Implement run() method that prints current thread name
    @Override
    public void run()
    {
        System.out.println("Hey, I am " + Thread.currentThread().getName());
    }
  public static void main(String[] args) throws InterruptedException {
    // 2.  Main thread print current thread name
    System.out.println("Main thread: " + Thread.currentThread().getName());

    // 3. Create and start  2 threads
    Runnable obj = new Example2();
    /* Creating individual threads
    Thread th1 = new Thread(obj);
    th1.start();

    Thread th2 = new Thread(obj);
    th2.start();

    th1.join();
    th2.join();
    */

    Thread[] arr = new Thread[10];

    for (int i = 0; i < arr.length; i++)
    {
        arr[i] = new Thread(obj);
        arr[i].start();
    }

    for (int i = 0; i < arr.length; i++)
    {
        arr[i].join();
    }

  }

}
