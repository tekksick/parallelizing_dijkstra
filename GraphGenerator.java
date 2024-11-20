import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class GraphGenerator {
    // Define the maximum weight for edges
    private static final int MAX_WEIGHT = 15;
    // Define the weight for non-connected edges
    private static final int NO_CONNECTION = 9999999;

    // Method to generate a random graph with the given number of vertices
    public static int[][] generateGraph(int vertices) {
        int[][] graph = new int[vertices][vertices];
        Random rand = new Random();

        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (i == j) {
                    graph[i][j] = 0;
                } else {
                    graph[i][j] = rand.nextBoolean() ? NO_CONNECTION : rand.nextInt(MAX_WEIGHT) + 1;
                }
            }
        }
        return graph;
    }

    // Method to save the graph to a file
    public static void saveGraphToFile(int[][] graph, String filename) throws IOException {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filename))) {
            for (int[] row : graph) {
                for (int weight : row) {
                    writer.write(weight + " ");
                }
                writer.newLine();
            }
        }
    }

    public static void main(String[] args) {
        // Define the sizes of graphs to generate
        int[] sizes = {8, 64, 256, 512, 1024, 2048};

        // Generate and save graphs for each size
        for (int size : sizes) {
            System.out.println("Generating graph with " + size + " vertices...");
            int[][] graph = generateGraph(size);
            String filename = "input" + size + ".txt";
            try {
                saveGraphToFile(graph, filename);
                System.out.println("Graph saved to " + filename);
            } catch (IOException e) {
                System.err.println("Error saving graph to file: " + e.getMessage());
            }
        }
    }
}

