package com.kondanta;

import java.util.ArrayList;
import java.util.Scanner;

class Driver {
    private ArrayList<Thread> threadList = new ArrayList<>();
    private FileAccessors fileAccessors = new FileAccessors(Collector.getOccurrenceTable());


    void run(String[] args) {

        // Just a scanner thing . . . .
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter word: ");
        String searchedWord = scanner.nextLine();
        scanner.close();

        // Dispatching a thread for each CLI arg
        for (int i = 0; i < args.length; ++i) {
            Thread tmp = new Thread(
                    new ThreadSpawner(args[i], this.fileAccessors),
                    "t" + i);
            this.threadList.add(tmp);
            tmp.start();
        }

        // Dispatched threads are join
        for (Thread threads : this.threadList) {
            try {
                threads.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // prints result of the occurrence
        this.fileAccessors.printOccurrenceNumber(searchedWord);
    }
}
