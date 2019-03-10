package com.kondanta;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;

class FileAccessors{

    /**
     * Hash table that is going to store parsed strings and their occurrence
     * numbers
     */
    private HashMap<String, Integer> occurrenceTable;
    /**
     * Mutex for multi threaded approach
     */
    private final Object lock = new Object();

    /**
     * Injecting global hash map into the FileAccessors class. With that
     * we can stop relying on static occurrenceTable to keep track of key
     * value pairs.
     *
     * @param table Global hash map.
     */
    FileAccessors(HashMap<String, Integer> table) {
        this.occurrenceTable = table;
    }



    /**
     * @param key Hash table key value
     *            Populates the hash map with the key if its not already existing
     *            in the hash table.
     */
    private void initTable(String key) {
        occurrenceTable.putIfAbsent(key, 0);
    }

    /**
     * @param key    Hash table key that its value is going to be changed.
     * @param oldVal Old value of the key
     * @param newVal New value of the key
     */
    private void replaceValue(String key, Integer oldVal, Integer newVal) {
        occurrenceTable.replace(key, oldVal, newVal);
    }


    /**
     * @param key Hash table key that is going to be searched
     * @return true if key exists in the table
     */
    private boolean isExists(String key) {
        return occurrenceTable.containsKey(key);
    }

    /**
     * @param key Hash table key
     * @return Value of the key
     */
    private Integer value(String key) {
        if (isExists(key)) {
            return occurrenceTable.get(key);
        }
        return 0;
    }

    /**
     * @param word Searched value on the table
     *             Prints the occurrence number of the word.
     */
    void printOccurrenceNumber(String word) {
        System.out.printf("The word %s occurred %d", word, this.value(word));
    }


    /**
     * @param fileName File that is going to be parsed
     * Takes fileName and populates the hash table with the words that read from the file.
     * If the word exists in table, it'll just increment the occurrence number by one. If it's
     * not exists in the first place, it'll insert the word that is read and initialize with zero
     * and then increase it to one.
     */
    void read(String fileName) {
        try (BufferedReader bufferedReader = new BufferedReader(new FileReader(fileName))) {
            for (String line; (line = bufferedReader.readLine()) != null; ) {
                this.initTable(line);
                if (this.isExists(line)) synchronized (lock) {
                    Integer counter = this.value(line);
                    this.replaceValue(line, counter, ++counter);
                }
            }
        } catch (IOException e){
            e.printStackTrace();
        }
    }
}
