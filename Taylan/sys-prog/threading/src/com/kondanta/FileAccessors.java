package com.kondanta;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;

class FileAccessors{
    private HashMap<String, Integer> occurrenceTable =
            new HashMap<>();

    private void initTable(String key, Integer counter) {
        occurrenceTable.putIfAbsent(key, counter);
    }

    void replaceValue(String key, Integer oldVal, Integer newVal){
        occurrenceTable.replace(key, oldVal, newVal);
    }

    void printer(String word){
        System.out.printf("The word %s occured %d", word, occurrenceTable.get(word));
    }

    void read(String fileName) {
        Integer ctr = 0;
        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {
            StringBuilder sb = new StringBuilder();
            String line = br.readLine();

            while (line != null) {
                sb.append(line);
                sb.append(System.lineSeparator());
                line = br.readLine();
                this.initTable(line, ctr);
                if(occurrenceTable.containsKey(line)) {
                    replaceValue(line, ctr, ctr++);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
