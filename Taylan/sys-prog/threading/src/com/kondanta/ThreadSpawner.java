package com.kondanta;

public class ThreadSpawner implements Runnable {
    private Thread t;
    private String threadName;
    private String fileName;
    private String searchedWord;

    ThreadSpawner(String name, String file, String searchedWord){
        System.out.printf("Creating: %s", name);
        this.threadName = name;
        this.fileName = file;
        this.searchedWord = searchedWord;
    }

    @Override
    public void run() {
        FileAccessors acc = new FileAccessors();

        System.out.println("Running " +  threadName );
        acc.read(this.fileName);
        // Let the thread sleep for a while.
        System.out.println("Thread " +  threadName + " exiting.");
        acc.printer(this.searchedWord);
    }

    void start() {
        System.out.println("Starting " +  threadName );
        if (t == null) {
            t = new Thread (this, threadName);
            t.start ();
        }
    }
}
