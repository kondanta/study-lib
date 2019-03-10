package com.kondanta;


public class ThreadSpawner implements Runnable {
    private String fileName;
    private FileAccessors fileAccessors;


    /**
     * @param file          File name that is going to be parsed
     * @param fileAccessors Dependency injection for accessing
     *                      "read" function of the FileAccessors
     */
    ThreadSpawner(String file, FileAccessors fileAccessors) {
        this.fileName = file;
        this.fileAccessors = fileAccessors;
    }

    @Override
    public void run() {
        fileAccessors.read(this.fileName);
    }
}
