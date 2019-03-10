package com.kondanta;

import java.util.HashMap;

/**
 * Collector class is holding maps to be accessed globally by the threads.
 * To be more precise, maps that going to be injected into FileAccessors class.
 * I just want to practice some design patterns so this class happened.
 */
class Collector {
    private static HashMap<String, Integer> occurrenceTable;
    private static HashMap<String, HashMap<String, Integer>> fileHolder;

    private Collector() {
    }

    static HashMap<String, Integer> getOccurrenceTable() {
        if (occurrenceTable == null) {
            occurrenceTable = new HashMap<>();
        }
        return occurrenceTable;
    }

    static HashMap<String, HashMap<String, Integer>> getFileHolder() {
        if (fileHolder == null) {
            fileHolder = new HashMap<>();
        }
        return fileHolder;
    }


}
