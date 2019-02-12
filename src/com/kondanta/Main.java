package com.kondanta;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        String searchedWord;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter word: ");
        searchedWord = scanner.nextLine();
        scanner.close();

        // Run threads
        ThreadSpawner R1 = new ThreadSpawner( "Thread-1", "file1.dat", searchedWord);
        R1.start();

        ThreadSpawner R2 = new ThreadSpawner( "Thread-2", "file2.dat", searchedWord);
        R2.start();

    }
}

