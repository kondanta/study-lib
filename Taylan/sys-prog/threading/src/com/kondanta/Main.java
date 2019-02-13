package com.kondanta;

import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        // Decelerations
        String searchedWord;
        Scanner scanner;
        ArrayList<Thread> threadList = new ArrayList<>();
        FileAccessors fileAccessors = new FileAccessors();

        // Just a scanner thing . . . .
        scanner = new Scanner(System.in);
        System.out.println("Enter word: ");
        searchedWord = scanner.nextLine();
        scanner.close();

        // Dispatching a thread for each CLI arg
        for (int i = 0; i < args.length; ++i) {
            Thread tmp = new Thread(new ThreadSpawner(args[i], fileAccessors), "t" + i);
            threadList.add(tmp);
            tmp.start();
        }

        // Dispatched threads are join
        for (Thread threads : threadList) {
            try {
                threads.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // prints result of the occurrence
        fileAccessors.printOccurrenceNumber(searchedWord);
    }
}

